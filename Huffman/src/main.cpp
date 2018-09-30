#include "huffman.h"

int main(int argc, char* argv[]) {
	Huffman tree;
	if (argc != 6) {
	    std::cout << "wrong arguments";
	    return 0;
	} 
	if (strcmp(argv[2], "-f") != 0) {
	    std::cout << "second arg is wrong";
	}
	if (strcmp(argv[4], "-o") != 0) {
	    std::cout << "fourth arg is wrong";
	}
	if (strcmp(argv[1], "-c") == 0) {
	    std::ifstream in(argv[3], std::ios::binary | std::ios::in);
		try {
		    tree.fill_freq(in);
		}
		catch (std::exception &) {
		    std::cout << "error with input file";
		    return 0;
		}
		std::ofstream out(argv[argc - 1], std::ios::binary | std::ios::out);
		try {
		    tree.output_text(out);
		}
		catch (std::exception &) {
		    std::cout << "unknown mistake";
		    return 0;
		}
		in.close();
		out.close();
	}
	if (strcmp(argv[1], "-u") == 0) {
        std::ifstream in(argv[3], std::ios::binary | std::ios::in);
		try {
		    tree.build_tree_extr(in);
		}
		catch (std::exception &) {
		    std::cout << "file with error";
		    return 0;
		}
	    std::ofstream out(argv[argc - 1], std::ios::binary | std::ios::out);
		try {
		    tree.extract(in, out);
		}
		catch (std::exception &) {
		    std::cout << "unknown mistake";
		    return 0;
		}
		in.close();
		out.close();
	}
}
