#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX = 100;

// ======================================================
// BOOK STRUCTURE
// ======================================================

struct Book
{

    int id;
    string title;
    string author;
    bool issued;
};

// ======================================================
// GLOBAL VARIABLES
// ======================================================

Book books[MAX];

int totalBooks = 0;

// ======================================================
// STACK (UNDO)
// ======================================================

string undoStack[MAX];

int top = -1;

// ======================================================
// QUEUE (BOOK REQUESTS)
// ======================================================

int requestQueue[MAX];

int frontQ = 0;
int rearQ = -1;

// ======================================================
// BST NODE
// ======================================================

struct Node
{

    int id;
    string title;

    Node *left;
    Node *right;
};

Node *root = NULL;

// ======================================================
// FILE HANDLING
// ======================================================

void saveToFile()
{

    ofstream file("books.txt");

    if (!file)
    {

        cout << "File Error!\n";
        return;
    }

    for (int i = 0; i < totalBooks; i++)
    {

        file << books[i].id << endl;

        file << books[i].title << endl;

        file << books[i].author << endl;

        file << books[i].issued << endl;
    }

    file.close();
}

void loadFromFile()
{

    ifstream file("books.txt");

    if (!file)
    {

        cout << "books.txt not found.\n";
        return;
    }

    Book b;

    totalBooks = 0;

    while (file >> b.id)
    {

        // Prevent overflow
        if (totalBooks >= MAX)
        {

            cout << "Maximum storage reached.\n";
            break;
        }

        file.ignore();

        getline(file, b.title);

        getline(file, b.author);

        file >> b.issued;

        file.ignore();

        books[totalBooks] = b;

        totalBooks++;
    }

    file.close();
}

// ======================================================
// STACK OPERATIONS
// ======================================================

void pushUndo(string action)
{

    if (top < MAX - 1)
    {

        top++;

        undoStack[top] = action;
    }
}

void popUndo()
{

    if (top == -1)
    {

        cout << "Nothing to Undo.\n";
        return;
    }

    cout << "Undo Action: "
         << undoStack[top]
         << endl;

    top--;
}

// ======================================================
// QUEUE OPERATIONS
// ======================================================

void enqueueRequest(int id)
{

    if (rearQ >= MAX - 1)
    {

        cout << "Queue Full.\n";
        return;
    }

    rearQ++;

    requestQueue[rearQ] = id;
}

void dequeueRequest()
{

    if (frontQ > rearQ)
    {

        cout << "No Pending Requests.\n";
        return;
    }

    cout << "Processed Request for Book ID: "
         << requestQueue[frontQ]
         << endl;

    frontQ++;
}

// ======================================================
// BST OPERATIONS
// ======================================================

Node *createNode(int id, string title)
{

    Node *temp = new Node();

    temp->id = id;

    temp->title = title;

    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

Node *insertBST(Node *root,
                int id,
                string title)
{

    if (root == NULL)
        return createNode(id, title);

    if (id < root->id)

        root->left =
            insertBST(root->left,
                      id,
                      title);

    else

        root->right =
            insertBST(root->right,
                      id,
                      title);

    return root;
}

void inorder(Node *root)
{

    if (root == NULL)
        return;

    inorder(root->left);

    cout << root->id
         << " - "
         << root->title
         << endl;

    inorder(root->right);
}

// ======================================================
// ADD BOOK
// ======================================================

void addBook()
{

    if (totalBooks >= MAX)
    {

        cout << "Library Full!\n";
        return;
    }

    Book b;

    cout << "Enter Book ID: ";
    cin >> b.id;

    cin.ignore();

    // Prevent negative IDs
    if (b.id <= 0)
    {

        cout << "Invalid Book ID.\n";
        return;
    }

    // Duplicate ID Check
    for (int i = 0; i < totalBooks; i++)
    {

        if (books[i].id == b.id)
        {

            cout << "Book ID already exists!\n";
            return;
        }
    }

    cout << "Enter Book Title: ";
    getline(cin, b.title);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    // Empty validation
    if (b.title.empty() ||
        b.author.empty())
    {

        cout << "Title/Author cannot be empty.\n";
        return;
    }

    b.issued = false;

    books[totalBooks] = b;

    totalBooks++;

    // Insert into BST
    root = insertBST(root,
                     b.id,
                     b.title);

    // Push into Stack
    pushUndo("Added Book ID " + to_string(b.id));

    // Save
    saveToFile();

    cout << "Book Added Successfully!\n";
}

// ======================================================
// DISPLAY BOOKS
// ======================================================

void displayBooks()
{

    if (totalBooks == 0)
    {

        cout << "Library Empty.\n";
        return;
    }

    cout << "\n===== BOOK LIST =====\n";

    for (int i = 0; i < totalBooks; i++)
    {

        cout << "Book ID: "
             << books[i].id
             << endl;

        cout << "Title: "
             << books[i].title
             << endl;

        cout << "Author: "
             << books[i].author
             << endl;

        cout << "Issued: ";

        if (books[i].issued)
            cout << "Yes\n";

        else
            cout << "No\n";

        cout << "----------------------\n";
    }
}

// ======================================================
// LINEAR SEARCH
// ======================================================

void linearSearch()
{

    if (totalBooks == 0)
    {

        cout << "Library Empty.\n";
        return;
    }

    int id;

    cout << "Enter Book ID to Search: ";
    cin >> id;

    for (int i = 0; i < totalBooks; i++)
    {

        if (books[i].id == id)
        {

            cout << "\nBook Found!\n";

            cout << "Title: "
                 << books[i].title
                 << endl;

            cout << "Author: "
                 << books[i].author
                 << endl;

            return;
        }
    }

    cout << "Book Not Found.\n";
}

// ======================================================
// INSERTION SORT
// ======================================================

void insertionSort()
{

    for (int i = 1; i < totalBooks; i++)
    {

        Book key = books[i];

        int j = i - 1;

        while (j >= 0 &&
               books[j].id > key.id)
        {

            books[j + 1] = books[j];

            j--;
        }

        books[j + 1] = key;
    }

    saveToFile();

    cout << "Books Sorted using Insertion Sort.\n";
}

// ======================================================
// MERGE SORT
// ======================================================

void merge(Book arr[],
           int left,
           int mid,
           int right)
{

    int n1 = mid - left + 1;
    int n2 = right - mid;

    Book L[MAX], R[MAX];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 &&
           j < n2)
    {

        if (L[i].id <= R[j].id)
        {

            arr[k] = L[i];
            i++;
        }

        else
        {

            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {

        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {

        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Book arr[],
               int left,
               int right)
{

    if (left < right)
    {

        int mid = (left + right) / 2;

        mergeSort(arr,
                  left,
                  mid);

        mergeSort(arr,
                  mid + 1,
                  right);

        merge(arr,
              left,
              mid,
              right);
    }
}

// ======================================================
// BINARY SEARCH
// ======================================================

void binarySearch()
{

    if (totalBooks == 0)
    {

        cout << "Library Empty.\n";
        return;
    }

    // Auto sort before binary search
    insertionSort();

    int id;

    cout << "Enter Book ID to Search: ";
    cin >> id;

    int left = 0;
    int right = totalBooks - 1;

    while (left <= right)
    {

        int mid = (left + right) / 2;

        if (books[mid].id == id)
        {

            cout << "\nBook Found!\n";

            cout << "Title: "
                 << books[mid].title
                 << endl;

            cout << "Author: "
                 << books[mid].author
                 << endl;

            return;
        }

        if (books[mid].id < id)

            left = mid + 1;

        else

            right = mid - 1;
    }

    cout << "Book Not Found.\n";
}

// ======================================================
// ISSUE BOOK
// ======================================================

void issueBook()
{

    if (totalBooks == 0)
    {

        cout << "Library Empty.\n";
        return;
    }

    int id;

    cout << "Enter Book ID to Issue: ";
    cin >> id;

    for (int i = 0; i < totalBooks; i++)
    {

        if (books[i].id == id)
        {

            if (books[i].issued)
            {

                cout << "Book Already Issued.\n";

                enqueueRequest(id);
            }

            else
            {

                books[i].issued = true;

                pushUndo("Issued Book ID " + to_string(id));

                saveToFile();

                cout << "Book Issued Successfully.\n";
            }

            return;
        }
    }

    cout << "Book Not Found.\n";
}

// ======================================================
// RETURN BOOK
// ======================================================

void returnBook()
{

    if (totalBooks == 0)
    {

        cout << "Library Empty.\n";
        return;
    }

    int id;

    cout << "Enter Book ID to Return: ";
    cin >> id;

    for (int i = 0; i < totalBooks; i++)
    {

        if (books[i].id == id)
        {

            books[i].issued = false;

            if (frontQ <= rearQ &&
                requestQueue[frontQ] == id)
            {

                cout << "Book automatically issued "
                     << "to next waiting student.\n";

                books[i].issued = true;

                dequeueRequest();
            }

            pushUndo("Returned Book ID " + to_string(id));

            saveToFile();

            cout << "Book Returned Successfully.\n";

            return;
        }
    }

    cout << "Book Not Found.\n";
}

// ======================================================
// COMPLEXITY ANALYSIS
// ======================================================

void complexityAnalysis()
{

    cout << "\n===== TIME COMPLEXITY =====\n";

    cout << "Add Book          : O(1)\n";

    cout << "Display Books     : O(n)\n";

    cout << "Linear Search     : O(n)\n";

    cout << "Binary Search     : O(log n)\n";

    cout << "Insertion Sort    : O(n^2)\n";

    cout << "Merge Sort        : O(n log n)\n";

    cout << "BST Insert        : O(log n)\n";
}

// ======================================================
// MAIN FUNCTION
// ======================================================

int main()
{

    loadFromFile();

    // Safe BST Rebuild
    root = NULL;

    for (int i = 0; i < totalBooks; i++)
    {

        root = insertBST(root,
                         books[i].id,
                         books[i].title);
    }

    int choice;

    do
    {

        cout << "\n====== LIBRARY MANAGEMENT SYSTEM ======\n";

        cout << "1. Add Book\n";

        cout << "2. Display Books\n";

        cout << "3. Linear Search\n";

        cout << "4. Insertion Sort\n";

        cout << "5. Merge Sort\n";

        cout << "6. Binary Search\n";

        cout << "7. Issue Book\n";

        cout << "8. Return Book\n";

        cout << "9. Undo Last Action\n";

        cout << "10. Process Queue Request\n";

        cout << "11. Display BST (Inorder)\n";

        cout << "12. Complexity Analysis\n";

        cout << "0. Exit\n";

        cout << "Enter Choice: ";

        cin >> choice;

        switch (choice)
        {

        case 1:

            addBook();
            break;

        case 2:

            displayBooks();
            break;

        case 3:

            linearSearch();
            break;

        case 4:

            insertionSort();
            break;

        case 5:

            mergeSort(books,
                      0,
                      totalBooks - 1);

            saveToFile();

            cout << "Books Sorted using Merge Sort.\n";

            break;

        case 6:

            binarySearch();
            break;

        case 7:

            issueBook();
            break;

        case 8:

            returnBook();
            break;

        case 9:

            popUndo();
            break;

        case 10:

            dequeueRequest();
            break;

        case 11:

            cout << "\nBST Inorder Traversal:\n";

            inorder(root);

            break;

        case 12:

            complexityAnalysis();
            break;

        case 0:

            cout << "Exiting Program...\n";
            break;

        default:

            cout << "Invalid Choice.\n";
        }

    } while (choice != 0);

    return 0;
}