#!/bin/bash
g++ -std=c++17 -Iinclude fusegame.cpp -lSDL2 libfuse.a -o fusegame 