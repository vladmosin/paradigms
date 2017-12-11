import Prelude hiding (lookup)

data BinaryTree k v = Nil | Node k v (BinaryTree k v) (BinaryTree k v) deriving (Show, Eq)

lookup _ Nil = Nothing
lookup k' (Node k v l r)
    | k' < k    = lookup k' l
    | k' > k    = lookup k' r
    | otherwise = Just v

insert k' v' Nil = Node k' v' Nil Nil
insert k' v' (Node k v l r)
    | k' > k    = Node k v l (insert k' v' r)
    | k' < k    = Node k v (insert k' v' l) r
    | otherwise = Node k' v' l r

merge Nil            node = node
merge (Node k v l r) node = Node k v l (merge r node)

delete _ Nil = Nil
delete k' (Node k v l r)
    | k' < k    = Node k v (delete k' l) r
    | k' > k    = Node k v l (delete k' r)
    | otherwise = merge l r
