
#include <iostream>
/*This program is assigning ptr to an array that is local to the getPtrToArray function.
When getPtrToArray is finished being executing, all variables within it cease to exist,
so the array returned is simply an array that no longer exists. This means that ptr 
just refers to random values on the stack.*/
int *nochange(int *p)
{
    return p;
}

int *getPtrToArray(int &m)
{
    int anArray[100];
    for (int j = 0; j < 100; j++)
        anArray[j] = 100 - j;
    m = 100;
    return nochange(anArray);
}

void f()
{
    int junk[100];
    for (int k = 0; k < 100; k++)
        junk[k] = 123400000 + k;
    junk[50]++;
}

int main()
{
    // 100 99 98 3 2 1
    int n;
    int *ptr = getPtrToArray(n);
    //f();
    for (int i = 0; i < 3; i++)
        std::cout << ptr[i] << ' ';
    for (int i = n - 3; i < n; i++)
        std::cout << ptr[i] << ' ';
    std::cout << std::endl;
}
