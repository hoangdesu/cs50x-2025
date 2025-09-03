SELECT * FROM songs;
SELECT * FROM artists;

-- 1
SELECT name FROM songs;

-- 2
SELECT name --, tempo 
FROM songs
ORDER BY tempo;

-- 3
SELECT name --, duration_ms
FROM songs
ORDER BY duration_ms DESC
LIMIT 5;

-- 4
SELECT name --, danceability, energy, valence
FROM songs
WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;

-- 5
SELECT AVG(energy)
FROM songs;

-- 6: use aliases for song.name and artists.name
SELECT songs.name AS song_name, artist_id, artists.id, artists.name AS artist_name
FROM songs
JOIN artists
ON songs.artist_id = artists.id;

SELECT songs.name -- AS song_name, artist_id, artists.id, artists.name AS artist_name
FROM songs
JOIN artists
ON songs.artist_id = artists.id
WHERE artists.name LIKE 'post malone';

-- another way
SELECT name
FROM songs
WHERE artist_id =
(
    SELECT id
    FROM artists
    WHERE name = 'Post Malone'
);


-- 7
SELECT songs.name AS song_name, artist_id, artists.id, artists.name AS artist_name, energy
FROM songs
JOIN artists
ON songs.artist_id = artists.id
WHERE artists.name LIKE 'Drake';

SELECT AVG(energy)
FROM songs
JOIN artists
ON songs.artist_id = artists.id
WHERE artists.name LIKE 'Drake';

-- 8
SELECT name
FROM songs
WHERE name LIKE '%feat.%';