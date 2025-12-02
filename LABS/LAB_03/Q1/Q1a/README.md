# 🔍 Q1(a) – Binary Search (ADSA Lab 03)

## 📘 Problem Statement

Write a **C program** that implements **both recursive and non-recursive functions**  
to perform **Binary Search** for a given key in a **sorted list of integers**.

This experiment demonstrates classic search techniques and compares two approaches:
- **Iterative Binary Search**
- **Recursive Binary Search**

Both approaches are tested thoroughly using the **MUnit testing framework**.

---

## 📂 Code Files

| File Name | Description |
|-----------|-------------|
| `Q1a_binary_search.c` | Contains implementations of both **iterative** and **recursive** binary search methods. Also includes a user-input based main function (disabled during testing). |
| `test_Q1a_binary_search.c` | Contains **MUnit test cases** to validate the binary search implementations. |
| `munit.c` / `munit.h` | Lightweight C unit-testing framework used for automated verification. |

---

## 🧠 Code Overview

This program implements **two binary search functions**:

#### 🔹 `binarySearchIterative(int arr[], int n, int key)`
- Implements binary search using **loop iteration**
- Efficient and avoids overhead of recursion
- Returns:
  - Index of the found element  
  - `-1` if key is not found


#### 🔹 `binarySearchRecursive(int arr[], int low, int high, int key)`
- Implements binary search using **recursion**
- Elegant and simple to understand
- Follows the classic divide-and-conquer pattern


#### 🔹 `main()` (User Input Mode)
- Only compiled when **TEST_MODE is OFF**
- Allows:
  - User to input the size of array  
  - Sorted list of integers  
  - Key to be searched  
- Displays results of:
  - Iterative search  
  - Recursive search  

Wrapped in:

```c
#ifndef TEST_MODE
   // main()
#endif
```

So that MUnit tests do not conflict with your main program.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q1a_binary_search.c -o Q1a_binary_search
./Q1a_binary_search
```

---

### 📥 Input Example

```bash
Enter no. of elements: 7
Enter sorted elements: 2 4 6 8 10 12 14
Enter key to search: 10
```

---

### 📤 Output Example

```bash
Iterative Binary Search Index: 4
Recursive Binary Search Index: 4
```

---

## 🧩 MUnit Code Overview

The `test_Q1a_binary_search.c` file includes **9 automated test cases**  
to validate both the **iterative** and **recursive** implementations of Binary Search.  
These tests ensure correctness, boundary handling, and robustness across various scenarios.



### 🔎 Test Coverage

| Test Case | Description |
|----------|-------------|
| `/iter/basic`        | Basic test for iterative binary search. |
| `/iter/first`        | Searches for the first element in the array. |
| `/iter/last`         | Searches for the last element in the array. |
| `/iter/not_found`    | Tests behavior when the key is absent. |
| `/iter/single`       | Tests search inside a single-element array. |
| `/iter/duplicates`   | Ensures correct behavior with duplicate values. |
| `/rec/basic`         | Basic test for recursive binary search. |
| `/rec/not_found`     | Recursive version handling key not present. |
| `/rec/large`         | Tests recursive search on a large 100-element array. |

---

## 🧠 Key Testing Concepts

#### ✔ Boundary Cases
- First element search  
- Last element search  
- Single-element array  

#### ✔ Failure Cases
- Key not found  
- Duplicate values present  

#### ✔ Performance Cases
- Large array (100 elements) tested with recursive binary search  

#### ✔ Assertions Used
- `munit_assert_int()` — validates returned index  
- `munit_assert_true()` — used for duplicate-value cases  

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q1a_binary_search.c test_Q1a_binary_search.c munit.c -o test_Q1a
./test_Q1a
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/binary_search/iter/basic            [ OK    ] 
/binary_search/iter/first            [ OK    ] 
/binary_search/iter/last             [ OK    ] 
/binary_search/iter/not_found        [ OK    ] 
/binary_search/iter/single           [ OK    ] 
/binary_search/iter/duplicates       [ OK    ] 
/binary_search/rec/basic             [ OK    ] 
/binary_search/rec/not_found         [ OK    ] 
/binary_search/rec/large             [ OK    ] 
9 of 9 (100%) tests successful, 0 (0%) test skipped.
```
