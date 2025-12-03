# 🧮 Q5(b) – Dijkstra’s Algorithm (ADSA Lab 03)

## 📘 Problem Statement
Write a program to compute **Single Source Shortest Paths (SSSP)** using **Dijkstra’s Algorithm** for a weighted graph represented by an **Adjacency Matrix**.

The program:
- Accepts `n × n` adjacency matrix  
- Treats `0` as **no edge** (except diagonal)
- Computes **shortest distance from source vertex to all other vertices**

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q5b_Dijkstra.c` | Full implementation of Dijkstra’s algorithm using adjacency matrix. |
| `test_Q5b_Dijkstra.c` | Automated unit tests using the MUnit testing framework. |
| `munit.c` / `munit.h` | Testing framework used for writing and executing unit tests. |

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

### 🔹 **Initialization**

Before running Dijkstra:

```c
dist[i] = (cost[src][i] == 0 ? INF : cost[src][i]);
visited[i] = 0;
```

Source vertex:

```c
dist[src] = 0;
visited[src] = 1;
```

---

### 🔹 **Dijkstra Algorithm Steps**

The program follows the standard Dijkstra steps:

1. **Initialize:**
   - `dist[i]` = edge cost from source to i  
   - `visited[i] = 0`  
   - `dist[src] = 0`  
   - `visited[src] = 1`

2. **Find unvisited vertex with minimum distance**
3. **Mark it as visited**
4. **Relax edges**

   Update distance if a shorter path is found:
   
   ```c
   if (!visited[v] && cost[u][v] && dist[u] + cost[u][v] < dist[v])
    dist[v] = dist[u] + cost[u][v];
   ```

This repeats for **n − 1 iterations**.

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

The file **`test_Q5b_Dijkstra.c`** contains automated MUnit test cases that verify the correctness of the **Dijkstra’s Shortest Path Algorithm** implementation.

### 🔍 What the test suite checks

| Test Name | Purpose |
|----------|----------|
| `/simple_graph` | Verifies shortest path output for a small fully connected graph. |
| `/disconnected_graph` | Ensures the algorithm correctly returns **INF** for unreachable vertices. |
| `/zero_weight_edges` | Validates handling of graphs where valid edges have weight zero. |
| `/symmetric_vs_asymmetric` | Ensures distances differ for directed vs. undirected style inputs. |

### ✔️ Assertions Used

- `munit_assert_int()` – Validates correctness of computed shortest distances.

- `munit_assert_not_null()` – Confirms arrays and graph structures are properly initialized.

- `munit_assert_true()` – Used to check algorithm properties (e.g., INF cases, distance improvements).

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
