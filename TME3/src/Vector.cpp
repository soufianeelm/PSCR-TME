#include "Vector.h"

namespace pr {

template<typename T>
Vector<T>::Vector(const Vector<T>& other){
	capacity = other.capacity;
	CurrentSize = other.CurrentSize;
	space = new T[capacity];
	for (size_t i=0; i < CurrentSize; i++){
		space[i] = other.space[i];
	}
}

template<typename T>
T& Vector<T>::operator[](const size_t index) {
	if (index < CurrentSize)
		return space[index];
	throw std::out_of_range("Index out of range");
}

template<typename T>
const T& Vector<T>::operator[](const size_t index) const {
	if (index < CurrentSize)
		return space[index];
	throw std::out_of_range("Index out of range");
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		delete [] space;
		capacity = other.capacity;
		CurrentSize = other.CurrentSize;
		space = new T[capacity];
		for (size_t i=0; i < other.CurrentSize; i++){
			space[i] = other.space[i];
		}
	}
	return *this;
}

template<typename T>
void Vector<T>::push_back(const T& val) {
	if (CurrentSize == capacity) {
		capacity *= 2;
		T* temp = new T[capacity];
		for (size_t i=0; i < CurrentSize; i++){
			temp[i] = space[i];
		}
		delete [] space;
		space = temp;
	}
	space[CurrentSize] = val;
	CurrentSize++;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		os << vec[i];
	}
	return os;
}

}
