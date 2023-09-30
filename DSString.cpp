#include "DSString.h"

#include "string.h"

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

// constructor to convert to a cstring
DSString::DSString(const char *input) {
    len = 0;                      // initalize length variable
    while (input[len] != '\0') {  // checks for end of c-string
        ++len;
    }  // gets the length of the string!

    data = new char[len + 1];
    strcpy(data, input);

    //data[len] = '\0';
}

// destructor
DSString::~DSString() {
    delete[] data;  // FREEEEE THE MEMORY needs brackets since array
}

// assignment operator = i wanna make a current object (this) look like another object reference
DSString &DSString::operator=(const DSString &rhs) {
    //(this == lhs == calling object for which we call this function)
    // dont have two objects pointing to the same location
    // is this stealing the pointer from rhs and assigning it to lhs or it actually making a copy of rhs

    // is this a deep copy or a shallow copy? of the object

    // DSString lhs = *this;

    if (data == rhs.data && len == rhs.len) {
        return *this;
    }
    // delete
    delete[] data;
    // allocate
    data = new char[rhs.len + 1];
    // copy
    strcpy(data, rhs.data);
    // point lhs to new string and clean up pointers
    // redirect pointer
    // fix length
    len = rhs.len;

    return *this;

    // check if vals are the same if they are just return the data in the object

    // else delete that data, allocate enough space for the new rhs, and copy the stuff in and then return the new data in the object
}

// CAN I USE STRCPY on Assignment operator, copy constructor, and constructor?

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

// HAVE TO IMPLEMENT NOT STRCPY

// string concatenation operator
DSString DSString::operator+(const DSString &rhs) const {
    // get length of the concatenated string

    size_t newLen = len + rhs.len;

    // allocate space for the new concatenated string

    char *newString = new char[newLen + 1];  // a pointer to  point to the first character of the newly allocated  char  c string array.
    // Assuming data, rhs.data, and newString are char pointers
    // and len is the length of data

    // Copy data to newString
    for (size_t i = 0; i < len; ++i) {
        newString[i] = data[i];
    }

    // Append rhs.data to newString
    for (size_t i = 0; i < rhs.len; ++i) {
        newString[len + i] = rhs.data[i];
    }

    // Null-terminate the new string
    newString[len + rhs.len] = '\0';

    DSString ADDEDString(newString);

    delete[] newString;

    return ADDEDString;
}

bool DSString::operator==(const DSString &rhs) const {
    // first check if lengths are equal
    if (len != rhs.len) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (data[i] != rhs.data[i]) {
            return false;  // if at any point do the cstring array values not match return false
        }
    }

    return true;
}

// less than operator
bool DSString::operator<(const DSString &rhs) const {
    int pos = 0;

    while (data[pos] != '\0' && rhs.data[pos] != '\0') {
        if (data[pos] > rhs.data[pos]) {
            return false;
        } else if (data[pos] < rhs.data[pos]) {
            return true;
        }
    }

    return len < rhs.len;
}

// returns a new substring from start of string to start+numchars of string
DSString DSString::substring(size_t start, size_t numChars) const {
    if ((start >= len) || (start + numChars > len)) {
        std::cerr << "substring request out of range of string" << std::endl
                  << std::endl;
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

// TAKE OUT STRCPY AND IMPLEMENT A LOOP
DSString DSString::toLower() const {
    size_t i = 0;

    char *cpyString = new char[len + 1];

    // copy each character
    while (data[i] != '\0') {
        cpyString[i] = data[i];
        ++i;
    }
    cpyString[i] = '\0';  // Null-terminate the new string

    i = 0;  // Reset index
    while (cpyString[i] != '\0') {
        if (cpyString[i] >= 'A' && cpyString[i] <= 'Z') {
            cpyString[i] += 32;
        }
        ++i;
    }

    DSString lowerCaseStr(cpyString);
    delete[] cpyString;

    return lowerCaseStr;

    // only if the values are in a certain range on the ascii table are they alphabetical and need to be lowered, anything else just needs to be re-inserted into the string the STA_MODE

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