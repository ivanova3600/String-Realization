#ifndef _STRING_H_
#define _STRING_H_

#include <iostream>

class String{
private:
    char *string;
    size_t len;

public:
    explicit String();
    explicit String(const char *ptr);
    explicit String(const String &str);

    class StringIterator{
    private:
        String &str;
        int index;

        friend class String;
    public:    
        StringIterator(String &_str, int _index);
        
        StringIterator& operator++(); // префикс
        StringIterator& operator--(); 
        
        char &operator*();
        char *operator->();

        bool operator!=(const StringIterator &i);
        bool operator==(const StringIterator &i);
    };


    StringIterator begin(){
        return StringIterator(*this, 0);
    }


    StringIterator end(){
        return StringIterator(*this, len);
    }
    
    size_t getLen() const;
    
    friend std::ostream &operator<<(std::ostream &out, const String &str);
    friend std::istream &operator>>(std::istream &in, String &str);
    friend String operator+(const String &a, const String &b);
    friend bool operator!=(const String &a, const String &b);
    friend bool operator==(const String &a, const String &b);
    friend bool operator>(const String &a, const String &b);
    friend bool operator<(const String &a, const String &b);
    friend bool operator>=(const String &a, const String &b);
    friend bool operator<=(const String &a, const String &b);

    String &operator+=(const String &b);
    String &operator=(const String &str);
    String &operator=(const char *str);

    char &operator[] (const size_t index);
    const char &operator[] (const size_t index) const;

    operator int();
    operator double();

    //int toInt();
    //double toDouble();

    void reverse();


    static void copy(char *& a, const char *b);
    static char* concate(const char *a, const char *b);
    static int compare_string(const char *str1, const char *str2);
    static size_t getLen(const char *str);
    static void reverse(char *str);

    char *getString() { return string; }
    void clear();

     ~String();
};


#endif