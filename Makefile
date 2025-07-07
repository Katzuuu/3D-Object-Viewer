CC = g++
CFLAGS = -Iinclude -I/usr/include/GLFW
LDFLAGS = -lglfw -ldl -lGL -lm

SRC = src/main.cpp src/glad.c
TARGET = app

default:
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(TARGET)
