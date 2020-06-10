#include "automaton-lib/State.h"
#include "base/DeterminateFiniteAutomaton.h"
#include "base/DeterminateFiniteAutomatonChar.h"
#include <iostream>

using namespace std;

int main() {

    // testing
    State states[5];
    states[0] = State("q0");
    states[1] = State("q1");
    states[2] = State("q2");
    states[3] = State("q3");
    states[4] = State("q4");

    State states2[6];
    states2[0] = State("q0");
    states2[1] = State("q1");
    states2[2] = State("q2");
    states2[3] = State("q3");
    states2[4] = State("q4");
    states2[5] = State("q5");

    unsigned accept[2] = {0, 1};
    unsigned accept2[2] = {3, 4};

    DeterminateFiniteAutomaton automaton(states, 5, 0, accept, 2);
    cout << automaton << endl;

    automaton.setAcceptStatesArray(accept2, 2);
    cout << automaton << endl;

    automaton.setStateArray(states2, 6);
    automaton.setStartState(0);
    automaton.changeStartStateConsole();
    cout << automaton << endl;


//    automaton.changeStartStateConsole();

//    DeterminateFiniteAutomaton a2;
//    a2.setStartState(2);

    return 0;
}
