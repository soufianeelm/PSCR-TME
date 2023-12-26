#pragma once
#include <cstddef> // size_t
#include <ostream> // ostream

namespace pr {

template<typename T>

class Vector {
public :
	T* space;
	size_t capacity;
	size_t CurrentSize;
	// Constructeur par défault
	Vector(int size=10): space(new T[size]), capacity(size), CurrentSize(0) {}
	
	// Constructeur par copie
	Vector(const Vector& other){
		capacity = other.capacity;
		CurrentSize = other.CurrentSize;
		space = new T[capacity];
		for (size_t i=0; i < CurrentSize; i++){
			space[i] = other.space[i];
			}
		}
		
	// Destructeur
	virtual ~Vector() { delete [] space;}
		
	// Operator [] editor
	T& operator[](const size_t index) {
		if (index < CurrentSize)
			return space[index];
		throw std::out_of_range("Index out of range");
		}
	
	// Operator [] 
	const T& operator[](const size_t index) const {
		if (index < CurrentSize)
			return space[index];
		throw std::out_of_range("Index out of range");
		}
	
	// Operator =
	Vector& operator=(const Vector& other) {
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
	
	// Ajouter à la fin du vecteur
	void push_back(const T& val) {
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
	
	// taille (nombre d'éléments)
	size_t size() const { return CurrentSize; }
	
	// vide ?
	bool empty() const { return CurrentSize == 0;}
	
	friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
	  for (size_t i = 0; i < vec.size(); i++) {
	    os << vec[i];
	    }
	  return os;
	  }
	
};

} // fin namespace pr
