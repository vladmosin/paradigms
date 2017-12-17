/* 4 SQL Request*/
SELECT Country.Name, COUNT(City.Name) AS BigCityCnt FROM Country
LEFT JOIN City ON Country.Code = City.CountryCode and City.Population > 1000000
GROUP BY Country.Code
ORDER BY BigCityCnt desc, Country.Name;
