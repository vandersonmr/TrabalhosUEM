#!/usr/bin/python

import numpy as np
import cv2
import math
import sys
from collections import deque
from matplotlib import pyplot as plt

font = cv2.FONT_HERSHEY_SIMPLEX

img = cv2.imread(sys.argv[1], cv2.CV_LOAD_IMAGE_GRAYSCALE)
img[img > 127] = 255
img[img < 127] = 0

def isValid(img, x, y):
    return x >= 0 and x < img.shape[0] and y >= 0 and y < img.shape[1]

def paint(img, (x, y), color, toPaint = 255):
    centroid = (x, y)
    size = 0
    queue = deque([(x, y)])
    visited = img > 255
    while len(queue) != 0:
        a = queue.popleft()
        img[a[0], a[1]] = color
        centroid = (centroid[0] + a[0], centroid[1] + a[1])
        size += 1
        for nx, ny in [(a[0]+i, a[1]+j) for i in range(-1, 2) for j in range(-1, 2)]:
            if isValid(img, nx, ny) and img[nx, ny] == toPaint and not visited[nx][ny]:
                visited[nx][ny] = True
                queue.append((nx, ny))
    return centroid[1]/size, centroid[0]/size

def count(img, toPaint = 255):
    num = 0
    color = 100
    for x in range(0, img.shape[0]):
        for y in range(0, img.shape[1]):
            if img[x, y] == toPaint:
                centroid = paint(img, (x, y), color, toPaint)
                cv2.putText(img,str(num),centroid,font,0.7,(250,250,250),2)
                color = (color + 1) % 240 + 1
                num += 1
    return num

print count(img)
plt.hist(img.ravel(),256,[100,240]); plt.show()

cv2.imshow("count", img)
cv2.imwrite('count.png', img)
cv2.waitKey()
cv2.destroyAllWindows()
