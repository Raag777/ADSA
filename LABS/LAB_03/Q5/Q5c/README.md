# 🧮 Q5(c) – Floyd–Warshall Algorithm (ADSA Lab 03)

## 📘 Problem Statement
Implement the **Floyd–Warshall algorithm** to compute **all-pairs shortest paths** for a given weighted graph.

The algorithm supports:
- Graphs represented via **Adjacency Matrix**
- Automatic handling of **no-edge = INF**
- Computes shortest distances between **every pair (i, j)**
- Outputs final **distance matrix**

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q5c_FloydWarshall.c` | Full implementation of Floyd–Warshall algorithm. |
| `test_Q5c_FloydWarshall.c` | Automated unit tests using the **MUnit framework**. |
| `munit.c` / `munit.h` | Unit testing framework used for validating Q5c. |

---

## 🧠 Code Overview

### 🔹 1. Floyd–Warshall Input Handling
The program accepts an **N × N adjacency matrix** with the rule:
- `0` means **no edge**, except on diagonal.
- Non-zero values represent weights.

Zeros are converted to **INF (99999)** for correct APSP processing.


### 🔹 2. Core Floyd–Warshall Logic

For every intermediate node `k`, update:

```bash
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

This computes shortest paths between **all pairs**.


### 🔹 3. Output Format

The final matrix prints:

- Actual distance values  
- `INF` when no path exists

Example output:

```bash
All-Pairs Shortest Path Matrix:
0 3 5 INF
3 0 2 6
5 2 0 4
INF 6 4 0
```

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q5c_FloydWarshall.c -o Q5c_FloydWarshall
./Q5c_FloydWarshall
```

---

### 📥 Input Example

```bash
Enter number of vertices: 3
Enter adjacency matrix (0 for no edge, except diagonal):
0 3 0
2 0 4
0 1 0
```

---

### 📤 Output Example

```bash
All-Pairs Shortest Path Matrix:
0 3 7
2 0 4
3 1 0
```

---

## 🧩 MUnit Code Overview

The `test_Q5c_FloydWarshall.c` file validates the correctness of:
- Graph initialization  
- INF conversion  
- Floyd–Warshall path updates  
- Correct shortest-path outputs  

### ✔ Test Cases Included

| Test Name | Description |
|----------|-------------|
| `/basic_graph` | Verifies APSP on a simple weighted graph. |
| `/disconnected_graph` | Ensures INF is preserved where no path exists. |
| `/triangle_graph` | Checks shortest path through intermediate nodes. |

### ✔ Assertions Used

| Assertion | Purpose |
|----------|----------|
| `munit_assert_int()` | Validates computed shortest distances |
| `munit_assert_true()` | Checks derived relations like `dist[i][j] <= dist[i][k] + dist[k][j]` |

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q5c_FloydWarshall.c test_Q5c_FloydWarshall.c munit.c -o test_Q5c
./test_Q5c
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/FloydWarshall_Tests/basic_fw        [ OK    ] 
/FloydWarshall_Tests/with_inf        [ OK    ] 
/FloydWarshall_Tests/4node_graph     [ OK    ] 
3 of 3 (100%) tests successful, 0 (0%) test skipped.
```
