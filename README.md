
# B-Tree

## Overview

B-Tree is a custom, template-based B-Tree implementation developed from scratch in C++, supporting insertion, deletion, searching, traversal, and dynamic memory management.

Unlike a traditional Binary Search Tree, which stores one key per node, a B-Tree stores multiple sorted keys within each node and maintains multiple child pointers. The implementation manages tree structure through node splitting, key redistribution, and node merging during insertion and deletion.

---

## Key Features

- **Template-Based Implementation:** Supports different comparable data types using C++ templates.
- **Deletion and Rebalancing:** Handles node underflow through key redistribution, sibling rotations, and node merging.
- **Multi-Key Node Structure:** Stores multiple ordered keys and child pointers within each node.
- **Dynamic Insertion:** Splits overflowing nodes and promotes separator keys to maintain tree structure.
- **Efficient Searching:** Uses ordered keys to navigate through the appropriate subtrees.
- **Deep Copy Support:** Implements copy construction and assignment to create independent trees.
- **Dynamic Memory Management:** Recursively allocates and deallocates tree nodes.
- **In-Order Traversal:** Retrieves stored elements in sorted order.
- **Tree Visualization:** Displays tree structure, node keys, and child information.
- **GoogleTest Integration:** Includes test cases for tree operations, structural changes, and edge cases.

---

## Supported Operations

| Operation | Function | Description |
|-----------|----------|-------------|
| Insert | `insert()` | Inserts a key into the B-Tree |
| Remove | `remove()` | Removes a key and handles structural adjustments |
| Search | `contains()` | Checks whether a key exists |
| Find | `find()` | Returns a pointer to a matching key |
| Get | `get()` | Returns a reference to a matching key |
| Size | `size()` | Counts the stored keys |
| Check Empty | `empty()` | Determines whether the tree is empty |
| Clear | `clear_tree()` | Recursively deallocates tree nodes |
| Deep Copy | `copy_tree()` | Creates an independent copy of a tree |
| Traversal | `in_order()` | Returns keys in sorted order |
| Visualization | `print_tree()` | Displays the tree's structure |

---

## Technical Implementation

### 1. <ins>B-Tree Structure</ins>

The `BTree<T>` class implements a multiway search tree using fixed-size arrays to store keys and pointers to child nodes.

Each node maintains:

- An array of sorted keys.
- An array of pointers to child subtrees.
- The number of stored keys.
- The number of child pointers.

The implementation uses:

```cpp
static const int MINIMUM = 1;
static const int MAXIMUM = 2 * MINIMUM;
```

Each non-root node is designed to maintain between 1 and 2 keys, corresponding to a B-Tree of minimum degree 2 (a 2-3-4 tree).

Temporary overflow and underflow conditions are handled through structural adjustment operations.

### 2. <ins>Insertion and Node Splitting</ins>

Insertion uses recursive descent to locate the appropriate position for a new key.

When a node exceeds its maximum key capacity, the engine splits the overflowing node and promotes a separator key to its parent.

The insertion process uses two primary helper functions:

- `loose_insert()` — Recursively inserts a key, temporarily permitting an overflowing node.
- `fix_excess()` — Splits the overflowing child and promotes its middle key.

If the root overflows, a new root level is created to accommodate the promoted key.

This process maintains the B-Tree's multiway search structure as elements are inserted.

### 3. <ins>Deletion and Tree Rebalancing</ins>

Deletion is handled through recursive key removal and structural adjustments to address node underflow.

The implementation provides several helper functions:

- `loose_remove()` — Locates and removes a key recursively.
- `remove_biggest()` — Retrieves the largest key from a subtree for replacement.
- `fix_shortage()` — Handles nodes containing fewer than the minimum number of keys.
- `rotate_left()` — Redistributes keys by borrowing from a right sibling.
- `rotate_right()` — Redistributes keys by borrowing from a left sibling.
- `merge_with_next_subset()` — Combines adjacent subtrees when redistribution is unavailable.

These operations are designed to maintain valid key distribution across the tree during deletion.

### 4. <ins>Searching and Traversal</ins>

Searching uses the sorted keys within each node to determine which subtree to explore.

The `first_ge()` helper locates the first key greater than or equal to a target value.

The `find()` function then:

1. Searches the current node for the target key.
2. Returns a pointer if the key is found.
3. Recursively searches the appropriate child subtree otherwise.
4. Returns `nullptr` if the key does not exist.

The implementation also provides an in-order traversal that recursively visits child subtrees and their separator keys to produce sorted output.

### 5. <ins>Memory Management and Deep Copying</ins>

The B-Tree uses dynamically allocated child nodes and implements the Rule of Three:

- **Copy Constructor:** Creates an independent copy of an existing tree.
- **Copy Assignment Operator:** Replaces tree contents while handling self-assignment.
- **Destructor:** Releases dynamically allocated child nodes.

The `copy_tree()` function recursively duplicates nodes, while `clear_tree()` recursively releases allocated memory.

These operations demonstrate object ownership, recursive memory management, and pointer-based data structure implementation in C++.

---

## Core Components

| File | Responsibility |
|------|----------------|
| `btree.h` | Defines the B-Tree class and implements insertion, deletion, searching, copying, and traversal |
| `btree_array_functions.h` | Provides array manipulation utilities for inserting, removing, splitting, merging, and copying keys |
| `basic_test.cpp` | Exercises fundamental B-Tree operations, including insertion, searching, splitting, and deletion |
| `testB.cpp` | Contains additional GoogleTest cases and debugging scenarios for B-Tree operations and array utilities |

---

## Time Complexity

B-Trees maintain a logarithmic height by storing multiple keys per node and managing node splits and merges.

For a valid B-Tree with a fixed maximum number of keys per node:

| Operation | Time Complexity |
|-----------|-----------------|
| Search | O(log n) |
| Insert | O(log n) |
| Delete | O(log n) |
| In-Order Traversal | O(n) |
| Deep Copy | O(n) |
| Clear Tree | O(n) |

Unlike an unbalanced Binary Search Tree, a correctly maintained B-Tree preserves logarithmic height even when keys are inserted in sorted order.

---

## Testing

The project includes C++ test programs using **GoogleTest**, with scenarios covering B-Tree operations and structural modifications.

Testing scenarios include:

- Inserting keys and handling node overflow.
- Searching for existing and nonexistent keys.
- Removing keys and exercising node rebalancing.
- Removing all elements from a tree.
- Copying and clearing tree structures.
- Verifying in-order traversal output through inspection.
- Exercising array insertion, deletion, splitting, and merging utilities.
- Testing tree operations using randomized input sequences.

The test programs combine GoogleTest test cases with console-based structural inspection and debugging.

---

## Project Information

**Language:** C++  
**Data Structure:** B-Tree (2-3-4 Tree Configuration)  
**Testing:** GoogleTest  
**Core Concepts:** Multiway search trees, recursion, tree rebalancing, array manipulation, dynamic memory management, and object-oriented programming

**Developer:** Queency Tan
