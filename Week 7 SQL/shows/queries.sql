SELECT * FROM ratings LIMIT 10;

SELECT * FROM shows LIMIT 10;

-- subquery problem: no join so can't show the actual rating
SELECT *
FROM shows
WHERE id IN (
    SELECT show_id
    FROM ratings
    WHERE rating >= 6.0
    LIMIT 10
);

-- using joins: can use columns in ratings table e.g. rating
SELECT s.title, r.rating
FROM shows s
JOIN ratings r ON s.id = r.show_id
WHERE r.rating >= 6.0
LIMIT 10;

SELECT title FROM shows
WHERE id IN (
  SELECT show_id FROM genres
  WHERE genre = 'Comedy'
  LIMIT 10
);

SELECT * FROM shows
JOIN genres
ON shows.id = genres.show_id
--WHERE id = 63881;
WHERE shows.title LIKE 'catweazle';

-- nested queries
SELECT name FROM people WHERE id IN
    (SELECT person_id FROM stars WHERE show_id = 
        (SELECT id FROM shows WHERE title = 'The Office' AND year = 2005));
    
SELECT title FROM shows WHERE id IN 
    (SELECT show_id FROM stars WHERE person_id = 
        (SELECT id FROM people WHERE name = 'Steve Carell'));
        
-- old-style (implicit) join syntax
SELECT title
FROM shows, stars, people
WHERE shows.id = stars.show_id
  AND people.id = stars.person_id
  AND name = 'Steve Carell';
  
-- modern verion: explicit joins
SELECT title
FROM shows
JOIN stars ON shows.id = stars.show_id
JOIN people ON people.id = stars.person_id
WHERE people.name = 'Steve Carell';

-- Indexes: speed up queries
SELECT * FROM shows WHERE title = 'The Office';

-- creating index:
CREATE INDEX title_index ON shows (title);

-- show indexes
SELECT name, tbl_name, sql
FROM sqlite_master
WHERE type = 'index';

-- drop index
DROP INDEX IF EXISTS title_index;

CREATE INDEX name_index ON people (name);
CREATE INDEX person_index ON stars (person_id);

DROP INDEX IF EXISTS name_index;
DROP INDEX IF EXISTS person_index;
