#pragma once
#include <vector>
#include <algorithm>
#include <random>   
#include <chrono>    

#include "Repo.h"
#include "Observer.h"
using std::vector;


class ListaLocatari :public Observable {
	vector<Locatar> inLista;
    AbstractRepo& rep;
public:
	ListaLocatari(AbstractRepo& rep) :rep{ rep } {}

	void adauga(const Locatar& loc) {
		inLista.push_back(loc);
		notify();
	}
	void goleste() {
		inLista.clear();
		notify();
	}

	void umple(int cate) {
		inLista.clear();
		int seed = std::chrono::system_clock::now().time_since_epoch().count();
		vector<Locatar> all = rep.getAll();
		std::shuffle(all.begin(), all.end(), std::default_random_engine(seed));
		while (inLista.size() < cate && inLista.size() < rep.getAll().size() && all.size() > 0) {
			inLista.push_back(all.back());
			all.pop_back();
		}

		notify();
	}

	void umple() {
		inLista.clear();
		int seed = std::chrono::system_clock::now().time_since_epoch().count();
		vector<Locatar> all = rep.getAll();
		std::shuffle(all.begin(), all.end(), std::default_random_engine(seed));
		while (all.size() > 0) {
			inLista.push_back(all.back());
			all.pop_back();
		}
		notify();
	}

	const vector<Locatar>& lista() const {
		return inLista;
	}
};