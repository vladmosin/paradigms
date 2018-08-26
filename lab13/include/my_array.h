#include <iostream>

template<class T, std::size_t N>
class my_array {
public:
	T& at(std::size_t index);
	T& operator[](std::size_t index);
	const T& at(std::size_t index) const;
	const T& operator[](std::size_t index) const;
 	bool empty() const;
  	std::size_t size() const;
  	void fill(const T& val);
private:
	T _array[N];
};

template<class T, std::size_t N>
T& my_array<T, N>::operator[](std::size_t index) {
	return _array[index];
}

template<class T, std::size_t N>
const T& my_array<T, N>::operator[](std::size_t index) const {
	return _array[index];
}

template<class T, std::size_t N>
T& my_array<T, N>::at(std::size_t index) {
	if (index >= N && index < 1) {
		std::cout << "wrong index";
		exit(0);
	}
	return _array[index];
}

template<class T, std::size_t N>
const T& my_array<T, N>::at(std::size_t index) const {
	if (index >= N && index < 1) {
		std::cout << "wrong index";
		exit(0);
	}
	return _array[index];
}

template<class T, std::size_t N>
bool my_array<T, N>::empty() const {
	return N == 0;
} 

template<class T, std::size_t N>
std::size_t my_array<T, N>::size() const {
	return N;
}

template<class T, std::size_t N>
void my_array<T, N>::fill(const T& val) {
	for (std::size_t i = 0; i < N; i++) {
		_array[i] = val;
	}
}

// Специализация bool

class proxy {
public:
	proxy& operator=(bool value);
	operator bool() const;
	proxy(uint8_t* _pointer, uint8_t num);
	proxy& operator=(const proxy& value);
	~proxy() {}
private:
	uint8_t *_pointer;
	uint8_t _num;
};

proxy::proxy(uint8_t* pointer, uint8_t num):
	_pointer(pointer), _num(num)
{}

proxy::operator bool() const {
	return *_pointer & (1 << _num);
}

proxy& proxy::operator=(bool value) {
	if (value) {
		*_pointer |= (1 << _num);
	} else {
		*_pointer &= ((1 << 8) - (1 << _num) - 1);
	}
	return *this;
}

proxy& proxy::operator=(const proxy& value) {
	if (bool(value)) {
		*_pointer |= (1 << _num);
	} else {
		*_pointer &= ((1 << 8) - (1 << _num) - 1);
	}
	return *this;
}


template<std::size_t N>
class my_array<bool, N> {
public:
	my_array();
	proxy at(std::size_t index);
	proxy operator[](std::size_t index);
	bool at(std::size_t index) const;
	bool operator[](std::size_t index) const;
 	bool empty() const {return N == 0; };
  	std::size_t size() const {return N; };
  	void fill(bool val);
private:
	uint8_t _array[(N + 7) / 8];
};

template<std::size_t N>
my_array<bool, N>::my_array() {
	fill(0);
}

template<std::size_t N>
proxy my_array<bool, N>::at(std::size_t index) {
	if (index >= N && index < 0) {
		std::cout << "wrong index";
		exit(0);
	}
	return proxy(_array + index / 8, index % 8);
}

template<std::size_t N>
bool my_array<bool, N>::at(std::size_t index) const {
	if (index >= N && index < 0) {
		std::cout << "wrong index";
		exit(0);
	}
	return (*this)[index];
}

template<std::size_t N>
proxy my_array<bool, N>::operator[](std::size_t index) {
	return proxy(_array + index / 8, index % 8);
}

template<std::size_t N>
bool my_array<bool, N>::operator[](std::size_t index) const {
	return _array[index / 8]  & (1 << (index % 8));
}

template<std::size_t N>
void my_array<bool, N>::fill(bool value) {
	uint8_t val = 0;
	if (value) {
		val = (1 << 8) - 1;
	}
	for (std::size_t i = 0; i < (N + 7) / 8; i++) {
		_array[i] = val;
	}
}