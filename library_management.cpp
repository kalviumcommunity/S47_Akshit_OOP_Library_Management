#include <iostream>
#include <string>
using namespace std;

class Book {
    string title;
    string author;
    bool isAvailable;

    // Static variables to track total and available books
    static int totalBooksOwned;
    static int totalAvailableBooks;

public:
    // Constructor
    Book(string t, string a) : title(t), author(a), isAvailable(true) {
        totalBooksOwned++;    // Increment total books owned
        totalAvailableBooks++; // Increment available books count
    }

    // Destructor to decrease the total count when a book object is destroyed
    ~Book() {
        if (isAvailable) {
            totalAvailableBooks--;
        }
        totalBooksOwned--; // Decrementing the total books count
    }

    // Function to display book information
    void displayInfo() {
        cout << "Title: " << this->title << ", Author: " << this->author 
             << ", Available: " << (this->isAvailable ? "Yes" : "No") << endl;
    }

    // Function to borrow a book
    void borrowBook() {
        if (this->isAvailable) {
            this->isAvailable = false;
            totalAvailableBooks--; // Decreasing the total available books count
            cout << this->title << " has been borrowed. :) " << endl;
        } else {
            cout << this->title << " is currently unavailable. :( " << endl;
        }
    }

    // Function to return a borrowed book (resubmit :) )
    void returnBook() {
        if (!this->isAvailable) {
            this->isAvailable = true;
            totalAvailableBooks++; // Incrementing the total available books count
            cout << this->title << " has been returned. :) " << endl;
        } else {
            cout << this->title << " was not borrowed and is already available. :) " << endl;
        }
    }

    // Static function to display the current number of available and total books
    static void displayBookCounts() {
        cout << "Total books owned by the library: " << totalBooksOwned << endl;
        cout << "Total available books in the library: " << totalAvailableBooks << endl;
    }
};

// Initialize the static variables
int Book::totalBooksOwned = 0;
int Book::totalAvailableBooks = 0;

class Member {
    string name;
    int memberID;

    // Static variable to track the total number of members
    static int totalMembers;

public:
    // Constructor
    Member(string n, int id) : name(n), memberID(id) {
        totalMembers++; // Incrementing the total number of members when a member is created
    }

    // --- Destructor to decrease the totalMembers count when a member object is destroyed ---
    ~Member() {
        totalMembers--;
    }

    // Function to display member information
    void displayMemberInfo() {
        cout << "Member Name: Hello! " << this->name << ", Member ID: " << this->memberID << endl;
    }

    // Function for member to borrow a book
    void borrow(Book* book) { 
        cout << this->name << " is borrowing a book." << endl;
        book->borrowBook(); 
    }

    void returnBook(Book* book) { 
        cout << this->name << " is returning a book." << endl;
        book->returnBook();
    }

    // Static function to display the total number of members
    static void displayTotalMembers() {
        cout << "Total members registered: " << totalMembers << endl;
    }
};

// Initialize the static variable
int Member::totalMembers = 0;

int main() {
    // Dynamically allocating an array of books
    Book* library = new Book[3]{
        Book("Harry Potter and the Philosopher's Stone", "J.K. Rowling"),
        Book("The Hobbit", "J.R.R. Tolkien"),
        Book("1984", "George Orwell")
    };

    cout << "Books available in the library:" << endl;
    for (int i = 0; i < 3; ++i) {
        library[i].displayInfo();
    }

    // Display the total number of available and owned books
    Book::displayBookCounts();

    // Creating member objects dynamically
    Member* member1 = new Member("Akshit", 101);
    Member* member2 = new Member("Aki", 102);

    member1->displayMemberInfo();
    member2->displayMemberInfo();

    // Displaying total members using the static function
    Member::displayTotalMembers();

    // -------------------------------------------------------------------------

    // Member1 borrows a book
    member1->borrow(&library[0]); // Pass address of the book
    Book::displayBookCounts();    // Display current available and total books

    // Try borrowing the same book again
    member2->borrow(&library[0]); // Pass address of the book

    // Member2 borrows another book
    member2->borrow(&library[2]); 
    Book::displayBookCounts();    // Display current available and total books

    // -------------------------------------------------------------------------

    // Member1 returns the first book
    member1->returnBook(&library[0]);
    Book::displayBookCounts(); // Display current available and total books

    // Freeing dynamically allocated memory
    delete[] library; 
    delete member1;  
    delete member2;   

    return 0;
}
