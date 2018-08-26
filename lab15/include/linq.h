#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <iterator>

#define EMPTY_POINTER nullptr

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;


template<typename T>
class enumerator {
public:
	virtual const T& get_obj() = 0;
	virtual void first() = 0;
	virtual void operator++() = 0; 
	virtual operator bool() = 0;

	auto drop(int count) {
		return drop_enumerator<T>(this, count);
	}

	auto take(int count) {
		return take_enumerator<T>(this, count);
	}

	template<typename U = T, typename F>
	auto select(F func) {
		return select_enumerator<U, T, F> (this, func);
	}

	template<typename F>
	auto until(F func) {
		return until_enumerator<T, F> (this, func);
	}

	auto until_eq(const T& v) {
		return until([&v](const T& a) { return a == v; });
	}

	template<typename F>
	auto where(F func) {
		return where_enumerator<T, F>(this, func);
	}

	auto where_neq(const T& v) {
		return where([&v](const T& a) { return a != v; });
	}


	std::vector<T> to_vector() {
		std::vector<T> rs;
		first();
		while (*this) {
			rs.push_back(get_obj());
			++(*this);
		}
		return rs;
	}

	template<typename Iter>
	void copy_to(Iter it) {
		first();
		while (*this) {
			*it = get_obj();
			it++;
			++(*this);
		}
	}
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
	range_enumerator(Iter& begin, Iter& end) : begin_(std::move(begin)), end_(std::move(end)) {};
	
	const T& get_obj() {
		return *begin_;
	};
	
	void operator++() { begin_++; };
	
	operator bool() {
	    if (begin_ != end_)
	        return true;
	    return false;
	};
	
	void first() {};

private:
	Iter begin_, end_;
};

template<typename T>
auto from(T begin, T end) {
	return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
	drop_enumerator(enumerator<T> *parent, int count) : parent_(parent), count_(count) {};

	void first() {
		while (count_ > 0) {
		    parent_->first();
			count_--;
			if (*this)
			    ++(*parent_);
		}
	};

	void operator++() {
	    if (*this)
		    ++(*parent_);
	};

	const T& get_obj() {
		return parent_->get_obj();
	};
	
	operator bool() {
	    return *parent_;
	}

private:
	enumerator<T> *parent_;
	int count_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
	take_enumerator(enumerator<T> *parent, int count) : parent_(parent), count_(count) {};

	void operator++() {
		if (count_ > 0) {
			count_--;
			if (*this)
			    ++(*parent_);
		}
		return;
	};
	
	const T& get_obj() {
		return parent_->get_obj();
	};
	
	operator bool() {
	    return (*parent_) && (count_ > 0);
	};
	
	void first() { parent_->first(); };

private:
	enumerator<T> *parent_;
	int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
public:
	select_enumerator(enumerator<U> *parent, F& func) : parent_(parent), func_(std::move(func)) {};
	const T& get_obj() {
	    obj_ = func_(parent_->get_obj());
		return obj_;
	};
	
	void operator++() {
		return ++(*parent_);
	};
	
	operator bool() {
	    return *parent_;
	};
	
	void first() { parent_->first(); };

private:
	enumerator<U> *parent_;
	F func_;
	T obj_;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
	until_enumerator(enumerator<T> *parent, F& predicate) : parent_(parent), predicate_(std::move(predicate)), fl(true) {};

	const T& get_obj() { 
		return parent_->get_obj();
	};
	
	void operator++() {
		++(*parent_);
		if (! *this)
			return;
		if (predicate_(get_obj())) {
			fl = false;
			return;
		}
	};
	
	operator bool() {
	    return fl && *parent_;
	};
	
	void first() { 
	    parent_->first();
	    if (! *this)
			return;
		if (predicate_(get_obj())) {
			fl = false;
			return;
		}
	};

private:
	enumerator<T> *parent_;
	F predicate_;
	bool fl;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
	where_enumerator(enumerator<T> *parent, F& predicate) : parent_(parent), predicate_(std::move(predicate)) {};

	void first() {
	    parent_->first();
		if (! *this)
			return;
		while (!predicate_(get_obj())) {
			++(*parent_);
			if (! *this)
				return;
		}
	};

	const T& get_obj() {
		return parent_->get_obj();
	};
	
	void operator++() {
		++(*parent_);
		if (! *this)
			return;
		while (!predicate_(get_obj())) {
			++(*parent_);
			if (! *this)
				return;
		}
	};
	
	operator bool() {
	    return *parent_;
	};

private:
	enumerator<T> *parent_;
	F predicate_;
};

#endif
