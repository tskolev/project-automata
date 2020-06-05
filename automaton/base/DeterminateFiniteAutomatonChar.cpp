//
// Created on 22-May-20.
//

#include "DeterminateFiniteAutomatonChar.h"

// default constructor
DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar() {
    this->alphabetChar=nullptr;
    this->length = 0;
}

//constructor with parameters
DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(char* alphabetChar, int length) {
    this->alphabetChar = new char[length];
    this->length = length; 
}

//copy constructor
DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(const DeterminateFiniteAutomatonChar& obj){
    if (obj.alphabetChar!=nullptr){
        this->alphabetChar = new char[obj.length];
        this->length = obj.length;
        for (unsigned int i = 0; i < obj.length; i++)
            this->alphabetChar[i] = obj.alphabetChar[i];
    }
    else {
        this->alphabetChar = nullptr;
        this->length = 0;
    }
}

// destructor
DeterminateFiniteAutomatonChar::~DeterminateFiniteAutomatonChar() {
    if (this->alphabetChar!=nullptr) {
        delete []alphabetChar;
        this->alphabetChar = nullptr;
    }
}