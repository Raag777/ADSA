# 🧮 Q3 – Infix to Postfix Conversion & Postfix Evaluation (ADSA Lab 03)

## 📘 Problem Statement

Write a C program that uses **stack operations** to perform:

1. **Converting an infix expression to postfix expression**
2. **Evaluating the postfix expression**

This experiment implements stack-based parsing and arithmetic evaluation using both **character stack** and **integer stack**.

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q3_Stack_Infix_Postfix.c` | Main C program that converts infix → postfix and evaluates postfix expressions. |
| `test_Q3_Stack_Infix_Postfix.c` | MUnit-based automated test suite that validates conversion & evaluation logic. |
| `munit.c` / `munit.h` | Testing framework files required to run the unit tests. |

---

## 🧠 Code Overview

### 🔹 1. Infix → Postfix Conversion

The program implements the **Shunting Yard Algorithm** using a character stack.

Key operations:
- Push operators based on precedence  
- Pop until matching parenthesis  
- Append operands directly  
- Final flush of stack to postfix array

**Handled properly:**
- Parentheses  
- Operator precedence (`+ - < * /`)  
- Digits and variables (`A–Z`, `0–9`)

---

### 🔹 2. Postfix Evaluation

Evaluation uses an **integer stack**.

Features:
- Handles digits directly (`'5' → 5`)
- Handles variables (`A, B, C…`)  
- Asks user for value of each variable **only once**
- Supports operators: `+ - * /`

Example:

```bash
Infix: (A+B)C
Postfix: AB+C
Evaluation: (A + B) * C
```

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q3_Stack_Infix_Postfix.c -o Q3_Stack_Infix_Postfix
./Q3_Stack_Infix_Postfix
```

---

### 📥 Input Example

```bash
Enter infix expression: (1+2)*3
```

---

### 📤 Output Example

```bash
Postfix Expression: 12+3*
Postfix Evaluation Result: 9
```

---

## 🧩 MUnit Code Overview

The MUnit test file validates **both major components**:

### ✔️ **1. Infix → Postfix Tests**

| Test Name | Description |
|-----------|-------------|
| `/infix/basic` | Simple conversion (`A+B → AB+`) |
| `/infix/parentheses` | Parenthesis handling (`(A+B)*C → AB+C*`) |

---

### ✔️ **2. Postfix Evaluation Tests (Mocked Inputs)**

Values are fed programmatically (no stdin), using `evaluatePostfixMock()`.

| Test Name | Description |
|-----------|-------------|
| `/eval/variables` | Evaluates expressions with variable values (e.g., `(A+B)*C`) |
| `/eval/digits` | Evaluates digit-only expressions (`23*5+ → 11`) |

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q3_Stack_Infix_Postfix.c test_Q3_Stack_Infix_Postfix.c munit.c -o test_Q3    
./test_Q3
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/Q3_Infix_Postfix_Tests/infix/basic        [ OK    ] 
/Q3_Infix_Postfix_Tests/infix/parentheses  [ OK    ] 
/Q3_Infix_Postfix_Tests/eval/variables     [ OK    ] 
/Q3_Infix_Postfix_Tests/eval/digits        [ OK    ] 
4 of 4 (100%) tests successful, 0 (0%) test skipped.
```
