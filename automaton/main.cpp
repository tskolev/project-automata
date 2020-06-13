#include <sstream>
#include "automaton-lib/State.h"
#include "app/FiniteAutomaton.h"
#include "app/DeterministicFiniteAutomaton.h"

using namespace std;

int main() {

//     testing
//    State states[5];
//    states[0] = State("q0");
//    states[1] = State("q1");
//    states[2] = State("q2");
//    states[3] = State("q3");
//    states[4] = State("q4");
//
//    State states2[6];
//    states2[0] = State("q0");
//    states2[1] = State("q1");
//    states2[2] = State("q2");
//    states2[3] = State("q3");
//    states2[4] = State("q4");
//    states2[5] = State("q5");
//
//    unsigned accept[2] = {0, 1};
//    unsigned accept2[2] = {3, 4};
//
//    int alphabet1[2]{0, 1};
//    char alphabet2[5]{'a', 'b', 'c', 'd', 'e'};

//    DeterminateFiniteAutomaton1 automaton(states, 5, 0, accept, 2);
//    cout << automaton << endl;
//
//    automaton.setAcceptStatesArray(accept2, 2);
//    cout << automaton << endl;
//
//    automaton.setStateArray(states2, 6);
//    automaton.setStartState(0);
//    automaton.changeStartStateConsole();
//    cout << automaton << endl;


//    FiniteAutomaton<char> obj1(states, 5, alphabet2, 5, 0, accept2, 2);

//    unsigned **ptr = nullptr;
//    DeterministicFiniteAutomaton<int> obj1(states, 5, alphabet1, 5, 0, accept2, 2, ptr);
//
//    cout << obj1 << endl;

    DeterministicFiniteAutomaton<int> obj;
//    obj.configureStateArrayConsole();
    obj.configureAlphabetConsole();
    obj.configureTransitionTableConsole();
    obj.configureStartStateConsole();
    obj.configureAcceptStatesConsole();

//    DeterministicFiniteAutomaton<char> obj13;

//    automaton.changeStartStateConsole();

//    DeterminateFiniteAutomaton1 a2;
//    a2.setStartState(2);

    return 0;
}
