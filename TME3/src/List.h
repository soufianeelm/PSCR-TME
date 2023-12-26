#pragma once
#include <cstddef> // size_t
#include <ostream> // ostream

namespace pr {

template<typename T>

class Chainon {
public:
	T data;
	Chainon *next;
	// Constructeur par défault
	Chainon(const T& val, Chainon *next=nullptr): data(val), next(next){}
	
	// taille
	size_t length() const;

	};

template<typename T>

class List {
public:
	Chainon<T> *debut;

	// Constructeur vide
	List(): debut(nullptr) {}
	
	// Constructeur par copie
	List(const List<T>& other);

	// operator [] editor
	T& operator[](size_t index);
	
	// operator []
	const T& operator[](size_t index) const;

	// operator =
	List& operator=(const List& other);

	// ajoute en tête
	void push_front(const T& val);
	
	// Destructeur
	~List() { 
	        for (Chainon<T> * c = debut; c ; ){
	                Chainon<T> * tmp = c->next;
	                delete c;
	                c = tmp;
	                }
	        }
	
	// ajoute à la fin
	void push_back(const T& val);
			
	// taille (nombre d'éléments)
	size_t size() const;
	
	// vide?
	bool empty() const { return debut == nullptr;}

	template<typename V>
	// operator <<
	friend std::ostream& operator<<(std::ostream& os, const List<V>& list);

	class Iterator {
		Chainon<T> *ptr;
	public :
		Iterator(Chainon<T> *ptr=nullptr): ptr(ptr) {}

		bool operator!=(const Iterator& other) const;

		T& operator*();

		// pré-incrémentation
		Iterator& operator++();

		//post-incrémentation
		Iterator operator++(int);

	};

	class Const_Iterator {
		Chainon<T> *ptr;
	public :
		Const_Iterator(Chainon<T> *ptr=nullptr): ptr(ptr) {}

		bool operator!=(const Const_Iterator& other) const;

		const T& operator*() const;

		// pré-incrémentation
		Const_Iterator& operator++();

		//post-incrémentation
		Const_Iterator operator++(int);

	};

	// begin
	Iterator begin(){
		return Iterator(debut);
	}

	// end
	Iterator end(){
		return Iterator();
	}

	Const_Iterator begin() const{
		return Const_Iterator(debut);
	}

	// end
	Const_Iterator end() const{
		return Const_Iterator();
	}

};

} // fin namespace pr
