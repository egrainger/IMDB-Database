# IMDB-Database

CS201 Movie Database

This project is designed to build CRUD records of the users' movie libraries. It will load in the lookup dataset into memory from IMDB's movie database 'title.basics.tsv.gz' (https://datasets.imdbws.com/). Multiple users are allowed to use the application and can resume work on their personal files at a later time.

Before loading this program, please download 'title.basics.tsv.gz' into the same file as the c code and extract it. Utilize this command line code to create a file for just movies:

grep "movie" title.basics.tsv > movie_records.txt

The main code will pull data from movie_records.txt to create the initial movie database.

Information courtesy of IMDb (http://www.imdb.com). Used with permission.