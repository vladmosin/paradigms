/* 5 SQL Request*/
select GovernmentForm, Sum(Population) as totalPop from Country
Group by Country.GovernmentForm
order by totalPop desc
limit 1;
