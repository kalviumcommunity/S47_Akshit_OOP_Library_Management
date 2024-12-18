#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// ISP Interfaces
class IBorrowable {
public:
    virtual void borrowItem() = 0;
    virtual void returnItem() = 0;
    virtual bool isAvailable() const = 0;
    virtual ~IBorrowable() = default;
};

class IDisplayable {
public:
    virtual void displayDetails() const = 0;
    virtual ~IDisplayable() = default;
};

class ITrackable {
public:
    virtual string getUniqueIdentifier() const = 0;
    virtual ~ITrackable() = default;
};

class IMemberManagement {
public:
    virtual void registerMember() = 0;
    virtual void unregisterMember() = 0;
    virtual ~IMemberManagement() = default;
};

// Book Tracker Class
class BookTracker {
    static int totalBooksOwned;
    static int totalAvailableBooks;

public:
    static void addBook() {
        totalBooksOwned++;
        totalAvailableBooks++;
    }

    static void removeBook(bool isAvailable) {
        totalBooksOwned--;
        if (isAvailable)
            totalAvailableBooks--;
    }

    static void borrowBook() {
        if (totalAvailableBooks > 0)
            totalAvailableBooks--;
    }

    static void returnBook() { 
        totalAvailableBooks++; 
    }

    static void displayBookCounts() {
        cout << "Total books owned by the library: " << totalBooksOwned << endl;
        cout << "Total available books in the library: " << totalAvailableBooks << endl;
    }
};

// Initialize static variables
int BookTracker::totalBooksOwned = 0;
int BookTracker::totalAvailableBooks = 0;

// Book Class
class Book : public IBorrowable, public IDisplayable, public ITrackable {
private:
    string title;
    string author;
    bool available;
    string isbn;

public:
    Book(string t = "Unknown", string a = "Unknown", string i = "N/A") 
        : title(t), author(a), available(true), isbn(i) {
        BookTracker::addBook();
    }

    ~Book() {
        BookTracker::removeBook(available);
    }

    // Borrowing Implementation
    void borrowItem() override {
        if (available) {
            available = false;
            BookTracker::borrowBook();
            cout << "Book '" << title << "' has been borrowed successfully!" << endl;
        } else {
            cout << "Book '" << title << "' is currently unavailable." << endl;
        }
    }

    void returnItem() override {
        if (!available) {
            available = true;
            BookTracker::returnBook();
            cout << "Book '" << title << "' has been returned successfully!" << endl;
        } else {
            cout << "Book '" << title << "' was already in the library." << endl;
        }
    }

    bool isAvailable() const override { 
        return available; 
    }

    // Display Book Details
    void displayDetails() const override {
        cout << "Book Details:" << endl;
        cout << "   Title: " << title << endl;
        cout << "   Author: " << author << endl;
        cout << "   ISBN: " << isbn << endl;
        cout << "   Status: " << (available ? "Available" : "Borrowed") << endl;
    }

    // Unique Identifier
    string getUniqueIdentifier() const override { return isbn; }

    // Getters and Setters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
};

// Digital Book Extension
class DigitalBook : public Book {
private:
    double fileSize;
    string format;

public:
    DigitalBook(string t, string a, double fs, string fmt, string isbn = "N/A")
        : Book(t, a, isbn), fileSize(fs), format(fmt) {}

    void displayDetails() const override {
        Book::displayDetails();
        cout << "   File Size: " << fileSize << " MB" << endl;
        cout << "   Format: " << format << endl;
    }
};

// Person Base Class
class Person : public IMemberManagement, public IDisplayable {
protected:
    string name;
    int id;

public:
    Person(string n = "Unknown", int i = 0) : name(n), id(i) {}

    // Member Management
    virtual void registerMember() override {
        cout << name << " has been registered successfully!" << endl;
    }

    virtual void unregisterMember() override {
        cout << name << " has been unregistered from the library." << endl;
    }

    // Display Person Details
    virtual void displayDetails() const override {
        cout << "Person Details:" << endl;
        cout << "   Name: " << name << endl;
        cout << "   ID: " << id << endl;
    }

    virtual void borrow(Book* book) {
        cout << name << " is borrowing a book." << endl;
        book->borrowItem();
    }

    virtual void returnBook(Book* book) {
        cout << name << " is returning a book." << endl;
        book->returnItem();
    }
};

// Member Classes
class Member : public Person {
    static int totalMembers;

public:
    Member(string n = "Unknown", int i = 0) : Person(n, i) {
        totalMembers++;
    }

    ~Member() {
        totalMembers--;
    }

    void displayDetails() const override {
        cout << "Regular Member Details:" << endl;
        Person::displayDetails();
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

    ~PremiumMember() {
        totalPremiumMembers--;
    }

    void displayDetails() const override {
        cout << "Premium Member Details:" << endl;
        Person::displayDetails();
        cout << "   Subscription Fee: $" << subscriptionFee << endl;
    }

    static void displayTotalPremiumMembers() {
        cout << "Total premium members registered: " << totalPremiumMembers << endl;
    }
};

int PremiumMember::totalPremiumMembers = 0;

// Library Management System
class LibraryManagementSystem {
private:
    vector<unique_ptr<Book>> books;
    vector<unique_ptr<Person>> members;

public:
    void addBook(unique_ptr<Book> book) {
        books.push_back(move(book));
    }

    void addMember(unique_ptr<Person> member) {
        members.push_back(move(member));
    }

    void simulateLibraryOperations() {
        cout << "\nComprehensive Library Simulation\n" << endl;

        // Create and add books
        addBook(make_unique<Book>("Clean Code", "Robert Martin", "ISBN-001"));
        addBook(make_unique<DigitalBook>("Design Patterns", "Gang of Four", 2.5, "PDF", "ISBN-002"));

        // Create and add members
        addMember(make_unique<Member>("Alice Johnson", 101));
        addMember(make_unique<PremiumMember>("Bob Smith", 201, 50.0));

        // Simulate member and book interactions
        for (auto& member : members) {
            member->displayDetails();
            member->registerMember();
        }

        for (auto& book : books) {
            book->displayDetails();
            
            if (book->isAvailable()) {
                members[0]->borrow(book.get());
                members[1]->returnBook(book.get());
            }
        }

        // Display statistics
        BookTracker::displayBookCounts();
        Member::displayTotalMembers();
        PremiumMember::displayTotalPremiumMembers();
    }
};

int main() {
    LibraryManagementSystem librarySystem;
    librarySystem.simulateLibraryOperations();
    return 0;
}
