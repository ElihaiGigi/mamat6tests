#include "ip.h"

ip::~ip(){
     delete this->ip_arr;
}

int ip::get_mask() const{
    return this->mask;
}
ip_type ip::get_ds_type() const{
    return this->ds_type;
}

ip::ip(const char* str) {
    //getting a string type " dst-ip=158.243.66.138/32  " and triming it to "dst-ip=158.243.66.138/32"
    String A = String(str);
    GenericString *temp_str;
    A.trim();
    //create a string array of dst or src
    char *f_char = A.get_string();
    if(f_char[0] == 'd'){
        this->ds_type = dst;
    }else{
        this->ds_type = src;
    }
    StringArray B = A.split("/");
    temp_str = B.get_element(1);
    if(temp_str!= nullptr)
    {
        this->mask = temp_str->to_integer();
    }
    temp_str = B.get_element(0);
    //"dst-ip=158.243.66.138"
    StringArray C = temp_str->split("=");
    temp_str = C.get_element(1);
    temp_str->trim();
    //"158.243.66.138"
    A.set_string(temp_str->as_string().get_string()); // A = "158.243.66.138"
    //StringArray ref = StringArray(A.split("."));
    this->ip_arr = new StringArray(A.split("."));
    //"158   243   66   138"

}

bool ip::match(const GenericString &packet) const{
    StringArray str_pkt = packet.split(",");
    StringArray temp_arr;
    GenericString *element;
    char* str_to_search = new char[6];

    if(this->get_ds_type() == src) {
        strcpy(str_to_search,"src-i");
    }else{
        strcpy(str_to_search,"dst-i");
    }

    for(int i=0; i<MAX_SEPARATION;i++){
        element = str_pkt.get_element(i);
        element->trim();
        if(!strncmp(element->as_string().get_string(),str_to_search,FIRST_5_CHARS))
        {
            ip temp_ip(element->as_string().get_string());
            if(check_match(temp_ip.ip_arr, this->ip_arr, this->get_mask())){
                delete[] str_to_search;
                return true;
            }else {
                delete[] str_to_search;
                return false;
            }
        }
    }
    delete[] str_to_search;
    return false;
}

bool check_match(StringArray *ip1, StringArray *ip2 , const int mask){
    unsigned int bip1 = 0;
    unsigned int bip2 = 0;
    int temp_val;

    for(int i=0;i<MAX_SEPARATION;i++){
        temp_val = ip1->get_element(i)->to_integer();
        bip1 += temp_val << CHAR_SIZE*(MAX_SEPARATION-1-i);
        temp_val = ip2->get_element(i)->to_integer();
        bip2 += temp_val << CHAR_SIZE*(MAX_SEPARATION-1-i);
    }
    return ((bip1>>(INT_SIZE-mask)) == (bip2>>(INT_SIZE-mask)));
}
