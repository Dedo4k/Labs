all:
	clear
	gcc -shared -fPIC mylib.c -o lib.so -lrt
	gcc -c main.c
	g++ -rdynamic main.o -o main -ldl -lpthread
	./main