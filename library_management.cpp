#include <iostream>
#include <string>
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
        cout << "Title: " << this->title << ", Author: " << this->author 
             << ", Available: " << (this->isAvailable ? "Yes" : "No") << endl;
    }

    // Function to borrow a book
    void borrowBook() {
        if (this->isAvailable) {
            this->isAvailable = false;
            cout << this->title << " has been borrowed. :) " << endl;
        } else {
            cout << this->title << " is currently unavailable. :( " << endl;
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
        cout << "Member Name: Hello! " << this->name << ", Member ID: " << this->memberID << endl;
    }

    // Function for member to borrow a book
    void borrow(Book* book) { // Pass pointer to the book
        cout << this->name << " is borrowing a book." << endl;
        book->borrowBook(); // Use arrow operator to access member function
    }
};

int main() {
    // Dynamically allocating an array of books
    Book* library = new Book[3]{
        Book("Harry Potter and the Philosopher's Stone", "J.K. Rowling"),
        Book("The Hobbit", "J.R.R. Tolkien"),
        Book("1984", "George Orwell")
    };

    // Displaying information about all books in the array
    cout << "Books available in the library:" << endl;
    for (int i = 0; i < 3; ++i) {
        library[i].displayInfo();
    }

    // Creating member objects dynamically
    Member* member1 = new Member("Akshit", 101);
    Member* member2 = new Member("Aki", 102);

    // Displaying member information
    member1->displayMemberInfo();
    member2->displayMemberInfo();

    // Member1 borrows a book
    member1->borrow(&library[0]); 

    // Try borrowing the same book again
    member2->borrow(&library[0]); 

    // Member2 borrows another book
    member2->borrow(&library[2]); 

    // Freeing dynamically allocated memory
    delete[] library;
    delete member1; 
    delete member2; 

    return 0;
}
