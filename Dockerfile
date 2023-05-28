FRoM ubuntu:latest

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get -y install gcc g++ 
RUN apt-get -y install qtcreator
RUN apt-get -y install build-essential
RUN apt install qtbase5-dev qt5-qmake -y
RUN apt-get install -y python3-html5-parser

COPY . /Desktop/HtmlEditor

WORKDIR /Desktop/HtmlEditor

RUN qmake HTML_editor.pro 

RUN make
