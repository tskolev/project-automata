//
// Created by Tsvetomir Kolev on 22-May-20.
//

#include "State.h"

// constructor - default
State::State() : name(new char[2]{'-', '\0'}) {}

// constructor - parameters
State::State(const char *name) {
    if (name != nullptr) {
        unsigned int len = strlen(name);
        this->name = new char[len + 1]{'\0'};
        strcpy_s(this->name, len + 1, name);
    } else
        this->name = new char[2]{'-', '\0'};
}

// constructor - copy
State::State(const State &obj) {
    if (obj.name != nullptr) {
        unsigned int len = strlen(obj.name);
        this->name = new char[len + 1]{'\0'};
        strcpy_s(this->name, len + 1, obj.name);
    } else
        this->name = new char[2]{'-', '\0'};
}

// destructor
State::~State() {
    if (this->name != nullptr) {
        delete[] this->name;
        this->name = nullptr;
    }
}
