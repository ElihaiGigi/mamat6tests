#ifndef IP_H
#define IP_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "string-array.h"
#include "generic-field.h"
#include "string.h"

const int INT_SIZE = 32;
const int CHAR_SIZE = 8;
const int FIRST_5_CHARS = 5;
using namespace std;

typedef enum {dst,src} ip_type;

class ip : public GenericField {
private:
    int mask;
    ip_type ds_type;
    StringArray *ip_arr;
public:
    ip(const char* str = "");
    ~ip();
    int get_mask() const;
    ip_type get_ds_type() const;
    bool match(const GenericString &packet) const;
};
//given two ip as string array, its check the law according to mask
bool check_match(StringArray *ip1, StringArray *ip2 , int mask);

#endif

