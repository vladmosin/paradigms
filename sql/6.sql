/* 6 SQL Request*/
select City.Name, City.Population, Country.Name from City
join Country on City.CountryCode = Country.Code
order by (cast((City.Population) as float) / Country.Population) desc, City.Name desc
limit 20;
