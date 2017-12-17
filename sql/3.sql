/* 3 SQL Request*/
SELECT City.Name from City, Capital
JOIN Country ON City.CountryCode = Country.Code
WHERE Country.Name = 'Malaysia' AND Capital.CityId = City.Id;
