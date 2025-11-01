# 🔢 Q4 – Heap Sort in C (ADSA Lab 01)

This project implements the **Heap Sort algorithm** in C and verifies its correctness using the **MUnit testing framework**.  
Heap Sort is a **comparison-based**, **in-place**, and **O(n log n)** sorting algorithm built on the **Binary Heap** data structure.

---

## 📘 Objective
To implement and test **Heap Sort** for sorting an array of integers in ascending order.  
The testing ensures correctness for multiple cases including sorted, reverse, single-element, and duplicate arrays.

---

## 📂 Files Included

| File | Description |
|------|--------------|
| `Q4_heapsort.c` | Contains the Heap Sort implementation (with optional `main()` for manual input). |
| `test_Q4_heapsort.c` | MUnit test cases verifying Heap Sort’s correctness. |
| `munit.c` / `munit.h` | External MUnit framework files used for testing. |

---

## ⚙️ Algorithm Steps
1. **Build a Max Heap** from the input array.  
2. **Swap** the first (largest) element with the last unsorted element.  
3. **Reduce heap size** and call `heapify()` again to restore the heap property.  
4. **Repeat** until the array is sorted in ascending order.

---

## 💻 Functions Overview

| Function | Description |
|-----------|--------------|
| `heapify(int arr[], int n, int i)` | Ensures the max-heap property for a subtree rooted at index `i`. |
| `heapSort(int arr[], int n)` | Sorts the array using repeated heap construction and extraction. |
| `main()` *(optional)* | Takes input, calls `heapSort()`, and prints the sorted array. |

---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc Q4_heapsort.c -DMAIN_PROGRAM -o Q4
./Q4
```

---

### 📥 Input Format

```bash
Enter number of elements: 5
Enter 5 elements:
9 3 7 1 8
```

---

### 📤 Output Format

```bash
Sorted array: 1 3 7 8 9
```

---

## 🧩 MUnit Code Overview

The file `test_Q4_heapsort.c` includes **five automated test cases** that verify the correctness of the `heapSort()` function under different conditions.  
Each test case:
- Initializes an input array and an `expected` sorted array.  
- Calls the `heapSort()` function from `Q4_heapsort.c`.  
- Uses `munit_assert_int()` to compare each element of the output with the expected sorted values.  
- Returns `MUNIT_OK` if all comparisons pass successfully.  

The following test cases are defined:
1. **Basic Test** – Random unsorted input array.  
2. **Sorted Input Test** – Already sorted array remains unchanged.  
3. **Reverse Input Test** – Reverse-sorted array is properly sorted.  
4. **Single Element Test** – Edge case with one element.  
5. **Duplicate Elements Test** – Ensures correct handling of repeated values.  

If all tests succeed, MUnit displays:

```bash
[ OK ]
```

for each test case, indicating successful verification.

---

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_Q4_heapsort.c munit.c -o test_Q4
./test_Q4
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/heap_sort_tests/heap_sort_basic           [ OK    ] 
/heap_sort_tests/heap_sort_sorted_input    [ OK    ] 
/heap_sort_tests/heap_sort_reverse_input   [ OK    ] 
/heap_sort_tests/heap_sort_single_element  [ OK    ] 
/heap_sort_tests/heap_sort_duplicates      [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
