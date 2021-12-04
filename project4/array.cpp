#include <iostream>
#include <string>
#include <cassert>

// find minimum of 2 variables
#define MIN(x, y) ((x) < (y) ? (x) : (y))

bool arraysEqual(const std::string a1[], const std::string a2[], int n);
bool separateTest(std::string a[], int n, std::string seperator, int index);
int reduplicate(std::string a[], int n);
int locate(const std::string a[], int n, std::string target);
int locationOfMax(const std::string a[], int n);
int circleLeft(std::string a[], int n, int pos);
int enumerateRuns(const std::string a[], int n);
int flip(std::string a[], int n);
int locateDifference(const std::string a1[], int n1, const std::string a2[], int n2);
int subsequence(const std::string a1[], int n1, const std::string a2[], int n2);
int locateAny(const std::string a1[], int n1, const std::string a2[], int n2);
int separate(std::string a[], int n, std::string separator);

int main()
{
    const std::string animals[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"};

    std::string animals_reduplicated[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"};
    std::string animals_reduplicated_out[9] = {"dogdog", "catcat", "frogfrog", "", "birdbird", "elephantelephant", "zebrazebra", "lionlion", "bearbear"};
    std::string animals_reduplicated_half[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"};
    std::string animals_reduplicated_half_out[9] = {"dogdog", "catcat", "frogfrog", "", "birdbird", "elephant", "zebra", "lion", "bear"};
    assert(reduplicate(animals_reduplicated, -1) == -1);                                                                                // invalid parameters
    assert(reduplicate(animals_reduplicated, 9) == 9 && arraysEqual(animals_reduplicated, animals_reduplicated_out, 9));                //reduplicate entire array
    assert(reduplicate(animals_reduplicated_half, 5) == 5 && arraysEqual(animals_reduplicated_half, animals_reduplicated_half_out, 9)); // reduplicate part of array

    assert(locate(animals, -1, "frog") == -1); // invalid parameters
    assert(locate(animals, 9, "frog") == 2);   // frog at index 2
    assert(locate(animals, 4, "bird") == -1);  // bird doesn't exist in shortened array
    assert(locate(animals, 4, "cat") == 1);    // cat at index 1 in shortened array

    assert(locationOfMax(animals, -1) == -1); // invalid parameters
    assert(locationOfMax(animals, 9) == 6);   // zebra is max at index 6
    assert(locationOfMax(animals, 6) == 2);   // frog is max at index 2 in shortened array

    std::string animals_circled[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"};
    std::string animals_circled_out0[9] = {"dog", "frog", "", "bird", "elephant", "zebra", "lion", "bear", "cat"}; // circle index 1
    std::string animals_circled_out1[9] = {"dog", "frog", "", "elephant", "zebra", "lion", "bear", "cat", "bird"}; // circle index 3
    std::string animals_circled_out2[9] = {"dog", "frog", "", "elephant", "zebra", "lion", "bear", "bird", "cat"}; // circle index 7
    std::string animals_circled_out3[9] = {"dog", "frog", "", "elephant", "zebra", "lion", "bear", "bird", "cat"}; // circle index 8
    std::string animals_circled_half[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"};
    std::string animals_circled_half_out[9] = {"cat", "frog", "", "bird", "dog", "elephant", "zebra", "lion", "bear"}; // circle index 0

    assert(circleLeft(animals_circled, -1, 1) == -1);                                                                      // invalid parameters
    assert(circleLeft(animals_circled, 5, 7) == -1);                                                                       // invalid parameters
    assert(circleLeft(animals_circled, 9, 1) == 1 && arraysEqual(animals_circled, animals_circled_out0, 9));               // circle index 1
    assert(circleLeft(animals_circled, 9, 3) == 3 && arraysEqual(animals_circled, animals_circled_out1, 9));               // circle index 3
    assert(circleLeft(animals_circled, 9, 7) == 7 && arraysEqual(animals_circled, animals_circled_out2, 9));               // circle index 7
    assert(circleLeft(animals_circled, 9, 8) == 8 && arraysEqual(animals_circled, animals_circled_out3, 9));               // circle index 8 (no change)
    assert(circleLeft(animals_circled_half, 5, 0) == 0 && arraysEqual(animals_circled_half, animals_circled_half_out, 9)); // circle shortened array at index 0

    std::string animals_enumerated0[9] = {"dog", "cat", "cat", "", "", "", "zebra", "zebra", "bear"};      // 5 sequences
    std::string animals_enumerated1[9] = {"dog", "cat", "frog", "", "lion", "", "zebra", "zebra", "bear"}; // 8 sequences
    assert(enumerateRuns(animals_enumerated0, -1) == -1);                                                  // invalid parameters
    assert(enumerateRuns(animals_enumerated0, 9) == 5);                                                    // 5 sequences
    assert(enumerateRuns(animals_enumerated0, 7) == 4);                                                    // 4 sequences in shortened array
    assert(enumerateRuns(animals_enumerated1, 9) == 8);                                                    // 8 sequences

    std::string animals_flipped0[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"};
    std::string animals_flipped0_out[9] = {"bear", "lion", "zebra", "elephant", "bird", "", "frog", "cat", "dog"};
    std::string animals_flipped1[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"};
    std::string animals_flipped1_out[9] = {"", "frog", "cat", "dog", "bird", "elephant", "zebra", "lion", "bear"};
    assert(flip(animals_flipped0, 9) == 9 && arraysEqual(animals_flipped0, animals_flipped0_out, 9)); // flip entire array
    assert(flip(animals_flipped1, 4) == 4 && arraysEqual(animals_flipped1, animals_flipped1_out, 9)); // flip shortened array

    std::string animals_difference0[9] = {"dog", "cat", "frog", "", "bird", "other", "other", "other", "other"};  // differs at index 5
    std::string animals_difference1[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"}; // doesnt differ
    assert(locateDifference(animals, -1, animals_difference0, 9) == -1);                                          //invalid parameters
    assert(locateDifference(animals, 9, animals_difference0, -1) == -1);                                          //invalid parameters
    assert(locateDifference(animals, 9, animals_difference0, 9) == 5);                                            // differs at index 5
    assert(locateDifference(animals, 9, animals_difference0, 3) == 3);                                            // differs at index 3 in shortened array
    assert(locateDifference(animals, 5, animals_difference1, 9) == 5);                                            // array runs out when first is shortened
    assert(locateDifference(animals, 9, animals_difference1, 9) == 9);                                            // array runs out when all are same elements

    std::string animals_subsequence0[4] = {"", "bird", "elephant", "zebra"}; // appears at index 3
    std::string animals_subsequence1[1] = {"zebra"};                         // appears at index 6
    std::string animals_subsequence2[2] = {"elephant", "bird"};              // doesnt appear
    std::string animals_subsequence3[0] = {};                                // empty array
    assert(subsequence(animals, 9, animals_subsequence0, 4) == 3);           //appears at index 3
    assert(subsequence(animals, 5, animals_subsequence0, 4) == -1);          // doesnt appear because first array shortened
    assert(subsequence(animals, 9, animals_subsequence1, 1) == 6);           //appears at index 6
    assert(subsequence(animals, 9, animals_subsequence2, 2) == -1);          // doesnt appear
    assert(subsequence(animals, 9, animals_subsequence3, 0) == 0);           // empty array

    std::string animals_locate_any0[6] = {"tiger", "snake", "lizard", "bird", "shark", "whale"}; //bird at 4 in original
    std::string animals_locate_any1[5] = {"tiger", "snake", "lizard", "shark", "whale"};         //bird at 4 in original
    assert(locateAny(animals, 9, animals_locate_any0, -1) == -1);                                // invalid parameters
    assert(locateAny(animals, -1, animals_locate_any0, 6) == -1);                                // invalid parameters
    assert(locateAny(animals, 9, animals_locate_any0, 6) == 4);                                  // bird in array0 is at index 4
    assert(locateAny(animals, 9, animals_locate_any0, 3) == -1);                                 // array0 shortened to contain no elements of animals array
    assert(locateAny(animals, 9, animals_locate_any1, 5) == -1);                                 // no elements of array1 in animals

    std::string animals_separate[9] = {"dog", "cat", "frog", "", "bird", "elephant", "zebra", "lion", "bear"};
    std::string letters_separate[8] = {"f", "b", "e", "a", "c", "j", "p", "r"};
    assert(separateTest(animals_separate, -1, "frog", -1));   // invalid parameters
    assert(separateTest(animals_separate, 5, "car", 2));      // (NOTE: shortened array must come first in tests)
    assert(separateTest(animals_separate, 9, "", 0));         // empty string is minimum string
    assert(separateTest(animals_separate, 9, "zzzzz", 9));    // zzzzz is greater than any string in animals
    assert(separateTest(animals_separate, 9, "elephant", 5)); //split around index 5
    assert(separateTest(letters_separate, 8, "d", 3));        //split around index 3
    return 0;
}
bool arraysEqual(const std::string a1[], const std::string a2[], int n)
{
    // loops over all elements of 2 arrays to check if they are equal
    for (int i = 0; i < n; i++)
    {
        if (a1[i] != a2[i])
        {
            return false;
        }
    }
    return true;
}
// test the separate function
bool separateTest(std::string a[], int n, std::string seperator, int index)
{
    if (separate(a, n, seperator) != index)
    {
        // if seperation index is wrong return false
        return false;
    }
    //ensure that everything before the index is less than seperator and everything after the index is greater than or equal to seperator
    for (int i = 0; i < n; i++)
    {
        if (i < index && a[i] >= seperator)
        {
            return false;
        }
        else if (i >= index && a[i] < seperator)
        {
            return false;
        }
    }
    return true;
}

int reduplicate(std::string a[], int n)
{
    // check for invalid parameters
    if (n < 0)
    {
        return -1;
    }
    // loop over all elements of array and append each element to itself
    for (int i = 0; i < n; i++)
    {
        a[i] += a[i];
    }
    return n;
}
int locate(const std::string a[], int n, std::string target)
{
    // check for invalid parameters
    if (n < 0)
    {
        return -1;
    }
    // set intial element of index to -1 (wont be changed if target not found)
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
        {
            // set index to i if target is found at i
            index = i;
            break;
        }
    }
    return index;
}
int locationOfMax(const std::string a[], int n)
{
    // check for invalid parameters
    if (n < 0)
    {
        return -1;
    }
    int index = -1;
    std::string max;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > max)
        {
            // if current element is greater than stored maximum, set max index to i and set new max to current element
            index = i;
            max = a[i];
        }
    }
    return index;
}
int circleLeft(std::string a[], int n, int pos)
{
    // check for invalid parameters
    if (n < 0 || pos >= n || pos < 0)
    {
        return -1;
    }
    // store the shifting element in a buffer
    std::string to_shift = a[pos];
    for (int i = pos; i < n - 1; i++)
    {
        //shift each element from index pos on over 1
        a[i] = a[i + 1];
    }
    // set final element to buffer
    a[n - 1] = to_shift;
    return pos;
}
int enumerateRuns(const std::string a[], int n)
{
    // check for invalid parameters
    if (n < 0)
    {
        return -1;
    }
    int count = 0;
    std::string prev;
    for (int i = 0; i < n; i++)
    {
        if (prev != a[i])
        {
            // if the previous element in the array is not equal to the current one then a sequence has been started
            count += 1;
        }
        // store previous element in a buffer
        prev = a[i];
    }
    return count;
}
int flip(std::string a[], int n)
{
    // check for invalid parameters
    if (n < 0)
    {
        return -1;
    }
    // loop over half of array
    for (int i = 0; i < n / 2; i++)
    {
        // swap current element and element at opposite end of array
        std::string buf = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = buf;
    }
    return n;
}
int locateDifference(const std::string a1[], int n1, const std::string a2[], int n2)
{
    // check for invalid parameters
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }
    int i = 0;
    // loop until one of the arrays is completed
    for (; i < MIN(n1, n2); i++)
    {
        if (a1[i] != a2[i])
        {
            // break when the arrays differ at the given index
            break;
        }
    }
    return i;
}
int subsequence(const std::string a1[], int n1, const std::string a2[], int n2)
{
    // check for invalid parameters
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }
    // if second array is empty return 0 (as per spec)
    else if (n2 == 0)
    {
        return 0;
    }
    int sub_index = 0; // current index within subsequence
    int min_index = 0; // starting index of subsequence
    for (int i = 0; i < n1; i++)
    {
        if (a1[i] == a2[sub_index])
        {
            // if a1 matches subsequence so far, keep progressing
            sub_index += 1;
        }
        else
        {

            //if a1 does not match subsequence, try start looking at next index
            // increase min index by 1 and reset sub index back to 0
            min_index = i + 1;
            sub_index = 0;
        }
        if (sub_index == n2)
        {
            // if sub index has progressed through all of a2, return the index of the start of the subsequence
            return min_index;
        }
    }
    return -1;
}
int locateAny(const std::string a1[], int n1, const std::string a2[], int n2)
{
    // check for invalid parameters
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }
    // for each element in a1, compare it against all elements of a2; return i if there is a match
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (a1[i] == a2[j])
            {
                return i;
            }
        }
    }
    return -1;
}

int separate(std::string a[], int n, std::string separator)
{
    // check for invalid parameters
    if (n < 0)
    {
        return -1;
    }
    int left = 0;         // index of next unchecked string
    int right = n - 1;    // past this index, all elements have already been checked
    while (left <= right) // while we havent checked everything yet
    {
        if (a[left] >= separator)
        {
            // if left is not less than seperator, circle the current element left and decrease right index
            circleLeft(a, n, left);
            right--;
        }
        else
        {
            // if right is less than seperator, check the next string
            left++;
        }
    }
    return left;
}
