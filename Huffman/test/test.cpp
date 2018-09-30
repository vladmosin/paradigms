#include "huffman.h"

int check_eq() {
    std::ifstream in("in", std::ios::binary | std::ios::in);
    std::ifstream res("in", std::ios::binary | std::ios::in); 
    std::string s1 = "", s2 = "";
    char symb = ' ';
    while (in.peek() != std::ifstream::traits_type::eof()) {
        in.read(&symb, 1);
        s1.push_back(symb);
    }
    while (res.peek() != std::ifstream::traits_type::eof()) {
        res.read(&symb, 1);
        s2.push_back(symb);
    }
    if (s1 == s2)
        return 0;
    return 1;
}

int test_big() {
    std::ofstream out("in");
    srand(566);
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 100; j++) {
            out << char(rand() % 220 + 1);
        }
        out << '\n';
    }
    out.close();
    Huffman tree;
    std::ifstream input("in", std::ios::binary | std::ios::in);
    tree.fill_freq(input);
	std::ofstream output("out", std::ios::binary | std::ios::out);
	tree.output_text(output);
	input.close();
	output.close();
	std::ifstream input1("out", std::ios::binary | std::ios::in);
    tree.build_tree_extr(input1);
	std::ofstream output1("res", std::ios::binary | std::ios::out);
	tree.extract(input1, output1);
	input1.close();
	output1.close();
	return check_eq();
}

int test_empty() {
    std::ofstream out("in");
    out.close();
    Huffman tree;
    std::ifstream input("in", std::ios::binary | std::ios::in);
    tree.fill_freq(input);
	std::ofstream output("out", std::ios::binary | std::ios::out);
	tree.output_text(output);
	input.close();
	output.close();
	std::ifstream input1("out", std::ios::binary | std::ios::in);
    tree.build_tree_extr(input1);
	std::ofstream output1("res", std::ios::binary | std::ios::out);
	tree.extract(input1, output1);
	input1.close();
	output1.close();
	return check_eq();
}

int test_random() {
    std::ofstream out("in");
    srand(566);
    for (int i = 0; i < rand() % 1000; i++) {
        for (int j = 0; j < rand() % 1000; j++) {
            out << char(rand() % 220 + 1);
        }
        out << '\n';
    }
    out.close();
    Huffman tree;
    std::ifstream input("in", std::ios::binary | std::ios::in);
    tree.fill_freq(input);
	std::ofstream output("out", std::ios::binary | std::ios::out);
	tree.output_text(output);
	input.close();
	output.close();
	std::ifstream input1("out", std::ios::binary | std::ios::in);
    tree.build_tree_extr(input1);
	std::ofstream output1("res", std::ios::binary | std::ios::out);
	tree.extract(input1, output1);
	input1.close();
	output1.close();
	return check_eq();
}

int main() {
    int cnt = 0;
    if (test_big() != 0) {
        std::cout << "error_big\n";
        cnt++;
    }
    if (test_empty() != 0) {
        std::cout << "error_empty\n";
        cnt++;
    }
    if (test_random() != 0) {
        std::cout << "error_random\n";
        cnt++;
    }
    if (cnt == 0)
        std::cout << "No error\n";
}
