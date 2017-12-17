/* 2 SQL Request*/
select Country.Name, Rate from LiteracyRate 
join Country on LiteracyRate.CountryCode = Country.Code
Group by CountryCode
order by Year desc limit 1;
