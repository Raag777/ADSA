# 🔢 Heap Sort in C

This project implements the **Heap Sort algorithm** in C.  
Heap Sort is a **comparison-based sorting technique** based on a **Binary Heap data structure**.  
It has a time complexity of **O(n log n)** and sorts an array **in-place**.

---

## 📌 Features
- Implementation of **max-heap construction** and **heapify procedure**.
- Sorts any list of integers in **ascending order**.
- Efficient for large datasets since it avoids extra memory allocation.

---

## ⚙️ Algorithm
1. **Build a max heap** from the unsorted array.
2. Swap the root (maximum element) with the last element.
3. Reduce the heap size and call `heapify` to restore the heap property.
4. Repeat until all elements are sorted.

---

## 📂 Functions
- `heapify(int arr[], int n, int i)` → Ensures the heap property for a subtree.
- `heapSort(int arr[], int n)` → Sorts the array using heap operations.
- `main()` → Takes input from user, sorts array, and prints result.

---

## ⚡ Example Usage

### Compile:
```bash
Q4-HeapSort.exe
```

## 📥 Input Format
Enter number of elements: 5

Enter 5 elements: 9 3 7 1 8

## 📤 Output Format
Sorted array: 1 3 7 8 9 
