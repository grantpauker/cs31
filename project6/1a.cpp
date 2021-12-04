#include <iostream>
int main()
{
  int arr[3] = {5, 10, 15};
  int *ptr = arr;

  *ptr = 30;       // set arr[0] to 30
  *(ptr + 1) = 20; // set arr[1] to 20
  ptr += 2;
  ptr[0] = 10; // set arr[2] to 10

  int *tmp = arr;
  while (ptr >= tmp)
  {
    std::cout << *tmp << std::endl; // print values
    tmp++;
  }
}
