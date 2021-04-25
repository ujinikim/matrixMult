CC = g++
CFLAGS = -g -std=c++11
TARGET = matrixMult
LIBRARIES = -lpthread
EXECUTABLES = matrixMult

#creating executable


all: matrixMult



# Clean the directory
clean: 
	rm -f $(EXECUTABLES)  *.o