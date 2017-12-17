/* 3 SQL Request*/
SELECT City.Name 
FROM City
JOIN Country ON City.CountryCode = Country.Code
JOIN Capital ON Capital.CityId = City.Id
WHERE Country.Name = 'Malaysia';
