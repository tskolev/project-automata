//
// Created on 22-May-20.
//

#include "DeterminateFiniteAutomatonInt.h"

// default constructor
DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt() {
    this->alphabetInt=nullptr;
    this->length = 0;
}

//constructor with parameters
DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt(int* alphabetInt, int length) {
    this->alphabetInt = new int[length];
    this->length = length; 
}

//copy constructor
DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt(const DeterminateFiniteAutomatonInt& obj){
    if (obj.alphabetInt!=nullptr){
        this->alphabetInt = new int[obj.length];
        this->length = obj.length;
        for (unsigned int i = 0; i < obj.length; i++)
            this->alphabetInt[i] = obj.alphabetInt[i];
    }
    else {
        this->alphabetInt = nullptr;
        this->length = 0;
    }
}

// destructor
DeterminateFiniteAutomatonInt::~DeterminateFiniteAutomatonInt() {
    if (this->alphabetInt!=nullptr) {
        delete []alphabetInt;
        this->alphabetInt = nullptr;
    }
}