CFLAGS = -Wall -g --std=c++11 -Iinclude 
CC = g++

.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) $*.cpp -o $*.o

OBJS = \
       main.cpp \
       src/Genome.cpp \
       src/Connection.cpp \
       src/Node.cpp \
       src/utilities.cpp \
       src/NEAT.cpp \
       src/InnovationMap.cpp

TARGET = test

default: $(TARGET)

$(TARGET): $(OBJS:.cpp=.o)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

main.o: main.cpp include/NEAT.h

utilities.o: src/utilities.cpp include/utilities.h

NEAT.o: src/NEAT.cpp include/NEAT.h

Genome.o: src/Genome.cpp include/Genome.h

Connection.o: src/Connection.cpp include/Connection.h include/utilities.h include/options.h include/Node.h

Node.o: src/Node.cpp include/Node.h include/Connection.h

InnovationMap.o: src/InnovationMap.cpp include/InnovationMap.h

clean:
	rm -f main.o
	rm -f src/*.o
	rm -f $(TARGET)
