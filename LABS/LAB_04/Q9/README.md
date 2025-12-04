# 🧮 Q9 – KMP Algorithm & Rabin–Karp Fingerprinting (ADSA Lab 04)

## 📘 Problem Statement

Write a program to implement:

- **Knuth–Morris–Pratt (KMP) String Matching Algorithm**
- **Rabin–Karp Fingerprinting Algorithm**

Both algorithms are used for **pattern searching** inside a given text and report all valid match positions.

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q9_KMP_RabinKarp.c` | Full implementation of **KMP** (LPS table + search) and **Rabin–Karp** (rolling hash) pattern matching algorithms. |
| `test_Q9_KMP_RK.c` | MUnit test suite that validates LPS array, KMP matches, Rabin–Karp matches, no-match behavior, multiple match cases, and exact match correctness. |
| `munit.c` / `munit.h` | MUnit framework used for automated testing. |

---

## 🧠 Code Overview

This program implements **two major string-search algorithms**:

### 🔹 1. **Knuth–Morris–Pratt (KMP) Algorithm**

KMP improves naive matching by avoiding unnecessary comparisons.

It uses:

- **LPS (Longest Prefix Suffix) array**
- Efficient skipping of characters on mismatch
- Time complexity: **O(n + m)**

Key functions:

```c
void computeLPS(char* pattern, int m, int lps[]);
void KMP(char* text, char* pattern);
```

### 🔹 2. **Rabin–Karp Fingerprinting Algorithm**

Rabin–Karp uses **rolling hash** to detect substring occurrences.
- Uses base **d = 256** and modulo **q = 101**
- Faster average-case for multi-pattern search
- Time complexity: **O(n + m)** average

Key function:

```c
void RabinKarp(char* text, char* pattern);
```

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q9_KMP_RabinKarp.c -o Q9_KMP_RabinKarp
./Q9_KMP_RabinKarp
```

---

### 📥 Input Example

```bash
Enter text string: ABABDABACDABABCABAB
Enter pattern string: ABABCABAB
```

---

### 📤 Output Example

```bash
-----------------------------
Knuth-Morris-Pratt (KMP) Algorithm
-----------------------------
KMP Matches found at positions: 10 

-----------------------------
Rabin-Karp Fingerprinting Algorithm
-----------------------------
Rabin-Karp Matches found at positions: 10
```

---

## 🧩 MUnit Code Overview

The file `test_Q9_KMP_RK.c` contains a full automated test suite that verifies the correctness of both **KMP** and **Rabin–Karp** algorithms.

### ✔ What Is Tested?

| Test Name | Purpose |
|-----------|---------|
| `/lps/compute` | Validates correctness of the **LPS (Longest Prefix Suffix)** array for a known pattern. |
| `/kmp/basic` | Ensures KMP correctly identifies match positions in the sample text. |
| `/rk/basic` | Ensures Rabin–Karp finds the same match locations as KMP. |
| `/match/none` | Validates that both algorithms return **no matches** when the pattern does not appear in the text. |
| `/match/multiple` | Ensures detection of **all overlapping matches** (ex: pattern `"AAA"` inside `"AAAAAA"`). |
| `/match/exact` | Verifies behavior when **pattern = text** (match expected at index 0). |

### 🔍 How Tests Work

Each test captures algorithm output using:

```c
capture_output(KMP, text, pattern, output);
capture_output(RabinKarp, text, pattern, output);
```

### ✔ Assertions Used

```c
munit_assert_int();
munit_assert_not_null();
munit_assert_null();
munit_assert_string_equal();
```

### 🧪 What These Tests Guarantee

- Correct and complete construction of the **LPS array**
- Accurate match detection by both algorithms
- Proper handling of patterns that do not appear in the text
- Correct reporting of **multiple** and **overlapping** matches
- Proper behavior when pattern matches the entire text

This ensures both algorithms are **functionally correct**, **edge-case safe**, and **fully validated** against known results.

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q9_KMP_RabinKarp.c test_Q9_KMP_RK.c munit.c -o test_Q9
./test_Q9
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/Q9_KMP_RK_Tests/lps/compute         [ OK    ] 
/Q9_KMP_RK_Tests/kmp/basic           [ OK    ] 
/Q9_KMP_RK_Tests/rk/basic            [ OK    ] 
/Q9_KMP_RK_Tests/match/none          [ OK    ] 
/Q9_KMP_RK_Tests/match/multiple      [ OK    ] 
/Q9_KMP_RK_Tests/match/exact         [ OK    ] 
6 of 6 (100%) tests successful, 0 (0%) test skipped.
```
