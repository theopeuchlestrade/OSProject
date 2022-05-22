FROM ubuntu:latest
RUN mkdir -p /project/ 
ADD exo1 /project/exo1
ADD exo2 /project/exo2
ADD Makefile /project/Makefile
WORKDIR /project/ 
RUN  apt update
RUN apt install gcc make nano -y 
CMD make