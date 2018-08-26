#include "matrix.h"
#include <fstream>

int main() {
	char com[6];
	Matrix matr[10];
	while (true) {
		std::cin >> com;

		if (strcmp(com, "load") == 0) {
			char reg[3], filename[100];
			std::cin >> reg >> filename;
			std::ifstream in(filename);
			try {
				matr[reg[1] - '0'].load(in);
			} catch (MatrixException& exception){
				std::cout << exception.get_exception() << '\n';
			}
		}

		if (strcmp(com, "print") == 0) {
			char reg[3];
			std::cin >> reg;
			matr[reg[1] - '0'].print();
		}

		if (strcmp(com, "add") == 0) {
			char reg1[3], reg2[3];
			std::cin >> reg1 >> reg2;
			try {
				matr[reg1[1] - '0'] += matr[reg2[1] - '0'];
			} catch (MatrixException& exception) {
				std::cout << exception.get_exception() << '\n';
			}
		}

		if (strcmp(com, "mul") == 0) {
			char reg1[3], reg2[3];
			std::cin >> reg1 >> reg2;
			try {
				matr[reg1[1] - '0'] *= matr[reg2[1] - '0'];
			} catch (MatrixException& exception) {
				std::cout << exception.get_exception() << '\n';
			}
		}

		if (strcmp(com, "elem") == 0) {
			char reg[3];
			int i = 0, j = 0;
			std::cin >> reg >> i >> j;
			try {
				std::cout << matr[reg[1] - '0'].get(i, j) << '\n';
			} catch (MatrixException& exception) {
				std::cout << exception.get_exception() << '\n';
			}
		}

		if (strcmp(com, "exit") == 0) {
			break;
		}
	}
}