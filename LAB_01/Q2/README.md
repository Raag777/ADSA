## Graph Plot
<img width="720" height="400" alt="image" src="https://github.com/user-attachments/assets/128a1e5c-63f8-4cec-b2f8-58a48aa5620a" />




# 🔍 Binary vs Ternary Search Comparison in C

This C program compares the number of comparisons made by **Binary Search** and **Ternary Search** algorithms when searching for a key in a sorted array. It counts and displays the number of comparisons each algorithm makes, helping visualize their efficiency differences.

---

## 📋 Overview

- **Binary Search** splits the search space into two halves each iteration.
- **Ternary Search** splits the search space into three parts each iteration.
- The program counts the exact number of comparisons performed by each search for a given input.
- This allows empirical comparison of the two search methods.

---

## ⚙️ Features

- Reads size of sorted array and elements from the user.
- Reads the search key.
- Performs both binary and ternary search on the array.
- Outputs the index of the key if found.
- Displays the number of comparisons each search made.
- Suitable for running multiple times with different inputs to gather data for plotting.

---
## 🛠️ Algorithms Explained

### Binary Search
- Compute the middle index `mid`.  
- If `arr[mid] == key` → key found.  
- If `key < arr[mid]` → search the left half.  
- Otherwise → search the right half.  
- Repeat until the key is found or the range is empty.  

**Time Complexity:**  
- Best Case: **O(1)**  
- Worst Case: **O(log₂ n)**  

---

### Ternary Search
- Compute two midpoints:  
  - `mid1 = low + (high - low) / 3`  
  - `mid2 = high - (high - low) / 3`  
- Compare the key with `arr[mid1]` and `arr[mid2]`.  
- Decide which of the three parts to search:  
  - If `key < arr[mid1]` → search left third.  
  - If `key > arr[mid2]` → search right third.  
  - Else → search middle third.  

**Time Complexity:**  
- Best Case: **O(1)**  
- Worst Case: **O(log₃ n)**  

## 📥 Input Format
Enter size of array: 15
Enter 15 sorted elements:
2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
Enter key to search: 24

## 📤 Output Format
Binary Search: Key found at index 11
Ternary Search: Key found at index 11

Binary Search comparisons: 2
Ternary Search comparisons: 5

n, BinaryComparisons, TernaryComparisons : 15 2 5

## 🧑‍💻 Usage
### Compile

```bash
question2.exe
gnuplot -p plot.gp

