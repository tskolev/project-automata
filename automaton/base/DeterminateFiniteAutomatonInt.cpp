//
// Created on 22-May-20.
//

#include "DeterminateFiniteAutomatonInt.h"
using namespace std;

// default constructor
DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt() {
    
    this->alphabetInt=nullptr;
    this->length = 0;
    cout << "Empty object created." << endl;
}

//constructor with parameters
DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt(int* getAlphabetInt, int length) {
    //validation
    if (alphabetInt!=nullptr && length > 0){
    this->alphabetInt = new int[length];
    this->length = length; 
    } else {
        cerr << "Unable to assign new value to an existing alphabet. Length must be a positive integer!" << endl;
    }
}

//copy constructor
DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt(const DeterminateFiniteAutomatonInt& obj){
    //validation
    if (obj.alphabetInt!=nullptr && obj.length>0){
        this->alphabetInt = new int[obj.length];
        this->length = obj.length;
        for (unsigned int i = 0; i < obj.length; i++)
            this->alphabetInt[i] = obj.alphabetInt[i];
    }
    else {
        cerr << "Cannot copy empty object!" << endl;
        
    }
}

// destructor
DeterminateFiniteAutomatonInt::~DeterminateFiniteAutomatonInt() {
    if (this->alphabetInt!=nullptr) {
        delete []alphabetInt;
        this->alphabetInt = nullptr;
    }
}

//getter and setter 

void DeterminateFiniteAutomatonInt::setAlphabetInt(int* alphabetInt){
    //validation
    if (this->alphabetInt!=nullptr){
        cerr<<"Unable to set new alphabet of an existing object!" << endl;
    } else {
        this->alphabetInt = alphabetInt;
    }
}
    void DeterminateFiniteAutomatonInt::setLength(int length){
        //validation
        if (length <= 0){
            cerr << "Unable to set a negative or 0 length!" << endl;
        } else {
            this-> length = length;
        }
    };
    int* DeterminateFiniteAutomatonInt::getAlphabetInt() const {
        //validation
        if(this->alphabetInt!=nullptr){
        return this->alphabetInt;
        } else {
            cerr << "Unable to return value of non-existing alphabet!" << endl;
        }
    };
    int DeterminateFiniteAutomatonInt::getLength() const {
        //validation
        if (this->length>0){
            return this->length;
        } else {
            cerr << "Unable to return length of non-existing alphabet!" << endl;
        }
    };