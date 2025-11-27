## Primitive Data Structures
1. [Stack](#stack)
    1. [Stack Using Linked List](#stack-using-linked-list)
    1. [Stack Using Array](#stack-using-array)
    1. [Double Stack Using Array](#double-stack-using-array)
1. [Queues](#queues)
    1. [LL Queues](#ll-queues)
    1. [Circular Queue using Array](#circular-queue-using-array)
    1. [Specialized Queues](#specialized-queues)
        1. [Priority Queue](#priority-queue)
        1. [Deques](#deques)
1. [Linked list](#linked-list)
    1. [Singly Linked List](#singly-linked-list)
    1. [Doubly Linked List](#doubly-linked-list)
1. [Arrays](#arrays)

## Stack
### Stack Using Linked List
- use sentinel node
- add at front and remove from top 

```cpp
Push(Node: sentinel, Data: new_value)
    // create a new node
    Node: new_node = New Node
    new_node.val = new_value

    // add to front
    new_node.next = sentinel.next
    sentinel.next = new_node
End Push

Data: Pop(Node: sentinel)
    // check for empty
    if (sentinel.next == null) throw exception
    
    Data: result = sentinel.next.val;

    // remove from front
    sentinel.next = sentinel.next.next;

    Return result
End Pop
```
### Stack Using Array
- next_index     -> points to next available position in stack
- next_index : 0 -> stack is empty
```cpp
Push(Data: stack_values [], Integer: next_index, Data: new_value)
    if (next_index == <len of the stack_values>) 
        then thow exception
    
    stack_values[next_index] = new_value
    next_index = next_index + 1
End Push

Data: Pop(Data: stack_values [], Integer: next_index)
    // check for empty
    if (next_index == 0) throw exception

    // decrement next_index
    next_index = next_index - 1

    // return the top value
    Return stack_value[next_index]
End Pop
```

### Double stack using array
//todo

## Queues
- Enqueue -> push to queue
- Dequeue -> pop from queue
### LL Queues
- using DD LL to make removing last element easy
- top_sentinel: front guard.
- bottom_sentinel: end guard.
```cpp
Enqueue (Node: top_sentinal, Data: new_value)
    Node : new_node = New Node
    new_node.val = new_value

    // add to front
    new_node.next = top_sentinal.next
    top_sentinal.next = new_node
    new_node.prev = top_sentinal
End Enqueue

Data: Dequeue (Node: bottom_sentinal)
    if (bottom_sentinal.prev = top_sentinal)
        thow exception
    
    Data: result = bottom_sentinal.prev.val
    
    bottom_sentinel.prev = bottom_sentinel.prev.prev
    bottom_sentinel.prev.next = bottom_sentinel

    Return result
End Dequeue
```
### Circular queue using array
- normal queue using array is tricker as memory is wasted
- circular queue has better memory usage compared to former.

```cpp
// Global declaration
Data: Queue[<queue_size>]
Integer: next = 0
Integer: last = 0

Enqueue (Data: val)
    if (next + 1) Mod <queue_size> == last
        throw exception
    
    Queue[next] = val
    next = (next + 1) Mod <queue_size>
End Enqueue

Data: Dequeue ()
    if (next == last)
        throw exception

    Data: val = queue[last]
    last = (last + 1) Mod <queue_size>

    Return val
End Dequeue
```
### Specialized Queues
### Priority Queue
    - each item has a priority
    - dequeue remove item having highest priority.
    - always high-priority items are handled first
### Deques
    - pronouced "deck"
    - Double ended queue

## Linked List

### Singly Linked List
#### Basic Concept
```cpp
// Basic node in simple LL
struct node {
    int val;
    struct node *next;
};
```
#### Iterating over the list
```cpp
Iterate(Node: top)
    while (top != null)
        Print top.val
        top = top.next
    End While
End Iterate
```
- top points to null when loop ends

#### Finding a node
- using a sentinal node at the begining makes the algo simple
```cpp
Node: FindNodeBefore (Node: top, Val: target)
    while (top.next != null)
        if (top.next.val == targert)
            Return top
        top = top.next
    End while

    Return null
End FindNodeBefore
```
#### Adding Nodes at the beginning
```cpp
AddAtBeginning (Node: top, Node: new_node)
    new_node.next = top.next
    top.next = new_node
End AddAtBeginning
```

#### Adding Nodes at the end
```cpp
AddAtEnd (Node: top, Node: new_node)
    // find the end first
    while (top.next != null)
        top = top.next
    End while

    top.next = new_node
    new_node.next = null;
End AddAtEnd
```
- code would have been messier if sentinel was not there.

#### Inserting Node after another Node
- assuming we have the node's location after which we have to add the new one
```cpp
InsertNode (Node: after_me, Node: new_node)
    new_node.next = after_me.next
    after_me.next = new_node
End InsertNode
```

#### Deleting Cells
```cpp
DeleteAfter (Node: after_me)
    Node: target_node =  after_me.next
    after_me.next = after_me.next.next
    free(target_node)
End DeleteAfter
```
- To destroy whole list :
```cpp
DestroyList (Node: top)
    while (top != null)
        Node: new_node = top.next

        free(top)

        top = next_node
    End while
End DestroyList
```
### Doubly Linked List

#### Insert
```cpp
InsertNode (Node: after_me, Node: new_val)
    // Update next links
    new_node.next = after_me.next
    after_me.next = new_node

    // Update prev links
    new_node.prev = after_me
    new_node.next.prev = new_node
End InsertNode
```
#### Delete
```cpp
DeleteNode (Node: target_node)
    target_node.prev.next = target_node.next
    target_node.next.prev = target_node.prev
    free(target_node)
End DeleteNode
```

- if node has more than one type of data
- hang the data node in linked list just like cloths hanging in rope.
- no extra memory wastage
- to reach the structure from node we can use __*container_of*__ macro
```cpp
// better apporach 
#define LIST_INIT(list) { &(list), &(list) }

#define container_of(ptr, type, member) ({ \
		const typeof(((type *)0)->member)*__mptr = (ptr);  \
		(type *)((char *)__mptr - offsetof(type, member)); \
		})

struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

struct data_node {
    // data type
    // data type
    struct list_head node;
};

// List add
static inline void list_add(struct list_head *list, struct list_head *item)
{
	struct list_head *prev = list->prev;

	item->next = list;
	item->prev = prev;

	prev->next = list->prev = item;
}

// list push
static inline void list_del(struct list_head *item)
{
	item->prev->next = item->next;
	item->next->prev = item->prev;
}

#define list_for_each(item, list) \
	for (item = (list)->next; item != list; item = item->next)

#define list_for_each_safe(item, next, list) \
	for (item = (list)->next, next = item->next; item != list; item = next, next = item->next)

#define list_entry(item, type, member) \
	container_of(item, type, member)

#define list_entry_first(list, type, member) \
	container_of((list)->next, type, member)

#define list_entry_next(item, member) \
	container_of((item)->member.next, typeof(*(item)), member)

#define list_for_each_entry(item, list, member) \
	for (item = list_entry_first(list, typeof(*(item)), member); \
	     &item->member != list; \
	     item = list_entry_next(item, member))

#define list_for_each_entry_safe(item, next, list, member) \
	for (item = list_entry_first(list, typeof(*(item)), member), \
	     next = list_entry_next(item, member); \
	     &item->member != list; \
	     item = next, \
	     next = list_entry_next(item, member)) \
```

- Usage
```cpp
struct list_head my_list = LIST_INIT(my_list);

// to add
list_add(&my_list, &data_node->node);

// to delete

list_del(&data_node->node);

// to itrate
struct list_head *item;
struct list_head *next;
struct data_node *data;

list_for_each_safe(item, next, &my_list) {
	data = container_of(item, struct data_node, node);
    // process data
}

// to iterate 
struct list_head *next;
struct data_node *data;
list_for_each_entry_safe(data, next, &my_list, node) {
    if (data) {
        //process it
    }
}
```

### Arrays
- For 1D arrays, the mapping from array indices to mem entires is simple: index __i__ maps to entry __i__.
- For 2D arrays, two mapping types : row-major or column-major order.
    * In row-major order, program maps the first row of array entries to the first set of mem location. Then the second row to next mem loc.
    * In column-major order, program maps the column of array entries to the first set of mem location.
    * To store 3D array in row-major order, the program would map the first 2-D "slice" of the array where the third dimension's index is 0.
    * It would map that slice in row-major order as usual.
    * it would then similarly map the second slice where the third index is 1, and so on for the remaining slices.
- In 2D array : \  
    __index__ = row * \<row size> + column;
```cpp
Integer: FindIndex(Integer: r, Integer: c)
    Return r * row_size + c
End Integer
```
- In 3D array (h, r, c) : \
    __index__ = h * \<row size> * \<column size>; \
    __index__ = __index__ + r * \<row size>; \
    __index__ = __index__ + c;
```cpp
Integer: FindIndex(Integer: h, Integer: r, Integer: c)
    Return (h * row_size * col_size) + r * row_size + c
End Integer
```
- In Trianglure array (lower trinagle)
    * total elements: (N^2 + N) / 2
```cpp
Integer: FindIndex(Integer: r, Integer: c)
    Return ((r - 1) * (r - 1) +  (r - 1)) / 2 + c
End Integer
```