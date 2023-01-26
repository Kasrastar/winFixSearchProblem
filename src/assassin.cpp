#include <windows.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <array>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

std::string exec( const char* cmd) {

    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char** argv){

    std::string tempString = "TASKKILL /F /IM cmd.exe /T";
    std::string tempFile = "cmd";

    if ( argc != 2 ){
        SetConsoleTextAttribute(console,4);
        std::cout << "Wrong Usage Check The Documentation.";
        SetConsoleTextAttribute(console,7);
        exit(1);
    }else {

        std::string cmd = tempString.replace(
            tempString.find(tempFile),
            tempFile.length(),
            argv[1]
        );

        std::string result = exec(cmd.c_str());
        if ( result.find("SUCCESS") != std::string::npos ){
            SetConsoleTextAttribute(console,2);
            std::cout << "now enjoy of using win11 Search ;)";
            SetConsoleTextAttribute(console,7);
        }
    }

    return 0;
}