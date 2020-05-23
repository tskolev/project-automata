//
// Created on 22-May-20.
//

#ifndef AUTOMATON_DETERMINATEFINITEAUTOMATON_H
#define AUTOMATON_DETERMINATEFINITEAUTOMATON_H


#include "../exception-handling/AutomatonException.h"
#include "../automaton-lib/State.h"
#include <iostream>

class DeterminateFiniteAutomaton {
public:
    // constructor - default
    DeterminateFiniteAutomaton();
    // constructor - parameters
    DeterminateFiniteAutomaton(State *stateArray, unsigned int numberOfStates, unsigned int startState);
    // constructor - copy
    DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton &obj);
    // destructor
    ~DeterminateFiniteAutomaton();

    // setters / getters
    /// all setters throw exception of type (AutomatonException)
    void setStateArray(State *newStateArray, unsigned int newNumberOfStates, unsigned int newStartState);
    void setNumberOfStates(unsigned int newNumberOfStates);
    void setStartState(unsigned int newStartState);
    State *getStateArray() const;
    unsigned getNumberOfStates() const;
    unsigned getStartState() const;

    /*!
     * prints all states of the automation
     */
    void printAllStates();

    /*!
     * Puts the current start state startFlag to 0,
     * Puts the current startState data member to 0,
     * than calls setStartState
     * @param newStartState - the new index for the startState data member
     */
    void changeStartState(unsigned int newStartState);

    /*!
     * Prints and takes information from the console,
     * validates the input from the user
     * than calls (changeStartState)
     */
    void changeStartStateConsole();

private:
    // 1. states
    State *stateArray;
    unsigned int numberOfStates;

    // 4. start state
    unsigned int startState;
};


#endif //AUTOMATON_DETERMINATEFINITEAUTOMATON_H
