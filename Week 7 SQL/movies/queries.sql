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

-- 5: list the titles and release years of all Harry Potter movies, in chronological order
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
ORDER BY ratings.rating DESC, title ASC;

--Note: To also order alphabetically by title when ratings are the same, you just add title ASC as a secondary sort key

-- 8: list the names of all people who starred in Toy Story
-- approach: using multiple joins
SELECT people.name
FROM movies
JOIN stars
ON movies.id = stars.movie_id
JOIN people
ON people.id = stars.person_id
WHERE title LIKE 'toy story';

-- approach (BEST): joining stars with people table
SELECT people.name
FROM stars
JOIN people
ON stars.person_id = people.id
WHERE movie_id = (
    SELECT id
    FROM movies
    WHERE title LIKE 'toy story'
);

-- approach: using people as main table
/*
1. get id of toy story
2. get all the id of stars in the movie
3. get the name of those stars
*/
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id = (
        SELECT id
        FROM movies
        WHERE title LIKE 'toy story'
    )
);

-- 9: list the names of all people who starred in a movie released in 2004, ordered by birth year
SELECT *
FROM movies
WHERE year = 2004;

SELECT *
FROM stars
WHERE person_id IN (
    SELECT id
    FROM movies
    WHERE year = 2004
);

-- approach (faster): subquery
SELECT DISTINCT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT id
        FROM movies
        WHERE year = 2004
    )        
)
ORDER BY birth;

-- approach: using joins
SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.year = 2004
ORDER BY people.birth;

-- 10: list the names of all people who have directed a movie that received a rating of at least 9.0
SELECT name
FROM people
WHERE id IN (
    --IDs of directors of those movies
    SELECT person_id
    FROM directors
    WHERE movie_id IN (
        --IDs of movies with rating >= 9.0
        SELECT movie_id
        FROM ratings
        WHERE rating >= 9.0
    )
);

-- 11: list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT title --, rating
FROM ratings
JOIN movies
ON ratings.movie_id = movies.id
WHERE movie_id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id = (
        SELECT id
        FROM people
        WHERE name LIKE 'chadwick boseman'
    )
)
ORDER BY rating DESC
LIMIT 5;

-- 12: list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred
SELECT id
FROM people
WHERE name IN ('Bradley Cooper', 'Jennifer Lawrence');

-- approach 1: joining multiple tables + aggregate data
SELECT movies.title
FROM stars
JOIN movies ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name IN ('Bradley Cooper', 'Jennifer Lawrence')
/*WHERE stars.person_id IN (
    SELECT id FROM people WHERE name IN ('Bradley Cooper', 'Jennifer Lawrence')
)*/
GROUP BY movies.id
HAVING COUNT(DISTINCT people.id) = 2;
;

--using index to optimize the query
CREATE INDEX idx_people_name ON people(name);

SELECT name, tbl_name, sql
FROM sqlite_master
WHERE type = 'index';


EXPLAIN QUERY PLAN
SELECT DISTINCT m.title
FROM movies m
JOIN stars s1 ON m.id = s1.movie_id
JOIN people p1 ON s1.person_id = p1.id
JOIN stars s2 ON m.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id
WHERE p1.name = 'Bradley Cooper'
  AND p2.name = 'Jennifer Lawrence';

-- approach 2: using self-joins
SELECT title
FROM movies
JOIN stars s1 ON movies.id = s1.movie_id
JOIN stars s2 ON movies.id = s2.movie_id
WHERE s1.person_id = (
    SELECT id
    FROM people
    WHERE name = 'Bradley Cooper'
) AND s2.person_id = (
    SELECT id
    FROM people
    WHERE name = 'Jennifer Lawrence'
);


-- approach 3 (BEST): while seems subtle, this query VASTLY improves the lookup time, from 3.2s down to 0.2s
-- this is because the looking up the id is much faster since the id is indexed
SELECT movies.title
FROM stars
JOIN movies ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE stars.person_id IN (
    SELECT id FROM people WHERE name IN ('Bradley Cooper', 'Jennifer Lawrence')
)
GROUP BY movies.id
HAVING COUNT(DISTINCT people.id) = 2;

-- 13: list the names of all people who starred in a movie in which Kevin Bacon also starred
SELECT id
FROM people
WHERE name = 'Kevin Bacon' AND birth = 1958;

SELECT movie_id
FROM stars
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'Kevin Bacon' AND birth = 1958
);


SELECT DISTINCT person_id
FROM stars
WHERE movie_id IN (
    SELECT movie_id
    FROM stars
    WHERE person_id = (
        SELECT id
        FROM people
        WHERE name = 'Kevin Bacon' AND birth = 1958
    )
) AND person_id != (
    SELECT id
    FROM people
    WHERE name = 'Kevin Bacon' AND birth = 1958
);

-- approach (best): subqueries
SELECT name
FROM people
WHERE id IN (
    SELECT DISTINCT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT movie_id
        FROM stars
        WHERE person_id = (
            SELECT id
            FROM people
            WHERE name = 'Kevin Bacon' AND birth = 1958
        )
    ) AND person_id != (
        SELECT id
        FROM people
        WHERE name = 'Kevin Bacon' AND birth = 1958
    )
);

-- similar subquery approach with temp table (~0.3s)
WITH kevin_id AS (
    SELECT id
    FROM people
    WHERE name = 'Kevin Bacon' AND birth = 1958
)
SELECT name
FROM people
WHERE id IN (
    SELECT DISTINCT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT movie_id
        FROM stars
        WHERE person_id = (SELECT id FROM kevin_id)
    )
    AND person_id != (SELECT id FROM kevin_id)
);

--approach: joining tables (~2s)
SELECT DISTINCT p.name
FROM people p
JOIN stars s ON p.id = s.person_id
JOIN stars ks ON s.movie_id = ks.movie_id
JOIN people kb ON ks.person_id = kb.id
WHERE kb.name = 'Kevin Bacon'
  AND kb.birth = 1958
  AND p.id != kb.id;
  
-- approach: using Exists -> very slow (~12s)
SELECT DISTINCT p.name
FROM people p
WHERE EXISTS (
    SELECT 1
    FROM stars s1
    JOIN stars s2 ON s1.movie_id = s2.movie_id
    JOIN people kb ON s2.person_id = kb.id
    WHERE s1.person_id = p.id
      AND kb.name = 'Kevin Bacon'
      AND kb.birth = 1958
      AND p.id != kb.id
);





