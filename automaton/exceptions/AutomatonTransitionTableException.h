//
// Created by Tsvetomir Kolev on 10-Jun-20.
//

#ifndef AUTOMATON_AUTOMATONTRANSITIONTABLEEXCEPTION_H
#define AUTOMATON_AUTOMATONTRANSITIONTABLEEXCEPTION_H


#include <stdexcept>

class AutomatonTransitionTableException : public std::logic_error {
public:
    /// Constructor - parameters
    AutomatonTransitionTableException(const char *str);
};


#endif //AUTOMATON_AUTOMATONTRANSITIONTABLEEXCEPTION_H
