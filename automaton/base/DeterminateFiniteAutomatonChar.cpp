//
// Created on 22-May-20.
//

#include "DeterminateFiniteAutomatonChar.h"

DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar() : DeterminateFiniteAutomaton1(),
                                                                   alphabetChar(nullptr), alphabetLength(0),
                                                                   transitionTable(nullptr),
                                                                   tTColumnsNumber(0), tTRowsNumber(0) {}

DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(char *alphabetChar, unsigned int alphabetLength,
                                                               State *stateArray, unsigned int numberOfStates,
                                                               unsigned int **transitionTable,
                                                               unsigned int startState,
                                                               unsigned int *acceptStateArray = nullptr,
                                                               unsigned int numberOfAcceptStates = 0) :
        DeterminateFiniteAutomaton1(stateArray, numberOfStates, startState, acceptStateArray, numberOfAcceptStates) {

    try {
        if (alphabetChar == nullptr)
            throw AutomatonException("Invalid parameter - alphabetChar (alphabetChar == nullptr)");
        else if (alphabetLength == 0)
            throw AutomatonAlphabetException("Invalid parameter - alphabetLength (alphabetLength == 0)");
        else if (transitionTable == nullptr)
            throw AutomatonException("Invalid parameter - transition table (transitionTable == nullptr)");
        else {
            for (unsigned int row = 0; row < numberOfStates; ++row) {
                for (unsigned int col = 0; col < alphabetLength; ++col) {
                    if (!(0 <= transitionTable[row][col] && transitionTable[row][col] < numberOfStates))
                        throw AutomatonTransitionTableException("Transition table indices out of range!");
                }
            }
        }

        // Set up alphabetChar AND alphabetLength
        this->alphabetChar = new char[alphabetLength + 1]{'\0'};
        strcpy_s(this->alphabetChar, (alphabetLength + 1), alphabetChar);
        this->alphabetLength = alphabetLength;

        // Set up tTColumnsNumber AND tTRowsNumber
        this->tTRowsNumber = numberOfStates;
        this->tTColumnsNumber = alphabetLength;

        // Set up transition table
        this->transitionTable = new unsigned *[numberOfStates]{nullptr};
        for (unsigned int row = 0; row < numberOfStates; ++row)
            this->transitionTable[row] = new unsigned[alphabetLength]{0};

        for (unsigned int row = 0; row < numberOfStates; ++row) {
            for (unsigned int col = 0; col < alphabetLength; ++col)
                this->transitionTable[row][col] = transitionTable[row][col];
        }

    } catch (AutomatonException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterminateFiniteAutomatonChar.cpp" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    } catch (AutomatonAlphabetException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterminateFiniteAutomatonChar.cpp" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonAlphabetException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    } catch (AutomatonTransitionTableException exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterminateFiniteAutomatonChar.cpp" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonTransitionTableException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(const DeterminateFiniteAutomatonChar &obj) :
        DeterminateFiniteAutomaton1(obj) {

    // Set up alphabetChar AND alphabetLength
    if (obj.alphabetChar != nullptr) {
        this->alphabetChar = new char[obj.alphabetLength + 1]{'\0'};
        strcpy_s(this->alphabetChar, (obj.alphabetLength + 1), obj.alphabetChar);
        this->alphabetLength = obj.alphabetLength;
    } else {
        this->alphabetChar = nullptr;
        this->alphabetLength = 0;
    }

    // Set up tTColumnsNumber AND tTRowsNumber
    this->tTRowsNumber = obj.tTRowsNumber;
    this->tTColumnsNumber = obj.tTColumnsNumber;

    // Set up transition table
    if (obj.transitionTable != nullptr) {
        this->transitionTable = new unsigned *[obj.tTRowsNumber]{nullptr};
        for (unsigned int row = 0; row < obj.tTRowsNumber; ++row)
            this->transitionTable[row] = new unsigned[obj.tTColumnsNumber]{0};

        for (unsigned int row = 0; row < obj.tTRowsNumber; ++row) {
            for (unsigned int col = 0; col < obj.tTColumnsNumber; ++col)
                this->transitionTable[row][col] = obj.transitionTable[row][col];
        }
    } else {
        this->transitionTable = nullptr;
    }
}

DeterminateFiniteAutomatonChar::~DeterminateFiniteAutomatonChar() {
    // Delete alphabet
    if (this->alphabetChar != nullptr) {
        delete[] this->alphabetChar;
        this->alphabetChar = nullptr;
    }

    // Delete transition table
    if (this->transitionTable != nullptr) {
        for (unsigned int row = 0; row < tTRowsNumber; ++row) {
            if (this->transitionTable[row] != nullptr) {
                delete[] this->transitionTable[row];
                this->transitionTable[row] = nullptr;
            }
        }
        delete[] this->transitionTable;
        this->transitionTable = nullptr;
    }
}

void DeterminateFiniteAutomatonChar::setAlphabetChar(char *newAlphabetChar, unsigned int newAlphabetLength) {
    try {
        if (newAlphabetChar == nullptr)
            throw AutomatonException("Invalid parameter - alphabetChar (alphabetChar == nullptr)");
        else if (newAlphabetLength == 0)
            throw AutomatonAlphabetException("Invalid parameter - alphabetLength (alphabetLength == 0)");

        // Delete last alphabet AND reset alphabet length
        if (this->alphabetChar != nullptr) {
            delete[] this->alphabetChar;
            this->alphabetChar = nullptr;
            this->alphabetLength = 0;
        }

        // Set up alphabet AND alphabet length
        this->alphabetChar = new char[newAlphabetLength + 1]{'\0'};
        strcpy_s(this->alphabetChar, (newAlphabetLength + 1), newAlphabetChar);
        this->alphabetLength = newAlphabetLength;

    } catch (AutomatonException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterminateFiniteAutomatonChar.cpp" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    } catch (AutomatonAlphabetException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "DeterminateFiniteAutomatonChar.cpp" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonAlphabetException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

char *DeterminateFiniteAutomatonChar::getAlphabetChar() const {
    return this->alphabetChar;
}

int DeterminateFiniteAutomatonChar::getLength() const {
    return this->alphabetLength;
}