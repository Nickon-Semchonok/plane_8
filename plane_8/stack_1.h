#pragma once
#include <iostream>
#include <stdexcept>

template<typename T>
class Stack {
private:
	T* data;
	size_t capacity;
	size_t size;

	void resize(size_t new_capacity) {
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < size; ++i) {
			new_data[i] = std::move(data[i]);
		}
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}
public:
	Stack() : data(nullptr), capacity(0), size(0) {}

	Stack(size_t capacity) : capacity(capacity), size(0) {
		data = capacity > 0 ? new T[capacity] : NULL;
	}

	~Stack() {
		delete[] data;
		data = NULL;
		capacity = 0;
		size = 0;
	}

	Stack(const Stack& other) : capacity(other.capacity), size(other.size) {
		if (other.capacity > 0) {
			data = new T[other.capacity];
			for (size_t i = 0; i < other.size; ++i) {
				data[i] = other.data[i];
			}
		}
		else {
			data = NULL;
		}
	}

	Stack(Stack&& other) noexcept
		: data(other.data), capacity(other.capacity), size(other.size) {
		other.data = NULL;
		other.capacity = 0;
		other.size = 0;
	}

	Stack& operator=(const Stack& other) {
		if (this == &other) return *this;

		T* new_data = NULL;
		if (other.capacity > 0) {
			new_data = new T[other.capacity];
			for (size_t i = 0; i < other.size; ++i) {
				new_data[i] = other.data[i];
			}
		}

		delete[] data;
		data = new_data;
		capacity = other.capacity;
		size = other.size;
		return *this;
	}

	Stack& operator=(Stack&& other) noexcept {
		if (this == &other) return *this;

		delete[] data;
		data = other.data;
		capacity = other.capacity;
		size = other.size;

		other.data = NULL;
		other.capacity = 0;
		other.size = 0;
		return *this;
	}

	void push(const T& value) {
		if (size >= capacity) {
			size_t new_cap = capacity == 0 ? 1 : capacity * 2;
			resize(new_cap);
		}
		data[size++] = value;
	}

	void push(T&& value) {
		if (size >= capacity) {
			size_t new_cap = capacity == 0 ? 1 : capacity * 2;
			resize(new_cap);
		}
		data[size++] = std::move(value);
	}

	void pop() {
		if (is_empty()) {
			throw std::out_of_range("Stack is empty");
		}
		size--;
	}

	T& peek() {
		if (is_empty()) {
			throw std::out_of_range("Stack is empty");
		}
		return data[size - 1];
	}

	const T& peek() const {
		if (is_empty()) {
			throw std::out_of_range("Stack is empty");
		}
		return data[size - 1];
	}

	bool is_empty() const {
		return size == 0;
	}

	size_t get_size() const {
		return size;
	}

	size_t get_capacity() const {
		return capacity;
	}
};