#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#include <cstddef>
#include <string>
#include <ostream>

namespace pr {

class Chainon {
public :
	std::string data;
	Chainon * next;
	Chainon (const std::string & data, Chainon * next=nullptr);
	size_t length() ;
	// FAUTE : const en trop
	void print (std::ostream & os);
};

class List {
public:

	Chainon * tete;

	List(): tete(nullptr)  {}

	~List() {
		for (Chainon * c = tete ; c ; ) {
			Chainon * tmp = c->next;
			delete c;
			c = tmp;
		}
	}

	const std::string & operator[] (size_t index) const ;

	void push_back (const std::string& val) ;

	// FAUTE : code au mauvais endroit
	void push_front (const std::string& val);

	bool empty() ;

	size_t size() const ;

	// FAUTE : opération non mit en amie (ou en méthode)
	friend std::ostream & operator<< (std::ostream & os, const List & vec) ;

};



} /* namespace pr */

#endif /* SRC_LIST_H_ */
