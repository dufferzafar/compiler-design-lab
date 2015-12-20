#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

int main(){
    std::string input = "abc,def,ghi";
    std::istringstream ss(input);
    std::string token;

    while(std::getline(ss, token, ',')) {
        std::cout << token << '\n';
    }
}
