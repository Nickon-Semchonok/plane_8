#pragma once
#include <string>
#include <iostream>
#include <format>
#include <cstring>
#include <stdexcept>

template<typename T>
class vector2_t {
private:
	T x;
	T y;
	char* name;
public:
	vector2_t() {
		x = 0;
		y = 0;
		name = NULL;
	}

	vector2_t(T x) {
		this->x = x;
		this->y = 0;
		name = NULL;
	}

	vector2_t(T x, T y) : x{ x }, y{ y } {
		name = NULL;
	}

	vector2_t(T x, T y, const char* name) : x{ x }, y{ y } {
		if (name != NULL) {
			size_t len = strlen(name) + 1;
			this->name = new char[len];
			strcpy_s(this->name, len, name);
		}
		else {
			this->name = NULL;
		}
	}

	vector2_t(const vector2_t& other) {
		this->x = other.x;
		this->y = other.y;
		if (other.name != NULL) {
			size_t len = strlen(other.name) + 1;
			this->name = new char[len];
			strcpy_s(this->name, len, other.name);
		}
		else {
			this->name = NULL;
		}
	}

	vector2_t(vector2_t&& other) noexcept {
		this->x = other.x;
		this->y = other.y;
		this->name = other.name;
		other.name = NULL;
	}

	~vector2_t() {
		if (name != NULL) {
			delete[] name;
			name = NULL;
		}
	}

	T get_x() const { return x; }
	T get_y() const { return y; }
	void set_x(T x) { this->x = x; }
	void set_y(T y) { this->y = y; }

	char* get_name() const { return name; }
	void set_name(const char* name) {
		if (this->name != NULL) {
			delete[] this->name;
			this->name = NULL;
		}
		if (name != NULL) {
			size_t len = strlen(name) + 1;
			this->name = new char[len];
			strcpy_s(this->name, len, name);
		}
	}

	T& operator[](size_t index) {
		if (index == 0) return x;
		if (index == 1) return y;
		throw std::out_of_range("Vector index out of range");
	}

	const T& operator[](size_t index) const {
		if (index == 0) return x;
		if (index == 1) return y;
		throw std::out_of_range("Vector index out of range");
	}

	std::string to_string() const {
		if (name != NULL) {
			return std::format("{0}({1}; {2})", name, x, y);
		}
		return std::format("({0}; {1})", x, y);
	}

	vector2_t operator +(const vector2_t& other) const {
		char* new_name = NULL;
		if (this->name != NULL && other.name != NULL) {
			size_t len1 = strlen(this->name);
			size_t len = len1 + strlen(other.name) + 2;
			new_name = new char[len];
			strcpy_s(new_name, len, this->name);
			strcat_s(new_name, len, "+");
			strcat_s(new_name, len, other.name);
		}
		return vector2_t(this->x + other.x, this->y + other.y, new_name);
	}

	vector2_t operator -(const vector2_t& other) const {
		char* new_name = NULL;
		if (this->name != NULL && other.name != NULL) {
			size_t len1 = strlen(this->name);
			size_t len = len1 + strlen(other.name) + 2;
			new_name = new char[len];
			strcpy_s(new_name, len, this->name);
			strcat_s(new_name, len, "-");
			strcat_s(new_name, len, other.name);
		}
		return vector2_t(this->x - other.x, this->y - other.y, new_name);
	}

	vector2_t& operator =(const vector2_t& other) {
		if (this == &other) return *this;
		this->x = other.x;
		this->y = other.y;
		if (this->name != NULL) {
			delete[] this->name;
			this->name = NULL;
		}
		if (other.name != NULL) {
			size_t len = strlen(other.name) + 1;
			this->name = new char[len];
			strcpy_s(this->name, len, other.name);
		}
		else {
			this->name = NULL;
		}
		return *this;
	}

	vector2_t& operator =(vector2_t&& other) noexcept {
		if (this == &other) return *this;
		this->x = other.x;
		this->y = other.y;
		if (this->name != NULL) {
			delete[] this->name;
		}
		this->name = other.name;
		other.name = NULL;
		return *this;
	}

	void operator += (const vector2_t& other) {
		this->x += other.x;
		this->y += other.y;
	}

	void operator += (T n) {
		this->x += n;
		this->y += n;
	}

	void operator -= (const vector2_t& other) {
		this->x -= other.x;
		this->y -= other.y;
	}

	void operator -= (T n) {
		this->x -= n;
		this->y -= n;
	}
};

template<typename T>
vector2_t<T> operator -(const vector2_t<T>& v) {
	return vector2_t<T>(-v.get_x(), -v.get_y());
}

template<typename T>
vector2_t<T> operator *(const vector2_t<T>& v, T n) {
	return vector2_t<T>(v.get_x() * n, v.get_y() * n);
}

template<typename T>
vector2_t<T> operator *(T n, const vector2_t<T>& v) {
	return vector2_t<T>(v.get_x() * n, v.get_y() * n);
}

template<typename T>
vector2_t<T> operator /(const vector2_t<T>& v, T n) {
	return vector2_t<T>(v.get_x() / n, v.get_y() / n);
}

template<typename T>
std::ostream& operator <<(std::ostream& out, const vector2_t<T>& v) {
	out << v.to_string();
	return out;
}
