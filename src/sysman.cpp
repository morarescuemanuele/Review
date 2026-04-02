#include <sysman.h>
#include <iostream>
#include <cstdlib>
#include <exceptions.h>

SystemManager::SystemManager(){
    db.addUser(new Admin("admin", "admin"));
    db.addUser(new Client("client", "client"));
    db.addUser(new Author("autor","autor"));
    db.addUser(new ActiveAuthor("activ",""));

    LibraryItem* book1 = new EBook("The Shadow of What was Lost", "James Ilsington", 5, "PDF");
    LibraryItem* book2 = new EBook("The Will of The Many", "James Ilsington", 3, "PDF");
    LibraryItem* book3 = new AudioBook("1984", "George Orwell", 150, "Stephen Fry");
    LibraryItem* book4 = new PrintedBook("Crime and punishment", "F. Dostoievski", 800);

    book1->averageRatingCalculator(5);
    book1->averageRatingCalculator(4);

    book2->averageRatingCalculator(3);

    book3->averageRatingCalculator(5);
    book3->averageRatingCalculator(5);
    book3->averageRatingCalculator(4);
    db.addBook(book1);
    db.addBook(book2);
    db.addBook(book3);
    db.addBook(book4);
}

void SystemManager::handleLogin(){
    std::string usernameToValidate;
    std::string passwordToValidate;

    std::cout << "Enter your username: ";
    std::cin >> usernameToValidate;
    std::cout << "Enter your password: ";
    std::cin >> passwordToValidate;
    system("cls");
    
    try {
        User* user = db.getUserByUsername(usernameToValidate);
        if(user == nullptr || !user->passVerify(passwordToValidate)){
            throw AuthException("Error: Invalid username or password.");
        }
        std::cout << "Login successful. Welcome, " << user->getUsername() << "!\n";
        handleUserSession(user);
    } 
    catch (const BaseException& e) {
        std::cout << e.what() << "\n";
    }
}

void SystemManager::handleUserSession(User* user){
    bool isLoggedIn = true;

    while(isLoggedIn){
        int option;
        user->showMenu();
        std::cout << "Choose an option: ";
        std::cin >> option;
        system("cls");

        switch(option){
            case 0:{
                std::cout << "Logged out.\n";
                isLoggedIn = false;
                break;
            }
            default:{
                user->handleOption(option, db);
                break;
            }
        }
    }
}

void SystemManager::handleRegister(){
    std::string usernameToRegister;
    std::string passwordToRegister;
    int roleOption = 1;

    std::cout << "(Register) Enter your username: ";
    std::cin >> usernameToRegister;

    try {
        if(db.getUserByUsername(usernameToRegister) != nullptr){
            throw DuplicateUserException("Error: Username already exists.");
        }

        std::cout << "Enter your password: ";
        std::cin >> passwordToRegister;
        std::cout << "Choose account type:\n";
        std::cout << "1. Reader\n2. Author\n3. Active Author\n4. Admin\nChoice: ";
        std::cin >> roleOption;

        system("cls"); 

        switch(roleOption) {
            case 1: db.addUser(new Client(usernameToRegister, passwordToRegister)); break;
            case 2: db.addUser(new Author(usernameToRegister, passwordToRegister)); break;
            case 3: db.addUser(new ActiveAuthor(usernameToRegister, passwordToRegister)); break;
            case 4: db.addUser(new Admin(usernameToRegister, passwordToRegister)); break;
            default: 
                throw InvalidInputException("Error: Invalid role option selected.");
        }
        std::cout << "Account created successfully.\n";
    } 
    catch (const BaseException& e) {
        std::cout << e.what() << "\n";
    }
}

void SystemManager :: run(){
    bool programIsRunning = true;
    int option;

    while(programIsRunning){
        std::cout << "\n-----------System Manager-------------\n";
        std::cout << "1. Log in\n";
        std::cout << "2. Register\n";
        std::cout << "0. Close the program\n";
        std::cout << "Choose an option: ";
        std::cin >> option;
        system("cls");

        switch(option){
            case 1:{
                handleLogin();
                break;
            }
            case 2:{
                handleRegister();
                break;
            }
            case 0:{
                programIsRunning = false;
                break;
            }
            default:{
                throw InvalidInputException("Error: Invalid option. Please try again.");
                break;
            }
        }
    }
    std::cout << "Program closed.\n";
};