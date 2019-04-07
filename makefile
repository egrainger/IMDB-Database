main:	main.c databaseParse.c avltree.c lower.c
	#wget https://datasets.imdbws.com/title.basics.tsv.gz
	#7z x title.basics.tsv.gz
	#grep "movie" data.tsv > movie_records.txt
	gcc -Wall main.c databaseParse.c avltree.c lower.c -o main
	#make clean

clean:
	rm data.tsv
	rm title.basics.tsv.gz
