//
// Created on 10-Jun-20.
//

#ifndef AUTOMATON_AUTOMATONALPHABETEXCEPTION_H
#define AUTOMATON_AUTOMATONALPHABETEXCEPTION_H


#include <stdexcept>

class AutomatonAlphabetException : public std::logic_error {
public:
    /// Constructor - parameters
    AutomatonAlphabetException(const char *str);
};


#endif //AUTOMATON_AUTOMATONALPHABETEXCEPTION_H
