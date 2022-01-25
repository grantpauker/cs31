#include <iostream>
#include <cassert>
using namespace std;

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE END OF THE analyze FUNCTION
int *analyze(int *first, int *last, int *numNegatives){
    int negatives = 0;
    int *max = first;

    for(;first <= last; first++){
        if(*first >= *max){
            max = first;
        }
        if(*first < 0){
            negatives++;
        }
    }

    if(numNegatives != nullptr){
        *numNegatives = negatives;
    }

    return max;
}
// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AT THE START OF THE analyze FUNCTION

int main()
{
    int a[9] = { 17, -5, 42, -12, -40, 27, 0, 42, 37 };
    int negatives = 999;
    assert(analyze(a, a+3, &negatives) == a+2  &&  negatives == 2);
    assert(analyze(a+5, a+8, &negatives) == a+7  &&  negatives == 0);
    negatives = 888;
    assert(analyze(a, a+3, nullptr) == a+2  &&  negatives == 888);
    assert(analyze(a, a+8, &negatives) == a+7  &&  negatives == 3);
    assert(analyze(a+1, a+1, &negatives) == a+1  &&  negatives == 1);
    assert(analyze(a, a, &negatives) == a  &&  negatives == 0);

    cout << "All tests succeeded" << endl;    
}