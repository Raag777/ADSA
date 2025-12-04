# 🧮 Q – Maximum Bipartite Matching (ADSA LAB05)

## 📘 Problem Statement

Implement a program to compute the **Maximum Bipartite Matching** in a bipartite graph using the **DFS-based augmenting path algorithm**.

The program must:
- Accept input as an **adjacency matrix**
- Compute the **maximum matching size**
- Print **all matched pairs (Left → Right)**
- Be compatible with **MUnit test automation**

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Bipartite_Matching.c` | Implements DFS-based augmenting path algorithm to find maximum bipartite matching. |
| `test_Bipartite_Matching.c` | Contains automated MUnit test cases validating multiple graph structures. |
| `munit.c` / `munit.h` | MUnit testing framework used to execute the test suite. |

---

## 🧠 Code Overview

This program solves the **Maximum Bipartite Matching** problem in a bipartite graph \( G = (L, R, E) \) using DFS to find **augmenting paths**.

### 🔹 1. DFS for Augmenting Path

The function:

```c
bool bpmDFS(int u, int nRight, int graph[MAX][MAX], bool visited[], int matchR[])
```

tries to match a left-side vertex `u` by:
- Visiting all adjacent vertices on the right side
- If a vertex is unmatched → match immediately
- Else → recursively try to reassign its current match

This forms the core of the augmenting path strategy.

### 🔹 2. Maximum Matching Routine

The function:

```c
int maxBipartiteMatching(int nLeft, int nRight, int graph[MAX][MAX])
```

iterates through each vertex in the left set and:
- Calls DFS to find a match
- Tracks matched pairs using `matchR[]`
- Counts total matches

---

## 🧮 Algorithm Complexity

| Component               | Complexity                               |
|-------------------------|--------------------------------------------|
| Single DFS search       | O(E)                                      |
| Trying all left nodes   | O(V_L)                                    |
| **Total Time Complexity** | **O(V_L × E)**                          |
| Space Complexity        | O(V_R) for match array + visited array |

This makes the DFS-based augmenting path algorithm efficient for typical bipartite graphs used in academic settings.

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Bipartite_Matching.c -o Bipartite_Matching
./Bipartite_Matching
```

---

### 📥 Input Example

```bash
Enter number of vertices in Left set: 4
Enter number of vertices in Right set: 4
Enter adjacency matrix (4 x 4):
0 1 1 0
1 0 0 1
0 0 1 0
1 1 0 0
```

---

### 📤 Output Example

```bash
Matched Pairs (Left → Right):
  3 -> 0
  0 -> 1
  2 -> 2
  1 -> 3

Maximum Bipartite Matching = 4
```

---

## 🧩 MUnit Code Overview

The file `test_Bipartite_Matching.c` contains automated MUnit tests that verify:

- Correctness of the bipartite matching algorithm  
- Handling of graphs with no edges  
- Perfect matching scenarios  
- Partial matching cases  
- Rectangular (non-square) bipartite graphs  

### 🔍 What the Tests Check

| Test Case                      | Input Graph Description                               | Expected Output                                             |
|--------------------------------|--------------------------------------------------------|-------------------------------------------------------------|
| **/basic-matching**            | 4×4 graph with multiple valid matchings               | Maximum Matching = **4**                                    |
| **/no-edges**                  | All adjacency entries = 0 (no edges)                  | Maximum Matching = **0**                                    |
| **/perfect-matching**          | 3×3 graph where each Left node matches exactly one Right node | Maximum Matching = **3**                          |
| **/partial-matching**          | Some nodes unmatched due to missing edges             | Maximum Matching = **3**                                    |
| **/rectangular-graph**         | 3×5 bipartite graph (non-square adjacency matrix)     | Maximum Matching = **3**                                    |

### ✔ Tested Function

```c
maxBipartiteMatching(nLeft, nRight, graph);
```

### ✔ Assertions Used

```c
munit_assert_int();
```

### ✔ What These Tests Validate

- DFS-based augmenting path logic
- Each pair in the matching is valid (Left → Right)
- No vertex is matched more than once
- Matching count returned is correct
- Algorithm works for both square and non-square bipartite graphs

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Bipartite_Matching.c test_Bipartite_Matching.c munit.c -o test_BM
./test_BM
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/bipartite-matching-tests/basic-matching
Matched Pairs (Left -> Right):
  3 -> 0
  0 -> 1
  2 -> 2
  1 -> 3
[ OK    ] 
/bipartite-matching-tests/no-edges
Matched Pairs (Left -> Right):
[ OK    ] 
/bipartite-matching-tests/perfect-matching
Matched Pairs (Left -> Right):
  0 -> 0
  1 -> 1
  2 -> 2
[ OK    ] 
/bipartite-matching-tests/partial-matching
Matched Pairs (Left -> Right):
  3 -> 0
  0 -> 1
  1 -> 3
[ OK    ] 
/bipartite-matching-tests/rectangular-graph
Matched Pairs (Left -> Right):
  2 -> 0
  1 -> 1
  0 -> 2
[ OK    ] 
5 of 5 (100%) tests successful, 0 (0%) test skipped.
```
