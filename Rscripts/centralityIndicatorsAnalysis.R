# RScript used to analyse the graph and path centrality indicators

#--------------------------General Analysis--------------------------
Data <- read.csv("OriginalData.csv",stringsAsFactors=FALSE)
Data <- read.csv("AllData.csv",stringsAsFactors=FALSE)
Data <- read.csv("PathsData.csv",stringsAsFactors=FALSE)

Data
nrow(Data)
sum(Data$Degree)/2.0

names(Data)
summary(Data$Degree)
summary(Data$Betweennes)
quantile(Data$Degree, 0.92)
table(Data$Closeness)
log(table(Data$Closeness))

boxplot(Data$Degree, ylab = "Degree", main = "Boxplot of Degrees")

barplot()

hist(Data$Degree, xlab = "Degree", main = "Histogram of Degrees", 
     xlim = c(0,max(Data$Degree)), breaks = 100)
hist(Data$Betweennes, xlab = "Betweenness", main = "Histogram of Betweenness", 
     xlim = c(0,max(Data$Betweenne)), breaks = 100)
hist(Data$Closeness, xlab = "Closeness", main = "Histogram of Closeness", 
     xlim = c(0,max(Data$Closeness)), breaks = 100)
hist(Data$Occurrences, xlab = "Occurrences", main = "Histogram of Occurrences", 
     xlim = c(0,max(Data$Occurrences)), breaks = 100)
hist(Data$Intensity, xlab = "Intensity", main = "Histogram of Intensity", 
     xlim = c(0,max(Data$Intensity)), breaks = 100)

hist(table(log(Data$Degree)), xlab = "Log Degree", main = "Histogram of Degrees", 
     xlim = c(0,max(table(log(Data$Degree)))), breaks = 100)
hist(table(log(Data$Betweennes)), xlab = "Log Betweenness", main = "Histogram of Betweenness", 
     xlim = c(0,max(table(log(Data$Betweenne)))), breaks = 100)
hist(table(log(Data$Closeness)), xlab = "Log Closeness", main = "Histogram of Closeness", 
     xlim = c(0,max(table(log(Data$Closeness)))), breaks = 100)
hist(table(log(Data$Occurrences)), xlab = "Log Occurrences", main = "Histogram of Occurrences", 
     xlim = c(0,max(table(log(Data$Occurrences)))), breaks = 100)
hist(table(log(Data$Intensity)), xlab = "Log Intensity", main = "Histogram of Intensity", 
     xlim = c(0,max(table(log(Data$Intensity)))), breaks = 100)

plot(log(table(log(Data$Degree))), type = "p",xlab = "Log Degree", ylab = "Log Frequency",
     xlim = log(c(min(Data$Degree),max(Data$Degree))),  main = "Logarithmic Frequency & Degree")  
plot(log(table(log(Data$Betweennes))), type = "p",xlab = "Log Betweenness", ylab = "Log Frequency",
     xlim = log(c(1,max(Data$Betweennes))),  main = "Logarithmic Frequency & Betweenness") 
plot(log(table(log(Data$Closeness))), type = "p",xlab = "Log Closeness", ylab = "Log Frequency",
     xlim = log(c(min(Data$Closeness),max(Data$Closeness))),  main = "Logarithmic Frequency & Closeness") 
plot(log(table(log(Data$Occurrences))), type = "p",xlab = "Log Occurrences", ylab = "Log Frequency",
     xlim = log(c(1,max(Data$Occurrences))),  main = "Logarithmic Frequency & Occurrences") 
plot(log(table(log(Data$Intensity))), type = "p",xlab = "Log Intensity", ylab = "Log Frequency",
     xlim = log(c(1,max(Data$Intensity))),  main = "Logarithmic Frequency & Intensity") 

#-----------------------Outlaier Selection-----------------------
top <- head(sort(Data$Betweennes, decreasing = TRUE),100)
top

OutliersB = subset(Data, select = c(Protein, Betweennes))
OutliersB = head(OutliersB[order(- OutliersB$Betweennes),],50)
OutliersB

OutliersD = subset(Data,select = c(Protein, Degree))
OutliersD = head(OutliersD[order(- OutliersD$Degree),],50)
OutliersD

OutliersC = subset(Data, select = c(Protein, Closeness),Closeness > 100)
OutliersC = head(OutliersC[order(OutliersC$Closeness),], 50)
OutliersC


OutliersI = subset(Data, select = c(Protein, Intensity))
OutliersI = head(OutliersI[order(- OutliersI$Intensity),],50)
OutliersI

OutliersO = subset(Data, select = c(Protein, Occurrences))
OutliersO = head(OutliersO[order(- OutliersO$Occurrences),],50)
OutliersO

Outliers = merge(OutliersB,OutliersD, all=FALSE)
Outliers = merge(Outliers,OutliersB, all=FALSE)
Outliers = merge(Outliers,OutliersI, all=FALSE)
Outliers = merge(Outliers,OutliersC, all=FALSE)
Outliers


write(OutliersB$Protein, "TOP50Betweenness.txt",  sep="\n") 
write(OutliersD$Protein, "TOP50Degree.txt",  sep="\n") 
write(OutliersC$Protein, "TOP50Closeness.txt",  sep="\n") 
write(Outliers$Protein, "TOP50NaturalJoin.txt",  sep="\n") 

#-----------------------Variable Relationship Analysis-----------------------
summary(Data$Intensity)

cor(Data$Intensity, Data$Degree)
cor(Data$Intensity, Data$Betweennes)
cor(Data$Intensity, Data$Closeness)
cor(Data$Intensity, Data$Occurrences)

cor(Data$Betweennes, Data$Occurrences)
cor(Data$Closeness, Data$Occurrences)
cor(Data$Degree, Data$Occurrences)

cor(Data$Betweennes, Data$Degree)
cor(Data$Betweennes, Data$Closeness)

cor(Data$Betweennes, Data$Closeness)

