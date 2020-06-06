//
// Created on 05-Jun-20.
//

#ifndef AUTOMATON_AUTOMATONSTATEEXCEPTION_H
#define AUTOMATON_AUTOMATONSTATEEXCEPTION_H


#include <stdexcept>

class AutomatonStateException : public std::logic_error {
public:
    // Constructor - parameters
    AutomatonStateException(const char *str);
};


#endif //AUTOMATON_AUTOMATONSTATEEXCEPTION_H
