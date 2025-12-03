# 🌳 Q4(a) – AVL Tree [Insert + Delete + Traversals] (ADSA Lab 03)

## 📘 Problem Statement
Write a program that uses functions to perform the following operations on an **AVL Tree**:
- Insert a node  
- Delete a node  
- Perform Traversals:  
  - Inorder  
  - Preorder  
  - Postorder  

This AVL Tree implementation performs **self-balancing** using rotations after insertions and deletions.

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q4a_AVL_Tree.c` | Full implementation of AVL Tree with insert, delete, rotations, and traversals. |
| `test_Q4a_AVL_Tree.c` | MUnit test file to verify AVL operations including balance and traversals. |
| `munit.c` / `munit.h` | Unit testing framework used for automated testing. |

---

## 🧠 Code Overview

This program implements a fully functional **AVL Tree** with automatic self-balancing after every insertion or deletion.


### ✅ **AVL Tree Features**

### 🔹 **1. Insertion with Self-Balancing**
The tree automatically performs rotations to maintain height balance:
- **LL Rotation** → Right Rotate
- **RR Rotation** → Left Rotate
- **LR Rotation** → Left-Right Rotate
- **RL Rotation** → Right-Left Rotate

Every insertion maintains **balance factor = -1, 0, +1**.

---

### 🔹 **2. Deletion with Re-Balancing**
Supports all standard AVL deletion cases:
1. **Deleting a Leaf Node**
2. **Deleting a Node with One Child**
3. **Deleting a Node with Two Children**  
   - Replaces node using **inorder successor**
4. **Re-balancing after deletion**  
   - Performs LL, RR, LR, RL rotations as required
5. **Handles “Key Not Found” case with message:**
Key X does NOT exist in AVL Tree.

---

### 🔹 **3. Tree Traversals**
The program includes all major traversal functions:

| Traversal | Description |
|----------|-------------|
| `inorder()`  | Prints sorted keys (Left → Root → Right) |
| `preorder()` | Prints Root → Left → Right |
| `postorder()`| Prints Left → Right → Root |

---

### 🔹 **4. Interactive Menu (Only in main program)**

The program provides a user-friendly menu:

```bash
Insert
Delete
Inorder
Preorder
Postorder
Exit
```

---

### 🔹 **5. Improved Delete Feedback**

The program explicitly prints:
- **Success message when deletion happens**
- **Error message when key does NOT exist**

Example:

```bash
Key 50 deleted successfully.
Key 11 does NOT exist in AVL Tree.
```

---

### 🔹 **6. Modular Design**
The AVL Tree is divided into clean functional blocks:
- Node structure
- Height / balance utilities
- Rotations (LL, RR, LR, RL)
- Insert()
- Delete()
- Traversals
- Menu-driven main()

---

### 📌 Note

When compiling with **MUnit test cases**, define:

```c
#define TEST_MODE
```

to disable the menu.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q4a_AVL_Tree.c -o Q4a_AVL_Tree
./Q4a_AVL_Tree
```

---

### 🖥️ Sample Example

```bash
===== AVL Tree Menu =====
1. Insert
2. Delete
3. Inorder
4. Preorder
5. Postorder
6. Exit
Enter choice: 1
Enter value: 30

===== AVL Tree Menu =====
Enter choice: 1 
Enter value: 10

===== AVL Tree Menu =====
Enter choice: 1
Enter value: 20

===== AVL Tree Menu =====
Enter choice: 1
Enter value: 50

===== AVL Tree Menu =====
Enter choice: 1
Enter value: 40

===== AVL Tree Menu =====
Enter choice: 3
Inorder: 10 20 30 40 50 

===== AVL Tree Menu =====
Enter choice: 4
Preorder: 20 10 40 30 50 

===== AVL Tree Menu =====
Enter choice: 5
Postorder: 10 30 50 40 20 

===== AVL Tree Menu =====
Enter choice: 2
Enter value: 50
Key 50 deleted successfully.

===== AVL Tree Menu =====
Enter choice: 3
Inorder: 10 20 30 40 

===== AVL Tree Menu =====
Enter choice: 4
Preorder: 20 10 40 30 

===== AVL Tree Menu =====
Enter choice: 2
Enter value: 33
Key 33 does NOT exist in AVL Tree.
```

---

## 🧩 MUnit Code Overview

The `test_Q4a_AVL_Tree.c` file validates the correctness of AVL Tree operations such as **insertion**, **deletion**, **self-balancing**, and **tree traversals**.


### 🔹 1. Helper Functions

The test file includes traversal-to-array helpers used for validating tree structure:

- `inorder_to_array()` – captures AVL inorder traversal  
- `preorder_to_array()` – captures preorder traversal  
- `postorder_to_array()` – captures postorder traversal  

These functions store traversal output into arrays so the test assertions can compare them with the expected results.


### 🔹 2. Test Cases Included

| Test Name | Description |
|-----------|-------------|
| `/insert` | Tests AVL insertion and validates auto-balancing after LL, RR, LR, RL cases. |
| `/delete_leaf` | Deletes a leaf node and validates correct AVL restructuring. |
| `/delete_one_child` | Deletes a node with exactly one child. |
| `/delete_two_children` | Deletes a node with two children (checks inorder-successor replacement). |
| `/traversals` | Verifies inorder, preorder, and postorder traversal sequences. |

Each test ensures that the AVL tree maintains its balanced properties after operations.


### 🔹 3. Assertions Used

- `munit_assert_int()` – verifies node ordering after operations  
- `munit_assert_true()` – validates correct rotation & balancing cases  
- `munit_assert_not_null()` – checks node existence where applicable  

These assertions confirm AVL tree correctness after every tested operation.

`munit_assert_not_null()` → ensures node existence

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q4a_AVL_Tree.c test_Q4a_AVL_Tree.c munit.c -o test_Q4a
./test_Q4a  
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/AVL_Tree_Tests/insert                                                                             [ OK    ] 
/AVL_Tree_Tests/delete_leaf          Key 10 deleted successfully.                                  [ OK    ] 
/AVL_Tree_Tests/delete_one_child     Key 30 deleted successfully.                                  [ OK    ] 
/AVL_Tree_Tests/delete_two_children  Key 60 deleted successfully.  Key 50 deleted successfully.    [ OK    ] 
/AVL_Tree_Tests/traversals                                                                         [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
