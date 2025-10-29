# 🔍 Q2 - Binary vs Ternary Search Comparison in C (ADSA Lab 01)

## 📘 Problem Statement
This project implements and compares **Binary Search** and **Ternary Search** algorithms in C.  
It measures and displays the number of comparisons made by each algorithm while searching for a given key in a sorted array.  
The results can also be visualized graphically using **Gnuplot**, and verified automatically using **MUnit tests**.

---

## 🧠 Overview

- **Binary Search** divides the search space into 2 halves each iteration.  
- **Ternary Search** divides it into 3 nearly equal parts each iteration.  
- Both algorithms are implemented and compared based on the **number of comparisons** made.  
- Data is automatically written to **`output.dat`** for graph plotting using **`plot.gp`**.

---

## ⚙️ Features

- Takes input of array size, sorted elements, and key to search.  
- Performs both **Binary** and **Ternary** search operations.  
- Displays index if the key is found.  
- Prints the total number of comparisons for each search.  
- Appends results `(n, BinaryComparisons, TernaryComparisons)` to **`output.dat`**.  
- Includes **MUnit-based test file** to verify correctness through automated test cases.  

---

## 🛠️ Algorithms Explained

### 🔹 Binary Search
1. Compute middle index:  
   `mid = low + (high - low) / 2`
2. If `arr[mid] == key` → key found.  
3. If `key < arr[mid]` → search left half.  
4. Else → search right half.

**Complexity:**  
- Best Case → **O(1)**  
- Worst Case → **O(log₂ n)**  

---

### 🔸 Ternary Search
1. Compute two midpoints:  
   - `mid1 = low + (high - low) / 3`  
   - `mid2 = high - (high - low) / 3`
2. Compare `key` with both midpoints.  
3. Depending on range:  
   - `key < arr[mid1]` → search left third  
   - `key > arr[mid2]` → search right third  
   - Else → search middle third

**Complexity:**  
- Best Case → **O(1)**  
- Worst Case → **O(log₃ n)**  

---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc ternary_binary_search.c -o main
./main
```

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_ternary_binary_search.c munit.c -o test_search
./test_search
```

---

### 📥 Input Example

```bash
Enter size of array: 15
Enter 15 sorted elements:
2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
Enter key to search: 24
```

---

### 📤 Output Example

```bash
=== Results ===
Binary Search: Key found at index 11
Ternary Search: Key found at index 11

Comparisons made:
Binary Search comparisons: 2
Ternary Search comparisons: 5

n, BinaryComparisons, TernaryComparisons : 15 2 5

Data saved to output.dat
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/ternary_binary_search_tests/key_present        [ OK    ] 
/ternary_binary_search_tests/key_not_present    [ OK    ] 
/ternary_binary_search_tests/first_element      [ OK    ] 
/ternary_binary_search_tests/last_element       [ OK    ] 
/ternary_binary_search_tests/comparison_counts  [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```

---

## 📊 Graph Plot

After collecting multiple runs (which append data to **`output.dat`**), you can visualize the comparison using **Gnuplot**.

### 🧩 Steps

Run your program multiple times with increasing n (e.g., 5, 7, 10, 15, 20).

Then plot results with:

```bash
gnuplot -p plot.gp
```

### 📈 Sample Graph Output

<img width="1920" height="1023" alt="image" src="https://github.com/user-attachments/assets/fded45f6-e682-4c00-9b95-16982583c872" />

