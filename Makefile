CC = g++
FLAGS = -g -ldl

TARGET = a.out


all: a.out

$(TARGET): 
	$(CC) $(FLAGS) test.cpp

clean:
	rm -f $(TARGET) *.o
