//
// Created on 22-May-20.
//

#include "DeterminateFiniteAutomaton.h"

// constructor - default
DeterminateFiniteAutomaton::DeterminateFiniteAutomaton() :
        stateArray(nullptr), numberOfStates(0), startState(0) {}

// constructor - parameters
DeterminateFiniteAutomaton::DeterminateFiniteAutomaton
        (State *stateArray, unsigned int numberOfStates, unsigned int startState) {
    if (stateArray != nullptr) {
        this->stateArray = new State[numberOfStates];
        for (unsigned int i = 0; i < numberOfStates; ++i)
            this->stateArray[i] = stateArray[i];

        this->numberOfStates = numberOfStates;
        this->startState = startState;
        this->stateArray[startState].setStartFlag(true);
    } else {
        this->stateArray = nullptr;
        this->numberOfStates = 0;
        this->startState = 0;
    }
}

// constructor - copy
DeterminateFiniteAutomaton::DeterminateFiniteAutomaton
        (const DeterminateFiniteAutomaton &obj) {
    if (obj.stateArray != nullptr) {
        this->stateArray = new State[obj.numberOfStates];
        for (unsigned int i = 0; i < obj.numberOfStates; ++i)
            this->stateArray[i] = obj.stateArray[i];

        this->numberOfStates = obj.numberOfStates;
        this->startState = obj.startState;
        this->stateArray[this->startState].setStartFlag(true);
    } else {
        this->stateArray = nullptr;
        this->numberOfStates = 0;
        this->startState = 0;
    }
}

// destructor
DeterminateFiniteAutomaton::~DeterminateFiniteAutomaton() {
    if (this->stateArray != nullptr) {
        delete[] this->stateArray;
        this->stateArray = nullptr;
    }
}

// setters / getters
void DeterminateFiniteAutomaton::setStateArray
        (State *newStateArray, unsigned int newNumberOfStates, unsigned int newStartState) {
    try {
        if (newStateArray != nullptr) {
            if (this->stateArray != nullptr) {
                delete[] this->stateArray;
                this->stateArray = nullptr;
            }

            this->stateArray = new State[newNumberOfStates];
            for (unsigned int i = 0; i < newNumberOfStates; ++i)
                this->stateArray[i] = newStateArray[i];

            this->numberOfStates = newNumberOfStates;
            this->startState = newStartState;
            this->stateArray[this->startState].setStartFlag(true);
        } else
            throw AutomatonException("Invalid argument - nullptr");

    } catch (AutomatonException exc) {
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Function: " << "setStateArray(State *, unsigned int, unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
    }

}

void DeterminateFiniteAutomaton::setNumberOfStates(unsigned int newNumberOfStates) {
    try {
        if (this->stateArray != nullptr)
            throw AutomatonException("Trying to change the number of states on an existing array!");
        else
            this->numberOfStates = newNumberOfStates;

    } catch (AutomatonException exc) {
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Function: " << "setNumberOfStates(unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "Number of states: " << this->numberOfStates << std::endl;
    }
}

void DeterminateFiniteAutomaton::setStartState(unsigned int newStartState) {
    try {
        if (this->stateArray == nullptr)
            throw AutomatonException("Data member stateArray - nullptr");

        bool alreadyExistsStartState = false;
        for (unsigned int i = 0; i < this->numberOfStates; ++i) {
            if (this->stateArray[i].getStartFlag()) {
                alreadyExistsStartState = true;
                break;
            }
        }

        try {
            if (alreadyExistsStartState)
                throw AutomatonException("Trying to change start state, when there is already one!");
            else {
                try {
                    if (0 <= newStartState && newStartState < this->numberOfStates) {
                        this->startState = newStartState;
                        this->stateArray[this->startState].setStartFlag(true);
                    } else
                        throw AutomatonException("This state is out of range!");

                } catch (AutomatonException exc) {
                    std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
                    std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
                    std::cerr << "Caught: " << exc.what() << std::endl;
                    std::cerr << "Type: " << "AutomatonException" << std::endl;
                    std::cerr << "Number of states: " << this->numberOfStates << std::endl;
                    std::cerr << "Maximum index: " << (this->numberOfStates - 1) << std::endl;
                }
            }

        } catch (AutomatonException exc) {
            std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
            std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
            std::cerr << "Caught: " << exc.what() << std::endl;
            std::cerr << "Type: " << "AutomatonException" << std::endl;
            std::cerr << "Start state: " << this->stateArray[this->startState].getName() << std::endl;
            std::cerr << "Attempt: " << this->stateArray[newStartState].getName() << std::endl;
        }

    } catch (AutomatonException exc) {
        std::cerr << "File: " << "DeterminateFiniteAutomaton.cpp" << std::endl;
        std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
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

// prints all states
void DeterminateFiniteAutomaton::printAllStates() {
    std::cout << "[" << this->stateArray[0].getName() << "]";
    for (unsigned int i = 1; i < this->numberOfStates; ++i) {
        std::cout << " [" << this->stateArray[i].getName() << "]";
    }
    std::cout << std::endl;
}

// changes the startState data member and removes the last one
void DeterminateFiniteAutomaton::changeStartState(unsigned int newStartState) {
    this->stateArray[startState].setStartFlag(false);
    this->startState = 0;
    this->setStartState(newStartState);
}

// asks and validates the user for information in the console
void DeterminateFiniteAutomaton::changeStartStateConsole() {
    this->printAllStates();
    std::cout << "Current start state: [" << this->stateArray[this->startState].getName() << "]" << std::endl;

    bool done = false;
    do {
        std::cout << "Type name of a state to change the start state: " << std::endl;
        char newStartState[100] = {'\0'};
        std::cin.getline(newStartState, 100);

        bool stateExist = false;
        unsigned int indexOfNewStartState = 0;
        for (unsigned int i = 0; i < this->numberOfStates; ++i) {
            if (strcmp(this->stateArray[i].getName(), newStartState) == 0) {
                stateExist = true;
                indexOfNewStartState = i;
                break;
            }
        }

        if (stateExist) {
            this->changeStartState(indexOfNewStartState);
            std::cout << "The change is successful!" << std::endl;
            std::cout << "New start state: [" << this->stateArray[this->startState].getName() << "]" << std::endl;
            done = true;
        } else
            std::cout << "This state is not found!" << std::endl;
    } while (!done);
}
