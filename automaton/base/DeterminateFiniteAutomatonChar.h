//
// Created on 22-May-20.
//

#ifndef AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H
#define AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H


#include "DeterminateFiniteAutomaton.h"
#include "../exceptions/AutomatonAlphabetException.h"
#include "../exceptions/AutomatonTransitionTableException.h"

class DeterminateFiniteAutomatonChar : public DeterminateFiniteAutomaton {
public:
    /// Constructor - default
    DeterminateFiniteAutomatonChar();
    /// Constructor - parameters
    DeterminateFiniteAutomatonChar(char *alphabetChar, unsigned int alphabetLength,
                                   State *stateArray, unsigned int numberOfStates,
                                   unsigned int **transitionTable,
                                   unsigned int startState,
                                   unsigned int *acceptStateArray, unsigned int numberOfAcceptStates) noexcept(false);
    /// Constructor - copy
    DeterminateFiniteAutomatonChar(const DeterminateFiniteAutomatonChar &obj);
    /// Destructor
    virtual ~DeterminateFiniteAutomatonChar();

    /// Setters
    void setAlphabetChar(char *newAlphabetChar, unsigned int newAlphabetLength) noexcept(false);
    /// Getters
    char *getAlphabetChar() const;
    int getLength() const;

private:
    /// 2. Alphabet
    char *alphabetChar;
    unsigned int alphabetLength;

    /// 3. Transition table
    unsigned int **transitionTable;
    unsigned int tTColumnsNumber;
    unsigned int tTRowsNumber;
};


#endif //AUTOMATON_DETERMINATEFINITEAUTOMATONCHAR_H
