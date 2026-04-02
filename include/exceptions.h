#pragma once
#include <stdexcept>
#include <string>

class BaseException : public std::runtime_error {
public:
    explicit BaseException(const std::string& message);
};

class ItemNotFoundException : public BaseException {
public:
    explicit ItemNotFoundException(const std::string& message = "Error: Item not found.");
};

class InvalidInputException : public BaseException {
public:
    explicit InvalidInputException(const std::string& message = "Error: Invalid input provided.");
};

class DuplicateUserException : public BaseException {
public:
    explicit DuplicateUserException(const std::string& message = "Error: Username already exists.");
};

class AuthException : public BaseException {
public:
    explicit AuthException(const std::string& message = "Error: Authentication failed.");
};

class ActionNotAllowedException : public BaseException {
public:
    explicit ActionNotAllowedException(const std::string& message = "Error: Action not allowed.");
};