#include <string>
#include <exception>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <stdint.h>
#include <utility>
#include <queue>

class TreeNode {
public:
	TreeNode(char symb, int freq, int left = -1, int right = -1);
	~TreeNode() {};
	void set_left(int node) { _left = node; };
	void set_right(int node) { _right = node; };
	int get_left() const { return _left; };
	int get_right() const { return _right; };
	char get_symb() const { return _symb; };
	bool is_leaf() const { return (_right == -1) && (_left == -1); };
	int get_freq() const { return _freq; };
private:
	char _symb;
	int _freq;
	int  _left, _right;
};

class Huffman
{
public:
	Huffman();
	~Huffman();
	void add_symb(const std::string& code, char symb);
	void calc_node(int node, const std::string& code);
	std::string get_symb(const std::string& code) const;
	void build_code(const std::vector<std::pair<char, std::string>>& codes);
	void build_tree_arch();
	void fill_freq(std::ifstream& in);
	void proc_line(const std::string& line);
	int get_root() const { return _root; };
	void output_codes(std::ofstream& out);
	void output_text(std::ofstream& out);
	void build_tree_extr(std::ifstream& in);
	void extract(std::ifstream& in, std::ofstream& out);
private:
	int _root;
	int aux_inf;
	std::unordered_map<char, std::string> _codes;
	std::unordered_map<char, int> _v_ind;
	std::vector<std::pair<char, int>> _freq;
	std::vector<std::string> _lines;
	std::vector<TreeNode> _nodes;
};
