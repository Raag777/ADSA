## Graph Plot
<img width="900" height="400" alt="image" src="https://github.com/user-attachments/assets/128a1e5c-63f8-4cec-b2f8-58a48aa5620a" />




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

## 🧑‍💻 Usage

### Compile

```bash
question2.exe
gnuplot -p plot.gp
