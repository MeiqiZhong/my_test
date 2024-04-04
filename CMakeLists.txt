cmake_minimum_required(VERSION 3.16)
project(testProect)

set(CMAKE_CXX_STANDARD 14)

add_executable(testProect main.cpp Carte.cpp Carte.h Jeu.cpp Jeu.h BankCarte.cpp BankCarte.h Jeueur.cpp Jeueur.h Controleur.cpp Controleur.h AI.cpp AI.h)