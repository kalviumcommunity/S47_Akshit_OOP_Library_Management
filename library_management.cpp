
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
        totalBooksOwned++;
        totalAvailableBooks++;
    }

    // Destructor to decrease the total count when a book object is destroyed
    ~Book() {
        if (isAvailable) {
            totalAvailableBooks--;
        }
        totalBooksOwned--;
    }

    // Accessors (Getters)
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsAvailable() const { return isAvailable; }

    // Mutators (Setters)
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setAvailability(bool available) { isAvailable = available; }

    // Function to display book information
    void displayInfo() {
        cout << "Title: " << getTitle() << ", Author: " << getAuthor()
             << ", Available: " << (getIsAvailable() ? "Yes" : "No") << endl;
    }

    // Function to borrow a book
    void borrowBook() {
        if (getIsAvailable()) {
            setAvailability(false);
            totalAvailableBooks--;
            cout << getTitle() << " has been borrowed. :) " << endl;
        } else {
            cout << getTitle() << " is currently unavailable. :( " << endl;
        }
    }

    // Function to return a borrowed book
    void returnBook() {
        if (!getIsAvailable()) {
            setAvailability(true);
            totalAvailableBooks++;
            cout << getTitle() << " has been returned. :) " << endl;
        } else {
            cout << getTitle() << " was not borrowed and is already available. :) " << endl;
        }
    }

    // Static member function to display book counts
    static void displayBookCounts() {
        cout << "Total books owned by the library: " << totalBooksOwned << endl;
        cout << "Total available books in the library: " << totalAvailableBooks << endl;
    }
};

// Initialize static variables
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
        totalMembers++;
    }

    // Destructor
    ~Member() {
        totalMembers--;
    }

    // Accessors (Getters)
    string getName() const { return name; }
    int getMemberID() const { return memberID; }

    // Mutators (Setters)
    void setName(const string& n) { name = n; }
    void setMemberID(int id) { memberID = id; }

    // Function to display member information
    void displayMemberInfo() {
        cout << "Member Name: Hello! " << getName() << ", Member ID: " << getMemberID() << endl;
    }

    // Function for member to borrow a book
    void borrow(Book* book) {
        cout << getName() << " is borrowing a book." << endl;
        book->borrowBook();
    }

    // Function for member to return a book
    void returnBook(Book* book) {
        cout << getName() << " is returning a book." << endl;
        book->returnBook();
    }

    // Static member function to display total members
    static void displayTotalMembers() {
        cout << "Total members registered: " << totalMembers << endl;
    }
};

// Initialize static variable
int Member::totalMembers = 0;

int main() {
    // Dynamically allocate an array of books
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

    // Dynamically allocate members
    Member* member1 = new Member("Akshit", 101);
    Member* member2 = new Member("Aki", 102);

    member1->displayMemberInfo();
    member2->displayMemberInfo();

    // Display total members
    Member::displayTotalMembers();

    // Member1 borrows a book
    member1->borrow(&library[0]);
    Book::displayBookCounts();

    // Try borrowing the same book again
    member2->borrow(&library[0]);

    // Member2 borrows another book
    member2->borrow(&library[2]);
    Book::displayBookCounts();

    // Member1 returns the first book
    member1->returnBook(&library[0]);
    Book::displayBookCounts();

    // Free memory
    delete[] library;
    delete member1;
    delete member2;

    return 0;
}

