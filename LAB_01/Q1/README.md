# 📊 Function Growth Comparison

This repository contains a C program that compares the growth of multiple mathematical functions for values of `n` in a given range.  
It calculates each function, the **average value** across all functions, and prints the results in **increasing order** with respect to `n`.

---

## 📖 Functions Implemented

The program evaluates the following functions:

1. **f1(n) = 1/n**  
2. **f2(n) = log₂(n)**  
3. **f3(n) = 12√n**  
4. **f4(n) = 50√n**  
5. **f5(n) = n^0.51**  
6. **f6(n) = n·log₂(n)**  
7. **f7(n) = n² – 324**  
8. **f8(n) = 100n² + 6n**  
9. **f9(n) = 2n³**  
10. **f10(n) = n^(log₂(n))**  
11. **f11(n) = 3^n**  
12. **f12(n) = n·2³²**  

---

## 🛠️ How It Works

1. The user specifies:
   - **Start value of n**
   - **End value of n**
   - **Step size**
2. For each `n` in the range:
   - All 12 functions are computed.  
   - The **average value** of the functions is calculated.  
   - The functions are sorted in **increasing order**.  
   - Each function is compared with the average (`< average`, `= average`, `> average`).  

---

## 📥 Input Format
The program prompts the user:

Enter start value of n: <start>

Enter end value of n: <end>

Enter step size: <step>

---

## 📤 Output Format

For each `n`, the program prints:

1. Current value of `n`  
2. Average of all function values  
3. Functions in **increasing order**, along with their values and relation to the average  

---

## 🧑‍💻 Usage

### 🔧 Compile

```bash
question1.exe
