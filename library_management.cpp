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
    virtual ~Book() { // Virtual destructor for proper cleanup
        if (isAvailable) {
            totalAvailableBooks--;
        }
        totalBooksOwned--;
    }

    // Accessors
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getIsAvailable() const { return isAvailable; }

    // Mutators
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }
    void setAvailability(bool available) { isAvailable = available; }

    // Display basic book information
    virtual void displayInfo() {
        cout << "Title: " << title << ", Author: " << author
             << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }

    // Borrow a book
    virtual void borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            totalAvailableBooks--;
            cout << title << " has been borrowed. :) " << endl;
        } else {
            cout << title << " is currently unavailable. :( " << endl;
        }
    }

    // Return a book
    virtual void returnBook() {
        if (!isAvailable) {
            isAvailable = true;
            totalAvailableBooks++;
            cout << title << " has been returned. :) " << endl;
        } else {
            cout << title << " was not borrowed and is already available. :) " << endl;
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

// Derived class for digital books
class DigitalBook : public Book {
    double fileSize;  // in MB
    string format;    // e.g., PDF, ePub

public:
    // Parameterized constructor
    DigitalBook(string t, string a, double fs, string fmt)
        : Book(t, a), fileSize(fs), format(fmt) {}

    // Accessors
    double getFileSize() const { return fileSize; }
    string getFormat() const { return format; }

    // Mutators
    void setFileSize(double fs) { fileSize = fs; }
    void setFormat(const string& fmt) { format = fmt; }

    // Override displayInfo to include digital-specific details
    void displayInfo() override {
        Book::displayInfo();  // Call base class method
        cout << "File Size: " << fileSize << " MB, Format: " << format << endl;
    }
};


// Base class for all persons in the system
class Person {
protected:
    string name;
    int id;

public:
    // Constructor
    Person(string n = "Unknown", int i = 0) : name(n), id(i) {}

    // Destructor
    virtual ~Person() {}

    // Common accessor methods
    string getName() const { return name; }
    int getID() const { return id; }

    // Common mutator methods
    void setName(const string& n) { name = n; }
    void setID(int i) { id = i; }

    // Borrow and return books functionality
    virtual void borrow(Book* book) {
        cout << name << " is borrowing a book." << endl;
        book->borrowBook();
    }

    virtual void returnBook(Book* book) {
        cout << name << " is returning a book." << endl;
        book->returnBook();
    }

    // Common functionality
    virtual void displayInfo() const {
        cout << "Name: " << name << ", ID: " << id << endl;
    }
};

// Derived class for regular members
class Member : public Person {
    static int totalMembers;

public:
    // Constructor
    Member(string n = "Unknown", int i = 0) : Person(n, i) {
        totalMembers++;
    }

    // Destructor
    ~Member() {
        totalMembers--;
    }

    // Static method to display total members
    static void displayTotalMembers() {
        cout << "Total members registered: " << totalMembers << endl;
    }

    // Overriding displayInfo
    void displayInfo() const override {
        cout << "Regular Member Info - ";
        Person::displayInfo();
    }
};

// Initialize static member
int Member::totalMembers = 0;

// Derived class for premium members
class PremiumMember : public Person {
    static int totalPremiumMembers;
    double subscriptionFee;

public:
    // Constructor
    PremiumMember(string n = "Unknown", int i = 0, double fee = 0.0)
        : Person(n, i), subscriptionFee(fee) {
        totalPremiumMembers++;
    }

    // Destructor
    ~PremiumMember() {
        totalPremiumMembers--;
    }

    // Accessor for subscription fee
    double getSubscriptionFee() const { return subscriptionFee; }

    // Premium privilege
    void accessPremiumFeature() {
        cout << name << " is accessing premium features with subscription fee: $" << subscriptionFee << endl;
    }

    // Static method to display total premium members
    static void displayTotalPremiumMembers() {
        cout << "Total premium members registered: " << totalPremiumMembers << endl;
    }

    // Overriding displayInfo
    void displayInfo() const override {
        cout << "Premium Member Info - ";
        Person::displayInfo();
        cout << "Subscription Fee: $" << subscriptionFee << endl;
    }
};

// Initialize static member
int PremiumMember::totalPremiumMembers = 0;

int main() {
    // Create books
    Book book1("The Great Gatsby", "F. Scott Fitzgerald");
    Book book2("1984", "George Orwell");

        // Create digital books
    DigitalBook eBook1("Digital Minimalism", "Cal Newport", 2.5, "PDF");
    DigitalBook eBook2("Atomic Habits", "James Clear", 1.8, "ePub");

    // Create members using hierarchical inheritance
    Member member1("Alice", 101);
    PremiumMember premiumMember1("Bob", 102, 20.0);

    // Display their information
    member1.displayInfo();
    premiumMember1.displayInfo();

    // Test borrowing and returning books
    member1.borrow(&book1);
    premiumMember1.borrow(&book2);
    Book::displayBookCounts();

    member1.returnBook(&book1);
    premiumMember1.returnBook(&book2);
    Book::displayBookCounts();

    // Access premium features
    premiumMember1.accessPremiumFeature();

    // Display total members
    Member::displayTotalMembers();
    PremiumMember::displayTotalPremiumMembers();

    cout << "\n--- Digital Books ---" << endl;
    eBook1.displayInfo();
    eBook2.displayInfo();

    return 0;
}
