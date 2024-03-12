#include "string.h"

int String::get_size() const {
    return this->length;
}
char* String::get_string() const{
    return this->my_string;
}
void String::set_string(const char* str){
    if(this->get_string()){
        delete[] this->my_string;
    }
    this->length = strlen(str);
    this->my_string = new char[this->length + 1];
    strcpy(this->my_string, str);
}

String::String(const char* str) {
    my_string = nullptr;
    length = 0;
    String::set_string(str);
}

String::String(const String &str) {
    my_string = nullptr;
    length = 0;
    String::set_string(str.get_string());
}

String::~String(){
    if(this->get_string()){
        delete[] this->get_string();
    }
}

StringArray String::split(const char *delimiters) const{
    char* token = strtok(this->get_string(), delimiters);
    int index = 0;
    StringArray arr = StringArray();
    while (token) {
        GenericString *temp_gs = new String(token);
        arr.set_element(temp_gs,index);
        index++;
        token = strtok(nullptr, delimiters);
    }
    return arr;
}
GenericString& String::operator=(const char *str){
    this->set_string(str);
    return *this;
}

GenericString& String::trim(){
    int l=0;
    int len;
    int r=this->get_size() - 1;
    while(this->get_string()[l]==' ') l++;
    while(this->get_string()[r]==' ') r--;
    len = r-l+1;
    char* new_string = new char[len+1];
    strncpy(new_string, this->get_string() + l, len);
    new_string[len] = '\0';
    this->set_string(new_string);
    delete[] new_string;
    return *this;
}

bool String::operator==(const char *other) const{
    if(!strcmp(this->get_string(), other) == true){
        return true;
    } else {
        return false;
    }
}

bool String::operator==(const GenericString &other) const {
    const String& otherString = other.as_string();
    if(!strcmp(this->get_string(), otherString.get_string()) == true){
        return true;
    } else {
        return false;
    }
}

int String::to_integer() const{
    return atoi(this->get_string());
}

String& String::as_string(){
    return dynamic_cast<String&>(*this);
}

const String& String::as_string() const{
    return dynamic_cast<const String&>(*this);
}

GenericString* make_string(const char *str){
    return new String(str);
}