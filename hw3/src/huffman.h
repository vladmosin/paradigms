#pragma once
#include <string>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstring>
#include <iostream>

class TreeNode {
public:
	TreeNode(char symb, int freq, TreeNode* left = nullptr, TreeNode* right = nullptr);
	~TreeNode() {};
	void set_left(TreeNode* const node) { _left = node; };
	void set_right(TreeNode* const node) { _right = node; };
	TreeNode* get_left() const { return _left; };
	TreeNode* get_right() const { return _right; };
	char get_symb() const { return _symb; };
	bool is_leaf() const { return (_right == nullptr) && (_left == nullptr); };
	int get_freq() const { return _freq; };
private:
	char _symb;
	int _freq;
	TreeNode  *_left, *_right;
};

class Huffman
{
public:
	Huffman();
	~Huffman();
	void clear(TreeNode* node);
	void add_symb(const std::string& code, char symb);
	void calc_node(TreeNode* node, const std::string& code);
	std::string get_symb(const std::string& code) const;
	void build_code(const std::vector<std::pair<char, std::string>>& codes);
	void build_tree_arch();
	void fill_freq(std::ifstream& in);
	void proc_line(const std::string& line);
	TreeNode* get_root() const { return _root; };
	void output_codes(std::ofstream& out);
	void output_text(std::ofstream& out);
	void build_tree_extr(std::ifstream& in);
	void extract(std::ifstream& in, std::ofstream& out);
private:
	TreeNode* _root;
	std::unordered_map<char, std::string> _codes;
	std::unordered_map<char, int> _v_ind;
	std::vector<std::pair<char, int>> _freq;
	std::vector<std::string> _lines;
};
