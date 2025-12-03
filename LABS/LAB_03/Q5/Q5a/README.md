# 🧮 Q5(a) – Graph Creation Using SIF Format (ADSA Lab 03)

## 📘 Problem Statement

Write a program that reads a graph described in **Simple Interaction Format (SIF)** and generates its **Adjacency Matrix**.

### ✔ What the program must do
- Read edges in this format:

```bash
Node1 Node2 Weight
```

- Continue reading until the user enters **END**
- Automatically detect and add unique node labels (A, B, C, …)
- Construct an **undirected weighted adjacency matrix**
- Print the matrix neatly with row & column labels

### ✔ Purpose
To understand:
- How SIF format represents relationships  
- How to map node names to matrix indices  
- How adjacency matrices represent weighted graphs  

---

## 📂 Code Files

| File Name | Description |
|----------|-------------|
| `Q5a_Graph_SIF.c` | SIF graph builder + adjacency matrix printing (interactive mode). |
| `test_Q5a_Graph_SIF.c` | Fully automated **MUnit test suite** validating graph construction. |
| `munit.c` / `munit.h` | MUnit testing framework files. |

---

## 🧠 Code Overview

This program builds a graph from **SIF (Simple Interaction Format)** input and stores the graph in an **adjacency matrix**.  
It supports two modes:

---

### 🔹 **1. MUnit Testing Mode (NO `scanf`)**

`build_graph_sif_test()` — This function is used only inside the **MUnit test file**.

- Accepts edges as an array of strings:

```bash
A B 3
A C 2
B C 1
```

- Extracts node1, node2, weight using `scanf`.
- Automatically:
- Inserts new nodes into the `nodes[]` list
- Builds `adj[][]` adjacency matrix
- Supports **unordered nodes**
- Allows **duplicate edges** (latest one overwrites)

This makes automated unit testing possible without user input.

---

### 🔹 **2. Normal User Input Mode (Interactive)**

`build_graph_sif()` — This function is used when running the **main program**.

- Reads input from user:

```bash
A B 3
A C 2
C D 5
END
```

- Stops reading when `"END"` is detected.
- Inserts nodes if they are not present.
- Fills adjacency matrix for an **undirected graph**:

```bash
adj[u][v] = weight
adj[v][u] = weight
```

---

### 🔹 **3. Node Index Management**

Since input uses string node names (A, B, C, D…), each new node is:

1. Compared with existing names in `nodes[][]`
2. If not found → appended to the list
3. Assigned an incremental index (`0, 1, 2...`)

Example:

```bash
A → index 0
B → index 1
C → index 2
D → index 3
```

---

### 🔹 **4. Main Program (Interactive)**

Disabled during test using:

```c
#ifndef TEST_MODE
    … main() …
#endif
```

The main program:
- Accepts SIF input until `END`
- Builds adjacency matrix
- Prints the matrix clearly with labels

---

### 🔹 **5. Features of the Program**

- Accepts any number of edges
- Automatically handles new nodes
- Supports unordered node input
- Handles duplicate edges (latest value overwrites old)
- Prints a neat adjacency matrix

---

## 🧑‍💻 Usage

### ▶️ Compile & Run Main Program

```bash
gcc Q5a_Graph_SIF.c -o Q5a_Graph_SIF
./Q5a_Graph_SIF
```

---

### 📥 Input Example

```bash
Enter edges in SIF format (Node1 Node2 Weight). Enter END to stop.
A B 4
A C 1
B C 2
C D 7
END
```

---

### 📤 Output Example

```bash
Adjacency Matrix:
   A B C D
A 0 4 1 0
B 4 0 2 0
C 1 2 0 7
D 0 0 7 0
```

---

## 🧩 MUnit Code Overview

The file **`test_Q5a_Graph_SIF.c`** contains automated test cases written using the **MUnit testing framework**, designed to validate the correctness of the **SIF Graph Builder** implemented in `Q5a_Graph_SIF.c`.

These tests ensure that the program correctly:
- Parses SIF (Simple Interaction Format) input  
- Identifies and stores nodes uniquely  
- Builds the adjacency matrix accurately  
- Handles unordered input, duplicate edges, and variable node order  


### 🔍 What the test suite checks

| Test Name | Purpose |
|-----------|----------|
| `/basic_graph` | Verifies correct graph construction for a simple 3-edge SIF input. |
| `/unordered_nodes` | Ensures the program correctly handles edges where nodes appear in random order. |
| `/duplicate_edges` | Confirms that repeated edges overwrite with the latest weight. |


### ✔️ Assertions Used

- **`munit_assert_int()`** – Used to validate:
  - Node count  
  - Correct weights in adjacency matrix  
  - Proper overwrite behavior for duplicate edges  

- **`munit_assert_true()`** – Used for logical conditions (e.g., verifying at least one valid connection in unordered graphs).

- **`munit_assert_not_null()`** – Ensures arrays and graph structures are initialized before use.

---

### ▶️ Compile & Run MUnit Tests

```bash
gcc -DTEST_MODE Q5a_Graph_SIF.c test_Q5a_Graph_SIF.c munit.c -o test_Q5a
./test_Q5a
```

---

### 🧪 MUnit Testing Output

```bash
Running test suite with seed 0x15534978...
/Graph_SIF_Tests/basic_graph        [ OK    ]
/Graph_SIF_Tests/unordered_nodes    [ OK    ]
/Graph_SIF_Tests/duplicate_edges    [ OK    ]
3 of 3 (100%) tests successful, 0 (0%) test skipped.
```
