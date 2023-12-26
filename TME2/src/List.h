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
	size_t length() const {
	      size_t len = 1;
	      if (next != nullptr)
	          len += next->length();
	      return len;
	      }
	};

template<typename T>

class List {
public:
	Chainon<T> *debut;

	// Constructeur vide
	List(): debut(nullptr) {}
	
	// Constructeur par copie
	List(const List& other) {
		if (other.debut) {
			debut = new Chainon<T>(other.debut->data);
			Chainon<T> *p = debut;
			Chainon<T> *tmp = other.debut->next;
			while(tmp) {
				p->next = new Chainon<T>(tmp->data);
				p = p->next;
				tmp = tmp->next;
				}
			}
		}

	// operator [] editor
	T& operator[](size_t index) {
		Chainon<T> *p = debut;
		while(index && p){
			p = p->next;
			index--;
			}
		if (!index)
			return p->data;
		throw std::out_of_range("index out of range");
		}
	
	// operator []
	const T& operator[](size_t index) const {
			Chainon<T> *p = debut;
			while(index && p){
				p = p->next;
				index--;
				}
			if (!index)
				return p->data;
			throw std::out_of_range("index out of range");
			}

	// operator =
	List& operator=(const List& other) {
		if (this != &other) {
			if (other.debut) {
				for (Chainon<T> * c = debut; c ; ){
					Chainon<T> * tmp = c->next;
					delete c;
					c = tmp;
					}
				debut = new Chainon<T>(other.debut->data);
				Chainon<T> *p = debut;
				Chainon<T> *tmp = other.debut->next;
				while(tmp) {
					p->next = new Chainon<T>(tmp->data);
					p = p->next;
					tmp = tmp->next;
					}
			}
		}
		return *this;
	}

	// ajoute en tête
	void push_front(const T& val) {
		debut = new Chainon<T>(val, debut);
		}
	
	// Destructeur
	~List() { 
	        for (Chainon<T> * c = debut; c ; ){
	                Chainon<T> * tmp = c->next;
	                delete c;
	                c = tmp;
	                }
	        }
	
	// ajoute à la fin
	void push_back(const T& val) {
	        if (debut == nullptr)
	                debut = new Chainon<T>(val);
	        else {
		        Chainon<T> *p = debut;
		        while(p->next){
			        p = p->next;
			        }
		        p->next = new Chainon<T>(val);
		        }
		}
			
	// taille (nombre d'éléments)
	size_t size() const {
		if (debut == nullptr) 
		        return 0;
		else return debut->length();
		}
	
	// vide?
	bool empty() const { return debut == nullptr;}

	// operator <<
	friend std::ostream& operator<<(std::ostream& os, const List& list) {
		for (size_t i = 0; i < list.size(); i++) {
			os << list[i];
		}
		return os;
	}

};

} // fin namespace pr
