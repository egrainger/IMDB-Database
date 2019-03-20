all:	main.c databaseParse.c
	gcc -Wall main.c databaseParse.c -o main
