-- Keep a log of any SQL queries you execute as you solve the mystery.

-- .schema

-- the theft took place on July 28, 2024 on Humphrey Street
SELECT *
FROM crime_scene_reports
WHERE (year = 2024 AND month = 7 AND day = 28) 
    AND street = 'Humphrey Street'
    AND description LIKE '%CS50 duck%'
;
    
-- description: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

--crime_scene_reports -> interviews

SELECT *
FROM interviews
WHERE (year = 2024 AND month = 7 AND day = 28)
    AND transcript LIKE '%bakery%'
;


/* => transcripts: [
    Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.,
    
    I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.,
    
    As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
]*/


SELECT *
FROM bakery_security_logs
WHERE (year = 2024 AND month = 7 AND day = 28)
    AND hour = 10
--    AND minute > 15 + 5 AND minute <= 15 + 10 -- 10:15am + 10m ~ 10:25am => problem: cannot assume 15+5
    AND minute BETWEEN 15 AND 25
    AND activity = 'exit'
;

/*=> sus license_plate = [
    5P2BI95
    94KL13X
    6P58WS2
    4328GD8
    G412CB7
    L93JTIZ
    322W7JE
    0NTHK55
]*/


SELECT *
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE (year = 2024 AND month = 7 AND day = 28)
        AND hour = 10
        AND minute BETWEEN 15 AND 25
        AND activity = 'exit'
    )
;

/* => sus people = [
    221103	Vanessa	(725) 555-4692   2963008352	5P2BI95
    243696	Barry	(301) 555-4174	    7526138472	6P58WS2
    396669	Iman	(829) 555-5269	    7049073643	L93JTIZ    <<
    398010	Sofia	(130) 555-0289	    1695452385	G412CB7
    467400	Luca	(389) 555-5198	    8496433585	4328GD8    <<
    514354	Diana	(770) 555-1861	    3592750733	322W7JE    <<
    560886	Kelsey	(499) 555-9472	    8294398571	0NTHK55    <<
    686048	Bruce	(367) 555-5533	    5773159633	94KL13X    <<
]*/


SELECT *
FROM atm_transactions
WHERE (year = 2024 AND month = 7 AND day = 28)
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
;


-- matching transactions with accounts
SELECT *
FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
WHERE account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE (year = 2024 AND month = 7 AND day = 28)
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
);

/*=> accounts = [
    49610011	686048	2010	686048	Bruce	(367) 555-5533	5773159633	94KL13X    <<<
    26013199	514354	2012	514354	Diana	(770) 555-1861	3592750733	322W7JE    <<<
    16153065	458378	2012	458378	Brooke	(122) 555-4581	4408372428	QX4YZN3
    28296815	395717	2014	395717	Kenny	(826) 555-1652	9878712108	30G67EN
    25506511	396669	2014	396669	Iman	(829) 555-5269	7049073643	L93JTIZ    <<<
    28500762	467400	2014	467400	Luca	(389) 555-5198	8496433585	4328GD8    <<<
    76054385	449774	2015	449774	Taylor	(286) 555-6063	1988161715	1106N58
    81061156	438727	2018	438727	Benista	(338) 555-6650	9586786673	8X428L0
]*/


-- => sus = [Diana, Iman, Bruce, Luca]


-- the earliest flight out of Fiftyville TOMORROW (JUL 29)
SELECT *
FROM flights
WHERE (year = 2024 AND month = 7 AND day = 29)
ORDER BY hour, minute
;

/* => {
    flight_id: 36, 
    orgin_airport_id: 8,
    destination_airport_id: 4,
    time: 8:20am
    date: 7/29 (Jul 29)
}*/

SELECT *
FROM airports
WHERE id = 8 OR id = 4
;

-- Flight:
-- FROM: 8	CSF	Fiftyville Regional Airport    Fiftyville
-- TO:   4	LGA	LaGuardia Airport	           New York City


SELECT passport_number
FROM passengers
WHERE flight_id = (
    SELECT id
    FROM flights
    WHERE (year = 2024 AND month = 7 AND day = 29)
    ORDER BY hour, minute
    LIMIT 1
);

/* => passport_numbers = [
    7214083635
    1695452385
    5773159633
    1540955065
    8294398571 <-- sus: Kelsey
    1988161715
    9878712108
    8496433585
]*/


--matching the license plate with passport numbers
SELECT *
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE (year = 2024 AND month = 7 AND day = 28)
        AND hour = 10
        AND minute BETWEEN 15 AND 25
        AND activity = 'exit'
) AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT id
        FROM flights
        WHERE (year = 2024 AND month = 7 AND day = 29)
        ORDER BY hour, minute
        LIMIT 1
    )
);

-- => sú: 560886	Kelsey	(499) 555-9472	8294398571	0NTHK55
--=> new sú = [Sofia, Luca, Kelsey, Bruce]



-- getting list of people involved in calls
SELECT *
FROM phone_calls
WHERE (year = 2024 AND month = 7 AND day = 28)
AND duration < 60
;

SELECT *
FROM phone_calls calls
JOIN people caller ON caller.phone_number = calls.caller
JOIN people receiver ON receiver.phone_number = calls.receiver
WHERE (year = 2024 AND month = 7 AND day = 28)
AND duration < 60
;


SELECT 
--    *
    calls.caller, 
    calls.receiver,
    caller.name AS caller_name,
    receiver.name AS receiver_name
FROM phone_calls calls
JOIN people caller ON caller.phone_number = calls.caller
JOIN people receiver ON receiver.phone_number = calls.receiver
WHERE (year = 2024 AND month = 7 AND day = 28)
AND duration < 60
;

/*=> sus callers: [
    Sofia
    Kelsey <- sus
    Bruce
    Kelsey
    Taylor
    Diana < sus
    Carina
    Kenny
    Benista
]*/


/*
Calls:
Kelsey -> Larry
Kelsey -> Melissa
Diana -> Philip
*/



SELECT *
FROM people
WHERE name IN (
    SELECT name
    FROM interviews
    WHERE (year = 2024 AND month = 7 AND day = 28)
        AND transcript LIKE '%bakery%'
);


SELECT *
FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT id
        FROM flights
        WHERE (year = 2024 AND month = 7 AND day = 29)
        ORDER BY hour, minute
        LIMIT 1
    )
);

/*=> passengers: [
    Kenny
    Sofia    <<
    Taylor
    Luca     <<
    Kelsey   <<
    Edward    
    Bruce    <<
    Doris
]*/


SELECT *
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE people.name IN ('Larry', 'Melissa');



SELECT * 
FROM bank_accounts
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'Melissa'
);

--=> Melissa doesn't have a bank account


SELECT * 
FROM bank_accounts
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'Robin'
);

-- => Robin has a bank account

SELECT *
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE people.name = 'Robin';





-- big ass query 

SELECT DISTINCT name
FROM bank_accounts
JOIN people ON bank_accounts.person_id = people.id
JOIN phone_calls calls ON calls.caller = people.phone_number
/*JOIN people caller ON caller.phone_number = calls.caller
JOIN people receiver ON receiver.phone_number = calls.receiver*/
WHERE account_number IN (
--    get people making transaction on crime date
    SELECT account_number
    FROM atm_transactions
    WHERE (year = 2024 AND month = 7 AND day = 28)
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
) AND people.name IN (
--    get the owners of the car leaving the scene
    SELECT name
    FROM people
    WHERE license_plate IN (
--        get the license plate of the cars leaving the scene
        SELECT license_plate
        FROM bakery_security_logs
        WHERE (year = 2024 AND month = 7 AND day = 28)
            AND hour = 10
            AND minute BETWEEN 15 AND 25
            AND activity = 'exit'
    )
) AND people.passport_number IN (
--    get passport number of people boarding the flight
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT id
        FROM flights
        WHERE (year = 2024 AND month = 7 AND day = 29)
        ORDER BY hour, minute
        LIMIT 1
    )
) AND name IN (
--    matching the caller name
    SELECT caller.name
    FROM phone_calls calls
    JOIN people caller ON caller.phone_number = calls.caller
    JOIN people receiver ON receiver.phone_number = calls.receiver
    WHERE (year = 2024 AND month = 7 AND day = 28)
    AND duration < 60
)
;

-- => BRUCE I FOUND YOU!!!


-- chatgpt solution: cleaner and easy to read
SELECT DISTINCT p.name
FROM people p
JOIN bank_accounts ba ON ba.person_id = p.id
JOIN atm_transactions atm ON atm.account_number = ba.account_number
JOIN bakery_security_logs bsl ON bsl.license_plate = p.license_plate
JOIN passengers ps ON ps.passport_number = p.passport_number
JOIN flights f ON f.id = ps.flight_id
JOIN phone_calls c ON c.caller = p.phone_number
JOIN people r ON r.phone_number = c.receiver
WHERE 
    -- atm withdrawal on crime date/location
    atm.year = 2024 AND atm.month = 7 AND atm.day = 28
    AND atm.atm_location = 'Leggett Street'
    AND atm.transaction_type = 'withdraw'
    
    -- car exiting bakery scene
    AND bsl.year = 2024 AND bsl.month = 7 AND bsl.day = 28
    AND bsl.hour = 10 AND bsl.minute BETWEEN 15 AND 25
    AND bsl.activity = 'exit'
    
    -- flight on next day (only the earliest one)
    AND f.year = 2024 AND f.month = 7 AND f.day = 29
    AND f.id = (
        SELECT id FROM flights
        WHERE year = 2024 AND month = 7 AND day = 29
        ORDER BY hour, minute
        LIMIT 1
    )

    -- short phone call on crime date
    AND c.year = 2024 AND c.month = 7 AND c.day = 28
    AND c.duration < 60;

