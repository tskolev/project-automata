//
// Created on 22-May-20.
//

#ifndef AUTOMATON_STATE_H
#define AUTOMATON_STATE_H


#include <iostream>
#include <cstring>
#include "../exception-handling/AutomatonException.h"

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

    // setters / getters
    void setName(char *newName); // throws exception of type (AutomatonException)
    void setStartFlag(bool newStartFlag);
    void setAcceptFlag(bool newAcceptFag);
    char *getName() const;
    bool getStartFlag() const;
    bool getAcceptFlag() const;

    /*!
     * assignment = operator overload
     * copy the information from the rhs obj to the calling object
     * @param rhs - right hand site object
     * @return - reference to the calling object
     */
    State &operator=(const State &rhs);

private:
    char *name;
    bool startFlag;
    bool acceptFlag;
};


#endif //AUTOMATON_STATE_H
