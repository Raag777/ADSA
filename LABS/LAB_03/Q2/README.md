# 🌳 Q2 – Binary Search Tree (ADSA Lab 03)

## 📘 Problem Statement  
Write a C program using functions to perform the following operations on a **Binary Search Tree (BST)**:  
1. Creation  
2. Insertion  
3. Deletion  
4. Traversal:  
   - Inorder  
   - Preorder  
   - Postorder  

This folder contains both the **main BST program** and the **MUnit test suite** used to validate correctness.

---

## 📂 Code Files

| File Name        | Description |
|------------------|-------------|
| `Q2_BST.c`       | Full BST implementation with safe user input and menu-driven interface. |
| `test_Q2_BST.c`  | Automated unit tests using **MUnit** to verify all BST functionalities. |
| `munit.c / munit.h` | Unit testing framework (provided in ADSA Lab setup). |

---

## 🧠 Code Overview

The implementation includes the following major operations:

### 🔹 **1. Node Structure**
Each node contains:
- `data`
- `left` child
- `right` child

### 🔹 **2. Insertion**
Inserts nodes in proper BST order (left < root < right).

### 🔹 **3. Deletion**
Handles three cases:
- Node with **no child**
- Node with **one child**
- Node with **two children** (uses inorder successor)

### 🔹 **4. Traversals**
- **Inorder (LNR)** → Sorted order  
- **Preorder (NLR)**  
- **Postorder (LRN)**  

### 🔹 **5. Safe Input Handling**
A helper function `safeInput()` prevents infinite invalid input loops caused by non-numeric values.

### 🔹 **6. Menu-Driven Interface**
Users can:
- Insert nodes  
- Delete nodes  
- Display traversals  
- Exit the program  

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q2_BST.c -o Q2_BST
./Q2_BST
```

---

### 🖥️ Sample Example

```bash
===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 1
Enter value to insert: 4
Inserted successfully!

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 1
Enter value to insert: 6
Inserted successfully!

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 1
Enter value to insert: 7
Inserted successfully!

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 1
Enter value to insert: 9
Inserted successfully!

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 1
Enter value to insert: 11
Inserted successfully!

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 3
Inorder Traversal: 4 6 7 9 11 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 4
Preorder Traversal: 4 6 7 9 11 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 5
Postorder Traversal: 11 9 7 6 4 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 2
Enter value to delete: 9
Deleted successfully (if existed).

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 3
Inorder Traversal: 4 6 7 11 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 4
Preorder Traversal: 4 6 7 11 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 5
Postorder Traversal: 11 7 6 4 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 1
Enter value to insert: 1
Inserted successfully!

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 3
Inorder Traversal: 1 4 6 7 11 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 4
Preorder Traversal: 4 1 6 7 11 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 5
Postorder Traversal: 1 11 7 6 4 

===== Binary Search Tree Operations =====
1. Insert
2. Delete
3. Inorder Traversal
4. Preorder Traversal
5. Postorder Traversal
6. Exit
Enter your choice: 6
Exiting...
```

---

## 🧩 MUnit Code Overview

The `test_Q2_BST.c` file verifies correctness of every BST operation using structured test cases.

### 🔹 Helper Functions
To test traversals, arrays are used:

- `inorder_to_array()`  
- `preorder_to_array()`  
- `postorder_to_array()`  

These convert traversal output into arrays that can be validated using `munit_assert_int()`.


### 🔹 Test Cases Summary

| Test Name | What It Validates |
|----------|--------------------|
| `/insert` | Nodes inserted correctly in BST order. |
| `/delete_leaf` | Deletes a leaf node successfully. |
| `/delete_one_child` | Handles deletion of nodes with one child. |
| `/delete_two_children` | Correctly deletes nodes having two children (using inorder successor). |
| `/traversals` | All three traversals return correct sequences. |


### 🔹 Assertions Used

- `munit_assert_int()`  
   Verifies individual values in traversal sequences.

Example:

```c
munit_assert_int(arr[i], ==, expected[i]);
```

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q2_BST.c test_Q2_BST.c munit.c -o test_Q2_BST
./test_Q2_BST
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/BST_Tests/insert                    [ OK    ] 
/BST_Tests/delete_leaf               [ OK    ] 
/BST_Tests/delete_one_child          [ OK    ] 
/BST_Tests/delete_two_children       [ OK    ] 
/BST_Tests/traversals                [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
