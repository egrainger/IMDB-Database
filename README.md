# IMDB-Database

CS201 Movie Database

This project is designed to build CRUD records of the users' movie libraries. It will load in the lookup dataset into memory from IMDB's movie database 'title.basics.tsv.gz' (https://datasets.imdbws.com/). Mul\
tiple users are allowed to use the application and can resume work on their personal files at a later time.

Before loading this program, please download 'title.basics.tsv.gz' into the same file as the c code and extract it. To do so, you will need a program capable of unzipping such a zipped file. I recommend 7zip o\
r WinZip, but 7zip is free, so do with that information what you will. Please make sure the name of your extracted files is 'title.basics.tsv' for the command line prompt below.

Utilize this command line code to create a file for just movies:

grep "movie" title.basics.tsv > movie_records.txt

The main code will pull data from movie_records.txt to create the initial movie database, so it is imperative that you have this file in the same directory as the rest of the source and header files.

Information courtesy of IMDb (http://www.imdb.com). Used with permission.
