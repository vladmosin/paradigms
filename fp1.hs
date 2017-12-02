head' (x:_) = x

tail' (_:xs) = xs
tail' _ = []

take' 0 _ = []
take' _ [] = []
take' n (x:xs) = x:(take' (n - 1) xs)

drop' 0 xs = xs
drop' _ [] = []
drop' n (_:xs) = drop' (n - 1) xs

foldl' f z (x:xs) = f x (foldl' f z xs)
foldl' _ a _ = a

concat' xs [] = xs
concat' lst (x:xs) = concat' (lst ++ [x]) xs

filter' _  [] = []
filter' f (x:xs) | f x       = x:(filter' f xs)
                 | otherwise = filter' f xs

quickSort' [] = []
quickSort' (x:xs) = concat' (quickSort' (filter' (<= x) xs)) (x:quickSort' (filter' (> x) xs))
