# BFS
An implementation of the Bread First Search algorithm on a tree with any number of leaves. Note that this has not been tested and will most likely not work in graphs (that are not trees), but feel free to give it a try :).

# Code structure

The code consists of the following main components:

* function BFS
* class Node
* class Step

Function BFS has been implemented in a way that it just includes the logic corresponding to the main steps of the BFS algorithm. Specific logic regarding the problem being solved can be added in class Node and Step.

Particularly, class Node should implement the logic to children of a Node, the stop condition, and a method to get the path to get to the solution.

I have defined that a path is made up of Step elements: being the Step class a wrapper for whatever container is better to solve a specific problem. 

# Current implementation

The code included here solves a very specific problem where Nodes could have several children, which proved to be problematic. Thus, I restricted the Nodes that could be expanded based on the constraints of my specific problem.

# The problem

In case you are curious, this is the problem that I wanted to solve with this algorithm:

Having an array of length N containing V values (some may repeated) and E empty slots, with V + E = N

```
 1 2 2 "" "" 3 1
```

With `N = 7`, `V = 5` and `E = 2`

Return a list of swap operation required so every value V is in a valid position, as indicated by a second array:

```
3 1 1 2 2 "" ""
```

And only moving values in V to empty slots (so, swapping V values is not allowed).
