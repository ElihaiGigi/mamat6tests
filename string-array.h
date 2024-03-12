#ifndef STRING_ARRAY_H
#define STRING_ARRAY_H
#include "generic-string.h"
#include "string.h"

class StringArray {
private:
    GenericString **str_arr;
public:
    StringArray();
    StringArray(const StringArray &str_arr);
    ~StringArray();
    GenericString* get_element(int index) const;
    void set_element( GenericString* str, int index);
};
#endif