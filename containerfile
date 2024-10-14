FROM docker.io/tensorflow/tensorflow:latest-gpu-jupyter

WORKDIR /tf

RUN pip install seaborn
RUN pip install scipy
RUN pip install scikit-learn
RUN pip install tqdm
RUN pip install scikit-image
RUN pip install sqlalchemy
RUN pip install keras-tuner 
RUN pip install gym
RUN pip install gymnasium
RUN pip install plotly
RUN apt remove -y python3-blinker
RUN pip install mlflow

EXPOSE 8888
