import Prelude hiding (lookup)

data BinaryTree key value =  Nil | Node key value (BinaryTree key value) (BinaryTree key value) deriving (Show, Eq)

lookup _ Nil = Nothing
lookup k' (Node k v l r)
    | k' == k = Just v
    | k' < k  = lookup k' l
    | k' > k  = lookup k' r

insert k' v' Nil = Node k' v' Nil Nil
insert k' v' (Node k v l r)
    | k' == k = Node k' v' l r
    | k' > k  = Node k v l (insert k' v' r)
    | k' < k  = Node k v (insert k' v' l) r

addRight node Nil = node
addRight node (Node k v l r)   = Node k v l (addRight node r)

delete _ Nil = Nil
delete k' (Node k v l r)
    | k' == k = addRight r l
    | k' < k  = Node k v (delete k' l) r
    | k' > k  = Node k v l (delete k' r)
