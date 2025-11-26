## Primitive Data Structures
1. [Stack](#stack)
    1. [Stack Using Linked List](#stack-using-linked-list)
    1. [Stack Using Array](#stack-using-array)
    1. [Double Stack Using Array](#double-stack-using-array)
1. [Queues](#queues)
    1. [LL Queues](#ll-queues)
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