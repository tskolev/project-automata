//
// Created on 22-May-20.
//

#ifndef AUTOMATON_DETERMINATEFINITEAUTOMATON_H
#define AUTOMATON_DETERMINATEFINITEAUTOMATON_H


#include "../exception-handling/AutomatonException.h"
#include "../exception-handling/AutomatonStateException.h"
#include "../automaton-lib/State.h"

class DeterminateFiniteAutomaton {
public:
    /// Constructor - default
    DeterminateFiniteAutomaton();
    /// Constructor - parameters
    DeterminateFiniteAutomaton(State *stateArray, unsigned int numberOfStates, unsigned int startState,
                               unsigned int *acceptStateArray, unsigned int numberOfAcceptStates) noexcept(false);
    /// Constructor - copy
    DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton &obj);
    /// Destructor
    virtual ~DeterminateFiniteAutomaton();

    /// Setters
    void setStateArray(State *newStateArray, unsigned int newNumberOfStates) noexcept(false);
    void setStartState(unsigned int newStartState) noexcept(false);
    void setAcceptStatesArray(unsigned int *newAcceptStatesArray, unsigned int newNumberOfAcceptStates) noexcept(false);
    /// Getters
    State *getStateArray() const;
    unsigned getNumberOfStates() const;
    unsigned getStartState() const;
    unsigned *getAcceptStatesArray() const;
    unsigned getNumberOfAcceptStates() const;

    /*!
     * Inserts data in a given stream by parameter.
     * The inserted data is Object data fields and their details.
     * @param oStream object of std::ostream
     * @return reference to an stream object of std::ostream
     */
    std::ostream &inst(std::ostream &oStream) const;

    /*!
     * Prints all states of the automation.
     */
    void printAllStates();

    /*!
     * Puts the current start state startFlag to false,
     * puts the current startState data member to 0,
     * than calls (setStartState).
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
    // 1. States
    State *stateArray;
    unsigned int numberOfStates;

    // 4. Start state
    unsigned int startState;

    // 5. Accept states
    unsigned int *acceptStatesArray;
    unsigned int numberOfAcceptStates;
};

/*!
 * Overload of operator "<<".
 * Inserts data in a given stream by parameter through an object method.
 * The inserted data is Object data fields and their details.
 * @param oStream reference to an stream object of class std::ostream
 * @param obj const reference to an Object of class State
 * @return reference to an object of class std::ostream
 */
std::ostream &operator<<(std::ostream &oStream, const DeterminateFiniteAutomaton &obj);


#endif //AUTOMATON_DETERMINATEFINITEAUTOMATON_H
