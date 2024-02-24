## Mitsiu Alejandro Carreño Sarabia - E23S-18014

Resuelve el siguiente ejercicio.      

Se realiza un estudio para analizar el efecto de tres tipos de entrenamiento (A, B, C) en el tiempo que los atletas tardan en completar una carrera de 100 metros. Cada tipo de entrenamiento se aplicó a tres grupos diferentes de atletas, y se registraron los tiempos en segundos. Realiza un ANOVA de una vía para determinar si hay diferencias significativas en el tiempo de carrera debido al tipo de entrenamiento.       

Datos:      

- Entrenamiento A: [10.2, 10.5, 10.8] 

- Entrenamiento B: [9.8, 10.0, 10.3] 

- Entrenamiento C: [10.5, 10.7, 11.0]
        
Resultados obtenidos:      
Promedio grupo A: 10.5     
Promedio grupo B: 10.0333     
Promedio grupo C: 10.7333     
Promedio general: 10.4222     
       
Factor. Suma de cuadrados: 0.762224     
Factor. Grados de libertad: 2    
Factor. Cuadrado medio: 0.381112    
Factor. F: 5.27693     
     
Error. Suma de cuadrados: 0.433334      
Error. Grados de libertad: 6     
Error. Cuadrado medio: 0.0722223    
      
Total. Suma de cuadrados: 1.19556     
Total. Grados de libertad: 8     

Preguntas:

1. ¿Cuál es la hipótesis nula y alternativa?         
La hipótesis nula corresponde a que todos los grupos tienen un comportamiento similar, es décir varianza_grupo_a = varianza_grupo_b = varianza_grupo_c.      
La hipótesis alternativa corresponde a que al menos uno de los grupos tiene una diferencia significativa respecto al resto de grupos, es décir varianza_grupo_a - varianza_grupo_b != 0       

2. Calcula la suma total de cuadrados (SST).      
Total. Suma de cuadrados: 1.19556     
 
3. Calcula la suma de cuadrados entre grupos (SSB).       
Factor. Suma de cuadrados: 0.762224       

4. Calcula la suma de cuadrados dentro de grupos (SSW).      
Error. Suma de cuadrados: 0.433334       

5. Calcula los grados de libertad entre grupos (dfB) y dentro de grupos (dfW).     
dfB. Factor. Grados de libertad: 2         
dfW. Error. Grados de libertad: 6         
Extra: Grados de liberad totales. Total. Grados de libertad: 8       

6. Calcula la media de cuadrados entre grupos (MSB) y dentro de grupos (MSW).      
MSB. Factor. Cuadrado medio: 0.381112      
MSW. Error. Cuadrado medio: 0.0722223

7. Calcula el estadístico F.      
Estadístico F: 5.27693        

8. Determina si hay diferencias significativas utilizando un nivel de significancia común (por ejemplo, 0.05).               
Tomando la tabla de valores críticos de la distribución F con 2 grados de libertad del Numerador (Factor) y 6 grados de libertad del denominador (Error) obtenemos el valor 5.143             
Por lo tanto: Fcalculado = 5.27693 > Ftablas 5.143 entonces se rechaza Ho       

9. Interpreta los resultados y concluye si hay diferencias significativas en el tiempo de carrera debido al tipo de entrenamiento.             
Al haberse rechazaso Ho al menos uno de los grupos tiene una diferencia significativa respecto al resto y retomando los promedios, se puede notar que el grupo B tuvo un desempeño menor que el grupo A y B          


