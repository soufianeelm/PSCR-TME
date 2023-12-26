#include "HashMap.h"

namespace pr {

template <typename K, typename V>
V* HashMap<K, V>::get(const K& key) {
        size_t h = std::hash<K>()(key) % buckets.size();
        for (size_t i = 0; i < buckets[h].size(); i++) {
            if (buckets[h][i].key == key)
                return &buckets[h][i].value;
        }
        return nullptr;
    }

template <typename K, typename V>
bool HashMap<K, V>::put (const K& key, const V& value) {
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

template <typename K, typename V>
size_t HashMap<K, V>::size() {
    	size_t tot = 0;
    	for (size_t i = 0; i < buckets.size(); i++) {
    		tot += buckets[i].size();
    	}
        return tot;
    }

template <typename K, typename V>
void HashMap<K, V>::grow() {
        HashMap<K, V> tmp(buckets.size()*2);
        for (size_t i = 0; i < buckets.size(); i++) {
            for (size_t j = 0; j < buckets[i].size(); j++)
                tmp.put(buckets[i][j].key, buckets[i][j].value);
        }
        std::swap(buckets, tmp.buckets);
    }

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const HashMap<K, V>& tab) {
    	for (size_t i = 0; i < tab.buckets.size(); i++) {
    		os << "bucket : ";
    		for (size_t j = 0; j < tab.buckets[i].size(); j++) {
    			os << tab.buckets[i][j].key << " : " << tab.buckets[i][j].value << " ";
    			}
    		os << "\n";
    	    }
    	return os;
    }

template <typename K, typename V>
Entry<K, V>& HashMap<K, V>::operator[](size_t index) {
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

}
