/* 5 SQL Request*/
SELECT GovernmentForm, Sum(SurfaceArea) 
FROM Country
GROUP BY Country.GovernmentForm
ORDER BY Sum(SurfaceArea) DESC
LIMIT 1;
