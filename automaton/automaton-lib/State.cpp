//
// Created on 22-May-20.
//

#include "State.h"

// constructor - default
State::State() : name(new char[2]{'-', '\0'}), startFlag(false), acceptFlag(false) {}

// constructor - parameters
State::State(const char *name) : startFlag(false), acceptFlag(false) {
    if (name != nullptr) {
        unsigned int len = strlen(name);
        this->name = new char[len + 1]{'\0'};
        strcpy_s(this->name, (len + 1), name);
    } else
        this->name = new char[2]{'-', '\0'};
}

// constructor - copy
State::State(const State &obj) {
    if (obj.name != nullptr) {
        unsigned int len = strlen(obj.name);
        this->name = new char[len + 1]{'\0'};
        strcpy_s(this->name, (len + 1), obj.name);

        this->startFlag = obj.startFlag;
        this->acceptFlag = obj.acceptFlag;
    } else {
        this->name = new char[2]{'-', '\0'};
        this->startFlag = false;
        this->acceptFlag = false;
    }
}

// destructor
State::~State() {
    if (this->name != nullptr) {
        delete[] this->name;
        this->name = nullptr;
    }
}

// setters / getters
void State::setName(char *newName) {
    try {
        if (newName != nullptr) {
            if (this->name != nullptr) {
                delete[] this->name;
                this->name = nullptr;
            }
            unsigned int len = strlen(newName);
            this->name = new char[len + 1]{'\0'};
            strcpy_s(this->name, (len + 1), newName);
        } else
            throw AutomatonException("Invalid argument - nullptr");
    } catch (AutomatonException exc) {
        std::cerr << "File: " << "State.cpp" << std::endl;
        std::cerr << "Function: " << "setName(char *)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
    }
}

void State::setStartFlag(bool newStartFlag) {
    this->startFlag = newStartFlag;
}

void State::setAcceptFlag(bool newAcceptFlag) {
    this->acceptFlag = newAcceptFlag;
}

char *State::getName() const {
    return this->name;
}

bool State::getStartFlag() const {
    return this->startFlag;
}

bool State::getAcceptFlag() const {
    return this->acceptFlag;
}

// operator = overload
State &State::operator=(const State &rhs) {
    if (this != &rhs) {
        setName(rhs.name);
        setStartFlag(rhs.startFlag);
        setAcceptFlag(rhs.acceptFlag);
    }
    return *this;
}
