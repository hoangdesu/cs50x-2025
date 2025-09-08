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