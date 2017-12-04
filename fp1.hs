head' (x:_) = x

tail' (_:xs) = xs
tail' []     = []

take' 0 _      = []
take' _ []     = []
take' n (x:xs) = x:(take' (n - 1) xs)

drop' 0 xs     = xs
drop' _ []     = []
drop' n (_:xs) = drop' (n - 1) xs

foldl' f a (x:xs) = f x (foldl' f a xs)
foldl' _ a _      = a

concat' (x:xs) lst = x:concat' xs lst
concat' [] lst     = lst

filter' _  [] = []
filter' f (x:xs) | f x       = x:(filter' f xs)
                 | otherwise = filter' f xs

quickSort' []     = []
quickSort' (x:xs) = concat' (quickSort' (filter' (<= x) xs)) (x:quickSort' (filter' (> x) xs))
