# 🪙 Q3 – Find the Defective (Lighter) Coin (ADSA Lab 01)

## 📘 Problem Description

You are working as a **Quality-Control Engineer** for a coin manufacturing company.  
The company needs to ensure that all coins have **exactly identical weights**.

During inspection, you notice that one worker might have accidentally **over-shaped one coin**, making it possibly **lighter** than others — or maybe not defective at all.

Your task is to find **which coin (if any)** is defective (lighter) using a **divide and conquer algorithm**, which must run in  
**O(log₂ n + c)** time complexity.

You are provided with a **balance weighing scale** and a set of `n` coin weights.

---

## 🎯 Objective

Write a C program to:

1. Find the defective (lighter) coin’s index, if present.
2. Report *no defective coin* if all have the same weight.
3. Implement the logic using **Divide and Conquer**.
4. Verify correctness using **unit testing (MUnit framework)**.

---

## 📂 Code Files

| File Name | Description |
|------------|-------------|
| `Q3_defective_coin.c` | Implements the **Divide and Conquer** algorithm to identify the defective (lighter) coin among `n` coins. Handles both even and odd cases efficiently and displays the index and weight of the defective coin. |
| `test_Q3_defective_coin.c` | Contains **MUnit** test cases to validate the correctness of the defective coin detection algorithm. Tests include cases like all coins perfect, first/last defective, middle defective (odd count), and random distributions. |
| `munit.c` / `munit.h` | The **MUnit testing framework** used to execute and report automated unit test results (included in ADSA Lab setup). |

---

## ⚙️ Features

- Efficiently detects the defective coin using **group-wise comparisons**.
- Works for **both odd and even** number of coins.
- Returns the **index and weight** of the defective coin.
- Follows **O(log n)** time complexity using recursive division.

---

## 🛠️ Algorithm Overview

The algorithm follows a **divide and conquer** approach similar to binary search:

1. **Divide** the set of coins into two halves.
2. **Compare** the total weight of both halves using a balance scale.
3. **Recurse** into the lighter half (if any).
4. **Handle odd-sized groups** by excluding the middle coin for comparison.
5. If both sides are equal:
   - Either all coins are perfect → return `-1`
   - Or the middle coin is defective → return its index.

---

## 🧮 Algorithm Complexity

### ⏱️ Time Complexity

| Operation                     | Time Complexity |
|-------------------------------|------------------|
| Compare two halves (each step) | **O(1)** |
| Halving the search space       | **O(log n)** |
| Overall defective coin search  | **O(log n)** |

📌 **Explanation:**  
- Each iteration compares two groups and eliminates half of the coins.
- Thus, the algorithm follows:

  T(n) = T(n/2) + O(1) → **O(log n)**


---

### 🗃️ Space Complexity

| Component                           | Space Used |
|-------------------------------------|------------|
| Input array of coin weights         | **O(n)**   |
| Variables (`low`, `high`, etc.)     | **O(1)**   |
| No recursion / no extra structures  | **O(1)**   |
| Overall space complexity            | **O(n)**   |

📌 **Explanation:** 
- The algorithm runs **iteratively**, not recursively, and does **not allocate extra arrays**.
- Space usage comes only from the original input of `n` coin weights.

---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc Q3_defective_coin.c -DMAIN_PROGRAM -o Q3
./Q3
```

---

### 📥 Input Format

```bash
Enter number of coins: 7
Enter weights of 7 coins:
7 6 7 7 7 7 7
```

---

### 📤 Output Format
 
 ```bash
Defective (lighter) coin found at index 1 with weight 6
```

---

## 🧩 MUnit Test Code Overview

The **`test_Q3_defective_coin.c`** file uses the **MUnit framework** to automatically verify the correctness of the program.

Each test case provides a specific set of coin weights and checks whether the `findDefective()` function returns the correct index of the lighter coin (or `-1` if all are perfect).

### 🧪 Test Cases Included:

1. **test_defective_present** → Defective coin in the middle.  
2. **test_all_perfect** → All coins have equal weights (no defective).  
3. **test_first_defective** → Defective coin at the beginning.  
4. **test_last_defective** → Defective coin at the end.  
5. **test_odd_count_middle_defective** → Odd number of coins with a middle defective coin.

Each test uses:

 ```bash
munit_assert_int(result, ==, expected_index);
 ```

to confirm that the output matches the expected index.

If all assertions pass, the test suite reports:

 ```bash
[ OK ]
 ```

for every case, indicating successful verification.

---

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_Q3_defective_coin.c munit.c -o test_Q3
./test_Q3
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/Q3_defective_coin/test_defective_present              [ OK ]
/Q3_defective_coin/test_all_perfect                    [ OK ]
/Q3_defective_coin/test_first_defective                [ OK ]
/Q3_defective_coin/test_last_defective                 [ OK ]
/Q3_defective_coin/test_odd_count_middle_defective     [ OK ]
5 of 5 (100%) tests successful
```
