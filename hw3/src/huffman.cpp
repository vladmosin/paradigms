#include "huffman.h"

TreeNode::TreeNode(char symb, int freq, TreeNode* left, TreeNode* right) :
	_symb(symb), _freq(freq), _left(left), _right(right)
{}

Huffman::Huffman() {
	_root = new TreeNode(' ', 0);
}

Huffman::~Huffman() {
	clear(_root);
}

void Huffman::clear(TreeNode* node) {
	if (node) {
		clear(node->get_left());
		clear(node->get_right());
	}
	delete node;
}

void Huffman::add_symb(const std::string& code, char symb) {
	TreeNode* iter = _root;
	for (std::size_t i = 0; i < code.length(); i++) {
		if (code[i] == '1') {
			if (!iter->get_right())
				iter->set_right(new TreeNode(symb, 0));
			iter = iter->get_right();
		}
		if (code[i] == '0') {
			if (!iter->get_left())
				iter->set_left(new TreeNode(symb, 0));
			iter = iter->get_left();
		}
	}
}

void Huffman::calc_node(TreeNode* node, const std::string& code) {
	if (node->is_leaf()) {
		_codes[node->get_symb()] = code;
	} else {
		if (node->get_right())
			calc_node(node->get_right(), code + "1");
		if (node->get_left())
			calc_node(node->get_left(), code + "0");
	}
}

std::string Huffman::get_symb( const std::string& code) const {
	TreeNode* iter = _root;
	std::string res = "";
	for (std::size_t i = 0; i < code.length(); i++) {
		if (code[i] == '0')
			iter = iter->get_left();
		else
			iter = iter->get_right();
		if (!iter->get_left() && !iter->get_right()) {
			res += iter->get_symb();
			iter = _root;
		}
	}
	return res;
}

void Huffman::build_code(const std::vector<std::pair<char, std::string>>& codes) {
	for (const auto& i : codes) {
		add_symb(i.second, i.first);
	}
}

struct comp {
	bool operator()(const TreeNode* a, const TreeNode* b) {
		return a->get_freq() > b->get_freq();
	}
};

void Huffman::build_tree_arch() {
	std::priority_queue<TreeNode*, std::vector<TreeNode*>, comp> nodes;
	for (const auto& i : _freq) {
		nodes.push(new TreeNode(i.first, i.second));
	}
	while (nodes.size() > 1) {
		TreeNode* left = nodes.top();
		nodes.pop();
		TreeNode* right = nodes.top();
		nodes.pop();
		nodes.push(new TreeNode(' ', right->get_freq() + left->get_freq(), left, right));
	}
	if (_freq.size() == 1) {
		TreeNode* left = nodes.top();
		nodes.pop();
		nodes.push(new TreeNode(' ', left->get_freq() + 1, left, nullptr));
		std::cout << "sjdfkdg\n";
	}
	if (!nodes.empty()) {
		delete _root;
		_root = nodes.top();
	}
}

void Huffman::fill_freq(std::ifstream& in) {
	std::string line;
	while (getline(in, line)) {
	    _lines.push_back(line);
		proc_line(line);
	}
	build_tree_arch();
	calc_node(_root, "");
}

void Huffman::proc_line(const std::string& line) {
	for (std::size_t i = 0; i < line.length(); i++) {
		auto search = _v_ind.find(line[i]);
		if (search == _v_ind.end()) {
			_freq.push_back( {line[i], 1} );
			_v_ind[line[i]] = _freq.size() - 1;
		} else {
			_freq[search->second].second++;
		}
	}
}

void Huffman::output_codes(std::ofstream& out) {
	out << _codes.size() << '\n';
	for (const auto& code : _codes) {
		out << code.first << code.second << '\n';
	}
}

void Huffman::output_text(std::ofstream& out) {
	output_codes(out);
	std::string line = "";
	for (const auto& line : _lines) {
	    for (char symb : line)
		out << _codes[symb];
		out << '\n';
	}
}

void Huffman::build_tree_extr(std::ifstream& in) {
	int size = 0;
	std::string line = "";
	in >> size;
	getline(in, line);
	std::vector<std::pair<char, std::string>> codes;
	for (int i = 0; i < size; i++) {
		getline(in, line);
		char symb = line[0];
		line = line.erase(0, 1);
		codes.push_back({ symb, line });
	}
	build_code(codes);
}

void Huffman::extract(std::ifstream& in, std::ofstream& out) {
	std::string line = "";
	while (getline(in, line)) {
		if (line.length() > 0) {
			out << get_symb(line);
			out << '\n';
		}
	}
}
