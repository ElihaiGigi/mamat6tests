

#ifndef PORT_H
#define PORT_H
#include <iostream>
#include <cstring>
#include "generic-field.h"
#include "string-array.h"
#include "string.h"
using namespace std;

class port: public GenericField{
private:
    int low_port;
    int high_port;
    bool is_src;
    bool is_dst;
public:
    port(const char* rule);
    bool match(const GenericString &packet) const;
    int get_low_port() const;
    int get_high_port() const;
    ~port();

};


#endif //PORT_H
