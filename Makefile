biblioteka: obsluga.o czytelnik.o main.o
	gcc obsluga.o czytelnik.o main.o -o biblioteka
obsluga.o: obsluga.c
	gcc -c obsluga.c -o obsluga.o
czytelnik.o: czytelnik.c
	gcc -c czytelnik.c -o czytelnik.o
main.o: main.c
	gcc -c main.c -o main.o
