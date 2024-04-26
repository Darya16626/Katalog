#include <iostream>
#include <locale>
#include <algorithm>
#include <vector>
#include <Windows.h>

using namespace std;

class Book { //Создание нового объекта(атвтор и название)

public:
    string title;
    string author;

    Book(string title, string author)
        : title(title), author(author) {}
};

class Library {  //Создание объекта с пустым списком книг
private:
    vector<Book> books;

public:
    void addBook(const Book& book) { //добавление новой книги в библиотеку
        books.push_back(book);
    }

    void listBooks() { //выводит список книг в библиотеке
        for (const auto& book : books) {
            cout << book.title << " " << book.author << endl;
        }
    }

    Book BookTitle(const string& title) { //ищет книгу по названию
        auto it = find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.title == title;
            });
        if (it != books.end()) {
            return *it;
        }
        return Book("", "");
    }

    Book selectBookIndex(int index) { //резервирует книгу для пользователя
        if (index > 0 && index < books.size()) {
            return books[index];
        }
        return Book("", "");
    }
};

class Names { //выводит список зарезервированных книг пользователя
public:
    string name;
    vector<Book> reservedBooks;

    Names(string name) : name(name) {}

    void reservBook(const Book& book) { //добавляет указанную книгу в список зарезервированных книг.
        reservedBooks.push_back(book);
    }

    void removeReserv(const string& title) { //удаляет указанную книгу из списка зарезервированных книг.
        auto it = find_if(reservedBooks.begin(), reservedBooks.end(), [&title](const Book& book) {
            return book.title == title;
            });
        if (it != reservedBooks.end()) {
            reservedBooks.erase(it);
        }
    }

    void listBooks() { //отображает список зарезервированных книг.
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
        cout << "Выберите действие: 1. Удаление резервации; 2. Резервация книги; 3. Номер книги; 4. Список книг; 5. Создание книги; 6. Выход";
        int number;
        cin >> number;

        if (number == 6) {
            break;
        }

        if (number == 1) {
            cout << "Введите название книги для удаления резервации: " << endl;
            string titleToRemove;
            cin >> titleToRemove;
            auto it = find_if(user.reservedBooks.begin(), user.reservedBooks.end(), [&titleToRemove](const Book& book) {
                return book.title == titleToRemove;
                });
            if (it != user.reservedBooks.end()) {
                user.reservedBooks.erase(it);
                cout << "Резервация завершена\n";
            }
            else {
                cout << "Резервация не найдена\n";
            }
        }
        else if (number == 2)
        {
            cout << "Введите название книги: " << endl;
            string title;
            cin >> title;
            Book bookToReserve = library.BookTitle(title);
            if (bookToReserve.title.empty()) {
                cout << "Книга не найдена\n";
            }
            else {
                user.reservBook(bookToReserve);
                cout << "Книга зарезервирована\n";
            }
        }

        else if (number == 3) {
            cout << "Выберите номер книги: " << endl;
            library.listBooks();
            int index;
            cin >> index;
            Book selectedBook = library.selectBookIndex(index);
            if (selectedBook.title.empty()) {
                cout << "Книга не найдена\n";
            }
            else {
                cout << "Книга выбрана: " << selectedBook.title << " " << selectedBook.author << endl;
            }
        }
        else if (number == 4) {
            cout << "Книги:\n" << endl;
            library.listBooks();
        }
        else if (number == 5) {
            cout << "Введите название и автора книги: " << endl;
            string title, author;
            cin >> title >> author;
            library.addBook(Book(title, author));
        }
        else {
            cout << "Неверный выбор\n";
        }
    }

    return 0;
}