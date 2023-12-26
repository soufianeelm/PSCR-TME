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
    V* get(const K& key) {
        size_t h = std::hash<K>()(key) % buckets.size();
        for (size_t i = 0; i < buckets[h].size(); i++) {
            if (buckets[h][i].key == key)
                return &buckets[h][i].value;
        }
        return nullptr;
    }
    
    bool put (const K& key, const V& value) {
        V* entry = get(key);
        if (!entry) {
            size_t h = std::hash<K>()(key) % buckets.size();
            buckets[h].push_front(Entry<K, V>(key,value));
        } else 
            *entry = value;
        if (this->size()*10 >= 8*buckets.size())
        	this->grow();
        return entry != nullptr;
    }
    
    size_t size() {
    	size_t tot = 0;
    	for (size_t i = 0; i < buckets.size(); i++) {
    		tot += buckets[i].size();
    	}
        return tot;
    }

    void grow() {
        HashMap<K, V> tmp(buckets.size()*2);
        for (size_t i = 0; i < buckets.size(); i++) {
            for (size_t j = 0; j < buckets[i].size(); j++)
                tmp.put(buckets[i][j].key, buckets[i][j].value);
        }
        std::swap(buckets, tmp.buckets);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const HashMap& tab) {
    	for (size_t i = 0; i < tab.buckets.size(); i++) {
    		os << "bucket : ";
    		for (size_t j = 0; j < tab.buckets[i].size(); j++) {
    			os << tab.buckets[i][j].key << " : " << tab.buckets[i][j].value << " ";
    			}
    		os << "\n";
    	    }
    	return os;
    }

    Entry<K, V>& operator[](size_t index) {
    	if (index < this->size()) {
    		for (size_t i = 0; i < buckets.size(); i++) {
    			if (index < buckets[i].size()) {
    				return buckets[i][index];
    			}
    			index -= buckets[i].size();
    		}
    	}
    	throw std::out_of_range("index out of range");
    }

};

} // fin namespace pr
