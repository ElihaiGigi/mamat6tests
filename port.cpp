
#include "port.h"
const int LEN_TO_SEARCH = 8;

port::port(const char* in) {
    String in_str = String(in);
    in_str.trim(); // " dst-port = 22-56 "
    if(*in_str.get_string() == 'd'){
        this->is_dst = true;
        this->is_src = false;
    }
    else {
        this->is_dst = false;
        this->is_src = true;
    }
    // "dst-port = 22-56"
    StringArray rule_str = in_str.split("="); // elem1 = " 22-56"
    GenericString *tmp_port = rule_str.get_element(1);
    tmp_port->trim(); // tmp_port = "22-56"
    StringArray port_arr = tmp_port->split("-"); // elem0 = "22", elem1 = "56"
    this->low_port = port_arr.get_element(0)->as_string().to_integer();
    this->high_port = port_arr.get_element(1)->as_string().to_integer();
}

port::~port() {
}

int port::get_low_port() const{
    return this->low_port;
}

int port::get_high_port() const{
    return this->high_port;
}

bool port::match(const GenericString &packet) const {
    char* to_search = new char[LEN_TO_SEARCH+1];
    char substring[LEN_TO_SEARCH+1];
    char* elem_str;

    StringArray str_arr = packet.split(","); // src-ip=246.132.188.125,  dst-ip=187.19.197.50 ,  src-port=53,  dst-port=21573
    String to_compare;
    String elem_as_str;
    if(this->is_src) // define the string that needs to be searched
        strcpy(to_search, "src-port");
    else
        strcpy(to_search, "dst-port");
    // find the port

    for(int i=0; i<MAX_SEPARATION; i++){
        str_arr.get_element(i)->trim(); // removes any whitespaces before and after packet elements
        elem_str = str_arr.get_element(i)->as_string().get_string();
        elem_as_str.set_string(elem_str); // class String
        strncpy(substring, elem_as_str.get_string(), LEN_TO_SEARCH);
        substring[LEN_TO_SEARCH] = '\0';

        if(!strcmp(substring ,  to_search)){
            to_compare.set_string(elem_as_str.get_string());
            break;
        }

    }
    if(to_search != nullptr)
    {
        delete[] to_search;
    }
    StringArray port_arr = to_compare.split("="); // to compare: "dst-port= 21573 "
    String packet_port = port_arr.get_element(1)->as_string(); // port_arr[0] = "dst-port" , port_arr[1]=" 21573 "
    packet_port.trim(); // "21573"
    int packet_port_int = packet_port.to_integer();
    if((packet_port_int <= this->high_port) && (packet_port_int >= this->low_port))
        return true;
    else
        return false;
}