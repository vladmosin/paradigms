/* 6 SQL Request*/
SELECT City.Name, City.Population, Country.Population 
FROM City
JOIN Country ON City.CountryCode = Country.Code
ORDER BY (cast((City.Population) AS FLOAT) / Country.Population) desc, City.Name desc
LIMIT 20;
