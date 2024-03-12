#ifndef IP_H
#define IP_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "string-array.h"
#include "generic-field.h"
#include "string.h"

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
    StringArray* get_ip() const;
    bool match(const GenericString &packet) const;
};
//given two ip as string array, its check the law according to mask
bool check_match(StringArray *ip1, StringArray *ip2 , int mask);

#endif

