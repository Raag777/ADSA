# 🪙 Defective Coin Finder (Lighter Coin Detection)

This C program identifies the defective (lighter) coin among a set of coins using a modified binary search algorithm. The algorithm efficiently narrows down the defective coin by comparing sums of halves, minimizing the number of weighings.

---

## 📋 Overview

Given `n` coins where all except one have the same weight, this program finds the index of the lighter (defective) coin by repeatedly dividing the coins into halves and comparing their total weights.

---

## ⚙️ Features

- Input number of coins and their individual weights.
- Efficiently finds the lighter coin using a divide-and-conquer approach.
- Handles both even and odd number of coins.
- Prints the index and weight of the defective coin.

---

## 🧑‍💻 Usage

### Compile

```bash
gcc -o defective_coin defective_coin.c
