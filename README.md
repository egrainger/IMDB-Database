# IMDB-Database

CS201 Movie Database
This project is designed to build CRUD records of the users' movie libraries. It will load in the lookup dataset into memory from IMDB's movie database 'title.basics.tsv.gz' (https://datasets.imdbws.com/).

Multiple users are allowed to use the application and can resume work on their personal files at a later time provided they use the same username each time.

Before executing make, please ensure wget and 7zip are installed in your work environment as the makefile requires both to download and extract the files from IMDB. 

All the titles, specifically movie titles, will be placed into a text file called movie_records.txt. Please do not remove this from your working area. The main code will pull data from movie_records.txt to create your movie database, so it is imperative that you have this file in the same directory as the rest of the source and header files.

Code Breakdown: 

This code implements AVL trees as a way to store and sort structs of movie objects based on a unique manipulation of the movie title and release year. The reason for choosing an AVL tree rests on the fact tha insertion, deletion, and search functions are at most O(log n) time. This is extremely important as the database contains 500,000+ titles.   

This code supports adding a movie to your database, updating the purchase date or format in which you own the movie, retrieving a particular movie from your database, and deleting a movie from your database. Your final user AVL tree at the exit condition will be printed to your “username.txt” file. This will then be read in each time you load the code and type in your username that way you can resume work later. 

Note: The release year had to be included due to initial findings that duplicates would not be stored. This fix now assumes that no two movies with the same title are released the same year. 
Information courtesy of IMDb (http://www.imdb.com). Used with permission.
