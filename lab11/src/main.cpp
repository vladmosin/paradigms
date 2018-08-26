#include "employees.h"
#include <cstring>

int main() {
    EmployeesArray emp_arr;
    char com[20];
    while(true) {
        std::cin >> com;
        if (strcmp(com, "load") == 0) {
            char filename[100];
            std::cin >> filename;
            std::ifstream in(filename, std::ofstream::binary);
            in >> emp_arr;
        }
        if (strcmp(com, "list") == 0) {
            std::cout << emp_arr;
        }
        if (strcmp(com, "add") == 0) {
            int32_t num = 0;
            std::cin >> num;
            emp_arr.add(num);
            std::cin >> emp_arr;
        }
        if (strcmp(com, "save") == 0) {
            char filename[255];
            std::cin >> filename;
            std::ofstream out(filename, std::ofstream::binary);
            int32_t size = emp_arr.getsize();
            out.write((char*)&size, sizeof(int32_t));
            out << emp_arr;
        }
        if (strcmp(com, "exit") == 0) {
            break;
        }
    }
}
