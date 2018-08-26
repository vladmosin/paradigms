#include "employees.h" 

Employee::Employee():
    _base_salary(0)
{}

Employee::~Employee() {}

Developer::Developer():
    Employee(), _has_bonus(false)
{}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

Developer::~Developer() {}

void Developer::bread(std::ifstream& in) {
    in >> *this;
}

void SalesManager::bread(std::ifstream& in) {
    in >> *this;
}

void Developer::bwrite(std::ofstream& out) {
    out << *this;
}

void SalesManager::bwrite(std::ofstream& out) {
    out << *this;
}

void Developer::read(std::istream& in) {
    in >> *this;
}

void SalesManager::read(std::istream& in) {
    in >> *this;
}

void Developer::write(std::ostream& out) {
    out << *this;
}

void SalesManager::write(std::ostream& out) {
    out << *this;
}

SalesManager::SalesManager():
    Employee(), _sold_nm(0), _price(0)
{}

SalesManager::~SalesManager() {}

int SalesManager::salary() const {
    return _base_salary + (_sold_nm * _price) / 100;
}

EmployeesArray::EmployeesArray():
    _size(0), _cp(2)
{
     _employees = new Employee*[2];
}

void EmployeesArray::reserve() {
    Employee** tmp = new Employee*[2 * _cp];
    memcpy(tmp, _employees, _size * sizeof(Employee*));
    delete [] _employees;
    _employees = tmp;
    tmp = NULL;
    _cp *= 2;
}

int32_t EmployeesArray::total_salary() const {
    int res = 0;
    for (int i = 0; i < _size; i++) {
        res += _employees[i]->salary();
    }
    return res;
}

void EmployeesArray::add(int type) {
    if (_size == _cp)
        reserve();
    if (type == 1)
        _employees[_size]  = new Developer();
    if (type == 2)
        _employees[_size] = new SalesManager();
    _size++;
}

int32_t EmployeesArray::getsize() {
    return _size;
}

std::ifstream& operator>>(std::ifstream& in, EmployeesArray& emp_arr) {
    int32_t quant = 0;
    in.read((char*)&quant, sizeof(int32_t));
    for (int i = 0; i < quant; i++) {
        int32_t num = 0;
        in.read((char*)&num, sizeof(int32_t));
        emp_arr.add(num);
        emp_arr._employees[emp_arr._size - 1]->bread(in);
    }
    return in;
}

std::istream& operator>>(std::istream& in, EmployeesArray& emp_arr) {
    emp_arr._employees[emp_arr._size - 1]->read(in);
    return in;
}

std::ostream& operator<<(std::ostream& out, EmployeesArray& emp_arr) {
    for (int i = 0; i < emp_arr._size; i++) {
        out << i + 1 << ". ";
        emp_arr._employees[i]->write(out);
    }
    out << "== Total salary: " << emp_arr.total_salary() << "\n\n";
    return out;
}

std::ofstream& operator<<(std::ofstream& out, EmployeesArray& emp_arr) {
    for (int i = 0; i < emp_arr._size; i++) {
        emp_arr._employees[i]->bwrite(out);
    }
    return out;
}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < _size; i++) {
        delete _employees[i];
    }
    delete [] _employees;
}

std::ofstream& operator<<(std::ofstream &out, SalesManager &sm) {
    int32_t num = sm._num;
	out.write((char*)&num, sizeof(int32_t));
	out.write(sm._name, (strlen(sm._name) + 1) * sizeof(char));
	out.write((char*)&sm._base_salary, sizeof(int32_t));
	out.write((char*)&sm._sold_nm, sizeof(int32_t));
	out.write((char*)&sm._price, sizeof(int32_t));
	return out;
}

std::ifstream& operator>>(std::ifstream &in, SalesManager &sm) {
	for(int i = 0; i < 255; i++) {
		in.read(sm._name + i, sizeof(char));
		if(!sm._name[i])
			break;
	}
	in.read((char*)&sm._base_salary, sizeof(int32_t));
	in.read((char*)&sm._sold_nm, sizeof(int32_t));
	in.read((char*)&sm._price, sizeof(int32_t));
	return in;
}

std::ostream& operator<<(std::ostream &out, SalesManager &sm) {
	out << "Sales Manager\n";
	out << "Name: " << sm._name << '\n';
	out << "Base Salary: " << sm._base_salary << '\n';
	out << "Sold items: " << sm._sold_nm << '\n';
	out << "Item price: " << sm._price << '\n';
	return out;
}

std::istream& operator>>(std::istream &in, SalesManager &sm) {
	in >> sm._name >> sm._base_salary >> sm._sold_nm >> sm._price;
	return in;
}

std::ofstream& operator<<(std::ofstream &out, Developer &dev) {
    int32_t num = dev._num;
	out.write((char*)&num, sizeof(int32_t));
	out.write(dev._name, (strlen(dev._name) + 1) * sizeof(char));
	out.write((char*)&dev._base_salary, sizeof(int32_t));
	out.write((char*)&dev._has_bonus, sizeof(bool));
	return out;
}

std::ifstream& operator>>(std::ifstream &in, Developer &dev) {
	for(int i = 0; i < 255; i++) {
		in.read(dev._name + i, sizeof(char));
		if(!dev._name[i])
			break;
	}
	in.read((char*)&dev._base_salary, sizeof(int32_t));
	in.read((char*)&dev._has_bonus, sizeof(bool));
	return in;
}

std::ostream& operator<<(std::ostream &out, Developer &dev) {
	out << "Developer\n";
	out << "Name: " << dev._name << '\n';
	out << "Base Salary: " << dev._base_salary << '\n';
	out << "Has bonus: " << (dev._has_bonus ? '+' : '-') << '\n';
	return out;
}

std::istream& operator>>(std::istream &is, Developer &dev) {
	is >> dev._name >> dev._base_salary >> dev._has_bonus;
	return is;
}

std::istream& operator>>(std::istream& in, Employee& e) { std::cout << 'g'; return in;};
std::ostream& operator<<(std::ostream& out, Employee& e) { return out;};
std::ifstream& operator>>(std::ifstream& in, Employee& e) { std::cout << 'g'; return in;};
std::ofstream& operator<<(std::ofstream& out, Employee& e) { return out;};
