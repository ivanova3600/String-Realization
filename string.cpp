#include "string.h"
#include <cstdlib>
#include <cassert>

// String Iterator

String::StringIterator::StringIterator(String &_str, int _index) : str(_str), index(_index) { }


String::StringIterator& String::StringIterator::operator++(){
    ++index;
    return *this;
}
String::StringIterator& String::StringIterator::operator--(){
    --index;
    return *this;
}
        
char &String::StringIterator::operator*(){
    return str[index];
}
char *String::StringIterator::operator->(){
    return &str[index];
}

bool String::StringIterator::operator!=(const StringIterator &i){
   // std::cout << " here " << index << " " << i.index << std::endl;
    if(index != i.index) return true;
    if(&str != &(i.str)) return true;

    return false;
}

bool String::StringIterator::operator==(const StringIterator &i){
    if(index != i.index) return false;
    if(&str != &(i.str)) return false;

    return true;
}




size_t String::getLen(const char *str){
	if(!str) return 0;
    
    size_t len;
	for(len = 0; *str; str++) len++;
	return len;
}

String::String(){
    string = nullptr;
    len = 0;
}

String::String(const char *ptr)
{
    len = String::getLen(ptr);
   // string = new char[len + 1];
    copy(string, ptr);
}

String::String(const String &str){
    len = str.len;
    copy(string, str.string);
}


size_t String::getLen() const { return len; }


void String::copy(char *& a, const char *b){
    if(!b){
        std::cout << "Second string is nullptr. Don't copy" << std::endl;
        return;
    }

    size_t len_b = String::getLen(b);

    if(a) delete[] a; 

    a = new char[len_b + 1];
    for(size_t i = 0; i < len_b; i++)
        a[i] = b[i];
    a[len_b] = '\0';
}

char *String::concate(const char *a, const char *b){
    if(!a && !b) return nullptr;

    size_t len_a = String::getLen(a);
    size_t len_b = String::getLen(b);

    char *con = new char[len_a + len_b];

    for(size_t i = 0; i < len_a; i++)
        con[i] = a[i];

    for(size_t i = len_a; i < len_b + len_a; i++)
        con[i] = b[i-len_a];    

    return con;
}

int String::compare_string(const char *str1, const char *str2){
	while(*str1){
		if(!*str2)
			return 1;
		if(*str1 < *str2)
			return -1;
		if(*str1 > *str2)
			return 1;
		str1++;
		str2++;
	}

	if(*str2)
		return -1;

	return 0;
}

String::~String(){
    if(string){
        delete[] string;
    }
}


std::ostream &operator<<(std::ostream &out, const String &str){
    out << str.string;

    return out;
}

std::istream &operator>>(std::istream &in, String &str){
    if(str.string) delete[] str.string;
    str.string = new char[255];
    
    in.getline(str.string, 255, '\n');
    str.len = String::getLen(str.string);
    
    return in;
}

String operator+(const String &a, const String &b){
    char *c = String::concate(a.string, b.string);

    return String(c);
}


String& String::operator=(const String &str){
    if(this == &str)
        return *this;
    
    String::copy(string, str.string);
    len = str.len;

    return *this; // разыменивывание
}

String &String::operator=(const char *str){
    if(String::compare_string(this->string, str) == 0)
        return *this;
    
    String::copy(string, str);
    len = String::getLen(str);

    return *this;
}



bool operator!=(const String &a, const String &b){
    if(a.len != b.len) return true;

    return (String::compare_string(a.string, b.string) != 0) ? true : false;
}

bool operator==(const String &a, const String &b){
    if(a.len != b.len) return false;

    return (String::compare_string(a.string, b.string) == 0) ? true : false;
}

bool operator>(const String &a, const String &b){
    return (String::compare_string(a.string, b.string) == 1) ? true : false;
}

bool operator<(const String &a, const String &b){
    return (String::compare_string(a.string, b.string) == -1) ? true : false;
}

bool operator>=(const String &a, const String &b){
    int i = String::compare_string(a.string, b.string);
    return (i == -1 || i == 0) ? true : false;
}

bool operator<=(const String &a, const String &b){
    int i = String::compare_string(a.string, b.string);
    return (i == 1 || i == 0) ? true : false;
}


String::operator int(){
    if(len == 0) return 0;

    char *str = string;

    int k = 0, p = 1;
    if(str[0] == '-'){
        p = -1;
        str++;
    }
    else if(str[0] == '+') str++;
    while(*str){
        if(*str < '0' || *str > '9')
            return 0;
        k = k*10 + *str++ -'0';
    }

    return k*p;
}

String::operator double(){
    if(len == 0) return 0;

    char *str = string;

    double k = 0;
    int p = 1;
    double m = 10;
    int m_flag = 0;
    if(str[0] == '-'){
        p = -1;
        str++;
    }
    else if(str[0] == '+') str++;

     while(*str){
        if(*str < '0' || *str > '9'){
            if(*str == '.') {
                m_flag = 1;
                str++;
                continue;
            }
            else return 0;
        }
        else if(m_flag == 1){
            k += (*str  - '0')/ m;
            str++;
            m *= 10;
        }
        else
            k = k*10 + *str++ -'0';
    }

    return p*k;
}

void String::clear(){
    if(string){
        delete[] string;
        string = nullptr;
    }
    len = 0;
}

String &String::operator+=(const String &b){
    string = String::concate(string, b.string);
    len += b.len;

    return *this;
}

char &String::operator[] (const size_t index){
    if(index < 0 || index >= len){
        std::cout << "Index " <<index << " " << len << std::endl;
        assert(index < 0 || index >= len);
    }

    //assert(index < 0 || index >= len);

    return string[index];
}

const char &String::operator[] (const size_t index) const{
    if(index < 0 || index >= len){
        std::cout << "Index " <<index << " " << len << std::endl;
        assert(index < 0 || index >= len);
    }
    
    
    return string[index];
}


void String::reverse(){
    if (string == NULL)  return;
 
    for (size_t i = 0, j = len - 1; i < j; i++, j--){
        char ch = string[i];
        string[i] = string[j];
        string[j] = ch;
    }
}

void String::reverse(char *str){
    if (str == NULL)  return;

    size_t len = String::getLen(str);
 
    for (size_t i = 0, j = len - 1; i < j; i++, j--){
        char ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
}