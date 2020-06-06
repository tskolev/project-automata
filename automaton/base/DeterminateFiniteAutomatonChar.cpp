//
// Created on 22-May-20.
//

#include "DeterminateFiniteAutomatonChar.h"
using namespace std;

// default constructor
DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar() {
    
    this->alphabetChar=nullptr;
    this->length = 0;
    cout << "Empty object created." << endl;
}

//constructor with parameters
DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(char* alphabetChar, int length) {
    //validation
    if (alphabetChar!=nullptr && length > 0){
    this->alphabetChar = new char[length];
    this->length = length; 
    } else {
        cerr << "Unable to assign new value to an existing alphabet. Length must be a positive integer!" << endl;
    }
}

//copy constructor
DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(const DeterminateFiniteAutomatonChar& obj){
    //validation
    if (obj.alphabetChar!=nullptr && obj.length>0){
        this->alphabetChar = new char[obj.length];
        this->length = obj.length;
        for (unsigned int i = 0; i < obj.length; i++)
            this->alphabetChar[i] = obj.alphabetChar[i];
    }
    else {
        cerr << "Cannot copy empty object!" << endl;
        
    }
}

// destructor
DeterminateFiniteAutomatonChar::~DeterminateFiniteAutomatonChar() {
    if (this->alphabetChar!=nullptr) {
        delete []alphabetChar;
        this->alphabetChar = nullptr;
    }
}

//getter and setter 

void DeterminateFiniteAutomatonChar::setAlphabetChar(char* alphabetChar){
    //validation
    if (this->alphabetChar!=nullptr){
        cerr<<"Unable to set new alphabet of an existing object!" << endl;
    } else {
        this->alphabetChar = alphabetChar;
    }
}
    void DeterminateFiniteAutomatonChar::setLength(int length){
        //validation
        if (length <= 0){
            cerr << "Unable to set a negative or 0 length!" << endl;
        } else {
            this-> length = length;
        }
    };
    char* DeterminateFiniteAutomatonChar::getAlphabetChar() const {
        //validation
        if(this->alphabetChar!=nullptr){
        return this->alphabetChar;
        } else {
            cerr << "Unable to return value of non-existing alphabet!" << endl;
        }
    };
    int DeterminateFiniteAutomatonChar::getLength() const {
        //validation
        if (this->length>0){
            return this->length;
        } else {
            cerr << "Unable to return length of non-existing alphabet!" << endl;
        }
    };