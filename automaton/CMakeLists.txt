cmake_minimum_required(VERSION 3.16)
project(automaton)

set(CMAKE_CXX_STANDARD 17)

add_executable(automaton main.cpp DeterminateFiniteAutomaton.cpp DeterminateFiniteAutomaton.h DeterminateFiniteAutomatonInt.cpp DeterminateFiniteAutomatonInt.h DeterminateFiniteAutomatonChar.cpp DeterminateFiniteAutomatonChar.h State.cpp State.h)