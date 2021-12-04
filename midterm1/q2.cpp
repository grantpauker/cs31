#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    std::string str;
    std::getline(std::cin, str);
    int count = 0;
    for(int i = 0; i < (str.size()-1); i++){
        if(isupper(str[i]) && islower(str[i+1])){
            count++;
            i++;
        }
    }
    std::cout << count << std::endl;
    return 0;
}