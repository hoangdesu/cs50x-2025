SELECT * from favorites;

SELECT language, problem FROM favorites;

SELECT COUNT(*) FROM favorites;

SELECT DISTINCT language FROM favorites;

SELECT COUNT(DISTINCT language) FROM favorites;

SELECT COUNT(*) FROM favorites WHERE language = 'C';

SELECT language, COUNT(*) 
FROM favorites 
GROUP BY language;

SELECT language, COUNT(*) AS Counts
FROM favorites 
GROUP BY language
ORDER BY Counts DESC;

SELECT COUNT(*) 
FROM favorites 
WHERE language = 'C' 
    AND (problem = 'Hello, World' OR problem = 'Hello, It''s Me');

SELECT COUNT(*), problem, language FROM favorites WHERE language = 'C' AND problem LIKE 'Hello, %';

SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY n DESC LIMIT 2;


INSERT INTO favorites (language, problem) VALUES('SQL', '50Ville');

DELETE FROM favorites WHERE Timestamp IS NULL;


