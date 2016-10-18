# This script is used to analize the relationship between real path lenght and  minimum path lenght #
if (!require("ggplot2")) {
  install.packages("ggplot2", dependencies = TRUE)
  library(ggplot2)
}

rawPathData <- read.csv("paths.csv",sep=";",stringsAsFactors=FALSE,comment.char="#")

possiblePathData = subset(rawPathData[which(rawPathData$longPathMin > 0),], 
  select = c("longPathMin","longPathReal"))

str(possiblePathData)

# longPathMin vs longPathReal heatmap visualization
sp <- ggplot(possiblePathData, aes(x=possiblePathData$longPathReal,
  y=possiblePathData$longPathMin,xlab = "Real Path Length", ylab = "Minimum Path Length")) + geom_point()

sp + stat_density2d(aes(fill = ..level..), geom="polygon")+ scale_fill_gradient(low="blue", high="red")

## Ens interesen els paths de longitud 2, 3 i 4
longitud = 6 ## Seleccionar valor de longitud a analitzar
summary(possiblePathData)
longitudsReals = as.vector(possiblePathData[which(possiblePathData$longPathMin ==longitud), c("longPathReal")])
summary(longitudsReals)

##Aproximacio polinomica
h = hist(longitudsReals)
histCounts = h$counts
histBreaks<- head(h$breaks,-1)
target = data.frame(x=histBreaks, y=histCounts)
y.hat <- predict(lm(y~x+I(x^2)+I(x^3)+I(x^4), data=target))
qplot(x, y, data=target, geom="line",xlab = "Real Path Length", ylab = "Minimum Path Length Ocurrences") + geom_line(aes(x=x, y=y.hat), col=2)

