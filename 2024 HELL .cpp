#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include<algorithm>
#include<iomanip>

using namespace std;
void addBook();
void displayMenu();
void searchBook();
void borrowBook();
void returnBook();
void sortBooks();
void viewBorrowedBooks();
void countBooks();
void displayMenu();
void clearscreen();
void loadBooks();
void updateBook();
void deleteBooks();
void saveBooks();
void displayBooks();
void clearFile(const string& filename);
void clearLibraryAndFile(const string& inFile);
void filterString(string& choice);
void filterString2(string& input);

// Maximum number of books in the library
const int MAX_BOOKS = 100;
// Arrays to store book details
int bookIDs[MAX_BOOKS];
string titles[MAX_BOOKS];
string authors[MAX_BOOKS];
string borrowedBy[MAX_BOOKS];
int bookCount = 0;



using namespace std;                                // MAIN FUNCTION ... 
int main()
{
    fstream inFile("library.txt");
    loadBooks();                                            // Load books from the file at the start
    string choice;
    displayMenu();
    do {
        std::cout << " \n ENTER THE CHOICE TO PERFORM SPECIFIC FUNCTION =  ";
        getline(cin, choice);
        filterString(choice);
        long option = stoi(choice);
        switch (option)
        {
        case 1:
        {
            std::cout << " \n ADDING A NEW BOOK IN THE LIBRARY " << endl;
            addBook();
        }
        break;
        case 2:
        {
            std::cout << " \n NOW DISPLAYING ALL THE BOOKS IN THE LIBRARY " << endl;
            displayBooks();
        }
        break;
        case 3:
        {
            cout << " \n SCEARCHING BOOK FROM THE LIBRARY ENTER THE  " << endl;
            searchBook();
        } break;
        case 4: borrowBook(); break;
        case 5: returnBook(); break;
        case 6: viewBorrowedBooks(); break;
        case 7: updateBook(); break;
        case 8: deleteBooks(); break;
        case 9: countBooks(); break;
        case 10:sortBooks(); break;  // sorting the books 
        case 11:clearLibraryAndFile("library.txt"); break; // combination of two function.
        case 12:displayMenu(); break;
        case 13:clearscreen(); break;
        case 14:
        {
            cout << "Exiting...\n";
            saveBooks();
            break;
        }
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (stoi(choice) != 14);

    return 0;
}


// clear file is basically used in    clearLibraryAndFile(constant  string& inFile)  function 
void clearFile(const string& filename) {
    ofstream file(filename, ios::out | ios::trunc);                // Open the file in truncate mode
    file.close();
    cout << "File contents cleared.\n";
}

void clearLibraryAndFile(const string& inFile) {
    bookCount = 0;                                               // Reset book count

    // Reset arrays
    for (int i = 0; i < MAX_BOOKS; i++) {
        bookIDs[i] = 0;
        titles[i] = "";
        authors[i] = "";
        borrowedBy[i] = "";
    }

    // Clear the file contents
    clearFile(inFile);

    cout << "Library memory and file contents cleared.\n";
}

// Function to load books from a file
void loadBooks()
{
    ifstream inFile("library.txt");
    if (!inFile)
    {
        cout << "No existing library file found. Starting fresh.\n";
        return;
    }

    bookCount = 0;
    while (inFile >> bookIDs[bookCount])
    {
        inFile.ignore();
        getline(inFile, titles[bookCount]);
        getline(inFile, authors[bookCount]);
        getline(inFile, borrowedBy[bookCount]);
        bookCount++;
    }
    inFile.close();
    cout << "Library data loaded successfully.\n";
}

// Function to save books to a file
void saveBooks() {

    ofstream outFile("library.txt");
    for (int i = 0; i < bookCount; i++) {
        outFile << bookIDs[i] << "\n";
        outFile << titles[i] << "\n";
        outFile << authors[i] << "\n";
        outFile << borrowedBy[i] << "\n";
    }
    outFile.close();
    cout << "Library data saved successfully.\n";
}

// Function to display the main menu
void displayMenu() {
    cout << " **********************************************************************";
    cout << "\n---------------------- Library Management System ----------------------\n";
    cout << " **********************************************************************\n";
    cout << "                       1. Add Book\n";
    cout << "                       2. Display All Books\n";
    cout << "                       3. Search Book\n";
    cout << "                       4. Borrow Book\n";
    cout << "                       5. Return Book\n";
    cout << "                       6. View Borrowed Books\n";
    cout << "                       7. Update Book Details\n";
    cout << "                       8. Delete Book\n";
    cout << "                       9. Count Books\n";
    cout << "                      10. Sort Books\n";
    cout << "                      11. Clearing the library \n";
    cout << "                      12. Display the menu bar \n";
    cout << "                      13. To clear screen \n";
    cout << "                      14. Exit\n";
}

// Function to add a book

// Function to display all books
void displayBooks() {
    if (bookCount == 0) {
        cout << "No books in the library.\n";
        return;
    }
    cout << "\n--- Book List ---\n";
    for (int i = 0; i < bookCount; i++) {
        cout << " ID: " << setw(6) << bookIDs[i]
            << setw(6) << " , Title:   " << setw(30) << titles[i]
            << setw(6) << " , Author:    " << setw(3) << authors[i];
        if (borrowedBy[i] != "") {  // Check if the book is borrowed
            cout << " (Borrowed by: " << borrowedBy[i] << ")";
        }
        cout << "\n\n";
    }
}

// Function to search for a book
void searchBook() {
    cout << "Enter Book ID to search the book: ";
    string query;
    cin.ignore();
    getline(cin, query);

    // Filter to retain only numeric characters
    filterString(query);

    // Check if the filtered query is still valid (contains only digits)
    if (query.empty()) {
        cout << "Invalid input. Please enter a valid numeric Book ID.\n";
        return;
    }

    // Convert the query to integer
    int bookID = stoi(query);

    for (int i = 0; i < bookCount; i++) {
        if (bookIDs[i] == bookID) {  // Match by ID
            cout << "Book Found: ID: " << bookIDs[i]
                << ", Title: " << titles[i]
                << ", Author: " << authors[i];
            if (!borrowedBy[i].empty()) {  // Book is borrowed
                cout << " (Borrowed by: " << borrowedBy[i] << ")";
            }
            cout << "\n";
            return;
        }
    }
    cout << "Book not found.\n";
    return;
}

// Function to return a book

void returnBook() {
    cout << "Enter Book ID to return: ";
    int id;
    cin >> id;

    for (int i = 0; i < bookCount; i++) {
        if (bookIDs[i] == id) {
            if (borrowedBy[i] == "") {  // Book is not borrowed
                cout << "Book is not borrowed.\n";
                return;
            }
            borrowedBy[i] = "";
            cout << "Book returned successfully.\n";
            saveBooks();
            return;
        }
    }
    cout << "Book not found.\n";
}

// Function to view all borrowed books
void viewBorrowedBooks() {
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (borrowedBy[i] != "") {  // Check if the book is borrowed
            if (!found) {
                cout << "\n--- Borrowed Books ---\n";
                found = true;
            }
            cout << "ID: " << bookIDs[i]
                << ", Title: " << titles[i]
                << ", Borrowed by: " << borrowedBy[i] << "\n";
        }
    }
    if (!found) {
        cout << "No books are currently borrowed.\n";
    }
}

void updateBook()
{
    if (bookCount == 0) {
        cout << "No books available to update.\n";
        return;
    }

    string idInput;
    cout << "Enter Book ID to update: ";
    getline(cin, idInput);
    filterString(idInput);

    if (idInput.empty()) {
        cout << "Invalid input. Book ID must contain only digits.\n";
        return;
    }

    int bookID = stoi(idInput);

    int bookIndex = -1;
    for (int i = 0; i < bookCount; ++i) {
        if (bookIDs[i] == bookID) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        cout << "Book with ID " << bookID << " not found.\n";
        return;
    }

    cout << "Updating details for Book ID " << bookID << ":\n";

    // Update Title
    string newTitle;
    cout << "Enter new title (leave blank to keep current): ";
    getline(cin, newTitle);
    filterString2(newTitle);

    if (!newTitle.empty()) {
        titles[bookIndex] = newTitle;
    }
    else {
        cout << "Book title unchanged.\n";
    }

    // Update Author
    string newAuthor;
    cout << "Enter new author name (leave blank to keep current): ";
    getline(cin, newAuthor);
    filterString2(newAuthor);

    if (!newAuthor.empty()) {
        authors[bookIndex] = newAuthor;
    }
    else {
        cout << "Author name unchanged.\n";
    }

    // Save the updated book data
    saveBooks();
    cout << "Book details updated successfully!\n";
}

void deleteBooks()
{
    if (bookCount == 0)
    {
        cout << "\n No book found in the library ";
        return;
    }
    string inputID;
    cout << " \n Enter the book to delete it from the memory ";
    getline(cin, inputID);
    filterString(inputID);

    if (inputID.empty())
    {
        cout << "\n Invalid input... No digit found or blank input was entered ";
        return;
    }

    int bookID = stoi(inputID);
    int bookIndex = -1;
    for (int i = 0; i < bookCount; ++i) {
        if (bookIDs[i] == bookID) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        cout << "Book with ID " << bookID << " not found.\n";
        return;
    }

    // Shift books after the deleted book to the left
    for (int i = bookIndex; i < bookCount - 1; ++i) {
        bookIDs[i] = bookIDs[i + 1];
        titles[i] = titles[i + 1];
        authors[i] = authors[i + 1];
    }

    // Decrease the book count  by 1 position back
    bookCount--;

    // Save the updated books 
    saveBooks();

    cout << "Book with ID " << bookID << " deleted successfully.\n";
}

void sortBooks()                                      // A has ASCII 65 and a has ASCII 97.
{
    for (int i = 0; i < bookCount - 1; ++i) {
        for (int j = i + 1; j < bookCount; ++j) {
            if (titles[i] > titles[j]) {
                // Manually swap the books' data using a temporary variable
                string tempTitle = titles[i];
                titles[i] = titles[j];
                titles[j] = tempTitle;

                int tempID = bookIDs[i];
                bookIDs[i] = bookIDs[j];
                bookIDs[j] = tempID;

                string tempAuthor = authors[i];
                authors[i] = authors[j];
                authors[j] = tempAuthor;

                string tempBorrowedBy = borrowedBy[i];
                borrowedBy[i] = borrowedBy[j];
                borrowedBy[j] = tempBorrowedBy;
            }
        }
    }

    cout << "Books sorted by title in ascending order.\n";
    saveBooks(); // Save the sorted books to the file
}
// Function to count books 
void countBooks() {
    int borrowedCount = 0;
    for (int i = 0; i < bookCount; i++) {
        if (borrowedBy[i] != "") borrowedCount++;  // Count borrowed books
    }
    cout << "Total Books: " << bookCount << "\n";
    cout << "Available Books: " << (bookCount - borrowedCount) << "\n";
    cout << "Borrowed Books: " << borrowedCount << "\n";
}

void clearscreen()
{
    system("cls");
    displayMenu();
}

void addBook()
{
    if (bookCount >= MAX_BOOKS) {
        cout << "Library is full! Cannot add more books.\n";
        return;
    }

    string idInput;
    // Loop until valid Book ID is provided
    while (true) {
        cout << "Enter Book ID (digits only): ";
        getline(cin, idInput);
        filterString(idInput);  // Filter to ensure it contains only digits

        if (!idInput.empty()) {
            int bookID = stoi(idInput);

            // Check for duplicate Book ID
            bool duplicate = false;
            for (int i = 0; i < bookCount; ++i) {
                if (bookIDs[i] == bookID) {
                    cout << "Book ID already exists. Enter a unique ID.\n";
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate) {
                bookIDs[bookCount] = bookID;
                break; // Exit loop if valid ID is provided
            }
        }
        else {
            cout << "Invalid input. Book ID must contain only digits.\n";
            continue; // Ask again for valid input
        }
    }

    string title;
    // Loop until valid Book Title is provided
    while (true) {
        cout << "Enter Book Title (letters and spaces only): ";
        getline(cin, title);

        // Use filterString2 to clean the title input
        filterString2(title);

        // Check if title is not empty after removing invalid characters
        if (!title.empty()) {
            titles[bookCount] = title;
            break; // Exit loop if valid title is provided
        }
        else {
            cout << "Invalid input. Book Title must not be empty and must only contain letters and spaces.\n";
            continue; // Ask again for valid input
        }
    }

    string author;
    // Loop until valid Author Name is provided
    while (true) {
        cout << "Enter Author Name (letters and spaces only): ";
        getline(cin, author);

        // Use filterString2 to clean the author input
        filterString2(author);

        // Check if author is not empty after removing invalid characters
        if (!author.empty()) {
            authors[bookCount] = author;
            break; // Exit loop if valid author name is provided
        }
        else {
            cout << "Invalid input. Author Name must only contain letters and spaces.\n";
            continue; // Ask again for valid input
        }
    }

    borrowedBy[bookCount] = ""; // No borrower initially
    bookCount++;

    cout << "Book added successfully!\n";
    saveBooks(); // Save the book data to the file
}
// FS 2
void filterString2(string& input) {
    string result = "";
    for (char ch : input) {
        if (isalpha(ch) || isspace(ch) || ch == '+' || ch == '#') {
            result += ch;
        }
    }
    input = result; // Update the original string with filtered content
}
// BORROW BOOK.
void borrowBook() {
    cout << "Enter Book ID to borrow: ";
    string idInput;
    getline(cin, idInput);
    filterString(idInput);  // Filter to ensure it contains only digits

    if (idInput.empty()) {
        cout << "Invalid input. Please enter a valid numeric value for the BOOK ID.\n";
        return;
    }

    int bookID = stoi(idInput);  // Convert the filtered input to integer

    for (int i = 0; i < bookCount; i++) {
        if (bookIDs[i] == bookID) {
            if (!borrowedBy[i].empty()) {  // Book is already borrowed
                cout << "Book is already borrowed by " << borrowedBy[i] << ".\n";
                return;
            }

            // Asking for borrower's name (letters and spaces only)
            string borrowerName;
            do {
                cout << "Enter your name: ";
                getline(cin, borrowerName);
                filterString2(borrowerName);  // Filter to allow only letters and spaces

                if (borrowerName.empty()) {
                    cout << "Invalid name. Name should contain only letters and spaces. Please try again.\n";
                }

            } while (borrowerName.empty());

            borrowedBy[i] = borrowerName;  // Set the borrower name
            cout << "Book borrowed successfully by " << borrowedBy[i] << ".\n";
            saveBooks();
            return;
        }
    }

    cout << "Book not found.\n";
}

// FS 1
void filterString(string& choice) {
    do {
        string result = "";
        for (unsigned int i = 0; i < choice.length(); i++) {
            if (isdigit(choice[i])) {
                result += choice[i];
            }
        }

        if (!result.empty()) {
            choice = result; // Update choice with the filtered string
            break;
        }
        else {
            cout << "\nInvalid input. Enter only digits :::: ";
            getline(cin, choice);
        }
    } while (true);
}