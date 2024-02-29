# pip install hausdorff
# pip install numpy
import numpy as np
import csv
from hausdorff import hausdorff_distance

with open('testCleaned.csv', 'r') as file:
    csv_reader = csv.DictReader(file)
    data = [row for row in csv_reader]

#print(data)

for element in data:
    try:
        num_of_loan = int(element['Num_of_Loan'])
        interest_date = int(element['Interest_Rate'])

        num_bank_accounts = int(element['Num_Bank_Accounts'])
        num_credit_card = int(element['Num_Credit_Card'])

        age = int(element['Age'])
        annual_income = float(element['Annual_Income'])
        monthly_income = float(element['Monthly_Inhand_Salary'])
        change_credit_limit = float(element['Changed_Credit_Limit'])

        entry_x = np.array([[num_of_loan,interest_date],[num_bank_accounts,num_credit_card]])

        entry_y = np.array([[annual_income,monthly_income],[age,change_credit_limit]])

        print(f"Hausdorff distance test: {hausdorff_distance(entry_x, entry_y, distance='euclidean')}")
    except:
        continue







#ID unico SSN 
# Num_of_Loan
# Interest_Rate
# Num_Bank_Accounts    
# Num_Credit_Card
    
# Age
# Annual_Income
# Monthly_Inhand_Salary
# Changed_Credit_Limit

# Test computation of Hausdorff distance with different base distances
# manhattan : se define la distancia taxicab (del taxi o de Manhattan) como la suma de los valores absolutos de las diferencias de sus coordenadas

#print(f"Hausdorff distance test: {hausdorff_distance(X, Y, distance='manhattan')}")

# eucledian :  es la longitud del segmento de recta entre ellos
#print(f"Hausdorff distance test: {hausdorff_distance(X, Y, distance='euclidean')}")

# chebyshev : definida en un espacio vectorial donde la distancia entre dos puntos (representados por sus vectores) es la mayor de sus diferencias a lo largo de cualquiera de sus dimensiones coordenadas
#print(f"Hausdorff distance test: {hausdorff_distance(X, Y, distance='chebyshev')}")

# coseno: es una medida de la similitud existente entre dos vectores en un espacio que posee un producto interior con el que se evalúa el valor del coseno del ángulo comprendido entre ellos
#print(f"Hausdorff distance test: {hausdorff_distance(X, Y, distance='cosine')}")

# For haversine, use 2D lat, lng coordinates
def rand_lat_lng(N):
    lats = np.random.uniform(-90, 90, N)
    lngs = np.random.uniform(-180, 180, N)
    return np.stack([lats, lngs], axis=-1)
        
X = rand_lat_lng(100)
Y = rand_lat_lng(250)
#print("Hausdorff haversine test: {0}".format( hausdorff_distance(X, Y, distance="haversine") ))

