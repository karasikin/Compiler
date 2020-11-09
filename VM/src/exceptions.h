#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class InvalidOperatorException : public std::exception {

public:

    InvalidOperatorException(const std::string &invalidOperator)
        :msg("Error: invalid operator << " + invalidOperator + " >>")
    {}

    virtual const char *what() const noexcept override {
        return msg.c_str();
    }

private:

    std::string msg;
};

class InvalidTypeException : public std::exception {

public:

    InvalidTypeException(const std::string &invalidType)
        :msg("Error: invalid type << " + invalidType + " >>")
    {}

    virtual const char *what() const noexcept override {
        return msg.c_str();
    }

private:

    std::string msg;
};

class RedeclarationVariableException : public std::exception {

public:

    RedeclarationVariableException(const std::string &varname)
        :msg("Error: redeclaration << " + varname + " >>")
    {}

    virtual const char *what() const noexcept override {
        return msg.c_str();
    }

private:

    std::string msg;
};

class NotDeclaredVariableException : public std::exception {

public:

    NotDeclaredVariableException(const std::string &varname)
        :msg("Error: not declared variable << " + varname + " >>")
    {}

    virtual const char *what() const noexcept override {
        return msg.c_str();
    }

private:

    std::string msg;
};



#endif // EXCEPTIONS_H
