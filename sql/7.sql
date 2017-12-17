/* 7 SQL Request*/
select Country.Name from Country
join City on City.CountryCode = Country.Code
group by City.CountryCode
Having 2 * SUM(City.Population) < Country.Population and Country.Population > 0
order by Country.Name
