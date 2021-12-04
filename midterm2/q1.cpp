#include <iostream>
#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;
int hide(char* s, char ch){
    int count = 0;
    for(int i = 0; s[i] != '\0'; i++){
        if(!isdigit(s[i]) && !isupper(s[i])){
            s[i] = ch;
            count++;
        }
    }
    return count;
}
int main()
{
    char text[100] = "I'm UPSET that on Nov. 16th, 2021, my 2 brand-new BMW M850is were stolen!!";
    assert(hide(text, '*') == 53);
    assert(strcmp(text, "I***UPSET*********N****16****2021*****2***********BMW*M850****************") == 0);

    strcpy(text, "#%@!");
    assert(hide(text, 'x') == 4);
    assert(strcmp(text, "xxxx") == 0);

    strcpy(text, "CS31");
    assert(hide(text, '?') == 0);
    assert(strcmp(text, "CS31") == 0);

    strcpy(text, "");
    assert(hide(text, '-') == 0);
    assert(strcmp(text, "") == 0);

    cout << "All tests succeeded" << endl;
}