import Prelude hiding (lookup)

data BinaryTree key value =  Nil | Node key value (BinaryTree key value) (BinaryTree key value) deriving (Show, Eq)

lookup _ Nil = Nothing
lookup required_key (Node key value left right)
    | required_key == key = Just value
    | required_key < key = lookup required_key left
    | required_key > key = lookup required_key right

insert given_key given_value Nil = Node given_key given_value Nil Nil
insert given_key given_value (Node key value left right)
    | given_key == key = Node given_key given_value left right
    | given_key > key = Node key value left (insert given_key given_value right)
    | given_key < key = Node key value (insert given_key given_value left) right

add_right given_node (Node key value left Nil) = Node key value left given_node
add_right given_node right = right

delete given_key Nil = Nil
delete given_key (Node key _ left right)
    | given_key == key = (add_right right left)
    | given_key < key = delete given_key left
    | given_key > key = delete given_key right
