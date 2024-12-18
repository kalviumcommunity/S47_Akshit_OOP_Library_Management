#include <iostream>
#include <string>
using namespace std;

class Book {
    // Private members encapsulate the details of the book
    string title;
    string author;
    bool isAvailable;

    // Static variables to track total and available books
    static int totalBooksOwned;
    static int totalAvailableBooks;

public:
    // Default constructor
    Book() : title("Unknown"), author("Unknown"), isAvailable(true) {
        totalBooksOwned++;
        totalAvailableBooks++;
    }

    // Parameterized constructor
    Book(string t, string a) : title(t), author(a), isAvailable(true) {
        totalBooksOwned++;
        totalAvailableBooks++;
    }

    // Destructor
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

// Initialize static variables outside the class
int Book::totalBooksOwned = 0;
int Book::totalAvailableBooks = 0;

class Member {
    // Private members encapsulate the member details
    string name;
    int memberID;

    // Static variable to track the total number of members
    static int totalMembers;

public:
    // Default constructor
    Member() : name("Unknown"), memberID(0) {
        totalMembers++;
    }

    // Parameterized constructor
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

    // Function for a member to borrow a book
    void borrow(Book* book) {
        cout << getName() << " is borrowing a book." << endl;
        book->borrowBook();
    }

    // Function for a member to return a book
    void returnBook(Book* book) {
        cout << getName() << " is returning a book." << endl;
        book->returnBook();
    }

    // Static member function to display total members
    static void displayTotalMembers() {
        cout << "Total members registered: " << totalMembers << endl;
    }
};

// Initialize static variable outside the class
int Member::totalMembers = 0;

int main() {
    // Create books using both default and parameterized constructors
    Book book1;  // Calls default constructor
    Book book2("The Great Gatsby", "F. Scott Fitzgerald");  // Calls parameterized constructor

    // Create a member using both default and parameterized constructors
    Member member1;  // Calls default constructor
    Member member2("John Doe", 123);  // Calls parameterized constructor

    // Display book and member information
    book1.displayInfo();
    book2.displayInfo();
    member1.displayMemberInfo();
    member2.displayMemberInfo();

    // Clean up dynamic memory
    // In this example, memory is not dynamically allocated, so destructors will be called automatically when the program ends.

    return 0;
}
