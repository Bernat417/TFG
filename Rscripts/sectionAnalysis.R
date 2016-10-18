# Script used to analyse the start, mid and end sections #

library(gplots)

Paths <- read.csv("pathPosition.csv",sep=";",stringsAsFactors=FALSE,comment.char="#")
summary(Paths)
str(Paths)

proteinlessPaths = subset(Paths, select= c("timesStartNode","timesMidNode","timesEndNode") )
proteinlessPaths

summary(proteinlessPaths)
names(proteinlessPaths)
croppedMatrix = data.matrix(proteinlessPaths, rownames.force = NA)
hmcols<-colorRampPalette(c("yellow","orange","red","blue", "lightblue"))(256)
hmcols<-colorRampPalette(c("yellow","red","lightblue"))(256)

# Subset Analysis
pathsSubset= subset(proteinlessPaths[which(proteinlessPaths$timesStartNode > 30),], select = c("timesMidNode","timesEndNode"))
summary(pathsSubset)

# Heatmap generation (Takes quite some time)
cols <- c("start","mid","end")
colnames(proteinlessPaths) <- cols
names(proteinlessPaths)
heatmap.2(croppedMatrix,scale="row",dendrogram='none', Rowv=FALSE, Colv=FALSE,trace='none') 