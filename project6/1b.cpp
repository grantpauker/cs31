#include <iostream>
/* this function didn't work because the mutation of the pointer
was only valid within the scope of findMax. in order to actually
change what address in memory the pointer points to, findMax
would either have to take in int **pToMax or just allow it to
change by reference using int *&pToMax.
*/
void findMax(int arr[], int n, int *&pToMax)
{
  if (n <= 0)
    return; // no items, no maximum!

  pToMax = arr;

  for (int i = 1; i < n; i++)
  {
    if (arr[i] > *pToMax)
      pToMax = arr + i;
  }

}
  int main(){
    int nums[4] = {5, 3, 15, 6};
    int *ptr = &nums[0];

    findMax(nums, 4, ptr);
    std::cout << "The maximum is at address " << ptr << std::endl;
    std::cout << "It's at position " << ptr - nums << std::endl;
    std::cout << "Its value is " << *ptr << std::endl;
  }