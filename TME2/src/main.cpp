#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include "HashMap.h"

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("tmp/WarAndPeace.txt");

	if (!input.is_open()) {
		perror("Error");
	}

	auto start = steady_clock::now();
	cout << "Parsing War and Peace / using hashmap" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	// vecteur des mots rencontrés
	pr::HashMap<string, int> dejavu;
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// mot déjà vu ?
		if (int *p = dejavu.get(word)){
		        *p += 1;
		} else {
		        dejavu.put(word, 1);
		}

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words with " << dejavu.size() << " different words.\n" << endl;

    vector<pair<string, int>> cpy;
    for (size_t i = 0; i < dejavu.size() ; i++) {
    	cpy.push_back(make_pair(dejavu[i].key,dejavu[i].value));
    }

    sort(cpy.begin(), cpy.end(), [](const pair<string, int>& a, const pair<string, int>& b){ return a.second > b.second;});

    size_t cdt = 0;
    for (const auto& pair : cpy) {
    	if (cdt % 100 == 0)
    		cout << cdt << ": "<< pair.first << " , " << pair.second << "\n";
    	cdt++;
    }
    cout << endl;

    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    if (auto *p = dejavu.get("war"))
          count1 = *p;
    if (auto *p = dejavu.get("peace"))
          count2 = *p;
    if (auto *p = dejavu.get("toto"))
          count3 = *p;
    cout << "war : " << count1 << " times.\n";
    cout << "peace : " << count2 << " times.\n";
    cout << "toto : " << count3 << " times.\n" << endl;

    return 0;
}
