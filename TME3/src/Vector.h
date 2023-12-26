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
	Vector(const Vector<T>& other);
		
	// Destructeur
	virtual ~Vector() { delete [] space;}
		
	// Operator [] editor
	T& operator[](const size_t index);
	
	// Operator [] 
	const T& operator[](const size_t index) const;
	
	// Operator =
	Vector<T>& operator=(const Vector<T>& other);
	
	// Ajouter à la fin du vecteur
	void push_back(const T& val);
	
	// taille (nombre d'éléments)
	size_t size() const { return CurrentSize; }
	
	// vide ?
	bool empty() const { return CurrentSize == 0;}
	
	template <typename V>
	friend std::ostream& operator<<(std::ostream& os, const Vector<V>& vec);
	
	// begin
	T* begin(){
		return space;
	}

	// end
	T* end(){
		return space+CurrentSize;
	}

	// begin
	T* begin() const {
		return space;
	}

	// end
	T* end() const {
		return space+CurrentSize;
	}

};

} // fin namespace pr

