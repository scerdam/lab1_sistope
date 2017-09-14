compile: main.c
	gcc -o ejecutable main.c
exe:
	./ejecutable -i input.txt -n 10 -c 60 -p AAAA -d
all: main.c
	gcc -o ejecutable main.c
	./ejecutable -i ejemplo1.txt -n 5 -c 60 -p AAAA -d
