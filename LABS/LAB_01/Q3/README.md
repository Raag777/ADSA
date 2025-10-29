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

### 🔹 Time Complexity
- Each comparison halves the problem size → **O(log₂ n + c)**

---

## 📊 Recurrence and Solution

Let T(n) be the worst-case number of steps for an input of size *n*.

**T(n) = T(n / 2) + O(1)**

---

### 🔹 Applying (Repeated Substitution)

T(n) = T(n / 2) + c  
     = T(n / 4) + 2c  
     = ...  
     = T(n / 2ᵏ) + k·c

Stop when the subproblem size becomes 1:

n / 2ᵏ = 1  ⇒  k = log₂ n

Hence,

T(n) = T(1) + c·log₂ n  
**T(n) = O(log n)**

---

### 🔹 Base-Change Note

Changing the logarithm base only affects the constant factor:

logₐ n = (log_b n) / (log_b a)

---

### 🔹 Inductive View (Interval Halving)

At each step, the number of coins considered halves:

n → n/2 → n/4 → ... → n/2ᵏ

After **k = ⌈log₂ n⌉** iterations, only one coin remains. 

Thus, the worst-case number of comparisons grows as:

**Θ(log n)**

 ---

## 🧑‍💻 Usage

### ▶️ Compile and Run Main Program

```bash
gcc Q3_defective_coin.c -DMAIN_PROGRAM -o Q3
./Q3
```

---

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_Q3_defective_coin.c munit.c -o test_Q3
./test_Q3
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
