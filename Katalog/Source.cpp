#include <iostream>
#include <locale>
#include <algorithm>
#include <vector>
#include <Windows.h>

using namespace std;

class Book { //�������� ������ �������(������ � ��������)

public:
    string title;
    string author;

    Book(string title, string author)
        : title(title), author(author) {}
};

class Library {  //�������� ������� � ������ ������� ����
private:
    vector<Book> books;

public:
    void addBook(const Book& book) { //���������� ����� ����� � ����������
        books.push_back(book);
    }

    void listBooks() { //������� ������ ���� � ����������
        for (const auto& book : books) {
            cout << book.title << " " << book.author << endl;
        }
    }

    Book BookTitle(const string& title) { //���� ����� �� ��������
        auto it = find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.title == title;
            });
        if (it != books.end()) {
            return *it;
        }
        return Book("", "");
    }

    Book selectBookIndex(int index) { //����������� ����� ��� ������������
        if (index > 0 && index < books.size()) {
            return books[index];
        }
        return Book("", "");
    }
};

class Names { //������� ������ ����������������� ���� ������������
public:
    string name;
    vector<Book> reservedBooks;

    Names(string name) : name(name) {}

    void reservBook(const Book& book) { //��������� ��������� ����� � ������ ����������������� ����.
        reservedBooks.push_back(book);
    }

    void removeReserv(const string& title) { //������� ��������� ����� �� ������ ����������������� ����.
        auto it = find_if(reservedBooks.begin(), reservedBooks.end(), [&title](const Book& book) {
            return book.title == title;
            });
        if (it != reservedBooks.end()) {
            reservedBooks.erase(it);
        }
    }

    void listBooks() { //���������� ������ ����������������� ����.
        for (const auto& book : reservedBooks) {
            cout << book.title << " " << book.author << endl;
        }
    }
};


int main() {
    setlocale(LC_ALL, "");
    Library library;
    
    Names user("name");

    while (true) {
        cout << "�������� ��������: 1. �������� ����������; 2. ���������� �����; 3. ����� �����; 4. ������ ����; 5. �������� �����; 6. �����";
        int number;
        cin >> number;

        if (number == 6) {
            break;
        }

        if (number == 1) {
            cout << "������� �������� ����� ��� �������� ����������: " << endl;
            string titleToRemove;
            cin >> titleToRemove;
            auto it = find_if(user.reservedBooks.begin(), user.reservedBooks.end(), [&titleToRemove](const Book& book) {
                return book.title == titleToRemove;
                });
            if (it != user.reservedBooks.end()) {
                user.reservedBooks.erase(it);
                cout << "���������� ���������\n";
            }
            else {
                cout << "���������� �� �������\n";
            }
        }
        else if (number == 2)
        {
            cout << "������� �������� �����: " << endl;
            string title;
            cin >> title;
            Book bookToReserve = library.BookTitle(title);
            if (bookToReserve.title.empty()) {
                cout << "����� �� �������\n";
            }
            else {
                user.reservBook(bookToReserve);
                cout << "����� ���������������\n";
            }
        }

        else if (number == 3) {
            cout << "�������� ����� �����: " << endl;
            library.listBooks();
            int index;
            cin >> index;
            Book selectedBook = library.selectBookIndex(index);
            if (selectedBook.title.empty()) {
                cout << "����� �� �������\n";
            }
            else {
                cout << "����� �������: " << selectedBook.title << " " << selectedBook.author << endl;
            }
        }
        else if (number == 4) {
            cout << "�����:\n" << endl;
            library.listBooks();
        }
        else if (number == 5) {
            cout << "������� �������� � ������ �����: " << endl;
            string title, author;
            cin >> title >> author;
            library.addBook(Book(title, author));
        }
        else {
            cout << "�������� �����\n";
        }
    }

    return 0;
}