# 🪙 Q3 – Find the Defective (Lighter) Coin (ADSA Lab 01)

## 📘 Problem Statement
This C program identifies the **defective (lighter) coin** among a set of coins using a **Divide and Conquer** approach inspired by **binary search**.  
It assumes all coins have **identical weights** except one that is **lighter**.

---

## ⚙️ Features
- Efficiently detects the defective coin using **group-wise comparisons**.
- Works for **both odd and even** number of coins.
- Returns the **index and weight** of the defective coin.
- Follows **O(log n)** time complexity using recursive division.

---

## 🛠️ Algorithm Steps
1. **Divide** the coins into two halves.
2. **Compare** the total weight of the left half and right half:
   - If left < right → defective coin is in **left half**.
   - If right < left → defective coin is in **right half**.
   - If equal → the **middle coin** (if any) is defective.
3. **Repeat recursively** until only one coin remains.
4. Return its **index and weight**.

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

## 📥 Input Format

```bash
Enter number of coins: 7
Enter weights of 7 coins:
7 6 7 7 7 7 7
```

---

## 📤 Output Format
 
 ```bash
Defective (lighter) coin found at index 1 with weight 6
```

---

## 🧪 Unit Testing (MUnit)

To verify correctness, run the MUnit test suite:

### ▶️ Compile and Run MUnit Tests

```bash
gcc test_Q3_defective_coin.c munit.c -o test_Q3
./test_Q3
```

---

### 🧾 Sample Output

```bash
Running test suite with seed 0x15534978...
/Q3_defective_coin/test_defective_present              [ OK ]
/Q3_defective_coin/test_all_perfect                    [ OK ]
/Q3_defective_coin/test_first_defective                [ OK ]
/Q3_defective_coin/test_last_defective                 [ OK ]
/Q3_defective_coin/test_odd_count_middle_defective     [ OK ]
5 of 5 (100%) tests successful
```
