#!/usr/bin/Rscript
library(randomForest)
library(rgl)

cat("Carregando dados...")
trainData   <- read.table("UCI HAR Dataset/train/X_train.txt")
trainLabels <- read.table("UCI HAR Dataset/train/y_train.txt")

testData   <- read.table("UCI HAR Dataset/test/X_test.txt")
testLabels <- read.table("UCI HAR Dataset/test/y_test.txt")
cat("feito.\n")

trainLabels <- factor(trainLabels[,1])
testLabels  <- factor(testLabels[,1])

trainData["V562"] <- trainLabels

m <- seq(1, 201, by=40)
m <- sort(c(m, m+1, m+2))
means <- c(m, 214, 215, 216, 227, 228, 229, 240, 241, 242, 253, 254, 255)

cat("Criando florestas...\n");
# RFs with means
for(i in 1:((length(means)/3))) {
  cat(paste(c("Floresta ", i,'/',((length(means)/3)), "..."), collapse=''))
  rfMeans <- randomForest(V562~.,data=trainData[,c(means[((3*i)-2):(3*i)], 562)], 
                          xtest=testData[,means[((3*i)-2):(3*i)]], ytest=testLabels,
                          importance=T, proximity=T)

  svg(filename=(paste(c("graficos/rfMeans", i, ".svg"), collapse='')))
  plot(rfMeans)
  dev.off()

  plot3d(trainData[,means[((3*i)-2):(3*i)]], col=trainLabels)
  rgl.postscript((paste(c("graficos/means", i,".pdf"), collapse='')),"pdf") 

  print(rfMeans)
}

rfM <- randomForest(V562~.,data=trainData[,c(means, 562)], 
                            xtest=testData[,means], ytest=testLabels,
                            importance=T, proximity=T)

print(rfM)

svg(filename="graficos/rfMean.svg")
plot(rfM)
dev.off()

cat("feito.\n")

