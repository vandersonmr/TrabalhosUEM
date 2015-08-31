#!/usr/bin/python
#
# Generate color blocks -> calculate base means -> construct new image -> show
#

import numpy as np
import cv2
import math
import sys
import os


class CumulatedImg:
    def getW(self, i, j):
        if i >= self.W.shape[0]: i = self.W.shape[0]-1
        if j >= self.W.shape[1]: j = self.W.shape[1]-1
        return 0 if i < 0 or j < 0 else self.W[i][j]

    def __init__(self, img):
        self.W = np.zeros((img.shape[0], img.shape[1], img.shape[2]), dtype=np.uint64)
        for i in range(0, img.shape[0]):
            for j in range(0, img.shape[1]):
                self.W[i][j] += self.getW(i-1, j) + self.getW(i, j-1) + img[i][j] - self.getW(i-1, j-1)

    def getMeanFrom(self, xb, yb, xa, ya):
        assert xa > xb or ya > yb
        n = ((xb - xa)+1) * ((yb - ya)+1)
        z = self.getW(xb, yb) - self.getW(xb, ya-1) - self.getW(xa-1, yb) + self.getW(xa-1, ya-1)
        return z/n

class ImageDatabase:
    def mean(self, img):
        s = np.zeros(img.shape[2], dtype=np.uint64)
        for i in range(0, img.shape[0]):
            for j in range(0, img.shape[1]):
                s += img[i][j]
        return s/(img.shape[0]*img.shape[1])

    def __init__(self, uri):
        self.db = {}
        for f in os.listdir("./"+uri):
            img = cv2.imread(uri+f)
            self.db[self.mean(img).tostring()] = img

    def absSub(self, a, b): return a - b if a > b else b - a

    def colorDistance(self, c1, c2):
        rmean = (c1[2] + c2[2])/2
        r = self.absSub(c1[2], c2[2])
        g = self.absSub(c1[1], c2[1])
        b = self.absSub(c1[0], c2[0])
        return math.sqrt(np.right_shift(int((512+rmean)*r*r), 8) + 4*g*g + np.right_shift(int(self.absSub(767, rmean)*b*b), 8));

    def euclidianDistance(self, c1, c2):
        return math.sqrt(self.absSub(c2[0],c1[0])**2 + self.absSub(c2[1],c1[1])**2 + self.absSub(c2[2],c1[2])**2)

    def getClosestImage(self, cimg, x, y, width, e = False):
        minDist  =  1000
        for skey, value in self.db.iteritems():
            key = np.fromstring(skey, dtype=np.uint64)
            valueR = cv2.resize(value, (0,0), fx=1/float(width), fy=1/float(width))
            color = cimg.getMeanFrom(x, y, x+valueR.shape[0], y+valueR.shape[1])
            dist = self.euclidianDistance(key, color) if e else self.colorDistance(key, color)
            if dist < minDist:
                minDist  = dist
                minValue = valueR
        return minValue


def paint(img, x, y, newImg, visited):
    for i in range(0, img.shape[0]):
        for j in range(0, img.shape[1]):
            if i + x < newImg.shape[0] and j + y < newImg.shape[1]:
                newImg[i+x][j+y] = img[i][j]
                visited[i+x][j+y] = True

def doMosaic(img, db, width, e = False):
    print "Calculating Cumulated Img...."
    cimg    = CumulatedImg(img)
    print "Calculating Mosaic..."
    visited = np.zeros((img.shape[0], img.shape[1]), dtype=bool)
    newImg  = np.zeros((img.shape[0], img.shape[1], img.shape[2]), dtype=np.uint8)
    for i in range(0, img.shape[0]):
        for j in range(0, img.shape[1]):
            if not visited[i][j]:
                paint(db.getClosestImage(cimg, i, j, width, e), i, j, newImg, visited)
    print "Finish"
    return newImg

def blend(img1, img2):
    return (img1*0.2 + img2*0.8)/255

img = cv2.imread(sys.argv[1])

print "Loading database..."
db      = ImageDatabase(sys.argv[2])

mosaic1 = doMosaic(img, db, sys.argv[3])
mosaic2 = doMosaic(img, db, sys.argv[3], True)

mosaic1b = blend(img, mosaic1)
mosaic2b = blend(img, mosaic2)

mosaic1b.astype(int)
mosaic2b.astype(int)

cv2.imshow("count", img)
cv2.imshow("mosaic1", mosaic1)
cv2.imshow("mosaicE", mosaic2)
cv2.imshow("mosaic1b", mosaic1b)
cv2.imshow("mosaicEb", mosaic2b)

cv2.imwrite('mosaic1.png', mosaic1)
cv2.imwrite('mosaicE.png', mosaic2)
cv2.imwrite("mosaic1b.png", mosaic1)
cv2.imwrite("mosaicEb.png", mosaic2)

cv2.waitKey()
cv2.destroyAllWindows()
