# Mitsiu Alejandro Carreño Sarabia E23S-18014
'''
Genere una regresión lineal mediante el dataset que se encuentra disponible en : https://drive.google.com/file/d/1kboEQNTh8yVibxCHj5uo5DW9TLHzB-fx/view?usp=sharing

El objetivo es utilizar  "Open" como X y "Close" como Y. 

Pueden utilizar los siguientes valores para las otras variables : 

learning_rate = 0.040
beta_0 = -0.4
beta_1 = 1.3
'''


import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt

def plot(data, theta1, theta0):
    plt.scatter(data["Open"], data["Close"], s=25, marker="x")

    max_x = np.amax(data["Open"])
    max_y = np.amax(data["Close"])
    plt.axis([0, max_x +2, 0, max_y + 20])

    # line plot
    x = np.arange(0, int(max_x) + 10, 0.1)
    y = theta0 + theta1 * x
    plt.plot(x, y, c='red')

    # create label for information
    line_label = f"y = {round(theta0, 5)} + {round(theta1, 5)}x"
    labels = []
    labels.append("Mitsiu Alejandro Carreño Sarabia E23S-18014")
    labels.append(line_label)

    infostr = '\n'.join(labels)
    plt.text(5, max_y + 20, infostr)
    plt.show()

def reg_lin(x, y):
    reg = LinearRegression().fit(x,y)

    print(f"Coeficiente o intercepto (Tetha 1){reg.coef_}")
    print(f"Intercepto (Tetha 0) {reg.intercept_}")
    return dict(
        theta1= reg.coef_[0], 
        theta0= reg.intercept_
    )

def main():
    data = pd.read_csv("nfx.csv")

    x=np.array(data["Open"]).reshape(-1,1)
    y=data["Close"]
    
    model = reg_lin(x, y)
    print(model)    
    plot(data, model["theta1"], model["theta0"])

main()
