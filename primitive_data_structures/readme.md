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
### Basic Concept
```cpp
// Basic node in simple LL
struct node {
    int val;
    struct node *next;
};

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