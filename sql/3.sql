/* 3 SQL Request*/
select City.Name from Country, City, Capital
where Country.Name = 'Malaysia' and Capital.CityId = City.Id and City.CountryCode = Country.Code;
