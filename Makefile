CC = g++
LIBS = `allegro-config --libs`
CFLAGS = -Wall -pedantic -O2 -std=c++14
program07: main.o grafika.o
		$(CC) -o program07 main.o grafika.o $(CFLAGS) $(LIBS)
main.o:	main.cpp grafika.h
		$(CC) -o main.o -c main.cpp $(CFLAGS)
grafika.o:	grafika.cpp grafika.h
		$(CC) -o grafika.o -c grafika.cpp $(CFLAGS)
clean:
		rm *.o
