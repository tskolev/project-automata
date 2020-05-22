//
// Created by Tsvetomir Kolev on 22-May-20.
//

#ifndef AUTOMATON_STATE_H
#define AUTOMATON_STATE_H


#include <cstring>

class State {
public:
    // constructor - default
    State();
    // constructor - parameters
    State(const char *name);
    // constructor - copy
    State(const State &obj);
    // destructor
    ~State();

private:
    char *name;
};


#endif //AUTOMATON_STATE_H
