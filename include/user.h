#pragma once
#include <string>

class Database;

class User{
    std::string username;
    std::string password;
public:

    // Constructori
    User(std::string u, std::string p);
    virtual ~User();
    
    bool passVerify(std::string pass) const;

    // Getteri pt username si parola
    std::string getUsername();
    std::string getPassword();

    //Setteri pt username si parola
    bool updateUsername(std::string& newUsername, std::string& oldUsername);
    bool updatePassword(std::string& newPassword, std::string& oldPassword);
    
    // Arata meniul
    virtual void showMenu() const = 0;
    virtual void handleOption(int option, Database& db) = 0;

    // Sterge utilizatorul curent din baza de date
    void deleteUser();
};


class Client : virtual public User{
public:
    Client(std::string u, std::string p);
    void showMenu() const override;
    void handleOption(int option, Database& db) override;
};


class Admin : public User{
public:
    Admin(std::string u, std::string p);
    void showMenu() const override;
    void handleOption(int option, Database& db) override;
};

class Author : virtual public User {
public:
    Author(std::string u, std::string p);
    void showMenu() const override;
    void handleOption(int option, Database& db) override;
};

class ActiveAuthor : public Client, public Author {
public:
    // Constructorul
    ActiveAuthor(std::string u, std::string p);
    
    void showMenu() const override;
    void handleOption(int option, Database& db) override;
};