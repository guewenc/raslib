import os

print("Raslib project : https://github.com/antoninhrlt/raslib")
print("                     _   _   _      ")
print(" _ __   __ _   ___  | | (_) | |__   ")
print("| '__| / _\`| / __| | | | | | '_ \  ")
print("| |   | (_| | \__ \ | | | | | |_) | ")
print("|_|    \__,_| |___/ |_| |_| |_.__/  ")
print("                                    ")
print("> Compilation ...")

if os.system("g++ src/main.cpp include/raslib/*.cpp include/raslib/gpio/*.cpp include/raslib/motor/*.cpp include/raslib/socket/*.cpp -o bin/prog.com -I include -std=c++17") == 0:
    print("> Compilation successful")
    print("> Running ...")
    os.system("./bin/prog.com")
else:
    print("> Compilation failed")
