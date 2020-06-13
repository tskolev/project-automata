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

    /*! Configurations */
    void configureStateArray(State *newStateArray, unsigned int newNumberOfStates) noexcept(false);
    void configureStateArrayConsole() noexcept(false);

    void configureAlphabet(T *newAlphabet, unsigned int newAlphabetLength) noexcept(false);
    void configureAlphabetConsole() noexcept(false);

    void configureStartState(unsigned int newStartState) noexcept(false);
    void configureStartStateConsole() noexcept(false);

    void configureAcceptStates
            (unsigned int *newAcceptStatesArray, unsigned int newNumberOfAcceptStates) noexcept(false);
    void configureAcceptStatesConsole() noexcept(false);

    void configureTransitionTable(unsigned int **newTransitionTable) noexcept(false);
    void configureTransitionTableConsole() noexcept(false);

    /*! Output */
    void printTB() const;

private:
    /*!
     * 3. Transition table
     * rows = numberOfStates
     * columns = alphabetLength
     */
    unsigned int **transitionTable;
};

/*! Definitions: */
/*! Constructors, Destructors, Setters, Getters - start here */

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

/*! Constructors, Destructors, Setters, Getters - end here */
/*! Class member functions - start here */
/*! Configurations - start here */

template<typename T>
void DeterministicFiniteAutomaton<T>::configureStateArray
        (State *newStateArray, unsigned int newNumberOfStates) noexcept(false) {

    // Set up new stateArray & new numberOfStates
    this->setStateArray(newStateArray, newNumberOfStates);

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
}

template<typename T>
void DeterministicFiniteAutomaton<T>::configureStateArrayConsole() {
    std::cout << "---State configuration---" << std::endl;
    int localNumberOfStates = 0;

    // Validate given information
    do {
        // Ask for number of states
        std::cout << "Please enter a number of states:" << std::endl;
        std::cin >> localNumberOfStates;

        if (localNumberOfStates < 1 || 1000 < localNumberOfStates)
            std::cout << "Invalid number!" << std::endl;

    } while (localNumberOfStates < 1 || 1000 < localNumberOfStates);

    // Create local dynamic array of states
    State *localStateArray = new State[localNumberOfStates];

    // Ask for their name
    for (unsigned int i = 0; i < localNumberOfStates; ++i) {
        std::cout << "Please enter a name for state " << "[" << (i + 1) << "]:" << std::endl;

        char name[100] = {'\0'};
        std::cin.ignore();
        std::cin.getline(name, 100);

        // Set up state name
        localStateArray[i].setName(name);
    }

    // Set up stateArray
    this->configureStateArray(localStateArray, localNumberOfStates);

    // Delete local dynamic array
    if (localStateArray != nullptr) {
        delete[] localStateArray;
        localStateArray = nullptr;
    }
}

template<typename T>
void
DeterministicFiniteAutomaton<T>::configureAlphabet
        (T *newAlphabet, unsigned int newAlphabetLength) noexcept(false) {

    // Set up new alphabet & new alphabetLength
    this->setAlphabet(newAlphabet, newAlphabetLength);

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
}

template<typename T>
void DeterministicFiniteAutomaton<T>::configureAlphabetConsole() noexcept(false) {
    std::cout << "---Alphabet configuration---" << std::endl;

    int localAlphabetLength = 0;

    // Validate given information
    do {
        //Ask for number of characters
        std::cout << "Please enter the number of characters in the alphabet: " << std::endl;
        std::cin >> localAlphabetLength;

        if (localAlphabetLength < 1 || 1000 < localAlphabetLength)
            std::cout << "Invalid number of characters!" << std::endl;

    } while (localAlphabetLength < 1 || 1000 < localAlphabetLength);

    // Creat local dynamic array of characters
    T *localAlphabet = new T[localAlphabetLength]{0};

    // Ask for characters for the language
    for (unsigned int i = 0; i < localAlphabetLength; ++i) {
        T symbol = 0;

        std::cout << "Please enter a symbol for character " << "[" << (i + 1) << "]: " << std::endl;
        std::cin >> symbol;
        std::cin.ignore();

        localAlphabet[i] = symbol;
    }

    // Set up alphabet
    this->configureAlphabet(localAlphabet, localAlphabetLength);

    if (localAlphabet != nullptr) {
        delete[] localAlphabet;
        localAlphabet = nullptr;
    }
}

template<typename T>
void DeterministicFiniteAutomaton<T>::configureStartState(unsigned int newStartState) noexcept(false) {
    // Reset startSFlag of the state
    this->getStateArray()[this->getStartState()].setStartFlag(false);

    // Set up startState
    this->setStartState(newStartState);
}

template<typename T>
void DeterministicFiniteAutomaton<T>::configureStartStateConsole() noexcept(false) {
    std::cout << "---Start state configuration---" << std::endl;

    this->printAllStates();
    std::cout << "Current start state: [" << this->getStateArray()[this->getStartState()].getName()
              << "]" << std::endl;

    // Validate given information
    bool done = false;
    do {
        // Ask for name of the start state
        std::cout << "Type name of a state to change the start state: " << std::endl;
        char newStartState[100] = {'\0'};
        std::cin.getline(newStartState, 100);

        // Validate name
        bool stateExist = false;
        unsigned int indexOfNewStartState = 0;
        for (unsigned int i = 0; i < this->getNumberOfStates(); ++i) {
            if (strcmp(this->getStateArray()[i].getName(), newStartState) == 0) {
                stateExist = true;
                indexOfNewStartState = i;
                break;
            }
        }

        // Set up or try again
        if (stateExist) {
            this->configureStartState(indexOfNewStartState);
            std::cout << "The change is successful!" << std::endl;
            std::cout << "New start state: [" << this->getStateArray()[this->getStartState()].getName()
                      << "]" << std::endl;
            done = true;
        } else
            std::cout << "Invalid state!" << std::endl;
    } while (!done);
}

template<typename T>
void DeterministicFiniteAutomaton<T>::configureAcceptStates
        (unsigned int *newAcceptStatesArray,
         unsigned int newNumberOfAcceptStates) noexcept(false) {

    // Set up accept states
    this->setAcceptStatesArray(newAcceptStatesArray, newNumberOfAcceptStates);
}

template<typename T>
void DeterministicFiniteAutomaton<T>::configureAcceptStatesConsole() noexcept(false) {
    std::cout << "---Accept states configuration---" << std::endl;

    this->printAllStates();

    int localNumberOfAcceptStates = 0;
    // Validate given information
    do {
        // Ask for number of accept states
        std::cout << "Please enter the number of accept states: " << std::endl;
        std::cin >> localNumberOfAcceptStates;

        if (localNumberOfAcceptStates < 0 || this->getNumberOfStates() < localNumberOfAcceptStates)
            std::cout << "Invalid number of accept states!" << std::endl;

    } while (localNumberOfAcceptStates < 0 || this->getNumberOfStates() < localNumberOfAcceptStates);

    // Create local dynamic array of accept states
    unsigned *localAcceptStatesArray = new unsigned[localNumberOfAcceptStates]{0};

    // Initialize every accept state of the local array
    for (unsigned int acceptI = 0; acceptI < localNumberOfAcceptStates; ++acceptI) {
        char newStartState[100] = {'\0'};
        bool stateExist = false;
        unsigned int indexOfState = 0;

        // Validate the information
        do {
            std::cout << "Type name for accept state [" << (acceptI + 1) << "]" << std::endl;
            std::cin.getline(newStartState, 100);

            // Validate name
            for (unsigned int stateI = 0; stateI < this->getNumberOfStates(); ++stateI) {
                if (strcmp(this->getStateArray()[stateI].getName(), newStartState) == 0) {
                    stateExist = true;
                    indexOfState = stateI;
                    break;
                }
            }

            // Save index or try again
            if (stateExist)
                localAcceptStatesArray[acceptI] = indexOfState;
            else
                std::cout << "Invalid state!" << std::endl;

        } while (!stateExist);
    }

    // Set up acceptStates
    this->configureAcceptStates(localAcceptStatesArray, localNumberOfAcceptStates);

    // Delete local dynamic array of accept states
    if (localAcceptStatesArray != nullptr) {
        delete[] localAcceptStatesArray;
        localAcceptStatesArray = nullptr;
    }
}

template<typename T>
void DeterministicFiniteAutomaton<T>::configureTransitionTable
        (unsigned int **newTransitionTable) noexcept(false) {

    // Set up transition table
    this->setTransitionTable(newTransitionTable);
}

template<typename T>
void DeterministicFiniteAutomaton<T>::configureTransitionTableConsole() noexcept(false) {
    std::cout << "---Transition table configuration---" << std::endl;

    try {
        // Validate actions
        if (this->getStateArray() == nullptr)
            throw AutomatonTransitionTableException("Invalid action! - states not found (stateArray == nullptr)");
        else if (this->getAlphabet() == nullptr)
            throw AutomatonTransitionTableException("Invalid action! - alphabet not found (alphabet == nullptr)");

        // Create local dynamic two-dimensional array
        unsigned int **localTransitionTable = nullptr;
        localTransitionTable = new unsigned *[this->getTableRows()]{nullptr};
        for (unsigned int row = 0; row < this->getTableRows(); ++row)
            this->transitionTable[row] = new unsigned[this->getTableColumns()]{0};

        // Ask for information and validate the information
        for (unsigned int row = 0; row << this->getTableRows(); ++row) {
            for (unsigned int col = 0; col << this->getTableColumns(); ++col) {

                char stateName[100] = {'\0'};
                bool stateExist = false;
                unsigned int indexOfState = 0;

                // Ask
                do {
                    std::cout << "Type name of a state(" << this->getStateArray()[row].getName() << ", "
                              << this->getAlphabet()[col] << "): " << std::endl;
                    std::cin.getline(stateName, 100);

                    // Validate name
                    for (unsigned int stateI = 0; stateI < this->getNumberOfStates(); ++stateI) {
                        if (strcmp(this->getStateArray()[stateI].getName(), stateName) == 0) {
                            stateExist = true;
                            indexOfState = stateI;
                            break;
                        }
                    }

                    // Save index or try again
                    if (stateExist)
                        localTransitionTable[row][col] = indexOfState;
                    else
                        std::cout << "Invalid state!" << std::endl;

                } while (!stateExist);
            }
        }

        // Set up transition table
        this->configureTransitionTable(localTransitionTable);

        // Delete local dynamic two-dimensional array
        if (localTransitionTable != nullptr) {
            for (unsigned int row = 0; row < this->getTableRows(); ++row) {
                if (localTransitionTable[row] != nullptr) {
                    delete[] localTransitionTable[row];
                    localTransitionTable[row] = nullptr;
                }
            }
            delete[] localTransitionTable;
            localTransitionTable = nullptr;
        }

    } catch (AutomatonTransitionTableException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterministicFiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "configureTransitionTableConsole" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonTransitionTableException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

/*! Configurations - end here */

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
