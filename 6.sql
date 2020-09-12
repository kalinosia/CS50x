/*write a SQL query to determine the average rating of all movies released in 2012. */

SELECT SUM(rating)/COUNT(movie_id) FROM ratings 
JOIN movies 
ON movies.id=ratings.movie_id
WHERE year=2012;