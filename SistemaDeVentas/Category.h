#ifndef CATEGORY_H
#define CATEGORY_H
#include <iostream>
#include <string>

class Category
{
public:
    Category(int code = 0, std::string fullName = "", int age = 0, float salary = 0)
        :_code(code), _fullName(fullName), _age(age), _salary(salary) {}

    int getCode() {
        return this->_code;
    }

    std::string getFullName(){
        return this->_fullName;
    }
    int getAge() { 
        return this->_age;
    }

    float getSalary() { 
        return this->_salary;
    }

    void setSalary(float salary) { 
        this->_salary = salary;
    }
    friend std::ostream& operator<<(std::ostream& os, const Category& a) { 
        os << a._code << "," << a._fullName << ", " << a._age << ", " << a._salary; 
        return os;
    }
private: 
    int _code; 
    std::string _fullName; 
    int _age; 
    float _salary;  
};

#endif