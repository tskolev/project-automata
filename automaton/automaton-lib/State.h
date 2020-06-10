//
// Created on 22-May-20.
//

#ifndef AUTOMATON_STATE_H
#define AUTOMATON_STATE_H


#include <iostream>
#include <cstring>

class State {
public:
    /// Constructor - default
    State();
    /// Constructor - parameters
    State(const char *name);
    /// Constructor - copy
    State(const State &obj);
    /// Destructor
    ~State();

    /// Setters
    void setName(char *newName);
    void setStartFlag(bool newStartFlag);
    void setAcceptFlag(bool newAcceptFag);
    /// Getters
    char *getName() const;
    bool getStartFlag() const;
    bool getAcceptFlag() const;

    /*!
     * Inserts data in a given stream by parameter.
     * The inserted data is Object data fields.
     * @param oStream object of std::ostream
     * @return reference to an stream object of std::ostream
     */
    std::ostream &ins(std::ostream &oStream) const;

    /*!
     * assignment = operator overload
     * copy the information from the rhs obj to the calling object(lhs).
     * @param rhs - right hand site object
     * @return - reference to the calling object
     */
    State &operator=(const State &rhs);

private:
    char *name;
    bool startFlag;
    bool acceptFlag;
};

/*!
 * Overload of operator "<<".
 * Inserts data in a given stream by parameter through an object method.
 * @param oStream reference to an stream object of class std::ostream
 * @param obj const reference to an Object of class State
 * @return reference to an object of class std::ostream
 */
std::ostream &operator<<(std::ostream &oStream, const State &obj);


#endif //AUTOMATON_STATE_H
