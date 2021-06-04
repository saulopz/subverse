#!/bin/sh
clang++ -Wall -fexceptions -std=c++14 \
        -g src/*.cpp com/*.cpp \
        -o subverse \
        -lpthread -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

