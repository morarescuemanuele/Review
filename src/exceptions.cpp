#include "exceptions.h"

BaseException::BaseException(const std::string& message) : std::runtime_error(message) {}

ItemNotFoundException::ItemNotFoundException(const std::string& message) : BaseException(message) {}

InvalidInputException::InvalidInputException(const std::string& message) : BaseException(message) {}

DuplicateUserException::DuplicateUserException(const std::string& message) : BaseException(message) {}

AuthException::AuthException(const std::string& message) : BaseException(message) {}

ActionNotAllowedException::ActionNotAllowedException(const std::string& message) : BaseException(message) {}