SELECT movies.title
FROM stars
JOIN movies ON stars.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE stars.person_id IN (
    SELECT id FROM people WHERE name IN ('Bradley Cooper', 'Jennifer Lawrence')
)
GROUP BY movies.id
HAVING COUNT(DISTINCT people.id) = 2;