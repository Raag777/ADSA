# 🧮 Q8 – Longest Common Subsequence [LCS] (ADSA Lab 04) 

## 📘 Problem Statement  
Write a program to compute the **Longest Common Subsequence (LCS)** between two strings using **Dynamic Programming (DP)**.  
The program must:  
- Compute and print the **length** of the LCS  
- Print **one** valid LCS  
- Generate and print **all possible LCS strings** using recursion  

---

## 📂 Code Files  

| File Name | Description |
|----------|-------------|
| `Q8_LCS.c` | Implements DP-based LCS length calculation, single LCS traceback, and recursive generation of **all possible LCS strings**. |
| `test_Q8_LCS.c` | Automated **MUnit test suite** verifying LCS length and correctness of generated LCS sets across multiple test cases. |
| `munit.c` / `munit.h` | MUnit framework used to execute tests. |

---

## 🧠 Code Overview  

This program uses **Dynamic Programming** to compute the LCS of two strings `X` and `Y`.

### 🔹 1. **LCS Length Table (DP Matrix)**  
The DP table is built with:

```c
dp[i][j] = length of LCS between X[0..i-1] and Y[0..j-1]
```

Rules:
- If characters match → extend LCS
- Else → take maximum of left/top cell

Time Complexity: **O(m × n)**

Space Complexity: **O(m × n)**

### 🔹 2. **Generate ONE LCS (Standard Backtracking)**

The program traces back from `dp[m][n]` to print a single valid LCS:

```c
if (X[i-1] == Y[j-1]) → choose diagonal  
else choose larger of dp[i-1][j] and dp[i][j-1]
```

### 🔹 3. **Generate ALL LCS Strings (Recursive Backtracking)**

A recursive function:

```c
Node* getAllLCS(char* X, char* Y, int m, int n)
```

is used to produce **all distinct LCS strings**, avoiding duplicates using a linked list.

Cases:
- If characters match → append char and recurse
- Else → explore branches where DP value does not decrease
- Use a linked list to avoid duplicate solutions

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q8_LCS.c -o Q8_LCS
./Q8_LCS
```

---

### 📥 Input Example

```bash
Enter first string: ABCBDAB
Enter second string: BDCABA
```

---

### 📤 Output Example

```bash
Length of LCS = 4
One LCS: BDAB

All LCS strings:
BCAB
BDAB
BCBA
```

---

## 🧩 MUnit Code Overview

The file **`test_Q8_LCS.c`** contains automated MUnit test cases that verify the correctness of the LCS implementation in `Q8_LCS.c`.

### 🔍 What the Tests Check

| Test Case              | Input Strings                 | Expected Output                                              |
|------------------------|------------------------------|--------------------------------------------------------------|
| **/basic/lcs**         | `"ABCBDAB"` vs `"BDCABA"`    | LCS length = **4**; all LCS include: **BCAB**, **BDAB**, **BCBA** |
| **/edge/no_common**    | `"AAAA"` vs `"BBBB"`          | LCS length = **0**; only LCS is `""`                         |
| **/edge/identical**    | `"ABCDEFG"` vs `"ABCDEFG"`    | Full string `"ABCDEFG"` is the LCS                          |
| **/repeat/chars**      | `"AAAAAA"` vs `"AAA"`         | LCS = `"AAA"`                                                |

### ✔ Tested Functions

```c
computeLCSLength(X, Y);
getAllLCS(X, Y, m, n);
```

### ✔ Assertions Used

```c
munit_assert_int();
munit_assert_string_equal();
munit_assert_true();
```

### ✔ What These Tests Validate

- Accurate **DP table** construction
- Correct **LCS length**
- Correct collection of **all unique LCS strings**
- Avoids duplicate subsequences
- Works across edge cases (no common chars, identical strings, repeated chars)

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q8_LCS.c test_Q8_LCS.c munit.c -o test_Q8
./test_Q8
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/Q8_LCS_Tests/basic/lcs              [ OK    ] 
/Q8_LCS_Tests/edge/no_common         [ OK    ] 
/Q8_LCS_Tests/edge/identical         [ OK    ] 
/Q8_LCS_Tests/repeat/chars           [ OK    ] 
4 of 4 (100%) tests successful, 0 (0%) test skipped.
```
