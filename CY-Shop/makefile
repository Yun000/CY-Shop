OBJS	= common.o customer.o management_system.o product.o purchase_system.o main.o store.o
SOURCE	= common.c customer.c management_system.c product.c purchase_system.c main.c store.c
HEADER	= common.h customer.h management_system.h product.h purchase_system.h store.h
OUT	= main
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

common.o: common.c
	$(CC) $(FLAGS) common.c 

customer.o: customer.c
	$(CC) $(FLAGS) customer.c 

management_system.o: management_system.c
	$(CC) $(FLAGS) management_system.c 

product.o: product.c
	$(CC) $(FLAGS) product.c 

purchase_system.o: purchase_system.c
	$(CC) $(FLAGS) purchase_system.c 

main.o: main.c
	$(CC) $(FLAGS) main.c 

store.o: store.c
	$(CC) $(FLAGS) store.c 

clean:
	rm -f $(OBJS) $(OUT)