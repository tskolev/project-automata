//
// Created on 22-May-20.
//

#include "DeterminateFiniteAutomaton.h"

DeterminateFiniteAutomaton::DeterminateFiniteAutomaton() :
        stateArray(nullptr), numberOfStates(0), startState(0), acceptStatesArray(nullptr), numberOfAcceptStates(0) {}

DeterminateFiniteAutomaton::DeterminateFiniteAutomaton
        (State *stateArray, unsigned int numberOfStates, unsigned int startState,
         unsigned int *acceptStatesArray = nullptr, unsigned int numberOfAcceptStates = 0) {

    try {
        if (stateArray == nullptr)
            throw AutomatonException("Invalid parameter - stateArray! (stateArray = nullptr)");
        else if (numberOfStates == 0)
            throw AutomatonStateException("Invalid parameter - numberOfStates! (numberOfState = 0)");
        else if (!(0 <= startState && startState < numberOfStates))
            throw AutomatonStateException("Start state index out of range!");
        else if (acceptStatesArray == nullptr && numberOfAcceptStates != 0)
            throw AutomatonStateException("Invalid parameter - numberOfAcceptStates! (numberOfAcceptStates != 0)");
        else if (acceptStatesArray != nullptr && numberOfAcceptStates == 0)
            throw AutomatonStateException("Invalid parameter - numberOfAcceptStates! (numberOfAcceptStates == 0)");
        else if (acceptStatesArray != nullptr) {
            for (unsigned int i = 0; i < numberOfAcceptStates; ++i) {
                if (!(0 <= acceptStatesArray[i] && acceptStatesArray[i] < numberOfStates))
                    throw AutomatonStateException("Accept indices out of range!");
            }
        }

        // Set up array of states
        this->stateArray = new State[numberOfStates];
        for (unsigned int i = 0; i < numberOfStates; ++i)
            this->stateArray[i] = stateArray[i];
        this->numberOfStates = numberOfStates;

        // Set up start state
        this->startState = startState;
        this->stateArray[startState].setStartFlag(true);

        // Set up array of accept states AND number of accept states
        if (acceptStatesArray != nullptr) {
            this->acceptStatesArray = new unsigned[numberOfAcceptStates]{0};
            for (unsigned int i = 0; i < numberOfAcceptStates; ++i) {
                this->acceptStatesArray[i] = acceptStatesArray[i];
                this->stateArray[this->acceptStatesArray[i]].setAcceptFlag(true);
            }

            this->numberOfAcceptStates = numberOfAcceptStates;
        } else {
            this->acceptStatesArray = nullptr;
            this->numberOfAcceptStates = 0;
        }

    } catch (AutomatonException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Line: " << "14" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
    } catch (AutomatonStateException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Line: " << "14" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
    }
}

DeterminateFiniteAutomaton::DeterminateFiniteAutomaton(const DeterminateFiniteAutomaton &obj) {
    if (obj.stateArray != nullptr) {
        // Set up array of states
        this->stateArray = new State[obj.numberOfStates];
        for (unsigned int i = 0; i < obj.numberOfStates; ++i)
            this->stateArray[i] = obj.stateArray[i];
        this->numberOfStates = obj.numberOfStates;

        // Set up start state
        this->startState = obj.startState;
        this->stateArray[this->startState].setStartFlag(true);
    } else {
        this->stateArray = nullptr;
        this->numberOfStates = 0;

        this->startState = 0;
    }

    // Set up array of accept states AND number of accept states
    if (obj.acceptStatesArray != nullptr) {
        this->acceptStatesArray = new unsigned[obj.numberOfAcceptStates]{0};
        for (unsigned int i = 0; i < obj.numberOfAcceptStates; ++i) {
            this->acceptStatesArray[i] = obj.acceptStatesArray[i];
            this->stateArray[this->acceptStatesArray[i]].setAcceptFlag(true);
        }

        this->numberOfAcceptStates = obj.numberOfAcceptStates;
    } else {
        this->acceptStatesArray = nullptr;
        this->numberOfAcceptStates = 0;
    }
}

DeterminateFiniteAutomaton::~DeterminateFiniteAutomaton() {
    // Delete array of states
    if (this->stateArray != nullptr) {
        delete[] this->stateArray;
        this->stateArray = nullptr;
    }

    // Delete array of accept states
    if (this->acceptStatesArray != nullptr) {
        delete[] this->acceptStatesArray;
        this->acceptStatesArray = nullptr;
    }
}

void DeterminateFiniteAutomaton::setStateArray(State *newStateArray, unsigned int newNumberOfStates) {
    try {
        if (newStateArray == nullptr)
            throw AutomatonException("Invalid parameter = newStateArray! (stateArray = nullptr)");
        else if (newNumberOfStates == 0)
            throw AutomatonStateException("Invalid parameter - newNumberOfStates! (neNumberOfStates = 0)");

        // Reset stateArray - data member
        if (this->stateArray != nullptr) {
            delete[] this->stateArray;
            this->stateArray = nullptr;
            this->numberOfStates = 0;
        }

        // Reset startState - data member
        this->startState = 0;

        // Reset acceptStatesArray - data member
        if (this->acceptStatesArray != nullptr) {
            delete[] this->acceptStatesArray;
            this->acceptStatesArray = nullptr;
            this->numberOfAcceptStates = 0;
        }

        // Set up array of states
        this->stateArray = new State[newNumberOfStates];
        for (unsigned int i = 0; i < newNumberOfStates; ++i)
            this->stateArray[i] = newStateArray[i];
        this->numberOfStates = newNumberOfStates;

    } catch (AutomatonException &exc) {
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Line: " << "123" << std::endl;
        std::cerr << "Function: " << "setStateArray(State *, unsigned)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
    } catch (AutomatonStateException &exc) {
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Line: " << "123" << std::endl;
        std::cerr << "Function: " << "setStateArray(State *, unsigned)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
    }
}

void DeterminateFiniteAutomaton::setStartState(unsigned int newStartState) {
    try {
        // Check for available states
        if (this->stateArray == nullptr)
            throw AutomatonStateException("Invalid action - work with empty data field (stateArray = nullptr)");

        // Search for existing start state
        bool alreadyExistsStartState = false;
        for (unsigned int i = 0; i < this->numberOfStates; ++i) {
            if (this->stateArray[i].getStartFlag()) {
                alreadyExistsStartState = true;
                break;
            }
        }

        try {
            // Check for existing start state
            if (alreadyExistsStartState)
                throw AutomatonException("Invalid action - start state already exist!");
            else {

                try {
                    // Validating index for start state
                    if (0 <= newStartState && newStartState < this->numberOfStates) {
                        // Set up start state
                        this->startState = newStartState;
                        this->stateArray[this->startState].setStartFlag(true);
                    } else
                        throw AutomatonStateException("State out of range!");

                } catch (AutomatonStateException &exc) {
                    std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
                    std::cerr << "Line: " << "190" << std::endl;
                    std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
                    std::cerr << "Caught: " << exc.what() << std::endl;
                    std::cerr << "Type: " << "AutomatonStateException" << std::endl;
                    std::cerr << "Number of states: " << this->numberOfStates << std::endl;
                    std::cerr << "Maximum index: " << (this->numberOfStates - 1) << std::endl;
                    std::cerr << "----- ----- -----" << std::endl;
                }
            }

        } catch (AutomatonException &exc) {
            std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
            std::cerr << "Line: " << "184" << std::endl;
            std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
            std::cerr << "Caught: " << exc.what() << std::endl;
            std::cerr << "Type: " << "AutomatonException" << std::endl;
            std::cerr << "Start state: " << this->stateArray[this->startState].getName() << std::endl;
            std::cerr << "Attempt: " << this->stateArray[newStartState].getName() << std::endl;
            std::cerr << "----- ----- -----" << std::endl;
        }

    } catch (AutomatonStateException &exc) {
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Line: " << "170" << std::endl;
        std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
    }
}

void DeterminateFiniteAutomaton::setAcceptStatesArray(unsigned int *newAcceptStatesArray,
                                                      unsigned int newNumberOfAcceptStates) noexcept(false) {
    try {
        if (newAcceptStatesArray == nullptr && newNumberOfAcceptStates != 0)
            throw AutomatonStateException("Invalid parameter! (newNumberOfAcceptStates != 0)");
        else if (newAcceptStatesArray != nullptr && newNumberOfAcceptStates == 0)
            throw AutomatonStateException("Invalid parameter! (newNumberOfAcceptStates == 0)");
        else if (newAcceptStatesArray != nullptr) {
            for (unsigned int i = 0; i < newNumberOfAcceptStates; ++i) {
                if (!(0 <= newAcceptStatesArray[i] && newAcceptStatesArray[i] < this->numberOfStates))
                    throw AutomatonStateException("Accept indices out of range!");
            }
        }

        // Reset state`s acceptFlag to false AND delete the array of accept states AND reset numberOfAcceptStates
        if (this->acceptStatesArray != nullptr) {
            for (unsigned int i = 0; i < this->numberOfAcceptStates; ++i)
                this->stateArray[acceptStatesArray[i]].setAcceptFlag(false);

            delete[] this->acceptStatesArray;
            this->numberOfAcceptStates = 0;
        }

        // Set up array of accept states AND numberOfAcceptStates
        if (newAcceptStatesArray != nullptr) {
            this->acceptStatesArray = new unsigned[newNumberOfAcceptStates]{0};
            for (unsigned int i = 0; i < newNumberOfAcceptStates; ++i) {
                this->acceptStatesArray[i] = newAcceptStatesArray[i];
                this->stateArray[this->acceptStatesArray[i]].setAcceptFlag(true);
                this->numberOfAcceptStates = newNumberOfAcceptStates;
            }
        } else {
            this->acceptStatesArray = nullptr;
            this->numberOfAcceptStates = 0;
        }

    } catch (AutomatonException &exc) {
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Line: " << "234" << std::endl;
        std::cerr << "Function: " << "setAcceptStatesArray(unsigned *, unsigned)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
    } catch (AutomatonStateException &exc) {
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Line: " << "234" << std::endl;
        std::cerr << "Function: " << "setAcceptStatesArray(unsigned *, unsigned)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
    }
}

State *DeterminateFiniteAutomaton::getStateArray() const {
    return this->stateArray;
}

unsigned DeterminateFiniteAutomaton::getNumberOfStates() const {
    return this->numberOfStates;
}

unsigned DeterminateFiniteAutomaton::getStartState() const {
    return this->startState;
}

unsigned *DeterminateFiniteAutomaton::getAcceptStatesArray() const {
    return this->acceptStatesArray;
}

unsigned DeterminateFiniteAutomaton::getNumberOfAcceptStates() const {
    return this->numberOfAcceptStates;
}

