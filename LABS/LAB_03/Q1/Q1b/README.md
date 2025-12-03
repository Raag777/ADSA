# 🧮 Q1(b) – Sorting Algorithms (ADSA Lab 03)

## 📘 Problem Statement

Write a **C program** to implement the following sorting algorithms to arrange a given list of integers in **ascending order**:

- **Quick Sort**
- **Merge Sort**
- **Heap Sort**

The program should allow the user to input:
- Array size  
- Array elements  
- Sorting method (Quick / Merge / Heap)

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q1b_sorting.c` | Main program implementing **Quick Sort**, **Merge Sort**, and **Heap Sort** with user input (wrapped in `#ifndef TEST_MODE`). |
| `test_Q1b_sorting.c` | Contains automated **MUnit** test cases validating all three sorting algorithms. |
| `munit.c` / `munit.h` | Testing framework used to execute and verify test cases (provided in ADSA lab setup). |

---

## 🧠 Code Overview

This program provides three classic comparison-based sorting algorithms, each with different performance characteristics:

### 🔹 **1. Quick Sort**  
A fast divide-and-conquer algorithm that chooses a pivot, partitions the array, and recursively sorts the partitions.

- **Average Time Complexity:** O(n log n)  
- **Worst Case:** O(n²)  
- **In-place** sorting  

### 🔹 **2. Merge Sort**  
A stable, reliable divide-and-conquer algorithm that divides the array, sorts halves, and merges them.

- **Guaranteed Time Complexity:** O(n log n)  
- Requires **additional memory**  
- Suitable for linked lists and large datasets  

### 🔹 **3. Heap Sort**  
Uses a **binary heap** to repeatedly extract the maximum element and build sorted array.

- **Time Complexity:** O(n log n)  
- **In-place** sorting  
- Not stable  

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q1b_sorting.c -o Q1b_sorting
./Q1b_sorting
```

---

### 📥 Input Example

```bash
Enter size of array: 5
Enter elements: 9 3 7 1 4

1. Quick Sort
2. Merge Sort
3. Heap Sort
Choose: 1
```

---

### 📤 Output Example

```bash
Sorted Array: 1 3 4 7 9
```

---

## 🧩 MUnit Code Overview

The file **`test_Q1b_sorting.c`** contains automated test cases to verify the correctness of the three sorting algorithms:

- **Quick Sort**
- **Merge Sort**
- **Heap Sort**

Each sorting method is tested on multiple scenarios to ensure correctness, stability, and behavior on edge cases.

---

## 🔍 Components Overview

### **1. Helper Function**

#### `check_sorted(int arr[], int expected[], int n)`
Compares each element of the sorted output with the expected sorted array using:

- `munit_assert_int()` for strict element-by-element comparison.

This ensures that all algorithms produce an identical, correctly sorted array.

---

## 🧪 Test Cases Included

### **Quick Sort Tests**

| Test Name | Description |
|----------|-------------|
| `/quick/basic` | Tests Quick Sort on a normal unsorted array. |
| `/quick/reverse` | Tests Quick Sort on a reverse-sorted array. |
| `/quick/dup` | Tests Quick Sort on an array with all duplicate values. |

---

### **Merge Sort Tests**

| Test Name | Description |
|----------|-------------|
| `/merge/sorted` | Tests Merge Sort on an already sorted array. |
| `/merge/negative` | Tests Merge Sort on an array containing negative numbers. |

---

### **Heap Sort Tests**

| Test Name | Description |
|----------|-------------|
| `/heap/basic` | Tests Heap Sort with mixed values. |
| `/heap/reverse` | Tests Heap Sort on a reverse-sorted array. |
| `/heap/single` | Tests Heap Sort on a single-element array. |

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q1b_sorting.c test_Q1b_sorting.c munit.c -o test_Q1b
./test_Q1b
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/sorting/quick/basic                 [ OK    ] 
/sorting/quick/reverse               [ OK    ] 
/sorting/quick/dup                   [ OK    ] 
/sorting/merge/sorted                [ OK    ] 
/sorting/merge/negative              [ OK    ] 
/sorting/heap/basic                  [ OK    ] 
/sorting/heap/reverse                [ OK    ] 
/sorting/heap/single                 [ OK    ] 
8 of 8 (100%) tests successful, 0 (0%) test skipped.
```
