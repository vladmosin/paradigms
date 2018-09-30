#include "huffman.h"

using std::pair;

TreeNode::TreeNode(char symb, int freq, int left,int right) :
	_symb(symb), _freq(freq), _left(left), _right(right)
{}

Huffman::Huffman() {
    _nodes.push_back({' ', 0});
	_root = 0;
	aux_inf = 0;
}

Huffman::~Huffman() {}

void Huffman::add_symb(const std::string& code, char symb) {
	int iter = _root;
	for (std::size_t i = 0; i < code.length(); i++) {
		if (code[i] == '1') {
			if (_nodes[iter].get_right() == -1) {
				_nodes[iter].set_right(_nodes.size());
				_nodes.push_back({symb, 0});
			}
			iter = _nodes[iter].get_right();
		}
		if (code[i] == '0') {
			if (_nodes[iter].get_left() == -1) {
				_nodes[iter].set_left(_nodes.size());
				_nodes.push_back({symb, 0});
			}
			iter = _nodes[iter].get_left();
		}
	}
}

void Huffman::calc_node(int node, const std::string& code) {
	if (_nodes[node].is_leaf()) {
		_codes[_nodes[node].get_symb()] = code;
	} else {
		if (_nodes[node].get_right() != -1)
			calc_node(_nodes[node].get_right(), code + "1");
		if (_nodes[node].get_left() != -1)
			calc_node(_nodes[node].get_left(), code + "0");
	}
}

std::string Huffman::get_symb( const std::string& code) const {
	int iter = _root;
	std::string res = "";
	for (std::size_t i = 0; i < code.length(); i++) {
		if (code[i] == '0')
			iter = _nodes[iter].get_left();
		else
			iter = _nodes[iter].get_right();
		if (_nodes[iter].is_leaf()) {
			res += _nodes[iter].get_symb();
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
	bool operator()(pair<int, int> a, pair<int, int> b) {
		return a.first > b.first;
	}
};

void Huffman::build_tree_arch() {
	std::priority_queue<pair<int, int>, std::vector<pair<int, int>>, comp> nodes;
	for (const auto& i : _freq) {
		_nodes.push_back({i.first, i.second});
		nodes.push({i.second, _nodes.size() - 1});
	}
	while (nodes.size() > 1) {
		int left = nodes.top().second;
		nodes.pop();
		int right = nodes.top().second;
		nodes.pop();
		_nodes.push_back({' ', _nodes[right].get_freq() + _nodes[left].get_freq(), left, right});
		nodes.push({_nodes[_nodes.size() - 1].get_freq(), _nodes.size() - 1});
	}
	if (_freq.size() == 1) {
		int left = nodes.top().second;
		nodes.pop();
		_nodes.push_back({' ', _nodes[left].get_freq() + 1, left, -1});
		nodes.push({_nodes[_nodes.size() - 1].get_freq(), _nodes.size() - 1});
	}
	if (!nodes.empty()) {
		_root = nodes.top().second;
	}
}

void Huffman::fill_freq(std::ifstream& in) {
	std::string line = "";
    int size = 0;
	while (in.peek() != std::ifstream::traits_type::eof()) {
		char symb;
		in.read(&symb, 1);
		line.push_back(symb);
		size++;
	}
	if (line.size() == 0)
	    return;
	_lines.push_back(line);
	proc_line(line);
	build_tree_arch();
	calc_node(_root, "");
	std::cout << size << '\n';
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
	uint32_t size = _freq.size();
	out.write(reinterpret_cast<char*>(&size), sizeof(uint32_t));
	for (auto& symb : _freq) {
		out.write(&symb.first, sizeof(char));
		out.write(reinterpret_cast<char*>(&symb.second), sizeof(int));
	}
	aux_inf =  size * 5 + 4;
}

void Huffman::output_text(std::ofstream& out) {
	output_codes(out);
	int size = 0;
	for (const auto& line : _lines) {
		for (char symb : line) {
			for (auto ch : _codes[symb]) {
				out.write(&ch, sizeof(char));
	            size++;        
	        }
		}
	}
	std::cout << size << '\n' << aux_inf << '\n';
}

void Huffman::build_tree_extr(std::ifstream& in) {
	int size = 0;
	in.read(reinterpret_cast<char*>(&size), sizeof(uint32_t));
	aux_inf = size * 5 + 4;
	for (int i = 0; i < size; i++) {
		int freq = 0;
		char symb = ' ';
		in.read(&symb, sizeof(char));
		in.read(reinterpret_cast<char*>(&freq), sizeof(int));
		_freq.push_back({symb, freq});
	}
	build_tree_arch();
	calc_node(_root, "");
}

void Huffman::extract(std::ifstream& in, std::ofstream& out) {
	std::string line = "";
	char symb = ' ';
	int size = 0;
	while (in.peek() != std::ifstream::traits_type::eof()) {
		in.read(&symb, sizeof(char));
		line.push_back(symb);
		size++;
	}
	std::cout << size << '\n';
	size = 0;
	if (line.length() > 0) {
		line = get_symb(line);
		for (auto symb : line) {
			out.write(&symb, sizeof(char));
		    size++;
		}
	}
	std::cout << size << '\n' << aux_inf << '\n';
}
