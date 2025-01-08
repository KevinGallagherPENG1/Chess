SHELL := cmd.exe
CC=g++
CFLAGS=-Wall -g
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=Vice

all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
<<<<<<< HEAD
	del /Q *.o *.obj $(TARGET)
=======
	del /Q *.o *.obj $(TARGET)

>>>>>>> master
