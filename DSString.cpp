#include "DSString.h"

/*
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project.
 *
 * Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions
 * from <string.h> or <cstring> other than for conversion from a c-sting.
 */

// default constructor needs to initialize a cstring
DSString::DSString() {
    data = new char[1];  // DYNAMICALLY ALLOCATING memory for the \0 character as a default c-string
    data[0] = '\0';
    len = 0;
}

// constructor a DSString from a cstring
DSString::DSString(const char *input) {
    len = 0;
    while (input[len] != '\0') {
        ++len;
    }

    data = new char[len + 1];

    // not  strcpy
    for (size_t i = 0; i <= len; ++i) {
        data[i] = input[i];
    }

    data[len] = '\0';

}

// destructor
DSString::~DSString() {
    delete[] data;  // FREEEEE THE MEMORY needs brackets since array
}

DSString &DSString::operator=(const DSString &rhs) {
    //(this == lhs == calling object for which we call this function)
    // dont have two objects pointing to the same location
    // is this stealing the pointer from rhs and assigning it to lhs or it actually making a copy of rhs

    // DSString lhs = *this;
    if (data == rhs.data && len == rhs.len) {
        return *this;
    }
    //delete
    delete[] data;
    //alocate
    data = new char[rhs.len + 1];
    // point lhs to new string and clean up pointers
    // redirect pointer
    // fix length
    len = rhs.len;

    // copy
    for (size_t i = 0; i <= len; ++i) {
        data[i] = rhs.data[i];
    }

    data[len] = '\0';

    return *this;
     // check if vals are the same if they are just return the data in the object

    // else delete that data, allocate enough space for the new rhs, and copy the stuff in and then return the new data in the object
}

// copy constructor
DSString::DSString(const DSString &rhs) {
    len = rhs.len;
    data = new char[len + 1];  // +1 for the null-terminator

    // copy each character
    for (size_t i = 0; i < len; ++i) {
        data[i] = rhs.data[i];
    }

    // add null-terminator
    data[len] = '\0';
}


// returns pointer to start of string
char *DSString::c_str() const {
    return data;
}

// returns length
size_t DSString::length() const {
    return len;
}

void DSString::setLength(size_t newLength) {
    len = newLength;
}

// index string operator
char &DSString::operator[](size_t i) {
    if (i >= len) { 
        std::cerr << "DSString index out of range" << std::endl
                  << std::endl;
    }

    return data[i];
}

// string concatenation operator
DSString DSString::operator+(const DSString &rhs) const {
    // get length of the concatenated string

    size_t newLen = len + rhs.len;

    // allocate space for the new concatenated string

    char *newString = new char[newLen + 1];  // a pointer to  point to the first character of the newly allocated  char  c string array.

    // copy data to newString
    for (size_t i = 0; i < len; ++i) {
        newString[i] = data[i];
    }

    // add rhs.data to newString
    for (size_t i = 0; i < rhs.len; ++i) {
        newString[len + i] = rhs.data[i];
    }

    // nullterminate the new string
    newString[len + rhs.len] = '\0';

    DSString ADDEDString(newString);

    delete[] newString;

    return ADDEDString;
}

// true if both DSString objects have the same length and contain the same characters.
// otherwise, returns false.
bool DSString::operator==(const DSString &rhs) const {
    // check if the lengths of both strings are equal, if not they cant be equal
    if (len != rhs.len) {
        return false;
    }

    if(data == rhs.data) {
        return true;
    }

    // iterate through each character in the string to check for equality.
    for (size_t i = 0; i < len; i++) {
        // if a character is different, return false.
        if (data[i] != rhs.data[i]) {
            return false;
        }
    }

    // else gone through all checks and strings are equal
    return true;
}


//less-than operator
// returns true if the lhs is lexicographically smaller than the rhs object. (lhs < rhs) 
bool DSString::operator<(const DSString &rhs) const {
    int pos = 0;  // position variable to start at the beginning of the strings.
    int length = 0;

    // iterate through each character in both strings until reaching the end of either string.
    if(rhs.len < len) 
    {
        length = rhs.len;
    }
    else 
    {
        length = len;
    }
    
    for(int i = 0; i < length; i++) 
    {
        //never see null terminator
        if (data[i] > rhs.data[i]) {
            return false;
        } 
        // if a character in lhs is smaller than the corresponding character in rhs, lhs is smaller.
        else if (data[i] < rhs.data[i]) {
            return true;
        }
    }

    if(rhs.len <= len){
        return false;
    }
    else {
        return true;
    }

/*
    while (data[pos] != '\0' && rhs.data[pos] != '\0') {
        // lexicographical rules = if a character in lhs is greater than the corresponding character in rhs, lhs cannot be smaller.
        if (data[pos] > rhs.data[pos]) {
            return false;
        } 
        // if a character in lhs is smaller than the corresponding character in rhs, lhs is smaller.
        else if (data[pos] < rhs.data[pos]) {
            return true;
        }
        //increment
        pos++;
    }
*/
    // if loop completes without returning, compare the lengths of the strings.
    // return the shorter (smaller) string
}


// returns a new substring from start of string to start+numchars of string
DSString DSString::substring(size_t start, size_t numChars) const {
    if ((start >= len) || (start + numChars > len)) {
        std::cerr << "substring request out of range of string" << std::endl << std::endl;
        return DSString("");  // exception
    }

    char *subString = new char[numChars + 1];  // allocate space for new char array

    for (size_t i = 0; i < numChars; ++i) {
        subString[i] = data[start + i];
    }

    subString[numChars] = '\0';  // starts at 0

    DSString result(subString);

    delete[] subString;

    return result;
}

DSString DSString::toLower() const {
    size_t i = 0;

    char *cpyString = new char[len + 1];

    cpyString[len] = '\0';  // Null-terminate the new string

    i = 0;  // Reset index
    
    while (data[i] != '\0') 
    {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            cpyString[i] = data[i] + 32;
        }
        else {
            cpyString[i] = data[i];
        }

        ++i;
    }

    DSString lowerCaseStr(cpyString);
    delete[] cpyString;

    return lowerCaseStr;

    // look for range of ascii values as you go through the string
    // if falls in range -32 from that range of each character
    // and somehow reinsert that into the string, maybe call the [] overloader or whatever we used

    // return the lower case string
}

std::ostream &operator<<(std::ostream &out, const DSString &str) {
    // TODO: insert return statement here
    out << str.data;
    return out;
}