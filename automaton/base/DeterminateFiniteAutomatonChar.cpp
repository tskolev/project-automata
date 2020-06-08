//
// Created on 22-May-20.
//

#include "DeterminateFiniteAutomatonChar.h"

DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar() : DeterminateFiniteAutomaton(),
                                                                   alphabetChar(nullptr), length(0) {}

DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(char *alphabetChar, unsigned int length) {
    if (alphabetChar != nullptr) {
        this->alphabetChar = new char[length + 1]{'\0'};
        strcpy_s(this->alphabetChar, (length + 1), alphabetChar);
        this->length = length;
    } else {
        this->alphabetChar = nullptr;
        this->length = 0;
    }
}

DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(const DeterminateFiniteAutomatonChar &obj) {
    if (obj.alphabetChar != nullptr) {
        this->alphabetChar = new char[obj.length + 1]{'\0'};
        strcpy_s(this->alphabetChar, (obj.length + 1), obj.alphabetChar);
        this->length = obj.length;
    } else {
        this->alphabetChar = nullptr;
        this->length = 0;
    }
}

DeterminateFiniteAutomatonChar::~DeterminateFiniteAutomatonChar() {
    if (this->alphabetChar != nullptr) {
        delete[] this->alphabetChar;
        this->alphabetChar = nullptr;
    }
}

void DeterminateFiniteAutomatonChar::setAlphabetChar(char *newAlphabetChar, unsigned int newLength) {
    if (newAlphabetChar != nullptr) {
        if (this->alphabetChar != nullptr) {
            delete[] this->alphabetChar;
            this->alphabetChar = nullptr;
        }

        this->alphabetChar = new char[newLength + 1]{'\0'};
        strcpy_s(this->alphabetChar, (newLength + 1), newAlphabetChar);
        this->length = newLength;
    }
}

char *DeterminateFiniteAutomatonChar::getAlphabetChar() const {
    return this->alphabetChar;
}

int DeterminateFiniteAutomatonChar::getLength() const {
    return this->length;
}