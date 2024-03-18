set.seed(2020)
enfms <- rnorm(100,173,2)
#enfms <- rnorm(100,170,2)
#enfms <- rnorm(100,180,2)
sanos <- rnorm(100,167,2)
datos <- data.frame(c(enfms,sanos),
                    as.factor(rep(c("Sanos","Enfermos"), times = 1, each = 100)))
colnames(datos) <- c("Valor","Clase")
denEnf <- density(enfms)
denSan <- density(sanos)
plot(NULL,xlim=c(160,185),ylim=c(0,0.25), type="n",
     xlab="Cantidad de glucosa en la sangre",ylab="Densidades")

lines(denEnf,col="red")
lines(denSan,col="blue")
text(164,0.25, "Sanos")
text(176,0.25, "Enfermos")
#####################################################################
#install.packages("ROCR")
#library(ROCR)

pred <- prediction(datos$Valor, datos$Clase)
perf <- performance(pred,measure="tpr",x.measure="fpr")

plot(perf,colorize=TRUE,type="l") 
abline(a=0,b=1)

# �rea bajo la curva
AUC       <- performance(pred,measure="auc")
AUCaltura <- AUC@y.values

# Punto de corte �ptimo
cost.perf <- performance(pred, measure ="cost")
opt.cut   <- pred@cutoffs[[1]][which.min(cost.perf@y.values[[1]])]
#coordenadas del punto de corte �ptimo
x<-perf@x.values[[1]][which.min(cost.perf@y.values[[1]])]
y<-perf@y.values[[1]][which.min(cost.perf@y.values[[1]])]
points(x,y, pch=20, col="red")

cat("AUC:", AUCaltura[[1]]) 
cat("Punto de corte �ptimo:",opt.cut)

######## Otro ejemplo #############################################################
#Para los enfermos
muestra1 <- which(denEnf$y>0.005)
muestra1 <- sample(muestra1,75,replace=F)
y1 <- vector()
for(i in muestra1){
  y1 <- append(y1,runif(1,min(denEnf$y),denEnf$y[i])) 
}
#Para los sanos
muestra2 <- which(denSan$y>0.005)
muestra2 <- sample(muestra2,75,replace=F)
y2 <- vector()
for(i in muestra2){
  y2 <- append(y2,runif(1,min(denSan$y),denSan$y[i]))
}
incr <- 0
intersX <- which(diff(denEnf$y<denSan$y)!=0)

curvas <- function() {
  plot(denEnf$x,denEnf$y,type = "l",
       xlim =c(min(min(denEnf$x ),min(denSan$x)),max(max(denEnf$x),max(denSan$x))),ylim=c(0,0.25)) 
  lines(denSan$x,denSan$y)
  points(denEnf$x[muestra1], y1, pch = "+",col="red")
  text(175,0.25,labels = "Enfermos" )
  points(denSan$x[muestra2], y2, pch = "*",col="blue")
  text(165,0.25,labels = "Sanos" )
  text(c(169,167,174,172),c(0,0.10,0.10,0), labels = c("FN","TN","TP","FP"))}

curvas()
abline(v=170.2,col="green") 


# n�mero de Falsos Negativos (FN)
FN <- length(which(denEnf$x[muestra1] < denEnf$x[intersX]))

# N�mero de Verdaderos Positivos VP (TP)
TP <- length(which(denEnf$x[muestra1] >= denEnf$x[intersX]))

# N�mero de Falsos Positivos (FP)
FP <- length(which(denSan$x[muestra2] >= denSan$x[intersX]))

# N�mero de Verdaderos Negativos (TN)
TN <- length (which(denSan$x[muestra2] < denSan$x[intersX]))

(Sensibilidad  <- TP/(FN+TP))
(Especificidad <- TN/(FP+TN))


