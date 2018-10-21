if ! [ -d bin ] ; then
    mkdir bin
fi

g++ src/main.cpp -o bin/run

