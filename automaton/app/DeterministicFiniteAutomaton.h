//
// Created on 11-Jun-20.
//

#ifndef AUTOMATON_DETERMINISTICFINITEAUTOMATON_H
#define AUTOMATON_DETERMINISTICFINITEAUTOMATON_H


#include "FiniteAutomaton.h"
#include "../exceptions/AutomatonTransitionTableException.h"

template<typename T>
class DeterministicFiniteAutomaton : public FiniteAutomaton<T> {
public:
    /// Constructor - default
    DeterministicFiniteAutomaton();
    /// Constructor - parameters
    DeterministicFiniteAutomaton(State *stateArray, unsigned int numberOfStates,
                                 T *alphabet, unsigned int alphabetLength,
                                 unsigned int startState,
                                 unsigned int *acceptStateArray, unsigned int numberOfAcceptStates,
                                 unsigned int **transitionTable) noexcept(false);
    /// Constructor - copy
    DeterministicFiniteAutomaton(const DeterministicFiniteAutomaton &obj);
    /// Destructor
    ~DeterministicFiniteAutomaton();

    /// Setters
    void setTransitionTable(unsigned int **newTransitionTable) noexcept(false);
    /// Getters
    unsigned **getTransitionTable() const;
    unsigned getTableRows() const;
    unsigned getTableColumns() const;

    /*!
     * Prints transition table
     */
    void printTB() const;

private:
    /*!
     * 3. Transition table
     * rows = numberOfStates
     * columns = alphabetLength
     */
    unsigned int **transitionTable;
};

template<typename T>
DeterministicFiniteAutomaton<T>::DeterministicFiniteAutomaton() : FiniteAutomaton<T>(),
                                                                  transitionTable(nullptr) {}

template<typename T>
DeterministicFiniteAutomaton<T>::DeterministicFiniteAutomaton
        (State *stateArray, unsigned int numberOfStates,
         T *alphabet, unsigned int alphabetLength,
         unsigned int startState,
         unsigned int *acceptStateArray, unsigned int numberOfAcceptStates,
         unsigned int **transitionTable) noexcept(false) :FiniteAutomaton<T>(stateArray, numberOfStates,
                                                                             alphabet, alphabetLength,
                                                                             startState,
                                                                             acceptStateArray, numberOfAcceptStates) {
    try {
        // Validate Transition table related parameters
        if (transitionTable == nullptr)
            throw AutomatonException("Invalid parameter - transition table (transitionTable == nullptr)");
        else {
            for (unsigned int row = 0; row < numberOfStates; ++row) {
                for (unsigned int col = 0; col < alphabetLength; ++col) {
                    if (!(0 <= transitionTable[row][col] && transitionTable[row][col] < numberOfStates))
                        throw AutomatonTransitionTableException("Transition table indices out of range!");
                }
            }
        }

        // Set up transition table
        this->transitionTable = new unsigned *[numberOfStates]{nullptr};
        for (unsigned int row = 0; row < numberOfStates; ++row)
            this->transitionTable[row] = new unsigned[alphabetLength]{0};

        for (unsigned int row = 0; row < numberOfStates; ++row) {
            for (unsigned int col = 0; col < alphabetLength; ++col)
                this->transitionTable[row][col] = transitionTable[row][col];
        }

    } catch (AutomatonTransitionTableException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterministicFiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonTransitionTableException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

template<typename T>
DeterministicFiniteAutomaton<T>::DeterministicFiniteAutomaton(const DeterministicFiniteAutomaton &obj) :
        FiniteAutomaton<T>(obj) {

    // Set up transition table
    if (obj.transitionTable != nullptr) {
        this->transitionTable = new unsigned *[obj.getTableRows()]{nullptr};
        for (unsigned int row = 0; row < obj.getTableRows(); ++row)
            this->transitionTable[row] = new unsigned[obj.getTableColumns()]{0};

        for (unsigned int row = 0; row < obj.getTableRows(); ++row) {
            for (unsigned int col = 0; col < obj.getTableColumns(); ++col)
                this->transitionTable[row][col] = obj.transitionTable[row][col];
        }

    } else
        this->transitionTable = nullptr;
}

template<typename T>
DeterministicFiniteAutomaton<T>::~DeterministicFiniteAutomaton() {
    // Delete transition table
    if (this->transitionTable != nullptr) {
        for (unsigned int row = 0; row < this->getTableRows(); ++row) {
            if (this->transitionTable[row] != nullptr) {
                delete[] this->transitionTable[row];
                this->transitionTable[row] = nullptr;
            }
        }
        delete[] this->transitionTable;
        this->transitionTable = nullptr;
    }
}

template<typename T>
void DeterministicFiniteAutomaton<T>::setTransitionTable(unsigned int **newTransitionTable) noexcept(false) {
    try {
        // Validate Transition table related parameters
        if (transitionTable == nullptr)
            throw AutomatonException("Invalid parameter - transition table (transitionTable == nullptr)");
        else {
            for (unsigned int row = 0; row < this->getTableRows(); ++row) {
                for (unsigned int col = 0; col < this->getTableColumns(); ++col) {
                    if (!(0 <= transitionTable[row][col] && transitionTable[row][col] < this->getNumberOfStates()))
                        throw AutomatonTransitionTableException("Transition table indices out of range!");
                }
            }
        }

        // Reset transition table
        if (this->transitionTable != nullptr) {
            for (unsigned int row = 0; row < this->getTableRows(); ++row) {
                if (this->transitionTable[row] != nullptr) {
                    delete[] this->transitionTable[row];
                    this->transitionTable[row] = nullptr;
                }
            }
            delete[] this->transitionTable;
            this->transitionTable = nullptr;
        }

        // Set up transition table
        this->transitionTable = new unsigned *[this->getTableRows()]{nullptr};
        for (unsigned int row = 0; row < this->getTableRows(); ++row)
            this->transitionTable[row] = new unsigned[this->getTableColumns()]{0};

        for (unsigned int row = 0; row < this->getTableRows(); ++row) {
            for (unsigned int col = 0; col < this->getTableColumns(); ++col)
                this->transitionTable[row][col] = newTransitionTable[row][col];
        }

    } catch (AutomatonTransitionTableException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterministicFiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setTransitionTable(unsigned **)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonTransitionTableException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

template<typename T>
unsigned **DeterministicFiniteAutomaton<T>::getTransitionTable() const {
    return this->transitionTable;
}

template<typename T>
unsigned DeterministicFiniteAutomaton<T>::getTableRows() const {
    return this->getNumberOfStates();
}

template<typename T>
unsigned DeterministicFiniteAutomaton<T>::getTableColumns() const {
    return this->getAlphabetLength();
}

template<typename T>
void DeterministicFiniteAutomaton<T>::printTB() const {
    for (unsigned int row = 0; row < this->getTableRows(); ++row) {
        std::cout << this->transitionTable[row][0];
        for (unsigned int col = 1; col < getTableColumns(); ++col) {
            std::cout << ", " << this->transitionTable[row][col];
        }
        std::cout << std::endl;
    }
}


#endif //AUTOMATON_DETERMINISTICFINITEAUTOMATON_H
