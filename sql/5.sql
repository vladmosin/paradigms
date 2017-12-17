/* 5 SQL Request*/
SELECT GovernmentForm, Sum(SurfaceArea) AS totalArea 
FROM Country
GROUP BY Country.GovernmentForm
ORDER BY totalArea DESC
LIMIT 1;
