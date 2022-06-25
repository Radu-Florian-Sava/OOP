#include "Locatar.h"

bool cmpProp(const Locatar& l1, const Locatar& l2) {
	return l1.getProprietar() < l2.getProprietar();
}

bool cmpSupr(const Locatar& l1, const Locatar& l2) noexcept{
	return l1.getSuprafata() < l2.getSuprafata();
}
