CS 210 PROJECT TWO - AIRGEAD BANKING INVESTMENT APPLICATION
============================================================

Author: Ziyan Noorani
Course: CS 210

FILES INCLUDED
--------------
  main.cpp        - Driver / entry point. Handles input, validation, and
                    instantiates the Investment object. Kept minimal per
                    the Airgead Banking Standards.
  Investment.h    - Class prototype with #define include guard.
  Investment.cpp  - Class implementation (compound-interest math + reports).
  Pseudocode.docx - Step-by-step program logic plan (separate deliverable).
  README.txt      - This file.

HOW TO BUILD
------------
Visual Studio:
  Create a new C++ Console project, add main.cpp, Investment.h, and
  Investment.cpp to the project, then Build and Run.

Command line (g++, C++14 or later):
  g++ -std=c++14 -Wall -Wextra -o AirgeadBanking main.cpp Investment.cpp
  ./AirgeadBanking

DESIGN NOTES (mapped to the rubric)
-----------------------------------
  - Object-oriented: All investment data and behavior live in the
    Investment class. main() is only a driver.
  - Input validation: Non-numeric input, negative values, and zero
    values are rejected with clear messages and re-prompts. The monthly
    deposit is allowed to be 0.
  - User interface: Console collects all four required inputs (initial
    investment, monthly deposit, annual interest, number of years) and
    echoes them back.
  - Charts: Two tables print year-end balance and year-end earned
    interest - one WITHOUT additional monthly deposits and one WITH
    them. Output matches the project's sample values exactly.
  - Standards: #define header guard, m_ prefix for member data, t_
    prefix for parameters, camelCase functions/variables, in-line
    comments, try/catch (no assert()), header/CPP separation, minimal
    main().
