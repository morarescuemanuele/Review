#pragma once
#include <user.h>
#include <database.h>

class SystemManager{
private:
    Database db;
public:
    SystemManager();
    void handleLogin();
    void handleRegister();
    void handleUserSession(User* user);
    void run();

};