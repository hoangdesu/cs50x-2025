-- 1: list the titles of all movies released in 2008
SELECT title
FROM movies
WHERE year = 2008;

-- 2: determine the birth year of Emma Stone
SELECT birth
FROM people
WHERE name LIKE 'emma stone';

-- 3: list the titles of all movies with a release date on or after 2018, in alphabetical order
SELECT title
FROM movies
WHERE year >= 2018
ORDER BY title;

-- 4: determine the number of movies with an IMDb rating of 10.0
SELECT title, rating -- COUNT(*)
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id
WHERE ratings.rating = 10.0;

SELECT COUNT(*)
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id
WHERE ratings.rating = 10.0;

-- 5: list the titles and release years of all Harry Potter movies, in chronological order.
SELECT title, year
FROM movies
WHERE title LIKE '%harry potter%'
ORDER BY year;

-- 6: determine the average rating of all movies released in 2012
SELECT title, year, rating
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id
    AND movies.year = 2012;
    
SELECT AVG(ratings.rating)
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id
    AND movies.year = 2012;
    
-- 7: list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title
SELECT title, ratings.rating
FROM movies
INNER JOIN ratings
ON movies.id = ratings.movie_id
WHERE movies.year = 2010
ORDER BY ratings.rating ASC, title ASC;

--Note: To also order alphabetically by title when ratings are the same, you just add title ASC as a secondary sort key
