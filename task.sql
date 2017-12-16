/* 1 SQL Request*/
select Name from Country order by SurfaceArea desc, Name limit 5;

/* 2 SQL Request*/
select Country.Name, Rate from LiteracyRate 
join Country on LiteracyRate.CountryCode = Country.Code
Group by CountryCode
order by Year desc limit 1;

/* 3 SQL Request*/
select City.Name from Country, City, Capital
where Country.Name = 'Malaysia' and Capital.CityId = City.Id and City.CountryCode = Country.Code;

/* 4 SQL Request*/
SELECT Country.Name, COUNT(City.Name) AS BigCityCnt FROM Country
LEFT JOIN City ON Country.Code = City.CountryCode and City.Population > 1000000
GROUP BY Country.Code
ORDER BY BigCityCnt desc, Country.Name;

/* 5 SQL Request*/
select GovernmentForm, Sum(Population) as totalPop from Country
Group by Country.GovernmentForm
order by totalPop desc
limit 1;

/* 6 SQL Request*/
select City.Name, City.Population, Country.Name from City
join Country on City.CountryCode = Country.Code
order by (cast((City.Population) as float) / Country.Population) desc, City.Name desc
limit 20;

/* 7 SQL Request*/
select Country.Name from Country
join City on City.CountryCode = Country.Code
group by City.CountryCode
Having 2 * SUM(City.Population) < Country.Population and Country.Population > 0
order by Country.Name

/* 8 SQL Request */

