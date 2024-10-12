#pragma once

#include "Compte.h"
#include <vector>
#include <mutex>

using namespace std;

namespace pr {

class Banque {
	typedef std::vector<Compte> comptes_t;
	comptes_t comptes;
	mutable mutex m;
public :
	Banque (size_t ncomptes, size_t solde) : comptes (ncomptes, Compte(solde)){
	}
	void transfert(size_t deb, size_t cred, unsigned int val) ;
	size_t size() const ;
	bool comptabiliser (int attendu) const ;
	Compte& getCompte(size_t index); 
 
};

}
