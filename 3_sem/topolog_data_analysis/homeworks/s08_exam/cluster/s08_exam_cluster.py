# Mitsiu Alejandro Carreño Sarabia E23S-18014
'''
Utilizando el siguiente set de datos : 

https://drive.google.com/file/d/1kboEQNTh8yVibxCHj5uo5DW9TLHzB-fx/view?usp=sharing

Realice un calculo para determinar el numero de clusters a ser implementado mediante el metodo de 
Elbow

Una vez establecido el numero de clusters a ser implementado utilice  matplotlib.pyplot para poder graficar el comportamiento de los clusters. 
'''

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

def elbow(max_iter, n_init, data):
    wcss = []
    for i in range(1, 10):
        kmeans = KMeans(
            n_clusters=i,
            init = 'k-means++', 
            max_iter = max_iter, 
            n_init = n_init)
        kmeans.fit(data)
        wcss.append(kmeans.inertia_)

    plt.plot(range(1, 10), wcss)
    plt.title("Elbow method")
    plt.xlabel("Número de grupos")
    plt.ylabel("Suma de cuadrados en grupo")
    plt.show()

def cluster(k, max_iter, n_init, data):
    kmeans=KMeans(n_clusters= k, init = 'k-means++', max_iter = max_iter, n_init = n_init, random_state = 0)
    y_kmeans = kmeans.fit_predict(data)

    colors = ["red", "green", "yellow"]; # easter egg 420 will my teacher find this?
    for i in range(0, k):
        #print(colors[i])
        plt.scatter(data[y_kmeans == i, 0], data[y_kmeans == i,1],s = 100, c=colors[i], label = " ".join(["Cluster", str(i+1)]))
    '''
    plt.scatter(data[y_kmeans == 0, 0], data[y_kmeans == 0,1],s = 100, c='red', label = 'Cluster 1')
    plt.scatter(data[y_kmeans == 1, 0], data[y_kmeans == 1,1],s = 100, c='cyan', label = 'Cluster 2')
    plt.scatter(data[y_kmeans == 2, 0], data[y_kmeans == 2,1],s = 100, c='green', label = 'Cluster 3')
    '''

    plt.scatter(kmeans.cluster_centers_[:,0], kmeans.cluster_centers_[:,1], s = 25, c = 'black', label = 'Centroids')

    plt.title('Clusters de open')
    plt.xlabel('Open')
    plt.ylabel('Close')
    plt.legend()
    plt.show()

def main():
    data = pd.read_csv("nfx.csv")

    x=np.array(data["Open"]).reshape(-1,1)
    y=data["Close"]
    
    #model = reg_lin(x, y)
    cluster_data = data.loc[:, ["Open", "Close"]].values
    elbow(300, 3, cluster_data)
    k = 3
    
    cluster(k, 300, 3, cluster_data)


main()
