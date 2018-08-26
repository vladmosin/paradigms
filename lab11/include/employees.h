#ifndef __LAB11_EMPLOYEES_H_INCLUDED
#define __LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <cstring>

class Employee {
friend std::istream& operator>>(std::istream& in, Employee& e);
friend std::ostream& operator<<(std::ostream& out, Employee& e);
friend std::ifstream& operator>>(std::ifstream& in, Employee& e);
friend std::ofstream& operator<<(std::ofstream& out, Employee& e);
public:
    virtual int salary() const = 0;
    virtual void read(std::istream& in) = 0;
    virtual void write(std::ostream& out) = 0;
    virtual void bread(std::ifstream& in) = 0;
    virtual void bwrite(std::ofstream& out) = 0;
    Employee();
    virtual ~Employee();
protected:
    Employee(Employee& e);
    Employee& operator=(Employee& e);
    char _name[255];
    int32_t _base_salary;
};

class Developer : public Employee {
    friend std::istream& operator>>(std::istream& in, Developer& dev);
    friend std::ostream& operator<<(std::ostream& out, Developer& dev);
    friend std::ifstream& operator>>(std::ifstream& in, Developer& dev);
    friend std::ofstream& operator<<(std::ofstream& out, Developer& dev);
public:
    void read(std::istream& in);
    void write(std::ostream& out);
    void bread(std::ifstream& in);
    void bwrite(std::ofstream& out);
    Developer();
    ~Developer();
    int salary() const;
private:
    bool _has_bonus;
    const static int _num = 1;
};

class SalesManager : public Employee {
    friend std::istream& operator>>(std::istream& in, SalesManager& sm);
    friend std::ostream& operator<<(std::ostream& out, SalesManager& sm);
    friend std::ifstream& operator>>(std::ifstream& in, SalesManager& sm);
    friend std::ofstream& operator<<(std::ofstream& out, SalesManager& sm);
public:
    void read(std::istream& in);
    void write(std::ostream& out);
    void bread(std::ifstream& in);
    void bwrite(std::ofstream& out);
    SalesManager();
    ~SalesManager();
    int salary() const;
private:
    int32_t _sold_nm, _price;
    const static int _num = 2;
};

class EmployeesArray {
    friend std::istream& operator>>(std::istream& in, EmployeesArray& emp_arr);
    friend std::ostream& operator<<(std::ostream& out, EmployeesArray& emp_arr);
    friend std::ifstream& operator>>(std::ifstream& in, EmployeesArray& emp_arr);
    friend std::ofstream& operator<<(std::ofstream& out, EmployeesArray& emp_arr);
public:
    EmployeesArray();
    ~EmployeesArray();
    void reserve();
    int32_t getsize();
    void add(int type);
    int32_t total_salary() const;
private:
    int32_t _size;
    int32_t _cp;
    Employee **_employees;
};

std::istream& operator>>(std::istream& in, Developer& dev);
std::ostream& operator<<(std::ostream& out, Developer& dev);
std::ifstream& operator>>(std::ifstream& in, Developer& dev);
std::ofstream& operator<<(std::ofstream& out, Developer& dev);
std::istream& operator>>(std::istream& in, Employee& e);
std::ostream& operator<<(std::ostream& out, Employee& e);
std::ifstream& operator>>(std::ifstream& in, Employee& e);
std::ofstream& operator<<(std::ofstream& out, Employee& e);
std::istream& operator>>(std::istream& in, SalesManager& sm);
std::ostream& operator<<(std::ostream& out, SalesManager& sm);
std::ifstream& operator>>(std::ifstream& in, SalesManager& sm);
std::ofstream& operator<<(std::ofstream& out, SalesManager& sm);
std::istream& operator>>(std::istream& in, EmployeesArray& emp_arr);
std::ostream& operator<<(std::ostream& out, EmployeesArray& emp_arr);
std::ifstream& operator>>(std::ifstream& in, EmployeesArray& emp_arr);
std::ofstream& operator<<(std::ofstream& out, EmployeesArray& emp_arr);

#endif
