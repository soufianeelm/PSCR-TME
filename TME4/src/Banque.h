#pragma once

#include "Compte.h"
#include <unordered_set>
#include <vector>

namespace pr {

class Banque {
	mutable std::unordered_set<const Compte*> comptesVus;
	typedef std::vector<Compte> comptes_t;
	mutable comptes_t comptes;
public :
	Banque (size_t ncomptes, size_t solde) : comptes (ncomptes, Compte(solde)){
	}
	void transfert(size_t deb, size_t cred, unsigned int val) ;
	size_t size() const ;
	bool comptabiliser (int attendu) const ;
};

}
