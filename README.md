# splay trees

Splay Trees are one of the most useful tree data structures. I have implemented a splay tree data structure with insertion, deletion, searching, display operations. Along with this, there is an additional linked list data structure to keep track of the k-recently used nodes in the splay tree. 

The amortized cost of the splaying operation is O(log n) where n is the number of nodes in the tree. 

Any operation on the splay tree will result in updation of the linked list data structure. On search operation, the node is served from the tree and not from the linked list as the splaying operation is essential to keep the tree balanced.

To compile the files : 
gcc client.c splay_trees.c print_tree.c linked_list.c
