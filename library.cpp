#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Book {
public:
    int id;
    string title;
    bool issued;

    Book() {}

    Book(int i, string t, bool s) {
        id = i;
        title = t;
        issued = s;
    }
};

class User {
protected:
    string name;

public:
    User(string n) {
        name = n;
    }

    virtual void display() {
        cout << "User: " << name << endl;
    }
};

class Student : public User {
public:
    Student(string n) : User(n) {}

    void display() override {
        cout << "Student: " << name << endl;
    }
};

class Librarian : public User {
public:
    Librarian(string n) : User(n) {}

    void display() override {
        cout << "Librarian: " << name << endl;
    }
};

class Library {
    vector<Book> books;

public:

    void loadFromFile() {
        ifstream file("library.txt");
        Book b;

        while (file >> b.id >> b.title >> b.issued) {
            books.push_back(b);
        }

        file.close();
    }

    void saveToFile() {
        ofstream file("library.txt");

        for (auto &b : books) {
            file << b.id << " " << b.title << " " << b.issued << endl;
        }

        file.close();
    }

    void addBook() {
        int id;
        string title;

        cout << "Enter Book ID: ";
        cin >> id;

        cout << "Enter Book Title: ";
        cin >> title;

        books.push_back(Book(id, title, false));

        saveToFile();

        cout << "Book Added Successfully\n";
    }

    void showBooks() {
        for (auto &b : books) {

            cout << "ID: " << b.id
                 << " | Title: " << b.title
                 << " | ";

            if (b.issued)
                cout << "Issued";
            else
                cout << "Available";

            cout << endl;
        }
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id && !b.issued) {
                b.issued = true;
                saveToFile();
                cout << "Book Issued\n";
                return;
            }
        }

        cout << "Book Not Available\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID: ";
        cin >> id;

        for (auto &b : books) {
            if (b.id == id && b.issued) {
                b.issued = false;
                saveToFile();
                cout << "Book Returned\n";
                return;
            }
        }

        cout << "Invalid Book ID\n";
    }
};

int main() {

    Library lib;
    int choice;

    lib.loadFromFile();

    while (true) {

        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Show Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            lib.addBook();
            break;

        case 2:
            lib.showBooks();
            break;

        case 3:
            lib.issueBook();
            break;

        case 4:
            lib.returnBook();
            break;

        case 5:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid Choice\n";
        }
    }
}