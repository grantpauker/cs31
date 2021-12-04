// This function searches through str for the character chr.
// If the chr is found, it returns a pointer into str where
// the character was first found, otherwise nullptr (not found).

#include <iostream>
const char *findTheChar(const char *str, char chr)
{
    for (; *str != 0; str++)
        if (*str == chr)
            return str;
    return nullptr;
}
int main()
{
    const char *str = "abcdeghijkl";
    const char *c = findTheChar(str, 'h');
    std::cout << c << std::endl;
}
