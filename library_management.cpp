#include<iostream>
using namespace std;

class Book {
    string title;
    string author;
    bool isAvailable;

public:
    // Constructor
    Book(string t, string a) : title(t), author(a), isAvailable(true) {}

    // Function to display book information
    void displayInfo() {
        cout << "Title: " << title << ", Author: " << author << ", Available: " 
             << (isAvailable ? "Yes" : "No") << endl;
    }

    // Function to borrow a book
    void borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            cout << title << " has been borrowed. :) " << endl;
        } else {
            cout << title << " is currently unavailable. :( " << endl;
        }
    }
};

class Member {
    string name;
    int memberID;

public:
    // Constructor
    Member(string n, int id) : name(n), memberID(id) {}

    // Function to display member information
    void displayMemberInfo() {
        cout << "Member Name: Hello! " << name << ", Member ID: " << memberID << endl;
    }

    // Function for member to borrow a book
    void borrow(Book &book) {
        cout << name << " is borrowing a book." << endl;
        book.borrowBook();
    }
};

int main() {
    // Creating book object
    Book book1("Harry Potter and the Philosopher's Stone", "J.K. Rowling");

    // Creating member object
    Member member1("Akshit", 101);
    Member member2("Aki", 102);

    // Display book and member information
    book1.displayInfo();
    member1.displayMemberInfo();

    // Member borrows a book
    member1.borrow(book1);

    // Try borrowing the book again
    member1.borrow(book1);

    // Member 2 borrows the book ...........
    member2.borrow(book1);

    return 0;
}
