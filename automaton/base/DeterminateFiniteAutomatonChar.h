//
// Created on 22-May-20.
//

#ifndef AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H
#define AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H


#include "DeterminateFiniteAutomaton.h"

class DeterminateFiniteAutomatonChar : public DeterminateFiniteAutomaton {
public:
    /// Constructor - default
    DeterminateFiniteAutomatonChar();
    /// Constructor - parameters
    DeterminateFiniteAutomatonChar(char *alphabetChar, unsigned int length);
    /// Constructor - copy
    DeterminateFiniteAutomatonChar(const DeterminateFiniteAutomatonChar &obj);
    /// Destructor
    virtual ~DeterminateFiniteAutomatonChar();

    /// Setters
    void setAlphabetChar(char *newAlphabetChar, unsigned int newLength);
    /// Getters
    char *getAlphabetChar() const;
    int getLength() const;

private:
    char *alphabetChar;
    unsigned int length;
};


#endif //AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H
