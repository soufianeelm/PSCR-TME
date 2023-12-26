#include "List.h"

namespace pr {

template<typename T>
size_t Chainon<T>::length() const {
	size_t len = 1;
    if (next != nullptr){
    	len += next->length();
    }
	return len;
}

template<typename T>
List<T>::List(const List<T>& other) {
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

template<typename T>
T& List<T>::operator[](size_t index) {
	Chainon<T> *p = debut;
	while(index && p){
		p = p->next;
		index--;
	}
	if (!index)
		return p->data;
	throw std::out_of_range("index out of range");
}

template<typename T>
const T& List<T>::operator[](size_t index) const {
	Chainon<T> *p = debut;
	while(index && p){
		p = p->next;
		index--;
	}
	if (!index)
		return p->data;
	throw std::out_of_range("index out of range");
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
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

template<typename T>
void List<T>::push_front(const T& val) {
	debut = new Chainon<T>(val, debut);
}

template<typename T>
void List<T>::push_back(const T& val) {
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

template<typename T>
size_t List<T>::size() const {
	if (debut == nullptr)
	    return 0;
	else
		return debut->length();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
	for (size_t i = 0; i < list.size(); i++) {
		os << list[i];
	}
	return os;
}

template<typename T>
bool List<T>::Iterator::operator!=(const List<T>::Iterator& other) const {
	return ptr != other.ptr;
}

template<typename T>
T& List<T>::Iterator::operator*(){
	return ptr->data;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++(){
	ptr = ptr->next;
	return *this;
}

template<typename T>
		//post-incrémentation
typename List<T>::Iterator List<T>::Iterator::operator++(int){
	List<T>::Iterator tmp = *this;
	++(*this);
	return tmp;
}

template<typename T>
bool List<T>::Const_Iterator::operator!=(const List<T>::Const_Iterator& other) const {
	return ptr != other.ptr;
}

template<typename T>
const T& List<T>::Const_Iterator::operator*() const{
	return ptr->data;
}

template<typename T>
// pré-incrémentation
typename List<T>::Const_Iterator& List<T>::Const_Iterator::operator++(){
	ptr = ptr->next;
	return *this;
}

template<typename T>
//post-incrémentation
typename List<T>::Const_Iterator List<T>::Const_Iterator::operator++(int){
	List<T>::Const_Iterator tmp = *this;
	++(*this);
	return tmp;
}

}
