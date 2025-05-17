1.
    Given a sparse bit array A of size M stored in a database. The database provides an API query(L,R) which returns 1 if there is at least one bit equal to one in A[L..R] and 0 otherwise.

    You want to find all the 1 bits in a reasonable number of queries. E.g. for array 01100000001, positions of 1 bits are {1, 2, 10}.

    Return the array of all the positions of 1's.

    > use Binary search, Do recursively and divide and conquer.
1. You are given a 3D lattice graph where each node is either:

    Torch Node: Contains power 16.
    Wire Node: Initially has power 0.
    Power is transmitted from Torch Nodes to adjacent Wire Nodes with the following rules:
    
    When a Torch Node transmits power to a Wire Node, the Wire Node’s power becomes 15.
    Each subsequent Wire Node connected to a powered Wire Node receives power that is decremented by 1 for each transmission.
    The power transmission continues until the power value reaches 0 or a Torch Node is encountered.
    Your task is to return the final state of the graph after all power has been transmitted from all Torch Nodes.
    
    Input
    A 3D array representing the lattice graph.
    Each element is either a 16 (Torch Node) or 0 (Wire Node).
    Output
    The 3D array representing the final state of the graph after power transmission.
    
    Example:
    [
    [[16, 0, 16],
    [ 0, 0, 0],
    [16, 0, 16]]
    ]
    
    Output:
    [
    [[16, 15, 16],
    [15, 14, 15],
    [16, 15, 16]]
    ]
   > Can be solved using bfs, and stop on node whose value more than what is propagated!.
1. Given a and b in int return their diff in string, a and b could be large values.
1. 
