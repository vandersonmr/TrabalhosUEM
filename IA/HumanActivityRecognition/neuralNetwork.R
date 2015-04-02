#!/usr/bin/Rscript
library(nnet)
library(rgl)
source("nnet_plot_update.r")

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

cat("Criando rede neurais...\n");
# RFs with means
for(i in 1:((length(means)/3))) {
  cat(paste(c("Rede neural ", i,'/',((length(means)/3)), "..."), collapse=''))
  nnMeans <- nnet(V562~., data=trainData[,c(means[((3*i)-2):(3*i)], 562)], 
                          size=10, maxit=500)

  svg(filename=(paste(c("graficos/nnet", i, ".svg"), collapse='')))
  plot.nnet(nnMeans)
  dev.off()

  print(table(predict(nnMeans, testData[,c(means[((3*i)-2):(3*i)])], type="class"),
                testLabels))
}

nnM <- nnet(V562~.,data=trainData[,c(means, 562)], size=20, maxit=500)

print(nnM)

svg(filename="graficos/nnetMean.svg")
plot.nnet(nnM)
dev.off()

print(table(predict(nnM, testData[,means], type="class"),
                testLabels))


cat("feito.\n")

