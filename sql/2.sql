/* 2 SQL Request*/
SELECT Country.Name, Rate 
FROM LiteracyRate 
JOIN Country ON LiteracyRate.CountryCode = Country.Code
GROUP BY CountryCode
HAVING Max(Year)
ORDER BY Rate desc 
LIMIT 1;
