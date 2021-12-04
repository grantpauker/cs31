#include <iostream>
void computeCube(int n, int *ncubed)
{
  *ncubed = n * n * n;
}

/* This code did not work as ptr was not intialized. In order to fix this,
one would either have to create an integer and point ptr to it,
or dynamically allocate memory using malloc.
*/
int main()
{
  int tmp;
  int *ptr = &tmp;
  /*
  int *ptr = (int *)malloc(sizeof(int));
  */
  computeCube(5, ptr);
  std::cout << "Five cubed is " << *ptr << std::endl;
}
