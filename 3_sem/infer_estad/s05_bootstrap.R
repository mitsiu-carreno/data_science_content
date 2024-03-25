
################################################################################################
################################################################################################
##### Ejemplo Bootstrap

# Crear una muestra de datos de ejemplo
set.seed(123)  # Establecer semilla para reproducibilidad
muestra <- rnorm(100, mean = 10, sd = 2)
#muestra <- rexp(100, rate = 5)
muestra <- runif(100, min=2, max=6)
hist(muestra, freq=FALSE)
Media_MO<-mean(muestra)
Media_MO
sd(muestra)

# Funci�n para calcular la media de una muestra
media_muestra <- function(x) {
  return(mean(x))
}

# Implementar Bootstrap para estimar el intervalo de confianza de la media
n_replicas <- 1000  # N�mero de r�plicas Bootstrap
bootstrap_resultados <- replicate(n_replicas, media_muestra(sample(muestra, replace = TRUE)))

# Calcular intervalo de confianza del 95%
intervalo_confianza_MB <- quantile(bootstrap_resultados, c(0.025, 0.975))
intervalo_confianza_MB
# Imprimir resultados
print("Intervalo de confianza del 95% para la media:")
intervalo_confianza_MB
#var(bootstrap_resultados)
#sd(bootstrap_resultados)

hist(muestra, freq=FALSE, ylim=c(0,2.5), main='Muestra original vs resultados Bootstrap')
abline(v=Media_MO,lwd=2, col='blue' )
hist(bootstrap_resultados, freq=FALSE, add=TRUE, col='skyblue')

hist(bootstrap_resultados, freq=FALSE,  col='skyblue',  main='Aproximaci�n de la distribusi�n de la media \n(resultados Bootstrap)')
lines(density(bootstrap_resultados), lwd=2, col='blue')
abline(v=Media_MO,lwd=3, col='magenta4' )
abline(v=intervalo_confianza_MB,lwd=3, col='cyan4' )

####################################
Media_MO
sd(muestra)
mean(bootstrap_resultados)
sd(bootstrap_resultados)
####################################

# Crear una muestra de datos de ejemplo
set.seed(123)  # Establecer semilla para reproducibilidad
#muestra <- rnorm(100, mean = 10, sd = 2)
#muestra <- rexp(100, rate = 5)
muestra <- runif(100, min=2, max=6)
hist(muestra, freq=FALSE)
max(muestra)
sd(muestra)

# Funci�n para calcular la media de una muestra
media_muestra <- function(x) {
  return(max(x))
}

# Implementar Bootstrap para estimar el intervalo de confianza de la media
n_replicas <- 1000  # N�mero de r�plicas Bootstrap
bootstrap_resultados <- replicate(n_replicas, media_muestra(sample(muestra, replace = TRUE)))

# Calcular intervalo de confianza del 95%
intervalo_confianza_MB <- quantile(bootstrap_resultados, c(0.025, 0.975))
intervalo_confianza_MB
# Imprimir resultados
print("Intervalo de confianza del 95% para la media:")
intervalo_confianza_MB
#var(bootstrap_resultados)
#sd(bootstrap_resultados)

hist(muestra, freq=FALSE, ylim=c(0,2.5), main='Muestra original vs resultados Bootstrap')
abline(v=max(muestra),lwd=2, col='blue' )
hist(bootstrap_resultados, freq=FALSE, add=TRUE, col='skyblue')

hist(bootstrap_resultados, freq=FALSE,  col='skyblue',  main='Aproximaci�n de la distribusi�n de la media \n(resultados Bootstrap)')
lines(density(bootstrap_resultados), lwd=2, col='blue')
abline(v=max(muestra),lwd=3, col='magenta4' )
#abline(v=intervalo_confianza_MB,lwd=3, col='cyan4' )

####################################
Media_MO
sd(muestra)
mean(bootstrap_resultados)
sd(bootstrap_resultados)
####################################

################################################################################################
################################################################################################
##### Ejemplo Jackknife
# Crear una muestra de datos de ejemplo
set.seed(123)  # Establecer semilla para reproducibilidad
muestra <- rnorm(50, mean = 10, sd = 2)

muestra <- rexp(20, 1/4)
muestra<-c(muestra,rnorm(3, mean = 25, sd = 3))
muestra
hist(muestra, freq=FALSE)

# Funci�n para calcular la media de una muestra
media_muestra <- function(x) {
  return(mean(x))
}

# Implementar Jackknife para estimar el sesgo de la media
n <- length(muestra)
jackknife_resultados <- numeric(n) #se inicia el vector con 0s

for (i in 1:n) {
  muestra_jackknife <- muestra[-i]
  jackknife_resultados[i] <- (n - 1) * media_muestra(muestra) - (n - 2) * media_muestra(muestra_jackknife)# sesgos
  #print(c(i,(n - 1) * media_muestra(muestra),(n - 2) * media_muestra(muestra_jackknife),jackknife_resultados[i]))
}

jackknife_resultados
# Calcular sesgo promedio
sesgo_promedio <- mean(jackknife_resultados)

# Imprimir resultados
print(paste("Sesgo promedio estimado con Jackknife:", sesgo_promedio))

hist(muestra, freq=FALSE, ylim=c(0,2.5), main='Muestra original vs resultados Jackknife')
abline(v=mean(muestra),lwd=2, col='blue' )
hist(jackknife_resultados, freq=FALSE, add=TRUE, col='skyblue')

hist(jackknife_resultados, freq=FALSE,  col='skyblue',  main='Aproximaci�n de la distribusi�n de sesgo \n(resultados Jackknife)') #, xlim=c(0,20)
lines(density(jackknife_resultados), lwd=2, col='blue')

mean(muestra)
(intervalo_confianza_MO <- quantile(muestra, c(0.025, 0.975)))
mean(jackknife_resultados)
(intervalo_confianza_MJ <- quantile(jackknife_resultados, c(0.025, 0.975)))

abline(v=mean(muestra),lwd=2, col='magenta4' )
abline(v=intervalo_confianza_MO,lwd=2, col='magenta4' )

abline(v=mean(jackknife_resultados),lwd=3, col='cyan4' )
abline(v=intervalo_confianza_MJ,lwd=3, col='cyan4' )

################################################################################################
################################################################################################
################################################################################################
##### Ejemplos M�todos de permutaci�n
#Ejemplo 1: Prueba de Permutaci�n para la Diferencia de Medias
#En este ejemplo, realizaremos una prueba de permutaci�n para la diferencia de medias entre dos grupos utilizando el paquete perm en R.

# Instalar y cargar el paquete perm
install.packages("perm")
library(perm)

# Datos de ejemplo
set.seed(123)
grupo1 <- rnorm(20, mean = 5, sd = 2)
#grupo2 <- rnorm(25, mean = 8, sd = 2)
grupo2 <- rnorm(25, mean = 5.2, sd = 3)

# Observar la diferencia de medias observada
diferencia_obs <- mean(grupo2) - mean(grupo1)

# Realizar la prueba de permutaci�n
perm_test <- permTS(grupo2, grupo1, alternative = "two.sided", method = NULL)

#permTS(grupo2, grupo1, alternative = "two.sided", method = "exact.mc")
#permTS(grupo2, grupo1, alternative = "two.sided", method = "exact.network")

# Imprimir resultados
cat("Diferencia de Medias Observada:", diferencia_obs, "\n")
print(perm_test)

hist(grupo1, freq=FALSE,  main='Grupo 1 vs Grupo 2', col='rosybrown1',xlim=c(0,13)) 
hist(grupo2, freq=FALSE, add=TRUE, col='skyblue')
abline(v=mean(grupo1),lwd=2, col='magenta' )
abline(v=mean(grupo2),lwd=2, col='blue' )

#############################################################################################################################
#Ejemplo 2: Prueba de Permutaci�n para la Correlaci�n
#En este ejemplo, utilizaremos una prueba de permutaci�n para evaluar la significancia de la correlaci�n entre dos variables.
# Datos de ejemplo
set.seed(456)
variable1 <- rnorm(30)
#variable2 <- 2 * variable1 + rnorm(30)
variable2 <- rexp(30)

plot(variable1,variable2)

# Observar la correlaci�n observada
cor_obs <- cor(variable1, variable2)

# Realizar la prueba de permutaci�n
perm_test_cor <- cor.test(variable1, variable2, method = NULL)

# Imprimir resultados
cat("Correlaci�n Observada:", cor_obs, "\n")
print(perm_test_cor)

################################################################################################
################################################################################################
################################################################################################
################################################################################################
################################################################################################
################################################################################################






















################################################################################################
##### Ejemplo de inferencia por verosimilitud 
#Vamos a realizar un ejemplo simple de inferencia por verosimilitud en R utilizando un modelo normal. 
#Supongamos que tenemos una muestra de datos y queremos estimar la media y la desviaci�n est�ndar de la poblaci�n.
# Generamos una muestra de datos con una distribuci�n normal
set.seed(123)  # Establecemos una semilla para reproducibilidad
muestra <- rnorm(100, mean = 10, sd = 2)

# Definimos la funci�n de verosimilitud para una distribuci�n normal
likelihood <- function(parametros) {
  media <- parametros[1]
  desviacion <- parametros[2]
  
  # Calculamos la funci�n de densidad de probabilidad
  pdf <- dnorm(muestra, mean = media, sd = desviacion, log = TRUE)
  
  # La funci�n de verosimilitud es el logaritmo de la probabilidad
  log_verosimilitud <- sum(pdf, na.rm = TRUE)
  
  return(log_verosimilitud)
}

# Maximizamos la funci�n de verosimilitud para encontrar los estimadores de los par�metros
library(stats4)

likelihood(c(media = mean(muestra), desviacion = sd(muestra)))
is.numeric(media)
mle(likelihood(list(media = mean(muestra), desviacion = sd(muestra))))
ajuste <- mle(likelihood, start = list(media = mean(muestra), desviacion = sd(muestra)))

# Obtenemos los estimadores de los par�metros
estimador_media <- coef(ajuste)[1]
estimador_desviacion <- coef(ajuste)[2]

# Imprimimos los resultados
cat("Estimador de la media:", estimador_media, "\n")
cat("Estimador de la desviaci�n est�ndar:", estimador_desviacion, "\n")
###########################################################################################
# Definimos la funci�n de verosimilitud para una distribuci�n de Bernoulli
verosimilitud_bernoulli <- function(p, k, n) {
  verosimilitud <- dbinom(k, size = n, prob = p, log = TRUE)
  return(sum(verosimilitud, na.rm = TRUE))
}

# Supongamos que lanzamos la moneda 20 veces y obtenemos 15 caras
n_lanzamientos <- 20
caras_obs <- 15

# Maximizamos la funci�n de verosimilitud para encontrar el estimador de p
ajuste_bernoulli <- optim(par = 0.5, fn = verosimilitud_bernoulli, k = caras_obs, n = n_lanzamientos, method = "L-BFGS-B")

# Obtenemos el estimador de p
estimador_p <- ajuste_bernoulli$par

# Imprimimos el resultado
cat("Estimador de la probabilidad p:", estimador_p, "\n")


15/20

?dbinom(k=15, size = 20, prob = 0.5, log = TRUE)
###############################################################################################
#Supongamos que tenemos una muestra de datos de una variable aleatoria normal y queremos estimar la media ????? y la desviaci�n est�ndar ?????.
# Generamos una muestra de datos con una distribuci�n normal
set.seed(123)
muestra_normal <- rnorm(100, mean = 10, sd = 2)

# Definimos la funci�n de verosimilitud para una distribuci�n normal
verosimilitud_normal <- function(parametros, datos) {
  media <- parametros[1]
  desviacion <- parametros[2]
  
  verosimilitud <- dnorm(datos, mean = media, sd = desviacion, log = TRUE)
  return(sum(verosimilitud, na.rm = TRUE))
}

# Maximizamos la funci�n de verosimilitud para encontrar los estimadores de media y desviaci�n est�ndar
ajuste_normal <- optim(par = c(10, 2), fn = verosimilitud_normal, datos = muestra_normal, method = "L-BFGS-B")

# Obtenemos los estimadores de la media y la desviaci�n est�ndar
estimador_media_normal <- ajuste_normal$par[1]
estimador_desviacion_normal <- ajuste_normal$par[2]

# Imprimimos los resultados
cat("Estimador de la media:", estimador_media_normal, "\n")
cat("Estimador de la desviaci�n est�ndar:", estimador_desviacion_normal, "\n")



