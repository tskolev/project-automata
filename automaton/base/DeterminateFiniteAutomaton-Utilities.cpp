//
// Created on 05-Jun-20.
//

#include "DeterminateFiniteAutomaton.h"

void DeterminateFiniteAutomaton::printAllStates() {
    std::cout << "[" << this->stateArray[0].getName() << "]";
    for (unsigned int i = 1; i < this->numberOfStates; ++i) {
        std::cout << " [" << this->stateArray[i].getName() << "]";
    }
    std::cout << std::endl;
}

void DeterminateFiniteAutomaton::changeStartState(unsigned int newStartState) {
    this->stateArray[startState].setStartFlag(false);
    this->startState = 0;
    this->setStartState(newStartState);
}

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

std::ostream &DeterminateFiniteAutomaton::inst(std::ostream &oStream) const {
    oStream << "Number of states: " << this->numberOfStates << std::endl;
    oStream << "[" << this->stateArray[0].getName() << "]";
    for (unsigned int i = 1; i < this->numberOfStates; ++i)
        oStream << " [" << this->stateArray[i].getName() << "]";

    oStream << std::endl << std::endl;
    oStream << "Start state: " << this->stateArray[this->startState].getName() << "(" << this->startState << ")"
            << std::endl << std::endl
            << "Accept states: " << this->numberOfAcceptStates << std::endl;
    for (unsigned int i = 0; i < this->numberOfAcceptStates; ++i) {
        if (i == (this->numberOfAcceptStates - 1))
            oStream << "[" << this->stateArray[this->acceptStatesArray[i]].getName() << "]";
        else
            oStream << "[" << this->stateArray[this->acceptStatesArray[i]].getName() << "] ";
    }
    oStream << std::endl;
    oStream << std::endl;

    oStream << "Details about states:" << std::endl;
    for (unsigned int i = 0; i < this->numberOfStates; ++i) {
        oStream << "{" << std::endl
                << this->stateArray[i]
                << "}" << std::endl << std::endl;
    }

    return oStream;
}

std::ostream &operator<<(std::ostream &oStream, const DeterminateFiniteAutomaton &obj) {
    return obj.inst(oStream);
}

