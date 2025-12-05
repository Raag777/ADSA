# 🌳 Q2 – Splay Tree Operations (ADSA LAB08)

## 📘 Problem Statement

Implement a program to perform **Splay Tree operations** including:

✔ Insert  
✔ Search (with splaying effect)  
✔ Delete  
✔ Inorder Traversal  
✔ Preorder Traversal  

The program must:

- Maintain splay tree properties  
- Continuously splay accessed or inserted nodes to the root  
- Support interactive user menu  
- Be compatible with **MUnit test automation**

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Splay_Tree.c` | Implements rotations, splay operation, insert, delete, search, and traversal. |
| `Splay_Tree.h` | Header file exposing splay functions & node structure. |
| `test_Splay_Tree.c` | Contains automated MUnit test cases validating splay tree behaviour. |
| `munit.c` / `munit.h` | Framework used for test suite execution. |

---

## 🧠 Code Overview

A **Splay Tree** is a self-adjusting binary search tree where each access operation moves the accessed node closer to the root via **tree rotations**.

### 🔹 Core operations:

#### ➤ **1. Splaying**

Moves the accessed node to the root using:

- Zig–Zig (LL)
- Zig–Zag (LR)
- Zag–Zig (RL)
- Zag–Zag (RR)

This maintains fast amortized access.

#### ➤ **2. Insert**

- Insert as BST
- Splay inserted node to root

#### ➤ **3. Search**

- Find element
- Whether found or not — splay nearest accessed node to root

#### ➤ **4. Delete**

- Splay target
- Merge left and right trees while maintaining search structure

---

## 🧮 Algorithm Complexity

| Operation       | Amortized Complexity |
|-----------------|----------------------|
| Insert          | **O(log n)**         |
| Search          | **O(log n)**         |
| Delete          | **O(log n)**         |
| Traversal       | **O(n)**             |

📌 **Worst case is O(n), but amortized performance is O(log n)** due to splaying property.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Splay_Tree.c -o Splay_Tree
./Splay_Tree
```

---

### 🖥️ Sample Example

```bash
===== SPLAY TREE MENU =====
1. Insert
2. Search
3. Delete
4. Inorder Traversal
5. Preorder Traversal
6. Exit
Enter your choice: 1
Enter key to insert: 5
Inserted!

===== SPLAY TREE MENU =====
Enter your choice: 1
Enter key to insert: 10
Inserted!

===== SPLAY TREE MENU =====
Enter your choice: 1
Enter key to insert: 20
Inserted!

===== SPLAY TREE MENU =====
Enter your choice: 1
Enter key to insert: 90
Inserted!

===== SPLAY TREE MENU =====
Enter your choice: 1
Enter key to insert: 33
Inserted!

===== SPLAY TREE MENU =====
Enter your choice: 1
Enter key to insert: 11
Inserted!

===== SPLAY TREE MENU =====
Enter your choice: 4
Inorder: 5 10 11 20 33 90 

===== SPLAY TREE MENU =====
Enter your choice: 5
Preorder: 11 10 5 20 33 90 

===== SPLAY TREE MENU =====
Enter your choice: 2
Enter key to search: 5
Tree splayed with 5 at root (or nearest accessed node).

===== SPLAY TREE MENU =====
Enter your choice: 2
Enter key to search: 90
Tree splayed with 90 at root (or nearest accessed node).

===== SPLAY TREE MENU =====
Enter your choice: 2
Enter key to search: 33
Tree splayed with 33 at root (or nearest accessed node).

===== SPLAY TREE MENU =====
Enter your choice: 3
Enter key to delete: 20
Deleted if existed.

===== SPLAY TREE MENU =====
Enter your choice: 4
Inorder: 5 10 11 33 90 

===== SPLAY TREE MENU =====
Enter your choice: 90
Invalid choice.

===== SPLAY TREE MENU =====
Enter your choice: 2
Enter key to search: 90
Tree splayed with 90 at root (or nearest accessed node).

===== SPLAY TREE MENU =====
Enter your choice: 6
Exiting...
```

---

## 🧩 MUnit Code Overview

The file `test_Splay_Tree.c` contains automated MUnit test cases that validate:

- Correct splaying behaviour
- Movement of accessed or inserted elements toward root
- Proper deletion handling while maintaining structure
- Valid traversal ordering for BST correctness

### 🔍 What the Tests Check

| Test Case              | Purpose                                      |
|------------------------|----------------------------------------------|
| **/insert**            | Insert causes splayed key to become root     |
| **/search**            | Accessed key is rotated / splayed to root    |
| **/delete**            | Deleted key is no longer found in the tree   |
| **/splay_property**    | Rotation rules maintain splay behaviour      |
| **/inorder**           | Tree remains valid (sorted) after operations |


---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Splay_Tree.c test_Splay_Tree.c munit.c -o test_ST
./test_ST
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/splay_tree_tests/insert             [ OK    ] 
/splay_tree_tests/search             [ OK    ] 
/splay_tree_tests/delete             [ OK    ] 
/splay_tree_tests/splay_property     [ OK    ] 
/splay_tree_tests/inorder            [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
