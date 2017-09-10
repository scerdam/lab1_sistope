all: main.c
	gcc -o ejecutable main.c
exe1:
	./ejecutable -i input.txt -n 10 -c 60 -p AAAA -d
all1: main.c 
	gcc -o ejecutable main.c
	./ejecutable -i input.txt -n 10 -c 60 -p AAAA -d
