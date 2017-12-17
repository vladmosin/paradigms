/* 7 SQL Request*/
SELECT Country.Name 
FROM Country
LEFT JOIN City ON City.CountryCode = Country.Code
GROUP BY City.CountryCode
HAVING (2 * SUM(City.Population) < Country.Population OR City.Population IS NULL) AND Country.Population > 0
ORDER BY Country.Name
