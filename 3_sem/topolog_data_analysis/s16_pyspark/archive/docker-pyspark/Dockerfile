FROM ubuntu:latest
LABEL maintainer="masroorh"

# Set environment variables
ENV VIRTUAL_ENV=/opt/venv
ENV PATH="$VIRTUAL_ENV/bin:$PATH"

# Install OpenJDK 8
RUN \
  apt-get update && \
  apt-get install -y openjdk-8-jdk && \
  rm -rf /var/lib/apt/lists/*

# Install Python
RUN \
    apt-get update && \
    apt-get install -y python3 python3-dev python3-pip python3-venv && \
    rm -rf /var/lib/apt/lists/*

# Install virtualenv and create a virtual environment
RUN python3 -m venv $VIRTUAL_ENV

# Upgrade pip and install required packages within the virtual environment
RUN $VIRTUAL_ENV/bin/pip install --upgrade pip && \
    $VIRTUAL_ENV/bin/pip install numpy && \
    $VIRTUAL_ENV/bin/pip install pyspark

# Define working directory
COPY . .

# Define default command
CMD ["bash"]