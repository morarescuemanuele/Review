#include <database.h>
#include <iostream>
#include <exceptions.h>

void Database::addUser(User* u){
    if(u == nullptr) return;

    for(User* existingUser : userList){
        if(existingUser->getUsername() == u->getUsername()){
            delete u;
            throw DuplicateUserException("Error: Username already exists.");
        }
    }
    userList.push_back(u);
}

void Database::removeUser(int index){
    if(index < 0 || index >= static_cast<int>(userList.size())){
        throw ItemNotFoundException("Error: Cannot delete. Invalid user ID.");
    }
    delete userList[index];
    userList.erase(userList.begin() + index);
}

void Database::displayAllUsers() const {
    if(userList.empty()){
        std::cout << "Nu exista useri in baza de date in acest moment.\n";
        return;
    }

    for(size_t i = 0; i < userList.size(); ++i){
        std::cout << i+1 << ". " << userList[i]->getUsername() << "\n";
    }
}

void Database::displayAllBooks() const {
    if(bookList.empty()){
        std::cout << "There are no books in the database right now.\n";
        return;
    }

    for(auto i = 0; i < bookList.size(); ++i){
        std::cout << i+1 << ". " << *bookList[i] << " Rating: " << bookList[i]->getAverageRating() << " (" << bookList[i]->getReviewsCount() << " reviews)\n";
    }
}

LibraryItem* Database::getBook(int index) {
    if(index < 0 || index >= static_cast<int>(bookList.size())){
        throw ItemNotFoundException("Error: Invalid book ID. This book does not exist.");
    }
    return bookList[index];
}

User* Database::getUserByUsername(const std::string& username){
	for(User* user : userList){
		if(user->getUsername() == username){
			return user;
		}
	}

	return nullptr;
}

void Database::addBook(LibraryItem* book) {
    if (book != nullptr) {
        bookList.push_back(book);
    }
}

Database::~Database(){
    for(User* user : userList){
        delete user;
    }
    userList.clear();
	
    for(LibraryItem* book : bookList){
        delete book;
    }
    bookList.clear();
}

User* Database::getUser(int index) {
    if (index < 0 || index >= static_cast<int>(userList.size())) {
        throw ItemNotFoundException("Error: Invalid user ID. No user found.");
    }
    return userList[index];
}

void Database::removeBook(int index) {
    if (index < 0 || index >= static_cast<int>(bookList.size())) {
        throw ItemNotFoundException("Error: Cannot delete. Invalid book ID.");
    }
    delete bookList[index];
    bookList.erase(bookList.begin() + index);
}

void Database::displayBooksByAuthor(const std::string& authorName) const {
    bool found = false;
    for(size_t i = 0; i < bookList.size(); ++i){
        if(bookList[i]->getAuthor() == authorName) {
            std::cout << i+1 << ". " << *bookList[i] << " | Rating: " << bookList[i]->getAverageRating() << " (" << bookList[i]->getReviewsCount() << " reviews)\n";
            found = true;
        }
    }
    
    if(!found){
        std::cout << "You haven't published any books yet.\n";
    }
}