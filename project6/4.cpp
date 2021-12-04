#include <iostream>
using namespace std;

// returns the pointer to max of 2 ints
int *maxwell(int *a, int *b)
{
    if (*a > *b)
        return a;
    else
        return b;
}

// does nothing (swaps the addresses of 2 pointers within the scope of itself)
void swap1(int *a, int *b)
{
    int *temp = a;
    a = b;
    b = temp;
}

// swap the values stored in 2 pointers
void swap2(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int array[6] = {5, 3, 4, 17, 22, 19};

    int *ptr = maxwell(array, &array[2]); // max(5,4) = 5 so ptr = array[0]
    *ptr = -1;                            // array[0] = -1
    ptr += 2;                             // ptr = &array[2];
    ptr[1] = 9;                           // array[3] = 9
    *(array + 1) = 79;                    // array[1] = 79
    // array is now equal to {-1, 79, 4, 9, 22, 19}
    cout << &array[5] - ptr << endl; // &array[5] - &array[2] = 5-2 = 3

    swap1(&array[0], &array[1]); // swap1 changes nothing as shown in comments above
    swap2(array, &array[2]);     // the values in array[0] and array[2] are swapped
    // array is now equal to {4, 79, -1, 9, 22, 19}

    for (int i = 0; i < 6; i++)
        // prints 4 79 -1 9 22 19 (with newlines instead of spaces)
        cout << array[i] << endl; 
}
