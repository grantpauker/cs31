#include <iostream>
void removeS(char *str){
    char *parsed = str;
    for(; *str != 0; str++){
        if(tolower(*str) != 's'){
            *parsed = *str;
            parsed++;
        }
    }
    *parsed = '\0';
}
int main()
{
    char msg[50] = "She'll be a massless princess.";
    removeS(msg);
    std::cout << msg; // prints he'll be a male prince.
}