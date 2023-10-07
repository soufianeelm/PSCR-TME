#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

int main () {

	std::string abc = "abc";

	// FAUTE : caractère de fin manquant
	char * str = new char [4];
	str[0] = 'a';
	str[1] = 'b';
	str[2] = 'c';
	str[3] = '\0';
	size_t i = 0;

	if (! strcmp (str, abc.c_str())) {
		std::cout << "Equal !";
	}

	pr::List list;
	list.push_front(abc);
	list.push_front(abc);

	std::cout << "Liste : " << list << std::endl;
	std::cout << "Taille : " << list.size() << std::endl;

	// Affiche à l'envers

	// FAUTE : size_t ne peut pas prendre de valeur négative
	for (i= list.size(); i > 0 ; i--) {
		std::cout << "elt " << i << ": " << list[i-1] << std::endl;
	}

	// et la chaine elle meme
	delete [] str;

}
