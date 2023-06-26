#ifndef CATEGORY_H
#define CATEGORY_H
#include <iostream>
#include <string>

class Category
{
public:
    Category(int code = 0, std::string Name = "", std::string description = "")
        :_code(code), _Name(Name),_description(description) {}

    int getCode() {
        return this->_code;
    }
    std::string getName(){
        return this->_Name;
    }
    friend std::ostream& operator<<(std::ostream& os, const Category& a) { 
        os << a._code << "," << a._Name << ", " << a._description;
        return os;
    }
private: 
    int _code; 
    std::string _Name, _description;   
};

#endif