# 🌲 Q1 – Fibonacci Heap (ADSA LAB08)

## 📘 Problem Statement

Implement a **Fibonacci Heap** supporting the following operations:

- Insert a key  
- Extract-Min  
- Decrease-Key  
- Delete  
- Print root-list  
- Support **node IDs** for reference in decrease/delete  
- Fully compatible with **MUnit test automation**

The implementation follows the classical Fibonacci Heap design supporting amortized:

- **O(1)** insertion  
- **O(1)** find-min  
- **O(1)** decrease-key (amortized)  
- **O(log n)** extract-min  

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Fibonacci_Heap.c` | Full implementation of Fibonacci Heap (all operations). |
| `Fibonacci_Heap.h` | Header file exposing APIs for testing. |
| `test_Fibonacci_Heap.c` | Automated MUnit tests validating heap behavior. |
| `munit.c` / `munit.h` | MUnit testing framework. |

---

## 🧠 Code Overview

This program implements a **Fibonacci Heap** using circular doubly linked lists, lazy linking, and cascading cuts.

### 🔹 1. Insertion

```c
fibHeapInsert(H, createNode(key));
```

- Inserts a new node into the root list
- Updates the global minimum pointer
- Runs in **O(1)** amortized time

### 🔹 2. Extract-Min

```c
fibHeapExtractMin(H);
```

This operation:
1. Removes the min node
2. Moves all children to the root list
3. Performs **consolidation** to merge trees of equal degree
4. Updates the new minimum

Runs in **O(log n)** amortized time.

### 🔹 3. Decrease-Key

```c
fibHeapDecreaseKey(H, node, newKey);
```

- If decreased key becomes smaller than parent →
  - Cut the node
  - Move to root list
  - Apply **cascading-cut**

This is the key to Fibonacci Heap's amortized **O(1)** complexity.

### 🔹 4. Delete Node

```c
fibHeapDelete(H, node);
```

Implemented as:

```scss
decrease-key(node, −∞)
extract-min()
```

### 🔹 5. Find Node by ID

Since each inserted node receives a **unique ID**, the function:

  ```c
  findNodeById(H, id);
  ```

performs DFS over the entire heap structure.

---

## 🧮 Algorithm Complexity

| Operation        | Amortized Time Complexity |
|------------------|---------------------------|
| Insert           | **O(1)**                  |
| Find-Min         | **O(1)**                  |
| Decrease-Key     | **O(1)**                  |
| Merge Heaps      | **O(1)**                  |
| Extract-Min      | **O(log n)**              |
| Delete           | **O(log n)**              |

📌 **Space Complexity**

The Fibonacci Heap uses additional space for:

- Node structures  
- Circular doubly-linked root & child lists  
- Temporary degree array used during consolidation

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Fibonacci_Heap.c -o Fibonacci_Heap
./Fibonacci_Heap
```

---

### 🖥️ Sample Example

```bash
===== Fibonacci Heap Menu =====
1. Insert Key
2. Extract Min
3. Decrease Key (by node id)
4. Delete Node (by node id)
5. Print Root List
6. Exit
Enter choice: 1
Enter key to insert: 5
Inserted node id=1 key=5

===== Fibonacci Heap Menu =====
Enter choice: 1
Enter key to insert: 10
Inserted node id=2 key=10

===== Fibonacci Heap Menu =====
Enter choice: 1
Enter key to insert: 20
Inserted node id=3 key=20

===== Fibonacci Heap Menu =====
Enter choice: 1
Enter key to insert: 40
Inserted node id=4 key=40

===== Fibonacci Heap Menu =====
Enter choice: 1
Enter key to insert: 50
Inserted node id=5 key=50

===== Fibonacci Heap Menu =====
Enter choice: 1
Enter key to insert: 70
Inserted node id=6 key=70

===== Fibonacci Heap Menu =====
Enter choice: 5
Root List: (1:5) (6:70) (5:50) (4:40) (3:20) (2:10) 

===== Fibonacci Heap Menu =====
Enter choice: 2
Extracted Min -> id=1 key=5

===== Fibonacci Heap Menu =====
Enter choice: 5
Root List: (2:10) (3:20) 

===== Fibonacci Heap Menu =====
Enter choice: 3
Enter node id to decrease: 20
Node with id=20 not found.

===== Fibonacci Heap Menu =====
Enter choice: 3
Enter node id to decrease: 3
Current key of id=3 is 20. Enter new smaller key: 15
Decreased node id=3 to key=15

===== Fibonacci Heap Menu =====
Enter choice: 5
Root List: (2:10) (3:15) 

===== Fibonacci Heap Menu =====
Enter choice: 4
Enter node id to delete: 3
Deleted node id=3

===== Fibonacci Heap Menu =====
Enter choice: 5
Root List: (2:10) 

===== Fibonacci Heap Menu =====
Enter choice: 6
Exiting...
```

---

## 🧩 MUnit Code Overview

The file `test_Fibonacci_Heap.c` contains automated MUnit test cases that validate:

- Correct tracking of minimum node  
- Proper heap consolidation after extract-min  
- Cut and cascading-cut behavior during decrease-key  
- Correct deletion handling via decrease-key + extract-min  
- Node ID searching through full heap structure  

### 🔍 What the Tests Check

| Test Case              | Description                                    | Expected Outcome              |
|-----------------------|------------------------------------------------|-------------------------------|
| **/insert**           | Inserts nodes and updates min pointer         | Minimum node tracked correctly |
| **/extract_min**      | Removes smallest key, triggers consolidation   | New min selected correctly     |
| **/decrease_key**     | Cascading cut and heap restructuring           | Updated heap & min pointer     |
| **/delete**           | Node removed safely using delete logic         | Node no longer exists          |
| **/find_node**        | Locates nodes via DFS traversal                | Correct node found / removed   |

### ✔ Tested Functions

```c
fibHeapInsert()
fibHeapExtractMin()
fibHeapDecreaseKey()
fibHeapDelete()
findNodeById()
```

### ✔ Assertions Used

```c
munit_assert_int();
munit_assert_not_null();
munit_assert_null();
```

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Fibonacci_Heap.c test_Fibonacci_Heap.c munit.c -o test_FH
./test_FH
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/fibonacci_heap_tests/insert         [ OK    ] 
/fibonacci_heap_tests/extract_min    [ OK    ] 
/fibonacci_heap_tests/decrease_key   [ OK    ] 
/fibonacci_heap_tests/delete         [ OK    ] 
/fibonacci_heap_tests/find_node      [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
