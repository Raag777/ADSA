# 🌳 Q4(b) – B-Tree [Insert + Delete + Search + Traversal] (ADSA Lab 03)

## 📘 Problem Statement
Write a program that performs the following operations on a **B-Tree (minimum degree T = 3)**:

- Insert a key  
- Delete a key (leaf nodes only)  
- Search for a key  
- Traverse the B-Tree in sorted order  

The implementation supports **node splitting**, **root splitting**, and **leaf deletion**.  
Internal node deletion is *not required* as per lab instructions.

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q4b_B_Tree.c` | Full implementation of B-Tree including insert, delete (leaf only), search, and traversal. |
| `test_Q4b_B_Tree.c` | MUnit test file that verifies insertion, search, deletion, and root split behavior. |
| `munit.c` / `munit.h` | Unit testing framework used to run automated tests. |

---

## 🧠 Code Overview

This program implements a **B-Tree of order T = 3**, meaning:

- Each node can store **max 5 keys** (`2*T - 1`)
- Each node can have **max 6 children** (`2*T`)
- Root splitting occurs automatically when needed

---

## 🌟 Key Features of the B-Tree

### 🔹 1. **Insertion**
The insertion process handles:
- Empty tree creation  
- Insertion into non-full nodes  
- **Splitting full nodes**
- Automatic **root split** when root becomes full  

During a split:
- Middle key moves **up** to parent  
- Right half becomes a **new sibling node**  

---

### 🔹 2. **Search Operation**

The B-Tree `search()` function performs standard B-Tree lookup:

```c
BTreeNode* search(BTreeNode* root, int key);
```

- Returns **pointer to the node** containing the key → ✅ *if found*
- Returns **NULL** → ❌ *if key does not exist in the B-Tree*

This allows both the main program and MUnit tests to easily verify search correctness.

---

### 🔹 3. **Deletion (Leaf Only)**

The delete implementation intentionally supports **only leaf-node deletion**, matching ADSA Lab requirements.

Behavior:

- ✔️ **If key exists in a leaf** → key is deleted and a success message is shown  
  `Key X deleted successfully.`

- ⚠️ **If key exists but is in an internal node**  
  Deletion is *not implemented* for internal nodes, so the program prints:  
  `Key X found but NOT a leaf. Internal delete not implemented.`

- ❌ **If key does NOT exist in the B-Tree**  
  The program prints a clear message:  
  `Key X does NOT exist in B-Tree.`

---

### 🔹 4. **Traversal**

The `traverse()` function prints all keys in **sorted order**, following standard B-Tree DFS pattern:

```bash
child0 → key0 → child1 → key1 → child2 → ... → childN
```

This acts similar to an inorder traversal and is useful for test validations.

---

### 🔹 5. **Interactive Menu (Main Program)**

For user interaction, the main program includes a simple menu:

```bash
1. Insert
2. Delete (Leaf only)
3. Traverse
4. Exit
```

The menu runs in a loop, allowing multiple B-Tree operations during execution.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q4b_B_Tree.c -o Q4b_B_Tree
./Q4b_B_Tree
```

---

### 🖥️ Sample Example Output

```bash
===== B-Tree Menu =====
1. Insert
2. Delete (Leaf only)
3. Traverse
4. Exit
Enter choice: 1
Enter value: 5

===== B-Tree Menu =====
Enter choice: 1
Enter value: 10

===== B-Tree Menu =====
Enter choice: 1
Enter value: 20

===== B-Tree Menu =====
Enter choice: 3
B-Tree Traversal: 5 10 20

===== B-Tree Menu =====
Enter choice: 2
Enter value: 10
Key 10 deleted successfully.

===== B-Tree Menu =====
Enter choice: 3
B-Tree Traversal: 5 20

===== B-Tree Menu =====
Enter choice: 2
Enter value: 99
Key 99 does NOT exist in B-Tree.
```

---

## 🧩 MUnit Code Overview

The `test_Q4b_B_Tree.c` file contains automated tests to validate all major B-Tree operations including insertion, search, deletion, and node splitting.

### 🔹 Helper Function

- `traverse_to_array()` — This helper converts B-Tree traversal output into an array so that tests can easily compare the actual structure with expected results.

### 🔹 Test Cases Included

| Test Name | Description |
|----------|-------------|
| `/insert` | Verifies correct insertion order and structure for multiple keys. |
| `/search` | Ensures search returns a non-NULL pointer for existing keys and NULL for missing keys. |
| `/delete_leaf` | Deletes a leaf node and checks if B-Tree reorganizes correctly. |
| `/delete_not_found` | Attempts deletion of a non-existing key and ensures tree remains unchanged. |
| `/root_split` | Inserts enough keys to force a *root split* and validates final B-Tree structure. |

### 🔹 Assertions Used

- `munit_assert_int()` — confirms correct key ordering  
- `munit_assert_ptr_not_null()` — verifies successful search  
- `munit_assert_ptr_null()` — validates key absence  
- These ensure the B-Tree structure and behavior remain correct after each operation.

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q4b_B_Tree.c test_Q4b_B_Tree.c munit.c -o test_Q4b
./test_Q4b
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/BTree_Tests/insert                                                      [ OK    ] 
/BTree_Tests/search                                                      [ OK    ] 
/BTree_Tests/delete_leaf             Key 10 deleted successfully.        [ OK    ] 
/BTree_Tests/delete_not_found        Key 100 does NOT exist in B-Tree.   [ OK    ] 
/BTree_Tests/root_split                                                  [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
