CFLAGS = -Wall -g --std=c++11 -Iinclude 
CC = g++

.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) -c $(CFLAGS) $*.cpp -o $*.o

OBJS = \
       src/Genome.cpp \
       src/Connection.cpp \
       src/Node.cpp \
       src/utilities.cpp \
       src/NEAT.cpp \
       src/InnovationMap.cpp \
       src/options.cpp \
       src/Species.cpp

all: xor and or avg_xor

xor: xor.o $(OBJS:.cpp=.o)
	$(CC) $(CFLAGS) $^ -o xor

avg_xor: avg_xor.o $(OBJS:.cpp=.o)
	$(CC) $(CFLAGS) $^ -o avg_xor

and: and.o $(OBJS:.cpp=.o)
	$(CC) $(CFLAGS) $^ -o and

or: or.o $(OBJS:.cpp=.o)
	$(CC) $(CFLAGS) $^ -o or

run: $(TARGET)
	./$(TARGET)

xor.o: xor.cpp include/NEAT.h

avg_xor.o: avg_xor.cpp include/NEAT.h

or.o: or.cpp include/NEAT.h

and.o: and.cpp include/NEAT.h

utilities.o: src/utilities.cpp include/utilities.h

NEAT.o: src/NEAT.cpp include/NEAT.h

Genome.o: src/Genome.cpp include/Genome.h

Connection.o: src/Connection.cpp include/Connection.h include/utilities.h include/options.h include/Node.h

Node.o: src/Node.cpp include/Node.h include/Connection.h

InnovationMap.o: src/InnovationMap.cpp include/InnovationMap.h

options.o: src/options.cpp include/options.h

Species.o: src/Species.cpp include/Species.h

clean:
	rm -f *.o
	rm -f xor and or avg_xor
	rm -f src/*.o
