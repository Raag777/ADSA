# 🪙 Defective Coin Finder

This C program finds the **defective (lighter) coin** among a set of coins using a **binary search + divide-and-conquer strategy**.  
It assumes that **all coins have equal weight except one lighter coin**.

---

## 📌 Features
- Efficiently locates the defective coin using comparisons of group sums.
- Works for both **odd and even numbers of coins**.
- Returns the **index and weight** of the defective coin.

---

## 📂 Algorithm
1. Split the coins into two halves.
2. Compare the **sum of the left half** and the **sum of the right half**.
   - If left sum is smaller → defective coin is in the left half.
   - If right sum is smaller → defective coin is in the right half.
   - If both sums are equal → the middle coin (in case of odd count) is defective.
3. Repeat the process until only one coin remains.

Time complexity is approximately **O(n log n)** due to repeated summation.

---
### 📊 Recurrence and Solution

Let $T(n)$ be the worst-case number of steps for an input of size $n$.  

T(n) = T((n/2)) + O(1)

---

#### 🔹 Applying (repeated substitution)

T(n) = T((n/2)) + c  
     = T((n/4)) + 2c  
     = ...  
     = T((n/2^k)) + kc  

Stop when the subproblem size is 1:

(n / 2^k) = 1  ⇒  k = log₂ n  

Thus,

T(n) = T(1) + c log₂ n = O(log n)

---

#### 🔹 Base-change note

The base of the logarithm only changes the constant factor:

logₐ n = (log_b n) / (log_b a)

---

#### 🔹 Inductive view (interval halving)

After each iteration, the interval length halves:

n → n/2 → n/4 → ... → n/2^k  

After k = ⌈log₂ n⌉ iterations, the interval size is ≤ 1, so the search finishes.  
Hence, worst-case comparisons grow as:

Θ(log n)

**INPUT**

Enter number of coins: 7

Enter weights of 7 coins: 7 6 7 7 7 7 7

**OUTPUT**

Defective (lighter) coin found at index 1 with weight 6


## 🧑‍💻 Usage

### Compile

```bash
Q3.exe
