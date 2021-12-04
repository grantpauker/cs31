// The next line avoids a VC++ issue; it's harmless for Xcode and g31
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE track FUNCTION
int track(const int changes[], int n, int &highPrice){
    if(n <= 0){
        return -3;
    }  
    int price = 1000;
    int max = price;
    for(int i = 0; i < n; i++){
        if(changes[i] < -500 || changes[i] > 500){
            return -2;
        }
        price += changes[i];
        if(price > max){
            max = price;
        }
        if(price < 0){
            return -1;
        }
    }
    highPrice = max;
    return price;
}
// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE track FUNCTION

int main()
{
    const int chg1[10] = {40, 17, 0, -25, 30, -160, 63, -5, -2, -4};
    int m = 99999;
    assert(track(chg1, 10, m) == 954);
    assert(m == 1062);

    const int chg2[7] = {0, 80, -400, -300, -400, 100, 100};
    m = 99999;
    assert(track(chg2, 7, m) == -1);
    assert(m == 99999);

    const int chg3[3] = {300, 600, 300};
    m = 99999;
    assert(track(chg3, 3, m) == -2);
    assert(m == 99999);

    cout << "All tests succeeded" << endl;
}
