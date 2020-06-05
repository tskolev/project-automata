//
// Created on 22-May-20.
//

#ifndef AUTOMATON_DETERMINATEFINITEAUTOMATONINT_H
#define AUTOMATON_DETERMINATEFINITEAUTOMATONINT_H


#include "DeterminateFiniteAutomaton.h"

class DeterminateFiniteAutomatonInt :
    public DeterminateFiniteAutomaton {

private:
    int *alphabetInt;
    int length;
public:
    // default constructor
    DeterminateFiniteAutomatonInt();
    // constructor with parameters
    DeterminateFiniteAutomatonInt(int*, int);
    // destructor
    ~DeterminateFiniteAutomatonInt();
    //copy constructor
    DeterminateFiniteAutomatonInt(const DeterminateFiniteAutomatonInt& obj);

 // getter and setter
    void setAlphabetInt(int*);
    void setLength(int);
    char getAlphabetInt() const;
    int getLength() const;
    
    
    

};


#endif //AUTOMATON_DETERMINATEFINITEAUTOMATONINT_H
