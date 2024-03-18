
#Instala y carga el paquete 'MASS' para generar datos simulados
#install.packages("MASS")
library(MASS)

# Configura la semilla para reproducibilidad
set.seed(123)

# N�mero de observaciones
n <- 100

# Variables predictoras
x1 <- rnorm(n, mean = 1, sd = .5)  # Variable predictora 1
x2 <- rnorm(n, mean = 2, sd = .5)  # Variable predictora 2
#hist(x1)
#hist(x2)

# Coeficientes verdaderos
beta0 <- 1
beta1 <- 2
beta2 <- 3

# Error aleatorio
error <- rnorm(n, mean = 0, sd = 1)

# Variable respuesta simulada
y <- beta0 + beta1 * x1 + beta2 * x2 + error


# Crea un dataframe con los datos
data <- data.frame(y, x1, x2)

# Ajusta un modelo de regresi�n lineal m�ltiple
modelo <- lm(y ~ x1 + x2, data = data)

# Muestra un resumen del modelo
summary(modelo)

#
library(GGally)
ggpairs(data, lower = list(continuous = "smooth"),
        diag = list(continuous = "barDiag"), axisLabels = "none")

#Intervalos de confianza de los coeficientes.
confint(lm(formula = y ~ x1 + x2, data = data))

#relacion lineal entre los predictores
library(ggplot2)
library(gridExtra)
plot1 <- ggplot(data = data, aes(x1, modelo$residuals)) +
  geom_point() + geom_smooth(color = "firebrick") + geom_hline(yintercept = 0) +
  theme_bw()
plot2 <- ggplot(data = data, aes(x2, modelo$residuals)) +
  geom_point() + geom_smooth(color = "firebrick") + geom_hline(yintercept = 0) +
  theme_bw()
grid.arrange(plot1, plot2)

#distribucion normal de los residuos
qqnorm(modelo$residuals)
qqline(modelo$residuals)
shapiro.test(modelo$residuals)

#La hip�tesis nula (Ho. los residuales vienen de una dist normal), 
#Seg�n el resultado, el valor p > ?? = 0,05 (Con un nivel de confianza del 95%) 
#implica que la distribuci�n de los datos 
#no es significativamente diferente de la distribuci�n normal. 
#En otras palabras, podemos asumir la normalidad.


#Variabilidad constante de los residuos (homocedasticidad)
ggplot(data = data, aes(modelo$fitted.values, modelo$residuals)) +
geom_point() +
geom_smooth(color = "firebrick", se = FALSE) +
geom_hline(yintercept = 0) +
theme_bw()

library(lmtest)
bptest(modelo)

#Considerando un nivel de confianza del 95%; p-value = 0.4941 > ?? = 0.05, NO se rechaza 
#la hip�tesis nula (Ho. los residuales tienen varianza constante), por lo tanto, puede decirse que
#No hay evidencias de falta de homocedasticidad.


#No multicolinialidad:
  #Matriz de correlaci�n entre predictores.
library(corrplot)

col2 = colorRampPalette(c('navy', '#007FFF', 'cyan','blue','#00007F'))

#col2 = colorRampPalette(c('navy','blue','cyan','blue','navy'))
corrplot(cor(dplyr::select(data, y, x1,x2)),
         method = "number", tl.col = "black", col = col2(20))

#No existe evidencia de multicolinealidad


########### SIN RELACION LINEAL ENTRE X1 Y Y ######################################################################
# Configura la semilla para reproducibilidad
set.seed(123)

# N�mero de observaciones
n <- 100

# Variables predictoras
x1a <- runif(n, 3, 5)  # Variable predictora 1
x1 <- log(x1a)#*x1a
x2 <- rnorm(n, mean = 2, sd = .5)  # Variable predictora 2
hist(x1)
hist(x2)
plot(x1,x1a)

# Coeficientes verdaderos
beta0 <- 3
beta1 <- 1
beta2 <- 2

# Error aleatorio
error <- rnorm(n, mean = 0, sd = 1)

# Variable respuesta simulada
y <- beta0 + beta1 * x1 + beta2 * x2 + error

# Crea un dataframe con los datos
data <- data.frame(y, x1, x2)

# Ajusta un modelo de regresi�n lineal m�ltiple
modelo <- lm(y ~ x1 + x2, data = data)

# Muestra un resumen del modelo
summary(modelo)

#
library(GGally)
ggpairs(data, lower = list(continuous = "smooth"),
        diag = list(continuous = "barDiag"), axisLabels = "none")

#Intervalos de confianza de los coeficientes.
confint(lm(formula = y ~ x1 + x2, data = data))

#relacion lineal entre los predictores
ibrary(ggplot2)
library(gridExtra)
plot1 <- ggplot(data = data, aes(x1, modelo$residuals)) +
  geom_point() + geom_smooth(color = "firebrick") + geom_hline(yintercept = 0) +
  theme_bw()
plot2 <- ggplot(data = data, aes(x2, modelo$residuals)) +
  geom_point() + geom_smooth(color = "firebrick") + geom_hline(yintercept = 0) +
  theme_bw()
grid.arrange(plot1, plot2)

#distribucion normal de los residuos
qqnorm(modelo$residuals)
qqline(modelo$residuals)
shapiro.test(modelo$residuals)
# NO se confirma normalidad

#variabilidad constante de los residuos (homocedasticidad)
ggplot(data = data, aes(modelo$fitted.values, modelo$residuals)) +
  geom_point() +
  geom_smooth(color = "firebrick", se = FALSE) +
  geom_hline(yintercept = 0) +
  theme_bw()

library(lmtest)
bptest(modelo)

#No hay evidencias de falta de homocedasticidad.

#No multicolinialidad:

#Matriz de correlaci�n entre predictores.
library(corrplot)

col2 = colorRampPalette(c('navy', '#007FFF', 'cyan','blue','#00007F'))

#col2 = colorRampPalette(c('navy','blue','cyan','blue','navy'))
corrplot(cor(dplyr::select(data, y, x1,x2)),
         method = "number", tl.col = "black", col = col2(20))

#No existe evidencia de multicolinealidad


########### CON ERRORES DIFERENTES ANORMALES ######################################################################
# Configura la semilla para reproducibilidad
set.seed(123)

# N�mero de observaciones
n <- 100

# Variables predictoras
#x1a <- runif(n, 3, 5)  # Variable predictora 1
#x1 <- log(x1a)#*x1a
x1 <- rnorm(n, mean = 1, sd = .5)  # Variable predictora 1
x2 <- rnorm(n, mean = 2, sd = .5)  # Variable predictora 2
#hist(x1)
#hist(x2)
#plot(x1,x1a)

# Coeficientes verdaderos
beta0 <- 3
beta1 <- 2
beta2 <- 1

# Error aleatorio
error <- rnorm(n, mean = 0, sd = 1)
error <- rexp(n, 1/10)
plot(error)
hist(error)

# Variable respuesta simulada
y <- beta0 + beta1 * x1 + beta2 * x2 + error

# Crea un dataframe con los datos
data <- data.frame(y, x1, x2)

# Ajusta un modelo de regresi�n lineal m�ltiple
modelo <- lm(y ~ x1 + x2, data = data)

# Muestra un resumen del modelo
summary(modelo)

#
library(GGally)
ggpairs(data, lower = list(continuous = "smooth"),
        diag = list(continuous = "barDiag"), axisLabels = "none")

#Intervalos de confianza de los coeficientes.
confint(lm(formula = y ~ x1 + x2, data = data))

#relacion lineal entre los predictores
ibrary(ggplot2)
library(gridExtra)
plot1 <- ggplot(data = data, aes(x1, modelo$residuals)) +
  geom_point() + geom_smooth(color = "firebrick") + geom_hline(yintercept = 0) +
  theme_bw()
plot2 <- ggplot(data = data, aes(x2, modelo$residuals)) +
  geom_point() + geom_smooth(color = "firebrick") + geom_hline(yintercept = 0) +
  theme_bw()
grid.arrange(plot1, plot2)

#distribucion normal de los residuos
qqnorm(modelo$residuals)
qqline(modelo$residuals)
shapiro.test(modelo$residuals)
# NO se confirma normalidad

#variabilidad constante de los residuos (homocedasticidad)
ggplot(data = data, aes(modelo$fitted.values, modelo$residuals)) +
  geom_point() +
  geom_smooth(color = "firebrick", se = FALSE) +
  geom_hline(yintercept = 0) +
  theme_bw()

library(lmtest)
bptest(modelo)

#No hay evidencias de falta de homocedasticidad.

#No multicolinialidad:
#Matriz de correlaci�n entre predictores.
library(corrplot)

col2 = colorRampPalette(c('navy', '#007FFF', 'cyan','blue','#00007F'))

#col2 = colorRampPalette(c('navy','blue','cyan','blue','navy'))
corrplot(cor(dplyr::select(data, y, x1,x2)),
         method = "number", tl.col = "black", col = col2(20))

#No existe evidencia de multicolinealidad
