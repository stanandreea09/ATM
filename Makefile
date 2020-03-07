build:atm.h atm.c main.c
	gcc atm.h atm.c main.c -o atm
run:atm.h atm.c main.c
	gcc atm.h atm.c main.c -o atm
	./atm
clean:
	rm -f atm
