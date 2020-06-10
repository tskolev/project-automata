//
// Created on 22-May-20.
//

#ifndef AUTOMATON_AUTOMATONEXCEPTION_H
#define AUTOMATON_AUTOMATONEXCEPTION_H


#include <stdexcept>

class AutomatonException : public std::logic_error {
public:
    /// Constructor - parameters
    AutomatonException(const char *str);
};


#endif //AUTOMATON_AUTOMATONEXCEPTION_H
