#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "generic-string.h"
#include "string-array.h"

using namespace std;
const int MAX_SEPARATION = 4;

class String : public GenericString {
private:
    char* my_string;
    int length;
public:
    String(const char* str = "");
    String(const String &str);
    ~String();
    char* get_string() const;
    int get_size() const;
    void set_string(const char* str);

    GenericString& operator=(const char *str);
    GenericString& trim();
    bool operator==(const GenericString &other) const;
    bool operator==(const char *other) const;
    int to_integer() const;
    String& as_string();
    const String& as_string() const;
    StringArray split(const char *delimiters) const;
};
GenericString* make_string(const char *str);

#endif