@echo off
if NOT EXIST bin mkdir bin
g++ src/main.cpp -o bin/run
