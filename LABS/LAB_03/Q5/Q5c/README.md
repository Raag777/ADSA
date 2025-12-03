# 🧮 Q5(c) – Floyd–Warshall Algorithm (ADSA Lab 03)

## 📘 Problem Statement
Write a program to compute **All-Pairs Shortest Paths (APSP)** using the **Floyd–Warshall Algorithm** for a weighted graph represented using an **Adjacency Matrix**.

The program must:
- Accept an **N × N adjacency matrix**
- Treat `0` as **no edge** (except diagonal)
- Convert missing edges to **INF (99999)**
- Compute shortest paths between **every pair of vertices (i, j)**
- Output the final **APSP matrix**
---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q5c_FloydWarshall.c` | Complete implementation of Floyd–Warshall with user input mode. |
| `test_Q5c_FloydWarshall.c` | Automated unit tests using the **MUnit framework**. |
| `munit.c` / `munit.h` | Unit testing framework (provided in ADSA lab setup). |

---

## 🧠 Code Overview

This program implements the **Floyd–Warshall Algorithm**, which computes shortest paths between all node pairs in a weighted graph.

### 🔹 1. Input Handling
The input graph is taken as an adjacency matrix.  
Rules applied:
- `dist[i][j] = 0` and `i != j` ➝ treated as **no edge**
- Such entries are converted to:

```c
INF  // 99999
```

### 🔹 2. Core Floyd–Warshall Logic

For every intermediate node `k`, update all distances:

```bash
if (dist[i][k] + dist[k][j] < dist[i][j])
    dist[i][j] = dist[i][k] + dist[k][j];
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

The file **`test_Q5c_FloydWarshall.c`** contains automated unit tests that verify the correctness of the **Floyd–Warshall All-Pairs Shortest Path (APSP) implementation**.

These tests ensure that:
- The algorithm correctly handles **INF (99999)** for disconnected nodes  
- Shortest paths are properly **updated using intermediate nodes**  
- The final **distance matrix** matches expected APSP results  
- The function behaves correctly without using `scanf`, using direct matrix inputs  


### 🔍 What the Test Suite Checks

| Test Name | Purpose |
|----------|----------|
| `/basic_fw` | Verifies APSP on a simple 3-node graph (checks path 0 → 1 → 2). |
| `/with_inf` | Ensures unreachable nodes remain **INF** and reachable ones update properly. |
| `/4node_graph` | Tests multi-hop shortest paths on a 4-node weighted graph. |

Each test provides a matrix to the function, calls `floydWarshall(n, dist)` and validates the updated values.


### ✔️ Assertions Used

The following MUnit assertions ensure correctness:

- `munit_assert_int()` – Validates shortest path correctness such as:

  ```c
  munit_assert_int(dist[0][2], ==, 6);
  ```
- `munit_assert_true()` – Used to verify inequalities like:

  ```c
  munit_assert_true(dist[i][j] <= dist[i][k] + dist[k][j]);
  ```

These checks confirm that:
- Distance values are updated correctly
- `INF` remains unchanged for disconnected nodes
- Multi-hop shortest routes are computed properly

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
