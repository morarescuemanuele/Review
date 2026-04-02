#pragma once
#include <user.h>
#include <library.h>
#include <vector>

class Database{
    std::vector<User*> userList;
    std::vector<LibraryItem*> bookList;
public:
    ~Database();
    void addUser(User* u);
    void removeUser(int id);
    void displayAllUsers() const;
    void displayAllBooks() const;
    User* getUserByUsername(const std::string& username);
    LibraryItem* getBook(int index);
    void addBook(LibraryItem* book);
    User* getUser(int index);
    void removeBook(int index);
    void displayBooksByAuthor(const std::string& authorName) const;
};