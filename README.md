# Library Management System

## Project Overview

The Library Management System is a console-based application developed using C++. It is designed to manage book records efficiently while demonstrating the practical implementation of various Data Structures and Algorithms (DSA).

The project allows users to add, display, search, issue, return, and delete books from the library. It also includes advanced features such as Undo functionality using Stack, Book Request Management using Queue, Binary Search Tree (BST) for sorted book organization, and File Handling for permanent data storage.

This project serves as a real-world application of DSA concepts and showcases how different data structures can work together to solve practical problems.

---

## Objectives

- To manage library records efficiently.
- To demonstrate the implementation of DSA concepts in a real-world application.
- To provide fast searching and sorting of books.
- To maintain a waiting list for unavailable books.
- To implement an Undo mechanism for recent operations.
- To store data permanently using file handling.

---

## Features

### 1. Add Book
Users can add a new book to the library by entering:

- Book ID
- Book Title
- Author Name

The system automatically stores the book in memory and saves it to the file.

---

### 2. Display Books

Displays all books currently available in the library along with:

- Book ID
- Title
- Author
- Issue Status

This helps users view the complete library inventory.

---

### 3. Search Book

The system supports two searching methods:

#### Linear Search
- Checks books one by one.
- Useful for unsorted data.

#### Binary Search
- Works on sorted data.
- Faster than linear search.
- Efficient for larger datasets.

---

### 4. Delete Book

Allows users to remove a book from the library.

The system:
- Searches for the book.
- Deletes it from the array.
- Updates the file.
- Records the action in the Undo Stack.

---

### 5. Issue Book

Allows a user to issue a book.

The system:
- Checks whether the book exists.
- Verifies if it is already issued.
- Marks the book as issued.
- Saves changes to the file.
- Stores the action in the Undo Stack.

---

### 6. Return Book

Allows a user to return a previously issued book.

The system:
- Marks the book as available.
- Checks the request queue.
- Automatically issues the book to the next waiting request if one exists.
- Updates the file.
- Stores the action in the Undo Stack.

---

### 7. Sort Books

Books can be sorted based on their Book ID using Bubble Sort.

Benefits:
- Easier viewing of records.
- Required before performing Binary Search.

---

### 8. Undo Operation

The project uses a Stack to maintain recent actions.

Examples:

- Added Book ID 101
- Issued Book ID 102
- Returned Book ID 103

The most recent action can be viewed and removed using the Undo feature.

---

### 9. Book Request System

When a book is unavailable, users can place a request.

The system:
- Stores requests in a Queue.
- Processes requests in FIFO order.
- Gives priority to the first request made.

---

### 10. Display Books Using BST

The project stores books in a Binary Search Tree according to their Book ID.

Using Inorder Traversal:

- Left Subtree
- Root Node
- Right Subtree

Books are displayed in ascending order of Book ID.

---

# Data Structures Used

## 1. Array

```cpp
Book books[MAX];
```

Purpose:
- Stores all book records.

Advantages:
- Easy implementation.
- Fast access using index.

---

## 2. Stack

```cpp
string undoStack[MAX];
```

Purpose:
- Stores recent actions for Undo functionality.

Operations Used:
- Push
- Pop

Principle:

LIFO (Last In First Out)

Example:

Add Book
Issue Book
Return Book

Undo → Return Book
Undo → Issue Book
Undo → Add Book

---

## 3. Queue

```cpp
int requestQueue[MAX];
```

Purpose:
- Maintains waiting requests for books.

Operations Used:
- Enqueue
- Dequeue

Principle:

FIFO (First In First Out)

Example:

Student A requests Book 101
Student B requests Book 101
Student C requests Book 101

When the book becomes available:

Student A gets priority first.

---

## 4. Binary Search Tree (BST)

```cpp
struct Node
{
    int id;
    string title;

    Node* left;
    Node* right;
};
```

Purpose:
- Organizes books according to Book ID.

Rule:

- Smaller IDs go to the Left Subtree.
- Larger IDs go to the Right Subtree.

Benefits:
- Efficient organization.
- Sorted traversal.

Example:

        105
       /   \
     101   110
       \
       103

Inorder Traversal Output:

101
103
105
110

---

# Algorithms Used

## Linear Search

Complexity:

O(n)

Used to search books one by one.

---

## Binary Search

Complexity:

O(log n)

Used for faster searching after sorting.

---

## Bubble Sort

Complexity:

O(n²)

Used to sort books by Book ID.

---

## BST Insertion

Average Complexity:

O(log n)

Used while building the Binary Search Tree.

---

## Inorder Traversal

Complexity:

O(n)

Used to display books in sorted order.

---

# File Handling

The project uses a text file:

```text
books.txt
```

for permanent data storage.

---

## saveToFile()

Purpose:

- Saves all books from memory into the file.
- Updates records after every modification.

---

## loadFromFile()

Purpose:

- Loads all saved books from the file when the program starts.
- Prevents data loss between executions.

---

## Sample File Format

```text
101
Atomic Habits
James Clear
0

102
Ikigai
Hector Garcia
1
```

Where:

- 0 = Available
- 1 = Issued

---

# Program Workflow

1. Program Starts
2. loadFromFile() loads all books
3. User selects an operation from the menu
4. Data is processed using appropriate DSA structures
5. saveToFile() updates the file
6. Program exits while preserving all records

---

# Time Complexity Analysis

| Operation | Complexity |
|------------|------------|
| Add Book | O(1) |
| Display Books | O(n) |
| Delete Book | O(n) |
| Linear Search | O(n) |
| Binary Search | O(log n) |
| Bubble Sort | O(n²) |
| Push Stack | O(1) |
| Pop Stack | O(1) |
| Enqueue Queue | O(1) |
| Dequeue Queue | O(1) |
| BST Insert | O(log n) Average |
| BST Traversal | O(n) |
| Save To File | O(n) |
| Load From File | O(n) |

---

# Advantages

- Easy to understand and use.
- Demonstrates multiple DSA concepts in one project.
- Supports persistent storage.
- Provides searching and sorting facilities.
- Includes request handling mechanism.
- Includes Undo functionality.
- Displays records in sorted order through BST.

---

# Limitations

- Fixed storage size due to static arrays.
- Queue currently stores only Book IDs and not student details.
- Bubble Sort is not efficient for very large datasets.
- BST is not self-balancing and may become skewed.

---

# Future Enhancements

- Implement AVL Tree for self-balancing.
- Add student management system.
- Store requester information in queue.
- Use Linked Lists instead of fixed arrays.
- Integrate a database such as MySQL.
- Develop a Graphical User Interface (GUI).
- Implement advanced sorting algorithms such as Merge Sort or Quick Sort.

---

# Conclusion

The Library Management System successfully demonstrates the practical application of Data Structures and Algorithms through a real-world scenario. The project combines Arrays, Stack, Queue, Binary Search Tree, Searching, Sorting, and File Handling to provide an efficient solution for managing library records. It serves as an excellent educational project for understanding how multiple DSA concepts work together in software development.
