
#include <iostream>
#include <string>
using namespace std;

// Class representing a book in the library
class Book {
    // Private members encapsulate the details of the book
    string title;
    string author;
    bool isAvailable;

    // Static variables to track total and available books
    static int totalBooksOwned;
    static int totalAvailableBooks;

public:
    // Constructor to initialize a book with a title and author
    Book(string t, string a) : title(t), author(a), isAvailable(true) {
        totalBooksOwned++;
        totalAvailableBooks++;
    }

    // Destructor to decrease the total count when a book is destroyed
    ~Book() {
        if (isAvailable) {
            totalAvailableBooks--;
        }
        totalBooksOwned--;
    }

    // Public getter methods for reading book details
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsAvailable() const { return isAvailable; }

    // Public setter methods for updating book details
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setAvailability(bool available) { isAvailable = available; }

    // Public method to display book information
    void displayInfo() {
        cout << "Title: " << getTitle() << ", Author: " << getAuthor()
             << ", Available: " << (getIsAvailable() ? "Yes" : "No") << endl;
    }

    // Method for borrowing a book, showing abstraction of the borrowing process
    void borrowBook() {
        if (getIsAvailable()) {
            setAvailability(false);
            totalAvailableBooks--;
            cout << getTitle() << " has been borrowed. :) " << endl;
        } else {
            cout << getTitle() << " is currently unavailable. :( " << endl;
        }
    }

    // Method for returning a borrowed book
    void returnBook() {
        if (!getIsAvailable()) {
            setAvailability(true);
            totalAvailableBooks++;
            cout << getTitle() << " has been returned. :) " << endl;
        } else {
            cout << getTitle() << " was not borrowed and is already available. :) " << endl;
        }
    }

    // Static method to display the total count of books
    static void displayBookCounts() {
        cout << "Total books owned by the library: " << totalBooksOwned << endl;
        cout << "Total available books in the library: " << totalAvailableBooks << endl;
    }
};

// Initialize static variables outside the class
int Book::totalBooksOwned = 0;
int Book::totalAvailableBooks = 0;

// Class representing a member of the library
class Member {
    // Private members encapsulate the member details
    string name;
    int memberID;

    // Static variable to track the total number of members
    static int totalMembers;

public:
    // Constructor to initialize a member
    Member(string n, int id) : name(n), memberID(id) {
        totalMembers++;
    }

    // Destructor
    ~Member() {
        totalMembers--;
    }

    // Public getter methods for member details
    string getName() const { return name; }
    int getMemberID() const { return memberID; }

    // Public setter methods for member details
    void setName(const string& n) { name = n; }
    void setMemberID(int id) { memberID = id; }

    // Public method to display member information
    void displayMemberInfo() {
        cout << "Member Name: Hello! " << getName() << ", Member ID: " << getMemberID() << endl;
    }

    // Method for a member to borrow a book
    void borrow(Book* book) {
        cout << getName() << " is borrowing a book." << endl;
        book->borrowBook();
    }

    // Method for a member to return a book
    void returnBook(Book* book) {
        cout << getName() << " is returning a book." << endl;
        book->returnBook();
    }

    // Static method to display total members
    static void displayTotalMembers() {
        cout << "Total members registered: " << totalMembers << endl;
    }
};

// Initialize static variable outside the class
int Member::totalMembers = 0;

int main() {
    // Creating an array of books using dynamic allocation
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

    // Creating library members
    Member* member1 = new Member("Akshit", 101);
    Member* member2 = new Member("Aki", 102);

    member1->displayMemberInfo();
    member2->displayMemberInfo();

    // Display total members
    Member::displayTotalMembers();

    // Member1 borrows a book
    member1->borrow(&library[0]);
    Book::displayBookCounts();

    // Member2 tries to borrow the same book
    member2->borrow(&library[0]);

    // Member2 borrows another book
    member2->borrow(&library[2]);
    Book::displayBookCounts();

    // Member1 returns the first book
    member1->returnBook(&library[0]);
    Book::displayBookCounts();

    // Free dynamically allocated memory
    delete[] library;
    delete member1;
    delete member2;

    return 0;
}
