# 🧮 Q1(c) – Quick Sort Using Median-of-Three Pivot (ADSA Lab 03)

## 📘 Problem Statement

Write a **C program** to implement **Quick Sort** using the **Median-of-Three pivot selection method** to sort a given list of integers in **ascending order**.

This improves pivot stability and reduces the chance of worst-case performance.

---

## 📂 Code Files

| File Name | Description |
|------------|-------------|
| `Q1c_quick_sort_median.c` | Contains the implementation of Quick Sort using the Median-of-Three pivot strategy. Includes optional main() for user input when not in testing mode. |
| `test_Q1c_quick_sort_median.c` | Contains automated **MUnit** test cases to verify correctness under multiple input scenarios. |
| `munit.c` / `munit.h` | Unit testing framework used to run and validate all tests (provided in ADSA lab setup). |

---

## 🧠 Code Overview

This program performs **Quick Sort** but selects a pivot using the **Median-of-Three** technique:

1. Pick the first, middle, and last elements of the array.
2. Sort these three values.
3. Use the **median** as the pivot.
4. Swap the median with the last element.
5. Continue with standard Quick Sort partitioning.

This improves performance on:

- Already sorted arrays  
- Reverse sorted arrays  
- Partially ordered inputs  

### 🔹 Key Functions

| Function | Description |
|----------|-------------|
| `medianOfThree(arr, low, mid, high)` | Determines the median among the first, middle, and last elements. |
| `partitionMedian(arr, low, high)` | Creates partition using the median pivot. |
| `quickSortMedian(arr, low, high)` | Recursively sorts the array using the custom partition function. |
| `printArray(arr, n)` | Helper function for output formatting. |

The `main()` function is wrapped in:

```c
#ifndef TEST_MODE
   // main() code...
#endif
```

So that the file can be compiled with or without MUnit tests cleanly.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q1c_quick_sort_median.c -o Q1c_quick_sort_median
./Q1c_quick_sort_median
```

---

### 📥 Input Example

```bash
Enter array size: 5
Enter elements: 9 3 7 1 6
```

---

### 📤 Output Example

```bash
Sorted using Quick Sort (Median-of-Three): 1 3 6 7 9
```

---

## 🧩 MUnit Code Overview

The file **`test_Q1c_quick_sort_median.c`** validates the *Quick Sort (Median-of-Three pivot)* implementation using  
multiple, well-structured MUnit test cases to ensure correctness across a wide variety of input conditions.

---

## 🔍 Components Overview


1. **Helper Function**
   - `assert_sorted()`  
     Verifies that the resulting array matches the expected sorted output element-wise.

2. **Six Comprehensive Test Scenarios**

| Test Name       | Description |
|-----------------|-------------|
| `/basic`        | Tests the algorithm on a standard unsorted random input. |
| `/sorted`       | Ensures that already sorted arrays remain unchanged. |
| `/reverse`      | Checks sorting correctness on reverse-ordered arrays. |
| `/duplicates`   | Confirms behavior when all elements are identical. |
| `/single`       | Validates correct handling of a single-element list. |
| `/negative`     | Tests sorting with negative and mixed integers. |

3. **Assertions Used**
   - `munit_assert_int()` — Compares individual array elements.
   - `assert_sorted()` — Compares two complete sequences to ensure exact sorted output.

All test cases run independently within a structured **MUnit test suite**, providing a reliable verification framework for the Quick Sort (Median-of-Three) implementation.

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q1c_quick_sort_median.c test_Q1c_quick_sort_median.c munit.c -o test_Q1c
./test_Q1c
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/quick_sort_median/basic             [ OK    ] 
/quick_sort_median/sorted            [ OK    ] 
/quick_sort_median/reverse           [ OK    ] 
/quick_sort_median/duplicates        [ OK    ] 
/quick_sort_median/single            [ OK    ] 
/quick_sort_median/negative          [ OK    ] 
6 of 6 (100%) tests successful, 0 (0%) test skipped.
```
