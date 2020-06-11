cmake_minimum_required(VERSION 3.16)
project(automaton)

set(CMAKE_CXX_STANDARD 17)

add_executable(automaton main.cpp automaton-lib/State.cpp automaton-lib/State.h exceptions/AutomatonException.cpp exceptions/AutomatonException.h exceptions/AutomatonStateException.cpp exceptions/AutomatonStateException.h exceptions/AutomatonAlphabetException.cpp exceptions/AutomatonAlphabetException.h exceptions/AutomatonTransitionTableException.cpp exceptions/AutomatonTransitionTableException.h app/FiniteAutomaton.h app/DeterministicFiniteAutomaton.h app/NondeterministicFiniteAutomaton.h)