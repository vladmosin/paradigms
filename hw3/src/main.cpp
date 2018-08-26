#include "huffman.h"

int main(int argc, char* argv[]) {
	Huffman tree;
	if (strcmp(argv[1], "-c") == 0) {
		std::ifstream in(argv[3]);
		tree.fill_freq(in);
		std::ofstream out(argv[argc - 1]);
		tree.output_text(out);
	}
	if (strcmp(argv[1], "-u") == 0) {
		std::ifstream in(argv[3]);
		tree.build_tree_extr(in);
		std::ofstream out(argv[argc - 1]);
		tree.extract(in, out);
	}
}
