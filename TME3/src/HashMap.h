#pragma once
#include "Vector.h"
#include "List.h"
#include <functional> // std::hash
#include <cstddef> // size_t
#include <ostream> // ostream

namespace pr {

template <typename K, typename V>
struct Entry {
    const K key;
    V value;

    Entry(const K& key, const V& value): key(key), value(value) {}

};

template <typename K, typename V>
class HashMap {
public:
    Vector<List<Entry<K, V>>> buckets;
    // Constructeur
    HashMap (size_t taille=10): buckets(taille) {
    	buckets.CurrentSize = taille;
    }

    // valeur d'une clé
    V* get(const K& key);

    bool put (const K& key, const V& value);

    size_t size();

    void grow();


    template <typename A, typename B>
    friend std::ostream& operator<<(std::ostream& os, const HashMap<A, B>& tab);

    Entry<K, V>& operator[](size_t index);



};

} // fin namespace pr
