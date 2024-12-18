#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract class to define the common interface for library entities
class LibraryEntity {
public:
    virtual void displayInfo() const = 0; // Pure virtual function
    virtual ~LibraryEntity() {}          // Virtual destructor
};

// Separate class to track book-related statistics (SRP applied here)
class BookTracker {
    static int totalBooksOwned;
    static int totalAvailableBooks;

public:
    // Increment book counts
    static void addBook() {
        totalBooksOwned++;
        totalAvailableBooks++;
    }

    // Decrement book counts
    static void removeBook(bool isAvailable) {
        totalBooksOwned--;
        if (isAvailable)
            totalAvailableBooks--;
    }

    // Update available count when a book is borrowed
    static void borrowBook() {
        if (totalAvailableBooks > 0)
            totalAvailableBooks--;
    }

    // Update available count when a book is returned
    static void returnBook() { totalAvailableBooks++; }

    // Display book counts
    static void displayBookCounts() {
        cout << "Total books owned by the library: " << totalBooksOwned << endl;
        cout << "Total available books in the library: " << totalAvailableBooks << endl;
    }
};

// Initialize static variables for BookTracker
int BookTracker::totalBooksOwned = 0;
int BookTracker::totalAvailableBooks = 0;

// Book class now focuses only on managing individual book details
class Book : public LibraryEntity {
    string title;
    string author;
    bool isAvailable;

public:
    // Default constructor
    Book() : title("Unknown"), author("Unknown"), isAvailable(true) {
        BookTracker::addBook();
    }

    // Parameterized constructor
    Book(string t, string a) : title(t), author(a), isAvailable(true) {
        BookTracker::addBook();
    }

    // Destructor
    virtual ~Book() {
        BookTracker::removeBook(isAvailable);
    }

    // Accessors
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsAvailable() const { return isAvailable; }

    // Mutators
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }

    // Borrow a book
    virtual void borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            BookTracker::borrowBook();
            cout << title << " has been borrowed. :) " << endl;
        } else {
            cout << title << " is currently unavailable. :( " << endl;
        }
    }

    // Return a book
    virtual void returnBook() {
        if (!isAvailable) {
            isAvailable = true;
            BookTracker::returnBook();
            cout << title << " has been returned. :) " << endl;
        } else {
            cout << title << " was not borrowed and is already available. :) " << endl;
        }
    }

    // Override displayInfo
    virtual void displayInfo() const override {
        cout << "Title: " << title << ", Author: " << author
             << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// Derived class for digital books
class DigitalBook : public Book {
    double fileSize;
    string format;

public:
    DigitalBook(string t, string a, double fs, string fmt)
        : Book(t, a), fileSize(fs), format(fmt) {}

    void displayInfo() const override {
        Book::displayInfo();
        cout << "File Size: " << fileSize << " MB, Format: " << format << endl;
    }
};


class Person : public LibraryEntity {
protected:
    string name;
    int id;

public:
    Person(string n = "Unknown", int i = 0) : name(n), id(i) {}

    virtual ~Person() {}

    virtual void displayInfo() const override {
        cout << "Name: " << name << ", ID: " << id << endl;
    }

    virtual void borrow(Book* book) {
        cout << name << " is borrowing a book." << endl;
        book->borrowBook();
    }

    virtual void returnBook(Book* book) {
        cout << name << " is returning a book." << endl;
        book->returnBook();
    }
};

class Member : public Person {
    static int totalMembers;

public:
    Member(string n = "Unknown", int i = 0) : Person(n, i) { totalMembers++; }

    ~Member() { totalMembers--; }

    void displayInfo() const override {
        cout << "Regular Member Info - ";
        Person::displayInfo();
    }

    static void displayTotalMembers() {
        cout << "Total members registered: " << totalMembers << endl;
    }
};

int Member::totalMembers = 0;

class PremiumMember : public Person {
    static int totalPremiumMembers;
    double subscriptionFee;

public:
    PremiumMember(string n = "Unknown", int i = 0, double fee = 0.0)
        : Person(n, i), subscriptionFee(fee) {
        totalPremiumMembers++;
    }

    ~PremiumMember() { totalPremiumMembers--; }

    void displayInfo() const override {
        cout << "Premium Member Info - ";
        Person::displayInfo();
        cout << "Subscription Fee: $" << subscriptionFee << endl;
    }

    static void displayTotalPremiumMembers() {
        cout << "Total premium members registered: " << totalPremiumMembers << endl;
    }
};

int PremiumMember::totalPremiumMembers = 0;

int main() {
    // Create books
    Book book1("The Great Gatsby", "F. Scott Fitzgerald");
    Book book2("1984", "George Orwell");

    // Create digital books
    DigitalBook eBook1("Digital Minimalism", "Cal Newport", 2.5, "PDF");
    DigitalBook eBook2("Atomic Habits", "James Clear", 1.8, "ePub");

    // Borrow and return books
    book1.borrowBook();
    book1.returnBook();

    // Display book counts using BookTracker
    BookTracker::displayBookCounts();

    return 0;
}
