SELECT title
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