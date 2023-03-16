# Ejercicio C2.4 Utiliza el comando <strong>if</strong> para poner validaciones, es decir, la calificación no puede ser menor a cero o mayor a 10.

import numpy as np

def promedio(n=3):   # parametro con valor default
    '''
    Este texto va a aparecer con shf+tab+tab
    Description:
        Calcula el promedio de calificaciones
    input:
        n (Def 2): el número de alumnos
    output:
        el promedio
    '''
    califs = np.array([None]*n)
    for i in range(n):
        while True:
            calif = int(input(f"Escribe la calificación del alumno {i+1}: "))
            if calif < 0 or calif > 10:
                print(f"Calif no valida {calif}")
                continue
            califs[i] = calif
            break
    suma = np.sum(califs)
    return suma/n

promedio()

################################################################################33

# Ejercicio C3.1 Hacer una función que calcule el índice de masa corporal (IMC) siguiendo las indicaciones de esta página [link](https://www.texasheart.org/heart-health/heart-information-center/topics/calculadora-del-indice-de-masa-corporal-imc/) y de acuerdo al índice de imprimir el estado del paciente.

import math

def IMC(peso, estatura):
    '''
    Description: 
        Calcula el indice de masa corporal para un peso, estatura dados
    input:
        peso (numerico): El peso del paciente
        estatura (numerico): La estatura del paciente
    output (numerico):
        El indice de masa corporal del paciente
    '''
    #IMC = peso (kg)/ [estatura (m)]2
    imc = peso / (math.pow(estatura, 2))
    if imc < 18.5:
        print("Peso inferior al normal")
    elif imc < 24.9:
        print("Normal")
    elif imc < 29.9:
        print("Peso superior al normal")
    else:
        print("Obesidad")
    return imc
    
    
peso = float(input("Ingrese el peso(kg) del paciente: "))
estatura = float(input("Ingrese la estatura(mts) del paciente: "))
print(f'El indice de masa corporal del paciente es: {IMC(peso, estatura)}')
