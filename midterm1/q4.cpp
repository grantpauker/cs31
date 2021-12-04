#include <iostream>
#include <string>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE box FUNCTION

void box(std::string s, int interval){
    for(int i = 0; i < interval; i++){
        for(int j = i; j < s.size(); j+=interval){
            std::cout << s[j];
        }
        std::cout << std::endl;
    }
    return;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE box FUNCTION

int main()
{
    std::cout << "======= Test 1:" << std::endl;
    box("abcdef @3xwvutsrq", 5);
    std::cout << "======= Test 2:" << std::endl;
    box("#", 3);
    std::cout << "======= Test 3:" << std::endl;
    box("abcdefghijklmnopqrstuvwxyz", 4);
}
