#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];

	lock(debiteur.getMutex(), crediteur.getMutex());

	if (comptesVus.find(&debiteur) == comptesVus.end() && comptesVus.find(&crediteur) == comptesVus.end()) {

		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}

	}

	debiteur.getMutex().unlock();
	crediteur.getMutex().unlock();
}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		comptesVus.insert(&compte);
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}

}
