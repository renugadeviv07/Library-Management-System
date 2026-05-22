#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

// ================= BOOK CLASS =================
class Book {
public:
    int id;
    string title;
    string author;
    int quantity;

    Book() {}

    Book(int i, string t, string a, int q) {
        id = i;
        title = t;
        author = a;
        quantity = q;
    }
};

// ================= MEMBER CLASS =================
class Member {
public:
    int id;
    string name;

    Member() {}

    Member(int i, string n) {
        id = i;
        name = n;
    }
};

// ================= ISSUE CLASS =================
class IssueRecord {
public:
    int bookId;
    int memberId;
    string issueDate;

    IssueRecord() {}

    IssueRecord(int b, int m, string d) {
        bookId = b;
        memberId = m;
        issueDate = d;
    }
};

// ================= LIBRARY CLASS =================
class Library {
private:
    unordered_map<int, Book> books;
    unordered_map<int, Member> members;
    vector<IssueRecord> issuedBooks;

public:

    // ================= DATE FUNCTION =================
    string currentDate() {
        time_t now = time(0);
        string dt = ctime(&now);

        if (!dt.empty() && dt.back() == '\n')
            dt.pop_back();

        return dt;
    }

    // ================= LOAD DATA =================
    void loadBooks() {
        ifstream file("books.txt");

        if (!file)
            return;

        Book b;

        while (file >> b.id) {
            file.ignore();
            getline(file, b.title);
            getline(file, b.author);
            file >> b.quantity;
            file.ignore();

            books[b.id] = b;
        }

        file.close();
    }

    void loadMembers() {
        ifstream file("members.txt");

        if (!file)
            return;

        Member m;

        while (file >> m.id) {
            file.ignore();
            getline(file, m.name);

            members[m.id] = m;
        }

        file.close();
    }

    void loadIssuedBooks() {
        ifstream file("issued.txt");

        if (!file)
            return;

        IssueRecord r;

        while (file >> r.bookId >> r.memberId) {
            file.ignore();
            getline(file, r.issueDate);

            issuedBooks.push_back(r);
        }

        file.close();
    }

    // ================= SAVE DATA =================
    void saveBooks() {
        ofstream file("books.txt");

        for (auto &pair : books) {
            Book b = pair.second;

            file << b.id << endl;
            file << b.title << endl;
            file << b.author << endl;
            file << b.quantity << endl;
        }

        file.close();
    }

    void saveMembers() {
        ofstream file("members.txt");

        for (auto &pair : members) {
            Member m = pair.second;

            file << m.id << endl;
            file << m.name << endl;
        }

        file.close();
    }

    void saveIssuedBooks() {
        ofstream file("issued.txt");

        for (auto &r : issuedBooks) {
            file << r.bookId << " "
                 << r.memberId << endl;
            file << r.issueDate << endl;
        }

        file.close();
    }

  // ================= LOGIN =================
bool login() {

    string setUsername, setPassword;
    string username, password;

    cout << "========== CREATE ACCOUNT ==========" << endl;

    cout << "Create Username: ";
    cin >> setUsername;

    cout << "Create Password: ";
    cin >> setPassword;

    cout << "\n========== LOGIN ==========" << endl;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    if (username == setUsername && password == setPassword) {
        cout << "\nLogin Successful!\n";
        return true;
    }

    cout << "\nInvalid Login!\n";
    return false;
}

    // ================= ADD BOOK =================
    void addBook() {
        int id, quantity;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;

        if (books.find(id) != books.end()) {
            cout << "Book ID Already Exists!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        cout << "Enter Quantity: ";
        cin >> quantity;

        books[id] = Book(id, title, author, quantity);

        saveBooks();

        cout << "\nBook Added Successfully!\n";
    }

    // ================= DISPLAY BOOKS =================
    void displayBooks() {

        if (books.empty()) {
            cout << "\nNo Books Available!\n";
            return;
        }

        cout << "\n=========== BOOK LIST ===========\n";

        for (auto &pair : books) {
            Book b = pair.second;

            cout << "\nBook ID    : " << b.id;
            cout << "\nTitle      : " << b.title;
            cout << "\nAuthor     : " << b.author;
            cout << "\nQuantity   : " << b.quantity;
            cout << "\nStatus     : ";

            if (b.quantity > 0)
                cout << "Available";
            else
                cout << "Out of Stock";

            cout << "\n--------------------------------\n";
        }
    }

    // ================= SEARCH BY TITLE =================
    void searchByTitle() {
        string title;
        bool found = false;

        cin.ignore();

        cout << "\nEnter Title: ";
        getline(cin, title);

        transform(title.begin(), title.end(), title.begin(), ::tolower);

        for (auto &pair : books) {
            Book b = pair.second;

            string temp = b.title;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

            if (temp.find(title) != string::npos) {
                cout << "\nBook Found!\n";
                cout << "ID       : " << b.id << endl;
                cout << "Title    : " << b.title << endl;
                cout << "Author   : " << b.author << endl;
                cout << "Quantity : " << b.quantity << endl;

                found = true;
            }
        }

        if (!found)
            cout << "\nNo Book Found!\n";
    }

    // ================= SEARCH BY AUTHOR =================
    void searchByAuthor() {
        string author;
        bool found = false;

        cin.ignore();

        cout << "\nEnter Author Name: ";
        getline(cin, author);

        transform(author.begin(), author.end(), author.begin(), ::tolower);

        for (auto &pair : books) {
            Book b = pair.second;

            string temp = b.author;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

            if (temp.find(author) != string::npos) {
                cout << "\nBook Found!\n";
                cout << "ID       : " << b.id << endl;
                cout << "Title    : " << b.title << endl;
                cout << "Author   : " << b.author << endl;
                cout << "Quantity : " << b.quantity << endl;

                found = true;
            }
        }

        if (!found)
            cout << "\nNo Book Found!\n";
    }

    // ================= ADD MEMBER =================
    void addMember() {
        int id;
        string name;

        cout << "\nEnter Member ID: ";
        cin >> id;

        if (members.find(id) != members.end()) {
            cout << "Member ID Already Exists!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Member Name: ";
        getline(cin, name);

        members[id] = Member(id, name);

        saveMembers();

        cout << "\nMember Added Successfully!\n";
    }

    // ================= DISPLAY MEMBERS =================
    void displayMembers() {

        if (members.empty()) {
            cout << "\nNo Members Found!\n";
            return;
        }

        cout << "\n========== MEMBER LIST ==========" << endl;

        for (auto &pair : members) {
            Member m = pair.second;

            cout << "\nMember ID : " << m.id;
            cout << "\nName      : " << m.name;
            cout << "\n------------------------------\n";
        }
    }

    // ================= ISSUE BOOK =================
    void issueBook() {
        int bookId, memberId;

        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cout << "Enter Member ID: ";
        cin >> memberId;

        if (books.find(bookId) == books.end()) {
            cout << "Book Not Found!\n";
            return;
        }

        if (members.find(memberId) == members.end()) {
            cout << "Member Not Found!\n";
            return;
        }

        if (books[bookId].quantity <= 0) {
            cout << "Book Out of Stock!\n";
            return;
        }

        books[bookId].quantity--;

        string date = currentDate();

        issuedBooks.push_back(IssueRecord(bookId, memberId, date));

        saveBooks();
        saveIssuedBooks();

        cout << "\nBook Issued Successfully!\n";
        cout << "Issue Date: " << date << endl;
    }

    // ================= RETURN BOOK =================
    void returnBook() {
        int bookId, memberId;
        bool found = false;

        cout << "\nEnter Book ID: ";
        cin >> bookId;

        cout << "Enter Member ID: ";
        cin >> memberId;

        for (int i = 0; i < issuedBooks.size(); i++) {

            if (issuedBooks[i].bookId == bookId &&
                issuedBooks[i].memberId == memberId) {

                found = true;

                issuedBooks.erase(issuedBooks.begin() + i);

                books[bookId].quantity++;

                saveBooks();
                saveIssuedBooks();

                cout << "\nBook Returned Successfully!\n";
                break;
            }
        }

        if (!found)
            cout << "\nIssue Record Not Found!\n";
    }

    // ================= DISPLAY ISSUED BOOKS =================
    void displayIssuedBooks() {

        if (issuedBooks.empty()) {
            cout << "\nNo Issued Books!\n";
            return;
        }

        cout << "\n========== ISSUED BOOKS ==========" << endl;

        for (auto &r : issuedBooks) {

            cout << "\nBook ID    : " << r.bookId;
            cout << "\nMember ID  : " << r.memberId;
            cout << "\nIssue Date : " << r.issueDate;
            cout << "\n-------------------------------\n";
        }
    }

    // ================= DELETE BOOK =================
    void deleteBook() {
        int id;

        cout << "\nEnter Book ID to Delete: ";
        cin >> id;

        if (books.find(id) == books.end()) {
            cout << "Book Not Found!\n";
            return;
        }

        books.erase(id);

        saveBooks();

        cout << "\nBook Deleted Successfully!\n";
    }

    // ================= UPDATE BOOK =================
    void updateBook() {
        int id;

        cout << "\nEnter Book ID to Update: ";
        cin >> id;

        if (books.find(id) == books.end()) {
            cout << "Book Not Found!\n";
            return;
        }

        cin.ignore();

        cout << "Enter New Title: ";
        getline(cin, books[id].title);

        cout << "Enter New Author: ";
        getline(cin, books[id].author);

        cout << "Enter New Quantity: ";
        cin >> books[id].quantity;

        saveBooks();

        cout << "\nBook Updated Successfully!\n";
    }
};

// ================= MAIN FUNCTION =================
int main() {

    Library lib;

    lib.loadBooks();
    lib.loadMembers();
    lib.loadIssuedBooks();

    if (!lib.login())
        return 0;

    int choice;

    do {

        cout << "\n\n========== LIBRARY MANAGEMENT SYSTEM ==========" << endl;

        cout << "1. Add Book" << endl;
        cout << "2. Display Books" << endl;
        cout << "3. Search by Title" << endl;
        cout << "4. Search by Author" << endl;
        cout << "5. Add Member" << endl;
        cout << "6. Display Members" << endl;
        cout << "7. Issue Book" << endl;
        cout << "8. Return Book" << endl;
        cout << "9. Display Issued Books" << endl;
        cout << "10. Update Book" << endl;
        cout << "11. Delete Book" << endl;
        cout << "12. Exit" << endl;

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            lib.addBook();
            break;

        case 2:
            lib.displayBooks();
            break;

        case 3:
            lib.searchByTitle();
            break;

        case 4:
            lib.searchByAuthor();
            break;

        case 5:
            lib.addMember();
            break;

        case 6:
            lib.displayMembers();
            break;

        case 7:
            lib.issueBook();
            break;

        case 8:
            lib.returnBook();
            break;

        case 9:
            lib.displayIssuedBooks();
            break;

        case 10:
            lib.updateBook();
            break;

        case 11:
            lib.deleteBook();
            break;

        case 12:
            cout << "\nThank You for Using Library Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 12);

    return 0;
}
