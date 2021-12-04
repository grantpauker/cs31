#include <iostream>
#include <string>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE wedge FUNCTION

void wedge(std::string s){
    for(size_t i = 0; i < s.size(); i++){
        for(int j = 0; j < s.size()-1-i; j++){
            std::cout << '@';
        }
        std::cout << (s[i] == '@' ? '#' : s[i]) << std::endl;
    }
    return;
}


// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE wedge FUNCTION

int main()
{
    cout << "======= Test 1:" << endl;
    wedge("Wow!");
    cout << "======= Test 2:" << endl;
    wedge("CS@UCLA #1");
    wedge("@@@");
}
