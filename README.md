# Bridges Problem for Scala Computing

## Overview

This repository contains code to solve the programming assignment given by Scala Computing. The goal is to move hikers across a series of bridges. At most two hikers can cross the bridge at once, and one of the hikers must carry a torch. If two hikers cross a bridge, they move at the pace of the slower hiker.

Information about hikers and bridges is provided in a YAML file. The code is written in C++.

## Files

This repository contains six files:
- **main.cpp** - Contains the C++ code that solves the problem
- **bridges.yaml** - Provides information about the hikers and bridges
- **Makefile** - Defines the steps needed to build the executable using GNU tools
- **yaml.h** - Header file containing declarations of [yaml-cpp](https://github.com/jbeder/yaml-cpp) routines
- **libyaml-cpp.a** - Static library containing [yaml-cpp](https://github.com/jbeder/yaml-cpp) routines
- **README.md** - Provides information about the repository

## Method

The `main` function in main.cpp performs eight steps:
1. Reads bridges.yaml and initializes a series of vectors containing hiker data (names and crossing speeds).
2. If there are N bridges, there will be N+1 vectors. The last vector always starts as empty.
3. The function iterates through the bridges and checks the number of hikers that need to cross.
4. Depending on the number of hikers, the function calls `moveForward` and `moveBack`.
5. `moveForward` moves one or two hikers forward across the bridge and updates the corresponding vectors.
6. `moveBack` always moves the fastest hiker back across the bridge.
7. As each hiker moves, the function updates the crossing time and prints the final sum.
8. The function makes sure that the initial vectors are all empty and that the final vector contains all the hikers.

## Output

Given the information in bridges.yaml, running the executable on my Ubuntu system produces the following output:

    Verified bridges.yaml exists, contains hikers/bridges sections

    Hikers A and B move forward across Bridge 0 in 2 min
    Hiker A moves back across Bridge 0 in 1 min
    Hikers D and C move forward across Bridge 0 in 10 min
    Hiker B moves back across Bridge 0 in 2 min
    Hikers A and B move forward across Bridge 0 in 2 min

    Hikers A and B move forward across Bridge 1 in 5 min
    Hiker A moves back across Bridge 1 in 2.5 min
    Hikers A and C move forward across Bridge 1 in 12.5 min
    Hiker A moves back across Bridge 1 in 2.5 min
    Hikers E and D move forward across Bridge 1 in 100 min
    Hiker B moves back across Bridge 1 in 5 min
    Hikers A and B move forward across Bridge 1 in 5 min

    Hikers A and B move forward across Bridge 2 in 3 min
    Hiker A moves back across Bridge 2 in 1.5 min
    Hikers A and F move forward across Bridge 2 in 6 min
    Hiker A moves back across Bridge 2 in 1.5 min
    Hikers A and C move forward across Bridge 2 in 7.5 min
    Hiker A moves back across Bridge 2 in 1.5 min
    Hikers A and G move forward across Bridge 2 in 10 min
    Hiker A moves back across Bridge 2 in 1.5 min
    Hikers E and D move forward across Bridge 2 in 60 min
    Hiker B moves back across Bridge 2 in 3 min
    Hikers A and B move forward across Bridge 2 in 3 min

    Total crossing time: 248 min
    Verified that all 7 hikers crossed final bridge
    
## Notes

- This application relies on [yaml-cpp](https://github.com/jbeder/yaml-cpp) to parse bridges.yaml.
- I'm not confident that the solution I've reached is the optimal one. Given more time, I am confident that I could improve the results.
- I'd originally intended to store hiker data in priority queues sorted by speed. But it's occasionally necessary to access slower hikers, so I used custom-sorted vectors instead.

