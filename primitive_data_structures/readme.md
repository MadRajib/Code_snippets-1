## Primitive Data Structures

1. [Stack Using Linked List](#stack-using-linked-list)

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

Pop(Node: sentinel) {
    // check for empty
    if (sentinel.next == null) throw exception
    
    Data: result = sentinel.next.val;

    // remove from front
    sentinel.next = sentinel.next.next;

    Return result
}
```

