# 🔍 Q3 – Knuth–Morris–Pratt (KMP) String Searching Algorithm (ADSA LAB08)

## 📘 Problem Statement
Implement the **KMP pattern matching algorithm** in C to efficiently search a substring (pattern) inside a text string using **prefix table (LPS array)** to skip redundant comparisons.

The program must:
- Accept **text** and **pattern**
- Build **LPS (Longest Prefix–Suffix) table**
- Perform **efficient string search**
- Display all occurrences (starting indices)

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `KMP.c` | Contains full implementation of KMP pattern matching and menu driver |
| `test_KMP.c` | Contains automated **MUnit test cases** validating algorithm correctness |
| `munit.c` / `munit.h` | Testing framework used to run the test suite |

---

## 🧠 Code Overview

This program implements the **Knuth–Morris–Pratt (KMP) pattern searching algorithm** using efficient preprocessing and linear-time substring matching.

### 🔹 1. LPS (Prefix Table) Construction

```c
computeLPS(pattern, m, lps);
```

- Builds the **Longest Prefix-Suffix (LPS)** table
- Identifies how much shift to apply upon mismatch
- Enables skipping re-comparisons
- Runs in **O(m)** time

### 🔹 2. Pattern Search

```c
KMPsearch(text, pattern);
```

This operation:

1. Uses the LPS table  
2. Matches characters without restarting comparisons  
3. Tracks the starting index of each match  

Ensures efficient scanning in **linear time**.

### 🔹 3. Handling Mismatches

Instead of backing up text pointer:

```c
j = lps[j - 1];
```

This efficiently repositions the pattern pointer using the precomputed table.

📌 This avoids redundant comparisons — the key reason KMP outperforms naive search.

---

## 🧮 Algorithm Complexity

| Component                     | Time Complexity |
|------------------------------|-----------------|
| LPS preprocessing            | **O(m)**        |
| Pattern matching phase       | **O(n)**        |
| **Total Time Complexity**    | **O(n + m)**    |
| Space Complexity             | **O(m)**        |

Where:  
- `n` → length of text  
- `m` → length of pattern  

The algorithm is optimal for string search because it performs running and preprocessing in **linear time** without backtracking over text.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc KMP.c -o KMP
./KMP
```

---

### 🖥️ Sample Example

```bash
===== KMP STRING MATCHING MENU =====
1. Enter Text
2. Enter Pattern
3. Search Pattern in Text
4. Exit
Enter your choice: 1
Enter text: ababcabcabababd

===== KMP STRING MATCHING MENU =====
Enter your choice: 2 
Enter pattern: ababd

===== KMP STRING MATCHING MENU =====
Enter your choice: 3

Searching occurrences...
Pattern found at index 10

===== KMP STRING MATCHING MENU =====
Enter your choice: 4
Exiting...
```

---

## 🧩 MUnit Code Overview

The file `test_KMP.c` includes automated tests that validate:

| Test Case | What It Checks |
|----------|----------------|
| `/lps` | Correct computation of LPS table |
| `/single_match` | Detection of one occurrence |
| `/multiple_match` | Detection of overlapping matches |
| `/no_match` | No false match |
| `/exact_match` | Pattern = text case |

✔ Uses `munit_assert_int()` to verify correctness.  
✔ Confirms both LPS preprocessing and KMP search logic.

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE KMP.c test_KMP.c munit.c -o test_KMP
./test_KMP
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/kmp_tests/lps                       [ OK    ] 
/kmp_tests/single_match              [ OK    ] 
/kmp_tests/multiple_match            [ OK    ] 
/kmp_tests/no_match                  [ OK    ] 
/kmp_tests/exact_match               [ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
