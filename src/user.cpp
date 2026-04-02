#include <user.h>
#include <database.h>
#include <exceptions.h>
#include <iostream>
#include <cstdlib>

// PARTEA DE BAZA USER

std::string User :: getUsername(){
    return username;
}

std::string User :: getPassword(){
    return password;
}

User::User(std::string u, std::string p) : username(u), password(p) {}

User::~User() = default;

bool User::passVerify(std::string pass) const{
    return pass==password;
}


// TREBUIE IMPLEMENTATE 
bool User::updateUsername(std::string& newUsername, std::string& oldUsername){
    if(oldUsername != username || newUsername.empty()){
        return false;
    }

    username = newUsername;
    return true;
}

bool User::updatePassword(std::string& newPassword, std::string& oldPassword){
    if(oldPassword != password || newPassword.empty()){
        return false;
    }

    password = newPassword;
    return true;
}
//

void User::deleteUser(){
    username.clear();
    password.clear();
}

// PARTEA DE CLIENT

Client::Client(std::string u, std::string p) : User(u, p) {}

void Client::showMenu() const{
    std::cout << "\n--- Client Menu ---\n";
    std::cout << "1. View books\n";
    std::cout << "2. Add review\n";
    std::cout << "0. Logout\n";
}

void Client::handleOption(int option, Database& db) {
    switch(option){
        case 1:
            std::cout << "\n--- Book List ---\n";
            db.displayAllBooks();
            break;
            
            case 2: {
                std::cout << "\n--- Leave a review ---\n";
                db.displayAllBooks();
                
                int bookIndex;
                std::cout << "\nInsert the book's ID for which you want to leave a review (or 0 to cancel): ";
                std::cin >> bookIndex;
                system("cls");
                
                if (bookIndex == 0) break;

                try {
                    LibraryItem* book = db.getBook(bookIndex - 1); 
                    
                    int rating;
                    std::cout << "Insert a rating from 1 to 10: ";
                    std::cin >> rating;
                    system("cls");
                    
                    book->averageRatingCalculator(rating);
                    std::cout << "Review added successfully!\n";
                } 
                catch (const BaseException& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            
        default:
            std::cout << "Invalid option, please try again.\n";
            break;
    }
}

//PARTEA DE AUTOR

Author::Author(std::string u, std::string p) : User(u, p) {}

void Author::showMenu() const {
    std::cout << "\n--- Author Menu ---\n";
    std::cout << "1. Publish a new book\n";
    std::cout << "2. View my published books\n";
    std::cout << "0. Logout\n";
}

void Author::handleOption(int option, Database& db) {
    switch(option) {
        case 1: {
            std::cout << "\n--- Publish a New Book ---\n";
            int type;
            std::cout << "Select book type:\n1. EBook\n2. AudioBook\n3. Printed Book\nChoice: ";
            std::cin >> type;

            std::string title;
            std::cout << "Enter title: ";
            std::getline(std::cin >> std::ws, title);
            
            std::string authorName = this->getUsername();

            if (type == 1) {
                int size; 
                std::string format;
                std::cout << "Enter size (MB): "; 
                std::cin >> size;
                std::cout << "Enter format (e.g., EPUB, PDF): "; 
                std::cin >> format;
                
                db.addBook(new EBook(title, authorName, size, format));
                std::cout << "EBook published successfully!\n";
            } 
            else if (type == 2) {
                int size; 
                std::string narrator;
                std::cout << "Enter size (MB): "; 
                std::cin >> size;
                
                std::cout << "Enter narrator: "; 
                std::getline(std::cin >> std::ws, narrator);
                
                db.addBook(new AudioBook(title, authorName, size, narrator));
                std::cout << "AudioBook published successfully!\n";
            } 
            else if (type == 3) {
                int weight;
                std::cout << "Enter weight (g): "; 
                std::cin >> weight;
                
                db.addBook(new PrintedBook(title, authorName, weight));
                std::cout << "Printed Book published successfully!\n";
            } 
            else {
                std::cout << "Error: Invalid book type.\n";
            }
            break;
        }
            
        case 2:
            std::cout << "\n--- My Published Books ---\n";
            db.displayBooksByAuthor(this->getUsername());
            break;
            
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
    }
}

// PARTEA DE ACTIV AUTOR

ActiveAuthor::ActiveAuthor(std::string u, std::string p) : User(u, p), Client(u, p), Author(u, p) {}

void ActiveAuthor::showMenu() const {
    std::cout << "\n--- Active Author Menu ---\n";
    std::cout << "1. View all books (Reader feature)\n";
    std::cout << "2. Leave a review (Reader feature)\n";
    std::cout << "3. Publish a new book (Author feature)\n";
    std::cout << "4. View my published books (Author feature)\n";
    std::cout << "0. Logout\n";
}

void ActiveAuthor::handleOption(int option, Database& db) {
    switch(option) {
        case 1:
            Client::handleOption(1, db);
            break;
            
        case 2:
            Client::handleOption(2, db);
            break;
            
        case 3:
            Author::handleOption(1, db);
            break;
            
        case 4:
            Author::handleOption(2, db);
            break;
            
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
    }
}


//PARTEA DE ADMIN

Admin::Admin(std::string u, std::string p) : User(u, p) {}

void Admin::showMenu() const{
    std::cout << "\n--- Admin Menu ---\n";
    std::cout << "1. Manage users\n";
    std::cout << "2. Manage books\n";
    std::cout << "0. Logout\n";
}

void Admin::handleOption(int option, Database& db) {
    switch(option) {
        case 1: {
            bool managingUsers = true;
            while (managingUsers) {
                std::cout << "\n--- User Management ---\n";
                std::cout << "1. View all users\n";
                std::cout << "2. Add a new user\n";
                std::cout << "3. Delete a user\n";
                std::cout << "4. Change a user's username\n";
                std::cout << "5. Change a user's password\n";
                std::cout << "0. Back to main menu\n";
                std::cout << "Choose an option: ";
                
                int subOption;
                std::cin >> subOption;

                switch (subOption) {
                    case 1: {
                        system("cls");
                        std::cout << "\n--- User List ---\n";
                        db.displayAllUsers();
                        break;
                    }
                    case 2: {
                        system("cls");
                        std::cout << "\n--- Add a New User ---\n";
                        std::string newUsername, newPassword;
                        int roleOption;

                        std::cout << "Enter new username: ";
                        std::cin >> newUsername;

                        if (db.getUserByUsername(newUsername) != nullptr) {
                            std::cout << "Error: Username already exists.\n";
                            break;
                        }

                        std::cout << "Enter new password: ";
                        std::cin >> newPassword;

                        std::cout << "Select role:\n";
                        std::cout << "1. Client\n2. Author\n3. Active Author\n4. Admin\n";
                        std::cout << "Choice: ";
                        std::cin >> roleOption;

                        switch (roleOption) {
                            case 1: db.addUser(new Client(newUsername, newPassword)); break;
                            case 2: db.addUser(new Author(newUsername, newPassword)); break;
                            case 3: db.addUser(new ActiveAuthor(newUsername, newPassword)); break;
                            case 4: db.addUser(new Admin(newUsername, newPassword)); break;
                            default: std::cout << "Invalid role.\n"; continue;
                        }
                        std::cout << "User added successfully!\n";
                        break;
                    }
                    case 3: {
                        system("cls");
                        std::cout << "\n--- Delete a User ---\n";
                        db.displayAllUsers();
                        
                        int id;
                        std::cout << "\nEnter the ID of the user you want to delete (or 0 to cancel): ";
                        std::cin >> id;

                        if (id == 0) break;

                        try {
                            User* userToDelete = db.getUser(id - 1);
                            if (userToDelete == this) {
                                throw ActionNotAllowedException("Error: You cannot delete your own account while logged in!");
                            }
                            db.removeUser(id - 1);
                            std::cout << "User deleted successfully.\n";
                        } 
                        catch (const BaseException& e) {
                            std::cout << e.what() << "\n";
                        }
                        break;
                    }
                    case 4: {
                        system("cls");
                        std::cout << "\n--- Change Username ---\n";
                        db.displayAllUsers();

                        int id;
                        std::cout << "\nEnter the ID of the user (or -1 to cancel): ";
                        std::cin >> id;

                        if (id == -1) break;

                        User* targetUser = db.getUser(id);
                        if (targetUser == nullptr) {
                            std::cout << "Error: No user found with this ID.\n";
                        } else {
                            std::string newUsername;
                            std::cout << "Enter the new username: ";
                            std::cin >> newUsername;

                            if (db.getUserByUsername(newUsername) != nullptr) {
                                std::cout << "Error: This username is already taken.\n";
                            } else {
                                std::string oldUsername = targetUser->getUsername();
                                if (targetUser->updateUsername(newUsername, oldUsername)) {
                                    std::cout << "Username updated successfully.\n";
                                } else {
                                    std::cout << "Error updating username.\n";
                                }
                            }
                        }
                        break;
                    }
                    case 5: {
                        system("cls");
                        std::cout << "\n--- Change Password ---\n";
                        db.displayAllUsers();

                        int id;
                        std::cout << "\nEnter the ID of the user (or -1 to cancel): ";
                        std::cin >> id;

                        if (id == -1) break;

                        User* targetUser = db.getUser(id);
                        if (targetUser == nullptr) {
                            std::cout << "Error: No user found with this ID.\n";
                        } else {
                            std::string newPassword;
                            std::cout << "Enter the new password: ";
                            std::cin >> newPassword;

                            std::string oldPassword = targetUser->getPassword();
                            if (targetUser->updatePassword(newPassword, oldPassword)) {
                                std::cout << "Password updated successfully.\n";
                            } else {
                                std::cout << "Error updating password.\n";
                            }
                        }
                        break;
                    }
                    case 0:
                        system("cls");
                        std::cout << "Returning to main menu...\n";
                        managingUsers = false;
                        break;
                    default:
                        std::cout << "Invalid option. Please try again.\n";
                        break;
                }
            }
            break;
        }
            
        case 2: {
            bool managingBooks = true;
            while (managingBooks) {
                std::cout << "\n--- Book Management ---\n";
                std::cout << "1. View all books\n";
                std::cout << "2. Add a new book\n";
                std::cout << "3. Delete a book\n";
                std::cout << "0. Back to main menu\n";
                std::cout << "Choose an option: ";

                int subOption;
                std::cin >> subOption;

                switch (subOption) {
                    case 1: {
                        system("cls");
                        std::cout << "\n--- Book List ---\n";
                        db.displayAllBooks();
                        break;
                    }
                    case 2: {
                        system("cls");
                        std::cout << "\n--- Add a New Book ---\n";
                        int type;
                        std::cout << "Select book type:\n1. EBook\n2. AudioBook\n3. Printed Book\nChoice: ";
                        std::cin >> type;

                        std::string title, author;
                        std::cout << "Enter title (use_underscores_for_spaces): "; 
                        std::cin >> title;
                        std::cout << "Enter author (use_underscores_for_spaces): "; 
                        std::cin >> author;

                        if (type == 1) {
                            int size; std::string format;
                            std::cout << "Enter size (MB): "; std::cin >> size;
                            std::cout << "Enter format (e.g., EPUB, PDF): "; std::cin >> format;
                            db.addBook(new EBook(title, author, size, format));
                            std::cout << "EBook added successfully!\n";
                        } 
                        else if (type == 2) {
                            int size; std::string narrator;
                            std::cout << "Enter size (MB): "; std::cin >> size;
                            std::cout << "Enter narrator: "; std::cin >> narrator;
                            db.addBook(new AudioBook(title, author, size, narrator));
                            std::cout << "AudioBook added successfully!\n";
                        } 
                        else if (type == 3) {
                            int weight;
                            std::cout << "Enter weight (g): "; std::cin >> weight;
                            db.addBook(new PrintedBook(title, author, weight));
                            std::cout << "Printed Book added successfully!\n";
                        } 
                        else {
                            std::cout << "Error: Invalid book type.\n";
                        }
                        break;
                    }
                    case 3: {
                        system("cls");
                        std::cout << "\n--- Delete a Book ---\n";
                        db.displayAllBooks();
                        
                        int id;
                        std::cout << "\nEnter the ID (index) of the book to delete (or 0 to cancel): ";
                        std::cin >> id;

                        if (id == 0) break;

                        try {
                            db.removeBook(id - 1);
                            std::cout << "Book deleted successfully.\n";
                        } 
                        catch (const BaseException& e) {
                            std::cout << e.what() << "\n";
                        }
                        break;
                    }
                    case 0:
                        system("cls");
                        std::cout << "Returning to main menu...\n";
                        managingBooks = false;
                        break;
                    default:
                        system("cls");
                        std::cout << "Invalid option. Please try again.\n";
                        break;
                }
            }
            break;
        }
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
    }
}