//
// Created on 22-May-20.
//

#ifndef AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H
#define AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H


#include "DeterminateFiniteAutomaton.h"

class DeterminateFiniteAutomatonChar :
    public DeterminateFiniteAutomaton {

private:
    char *alphabetChar;
    int length;

public:
    // default constructor
    DeterminateFiniteAutomatonChar();
    // constructor with parameters
    DeterminateFiniteAutomatonChar(char*, int);
    // destructor
    ~DeterminateFiniteAutomatonChar();
    // copy constructor
    DeterminateFiniteAutomatonChar(const DeterminateFiniteAutomatonChar& obj);

    // getter and setter
    void setAlphabetChar(const char*);
    void setLength(int);
    char getAlphabetChar() const;
    int getLength() const;
    
    
    
};


#endif //AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H
