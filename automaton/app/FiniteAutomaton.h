//
// Created on 11-Jun-20.
//

#ifndef AUTOMATON_FINITEAUTOMATON_H
#define AUTOMATON_FINITEAUTOMATON_H


#include "../exceptions/AutomatonException.h"
#include "../exceptions/AutomatonStateException.h"
#include "../exceptions/AutomatonAlphabetException.h"
#include "../automaton-lib/State.h"

template<typename T>
class FiniteAutomaton {
public:
    /// Constructor - default
    FiniteAutomaton();
    /// Constructor - parameters
    FiniteAutomaton(State *stateArray, unsigned int numberOfStates,
                    T *alphabet, unsigned int alphabetLength,
                    unsigned int startState,
                    unsigned int *acceptStateArray, unsigned int numberOfAcceptStates) noexcept(false);
    /// Constructor - copy
    FiniteAutomaton(const FiniteAutomaton &obj);
    /// Destructor
    virtual ~FiniteAutomaton();

    /// Setters
    void setStateArray
            (State *newStateArray, unsigned int newNumberOfStates) noexcept(false);
    void setAlphabet
            (T *newAlphabet, unsigned int newAlphabetLength) noexcept(false);
    void setStartState
            (unsigned int newStartState) noexcept(false);
    void setAcceptStatesArray
            (unsigned int *newAcceptStatesArray, unsigned int newNumberOfAcceptStates) noexcept(false);
    /// Getters
    State *getStateArray() const;
    unsigned getNumberOfStates() const;
    T *getAlphabet() const;
    unsigned getAlphabetLength() const;
    unsigned getStartState() const;
    unsigned *getAcceptStatesArray() const;
    unsigned getNumberOfAcceptStates() const;

    /// pure virtual function
    virtual void setTransitionTable(unsigned int **newTransitionTable) = 0;

    /*!
     * Prints all states of the automation.
     */
    void printAllStates();

    /*!
     * Inserts data in a given stream by parameter.
     * The inserted data is Object data fields and their details.
     * @param oStream - reference to an object of std::ostream.
     * @return reference to an object of std::ostream.
     */
    std::ostream &inst(std::ostream &oStream) const;

    /*!
     * Puts the current start state startFlag to false,
     * puts the current startState data member to 0,
     * than calls (setStartState).
     * @param newStartState - the new index for the startState data member.
     */
    void changeStartState(unsigned int newStartState) noexcept(false);

    /*!
     * Prints and takes information from the console,
     * Asks for new startState,
     * validates the input from the user,
     * than calls (changeStartState).
     */
    void changeStartStateConsole() noexcept(false);

private:
    /// 1. States
    State *stateArray;
    unsigned int numberOfStates;

    /// 2. Alphabet
    T *alphabet;
    unsigned int alphabetLength;

    /// 4. Start state
    unsigned int startState;

    /// 5. Accept states
    unsigned int *acceptStatesArray;
    unsigned int numberOfAcceptStates;
};

/*!
 * Overload of operator "<<".
 * Inserts data in a given stream by parameter through an object method.
 * The inserted data is Object data fields and their details.
 * @tparam T - template parameters for class FiniteAutomaton<>.
 * @param oStream - reference to an object of std::ostream.
 * @param obj - const reference to an object of class FiniteAutomaton<>.
 * @return reference to an object of class std::ostream.
 */
template<typename T>
std::ostream &operator<<(std::ostream &oStream, const FiniteAutomaton<T> &obj);

/*! Definitions: */
/*! Constructors, Destructors, Setters, Getters - start here */

template<typename T>
FiniteAutomaton<T>::FiniteAutomaton() : stateArray(nullptr), numberOfStates(0),
                                        alphabet(nullptr), alphabetLength(0),
                                        startState(0),
                                        acceptStatesArray(nullptr), numberOfAcceptStates(0) {}

template<typename T>
FiniteAutomaton<T>::FiniteAutomaton
        (State *stateArray, unsigned int numberOfStates,
         T *alphabet, unsigned int alphabetLength,
         unsigned int startState,
         unsigned int *acceptStatesArray, unsigned int numberOfAcceptStates) noexcept(false) {

    try {
        // Validate all State related parameters
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

        // Validate all Alphabet related parameters
        if (alphabet == nullptr) {
            throw AutomatonException("Invalid parameter - alphabet (alphabet == nullptr)");
        } else if (alphabetLength == 0) {
            throw AutomatonAlphabetException("Invalid parameter - alphabetLength (alphabetLength == 0)");
        }

        // Set up stateArray & numberOfStates
        this->stateArray = new State[numberOfStates];
        for (unsigned int i = 0; i < numberOfStates; ++i)
            this->stateArray[i] = stateArray[i];
        this->numberOfStates = numberOfStates;

        // Set up startState
        this->startState = startState;
        this->stateArray[startState].setStartFlag(true);

        // Set up acceptStatesArray & numberOfAcceptStates
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

        // Set up alphabet & alphabetLength
        this->alphabet = new T[alphabetLength]{0};
        for (unsigned int i = 0; i < alphabetLength; ++i)
            this->alphabet[i] = alphabet[i];
        this->alphabetLength = alphabetLength;

    } catch (AutomatonException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    } catch (AutomatonStateException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    } catch (AutomatonAlphabetException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "Constructor - parameters" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonAlphabetException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

template<typename T>
FiniteAutomaton<T>::FiniteAutomaton(const FiniteAutomaton &obj) {
    // Set up stateArray & numberOfStates & startState
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

    // Set up acceptStatesArray & numberOfAcceptStates
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

    // Set up alphabet AND alphabetLength
    if (obj.alphabet != nullptr) {
        this->alphabet = new T[obj.alphabetLength]{0};
        for (unsigned int i = 0; i < obj.alphabetLength; ++i)
            this->alphabet[i] = obj.alphabet[i];

        this->alphabetLength = obj.alphabetLength;
    } else {
        this->alphabet = nullptr;
        this->alphabetLength = 0;
    }
}

template<typename T>
FiniteAutomaton<T>::~FiniteAutomaton() {
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

    // Delete alphabet
    if (this->alphabet != nullptr) {
        delete[] this->alphabet;
        this->alphabet = nullptr;
    }
}

template<typename T>
void FiniteAutomaton<T>::setStateArray(State *newStateArray, unsigned int newNumberOfStates) noexcept(false) {
    try {
        // Validate parameters
        if (newStateArray == nullptr)
            throw AutomatonException("Invalid parameter = newStateArray! (stateArray = nullptr)");
        else if (newNumberOfStates == 0)
            throw AutomatonStateException("Invalid parameter - newNumberOfStates! (neNumberOfStates = 0)");

        // Reset stateArray & numberOfStates
        if (this->stateArray != nullptr) {
            delete[] this->stateArray;
            this->stateArray = nullptr;
            this->numberOfStates = 0;
        }

        // Reset startState
        this->startState = 0;

        // Reset acceptStatesArray & numberOfAcceptStates
        if (this->acceptStatesArray != nullptr) {
            delete[] this->acceptStatesArray;
            this->acceptStatesArray = nullptr;
            this->numberOfAcceptStates = 0;
        }

        // Set up stateArray & numberOfStates
        this->stateArray = new State[newNumberOfStates];
        for (unsigned int i = 0; i < newNumberOfStates; ++i)
            this->stateArray[i] = newStateArray[i];
        this->numberOfStates = newNumberOfStates;

    } catch (AutomatonException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setStateArray(State *, unsigned)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    } catch (AutomatonStateException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setStateArray(State *, unsigned)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

template<typename T>
void FiniteAutomaton<T>::setAlphabet(T *newAlphabet, unsigned int newAlphabetLength) noexcept(false) {
    try {
        // Validate parameters
        if (newAlphabet == nullptr)
            throw AutomatonException("Invalid parameter - alphabet (alphabet == nullptr)");
        else if (newAlphabetLength == 0)
            throw AutomatonAlphabetException("Invalid parameter - alphabetLength (alphabetLength == 0)");

        // Reset alphabet & alphabetLength
        if (this->alphabet != nullptr) {
            delete[] this->alphabet;
            this->alphabet = nullptr;
            this->alphabetLength = 0;
        }

        // Set up alphabet & alphabetLength
        this->alphabet = new T[newAlphabetLength]{0};
        for (unsigned int i = 0; i < newAlphabetLength; ++i)
            this->alphabet[i] = newAlphabet[i];
        this->alphabetLength = newAlphabetLength;

    } catch (AutomatonException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setAlphabet(T *, unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    } catch (AutomatonAlphabetException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setAlphabet(T *, unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonAlphabetException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

template<typename T>
void FiniteAutomaton<T>::setStartState(unsigned int newStartState) noexcept(false) {
    try {
        // Check for available states
        if (this->stateArray == nullptr)
            throw AutomatonStateException("Invalid action - work with empty data field (stateArray = nullptr)");

    } catch (AutomatonStateException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }

    try {
        // Search for existing start state
        bool alreadyExistsStartState = false;
        for (unsigned int i = 0; i < this->numberOfStates; ++i) {
            if (this->stateArray[i].getStartFlag()) {
                alreadyExistsStartState = true;
                break;
            }
        }

        // Check for existing start state
        if (alreadyExistsStartState)
            throw AutomatonException("Invalid action - start state already exist!");

    } catch (AutomatonException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "Start state: " << this->stateArray[this->startState].getName() << std::endl;
        std::cerr << "Attempt: " << this->stateArray[newStartState].getName() << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }

    try {
        // Validating index for start state
        if (0 <= newStartState && newStartState < this->numberOfStates) {

            // Set up start state
            this->startState = newStartState;
            this->stateArray[this->startState].setStartFlag(true);

        } else
            throw AutomatonStateException("State out of range!");

    } catch (AutomatonStateException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setStartState(unsigned int)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "Number of states: " << this->numberOfStates << std::endl;
        std::cerr << "Maximum index: " << (this->numberOfStates - 1) << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

template<typename T>
void FiniteAutomaton<T>::setAcceptStatesArray
        (unsigned int *newAcceptStatesArray, unsigned int newNumberOfAcceptStates) noexcept(false) {

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

        // Reset
        if (this->acceptStatesArray != nullptr) {
            // Reset acceptFlag(data member of State class) for every State
            for (unsigned int i = 0; i < this->numberOfAcceptStates; ++i)
                this->stateArray[acceptStatesArray[i]].setAcceptFlag(false);

            // Reset acceptStateArray & numberOfAcceptStates
            delete[] this->acceptStatesArray;
            this->numberOfAcceptStates = 0;
        }

        // Set up acceptStateArray & numberOfAcceptStates
        if (newAcceptStatesArray != nullptr) {
            this->acceptStatesArray = new unsigned[newNumberOfAcceptStates]{0};
            for (unsigned int i = 0; i < newNumberOfAcceptStates; ++i) {
                this->acceptStatesArray[i] = newAcceptStatesArray[i];
                this->stateArray[newAcceptStatesArray[i]].setAcceptFlag(true);
            }
            this->numberOfAcceptStates = newNumberOfAcceptStates;
        } else {
            this->acceptStatesArray = nullptr;
            this->numberOfAcceptStates = 0;
        }

    } catch (AutomatonException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setAcceptStatesArray(unsigned *, unsigned)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    } catch (AutomatonStateException &exc) {
        std::cerr << std::endl;
        std::cerr << "File: " << "FiniteAutomaton.h" << std::endl;
        std::cerr << "Function: " << "setAcceptStatesArray(unsigned *, unsigned)" << std::endl;
        std::cerr << "Caught: " << exc.what() << std::endl;
        std::cerr << "Type: " << "AutomatonStateException" << std::endl;
        std::cerr << "----- ----- -----" << std::endl;
        throw;
    }
}

template<typename T>
State *FiniteAutomaton<T>::getStateArray() const {
    return this->stateArray;
}

template<typename T>
unsigned FiniteAutomaton<T>::getNumberOfStates() const {
    return this->numberOfStates;
}

template<typename T>
T *FiniteAutomaton<T>::getAlphabet() const {
    return this->alphabet;
}

template<typename T>
unsigned FiniteAutomaton<T>::getAlphabetLength() const {
    return this->alphabetLength;
}

template<typename T>
unsigned FiniteAutomaton<T>::getStartState() const {
    return this->startState;
}

template<typename T>
unsigned *FiniteAutomaton<T>::getAcceptStatesArray() const {
    return this->acceptStatesArray;
}

template<typename T>
unsigned FiniteAutomaton<T>::getNumberOfAcceptStates() const {
    return this->numberOfAcceptStates;
}

/*! Constructors, Destructors, Setters, Getters - end here */
/*! Class member function - start here */

template<typename T>
void FiniteAutomaton<T>::printAllStates() {
    // list all states
    std::cout << "[" << this->stateArray[0].getName() << "]";
    for (unsigned int i = 1; i < this->numberOfStates; ++i) {
        std::cout << " [" << this->stateArray[i].getName() << "]";
    }
    std::cout << std::endl;
}

template<typename T>
std::ostream &FiniteAutomaton<T>::inst(std::ostream &oStream) const {
    // list all states
    oStream << "Number of states: " << this->numberOfStates << std::endl;
    oStream << "[" << this->stateArray[0].getName() << "]";
    for (unsigned int i = 1; i < this->numberOfStates; ++i)
        oStream << " [" << this->stateArray[i].getName() << "]";

    // list all elements from alphabet
    oStream << std::endl << std::endl;
    oStream << "Elements in alphabet: " << this->alphabetLength << std::endl;
    oStream << this->alphabet[0];
    for (unsigned int i = 1; i < this->alphabetLength; ++i)
        oStream << ", " << this->alphabet[i];

    // list start state & all accept states
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

    // print details about all states
    oStream << "Details about states:" << std::endl;
    for (unsigned int i = 0; i < this->numberOfStates; ++i) {
        oStream << "{" << std::endl
                << this->stateArray[i]
                << "}" << std::endl << std::endl;
    }

    return oStream;;
}

template<typename T>
void FiniteAutomaton<T>::changeStartState(unsigned int newStartState) noexcept(false) {
    // Reset startSFlag of the state
    this->stateArray[this->startState].setStartFlag(false);
    // Reset startState
    this->startState = 0;
    // Set up startState
    this->setStartState(newStartState);
}

template<typename T>
void FiniteAutomaton<T>::changeStartStateConsole() noexcept(false) {
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

/*! Class member functions - end here */
/*! Class object related, not member function - start here */

template<typename T>
std::ostream &operator<<(std::ostream &oStream, const FiniteAutomaton<T> &obj) {
    return obj.inst(oStream);
}


#endif //AUTOMATON_FINITEAUTOMATON_H
