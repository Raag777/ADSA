# 🧮 Q5(b) – Dijkstra’s Algorithm (ADSA Lab 03)

## 📘 Problem Statement
Write a program to compute the **Single Source Shortest Path (SSSP)** using **Dijkstra’s Algorithm** on a weighted graph represented using an **Adjacency Matrix**.

The program must:
- Accept the number of vertices  
- Accept a `n × n` adjacency matrix  
- Treat `0` as **no edge**, except for diagonal elements  
- Compute **shortest distance from the given source vertex to all vertices**

---

## 📂 Code Files

| File Name | Description |
|-----------|-------------|
| `Q5b_Dijkstra.c` | Full implementation of Dijkstra’s SSSP algorithm. Includes a standalone `dijkstra()` function used by both main program & MUnit tests. |
| `test_Q5b_Dijkstra.c` | Automated MUnit test cases validating the correctness of the Dijkstra algorithm. |
| `munit.c` / `munit.h` | MUnit testing framework used to execute the test suite. |

---

## 🧠 Code Overview

This program implements **Dijkstra’s Shortest Path Algorithm** for a graph represented using an **adjacency matrix**.  
The algorithm computes the **minimum distance from a selected source vertex to every other vertex** in the graph.

---

### 🔹 **Graph Input**

The program takes:

```bash
Enter number of vertices: n
Enter adjacency matrix (0 for no edge):
...
Enter source vertex (0 to n-1):
```

Matrix rule:
- `0` means **no edge**  
- But distance to itself is considered **0**  
- All other zero entries get replaced with **INF (99999)**

---

### 🔹 **Dijkstra Algorithm Steps**

Here standalone function is:

```c
void dijkstra(int n, int cost[MAX][MAX], int src, int dist[MAX]);
```

**Steps Performed:**
1. Initialize distance & visited arrays
2. Replace missing edges (`0`) with `INF`
3. Repeat for `n - 1` iterations:
   - Select vertex `u` with minimum `dist[u]` not visited
   - Mark as visited
   - Relax edges:

```c
if (!visited[v] && cost[u][v] &&
    dist[u] + cost[u][v] < dist[v]) {

    dist[v] = dist[u] + cost[u][v];
}
```

---

### 🔹 **Outputs Shortest Distances**

After running the algorithm, the program prints:

```bash
Shortest distances from source X:
To 0 = ...
To 1 = ...
To 2 = ...
To 3 = ...
```

Each value represents the **shortest path cost** from the chosen source.

---

### 🔹 **Notes**

- The implementation works for **positive weights only** (as required by Dijkstra).
- Input must not include negative edge weights.
- Matrix must be symmetric for an undirected graph, but Dijkstra also works for directed matrices.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q5b_Dijkstra.c -o Q5b_Dijkstra
./Q5b_Dijkstra
```

---

### 📥 Input Example

```bash
Enter number of vertices: 3
Enter adjacency matrix (0 for no edge):
1 2 3
4 5 6
7 8 9
Enter source vertex (0 to 2): 1
```

---

### 📤 Output Example

```bash
Shortest distances from source 1:
To 0 = 4
To 1 = 0
To 2 = 6
```

---

## 🧩 MUnit Code Overview

The file **`test_Q5b_Dijkstra.c`** contains automated MUnit test cases that validate the correctness of the `dijkstra()` function implemented in **Q5b_Dijkstra.c**.  
These tests ensure that the shortest-path values computed by the algorithm are accurate across multiple graph structures.

### 🔍 What the Test Suite Checks

| Test Name | Purpose |
|----------|----------|
| **`/basic`** | Tests Dijkstra on a fully connected graph and verifies exact shortest-path results. |
| **`/unreachable`** | Ensures unreachable vertices correctly receive distance = **INF (99999)**. |
| **`/zero_edge`** | Tests behavior when some edges have weight `0` (treated as no-edge except diagonal). |

Each test sets up a fixed graph (adjacency matrix), calls:

```c
dijkstra(n, cost, src, dist);
```

### ✔️ Assertions Used

- `munit_assert_int()` – Validates correctness of computed shortest distances.

These checks ensure:
- Correct minimum-path computation
- Proper handling of unreachable vertices
- Proper handling of zero-cost edges

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q5b_Dijkstra.c test_Q5b_Dijkstra.c munit.c -o test_Q5b
./test_Q5b
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/Dijkstra_Tests/basic                [ OK    ] 
/Dijkstra_Tests/unreachable          [ OK    ] 
/Dijkstra_Tests/zero_edge            [ OK    ] 
3 of 3 (100%) tests successful, 0 (0%) test skipped.
```
