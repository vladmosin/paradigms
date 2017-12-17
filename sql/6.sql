/* 6 SQL Request*/
SELECT City.Name, City.Population, Country.Population 
FROM City
JOIN Country ON City.CountryCode = Country.Code
ORDER BY (CAST((City.Population) AS FLOAT) / Country.Population) DESC, City.Name DESC
LIMIT 20;
