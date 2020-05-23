cmake_minimum_required(VERSION 3.16)
project(automaton)

set(CMAKE_CXX_STANDARD 17)

add_executable(automaton main.cpp base/DeterminateFiniteAutomaton.cpp base/DeterminateFiniteAutomaton.h base/DeterminateFiniteAutomatonInt.cpp base/DeterminateFiniteAutomatonInt.h base/DeterminateFiniteAutomatonChar.cpp base/DeterminateFiniteAutomatonChar.h automaton-lib/State.cpp automaton-lib/State.h exception-handling/AutomatonException.cpp exception-handling/AutomatonException.h)