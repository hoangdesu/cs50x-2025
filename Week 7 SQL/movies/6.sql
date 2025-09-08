SELECT AVG(ratings.rating)
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id
    AND movies.year = 2012;