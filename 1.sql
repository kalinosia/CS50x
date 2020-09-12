/*SELECT * FROM table1;
SELECT col1, col2 FROM table1 where col3=value; 
SELECT col1, col2 FROM table1 where col3 IN (SELECT....);

WPISAĆ NA POCZĄTEK -> sqlite3 movies.db

In 1.sql, write a SQL query to list the titles of all movies released in 2008. */
SELECT title FROM movies WHERE year=2008;