test : main.o Account.o Buy.o
	gcc -o test main.o Account.o Buy.o

Main.o : Main.c
	gcc -o main.o -c main.c

Account.o : ./Source/Account.c
	gcc -o Account.o -c ./Source/Account.c