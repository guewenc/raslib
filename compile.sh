#!/bin/bash
RED="\033[31m"
RED_BG="\033[41m"
GREEN="\033[32m"
RESET="\033[0m"

function echoclr() 
{ 
    echo -e "${GREEN}${1}${RESET}" 
}
function echoerr() { 
    echo -e "${RED_BG}${1}${RESET}" >&2 
}

if [[ -z $1 ]]
then
    echoerr "Select a directory ! (example : \"bash compile.sh /home/pi/my_project)\"" 
else
    echoclr "Selected Directory : ${1}"
    cd $1
    echoclr "Compilation (g++) . . ."

    if g++ src/main.cpp include/raslib/*.cpp -o bin/prog.com -I include -std=c++17
    then
        echoclr "Run program (bin/prog.com) . . ."
        sudo ./bin/prog.com
        echoclr "Return : ${?}"
    else
        echoerr "Compilation failed"
    fi
fi

# EOF