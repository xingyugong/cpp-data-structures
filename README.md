# Data Structures in C++ (CS 41)

Three classic data structures implemented from scratch in C++ — no STL containers, no starter code.

## Programs

1. **RPNCalculator.cpp** — Reverse Polish Notation calculator. Linked-list-based stack (arrays disallowed); handles operand/operator count errors and division by zero; evaluates expressions in a loop until 0 is entered.
2. **DualSortedLinkedList.cpp** — Doubly linked list of 15 name/weight records kept in two sorted orders at once (by name and by weight) using two sets of pointers.
3. **bst_assignment.cpp** — Binary search tree (linked, not array-based) over 15 name/weight records: pre-order, in-order and post-order traversals, recursive height computation (no stored height field), leaf counting, lookup by name, minimum weight, lexicographically first name.

## Build

```bash
g++ -std=c++17 -o rpn RPNCalculator.cpp
g++ -std=c++17 -o dlist DualSortedLinkedList.cpp
g++ -std=c++17 -o bst bst_assignment.cpp
```

*Coursework — CS 41 Data Structures, Irvine Valley College (Spring 2026). Each program graded 10/10.*
