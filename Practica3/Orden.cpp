#include "Orden.h"

Orden::Orden()
{

}



bool Orden::compare(DATA_TYPE a, DATA_TYPE b, unsigned short order)
{
	switch (order)
	{
	case ASC:
		return a < b;
	case DESC:
		return a > b;
	default:
		throw std::invalid_argument("Invalid sorting order!");
	}
}



bool Orden::esOrdenada(ListaContigua* lista, unsigned short order)
{
	for (unsigned i = 0; i + 1 < lista->getN(); ++i) {
		if (!compare(lista->getValor(i), lista->getValor(i + 1), order))
			return false;
	}
	return true;
}



void Orden::insertionSort(ListaContigua* lista, unsigned short order)
{
	DATA_TYPE tmp;
	unsigned i;
	int j;

	for (i = 1; i < lista->getN(); ++i) {
		tmp = lista->getValor(i);

		for (j = i - 1; j > 0 && compare(tmp, lista->getValor(j), order); --j) {
			lista->setValor(j + 1, lista->getValor(j));
		}

		if (compare(tmp, lista->getValor(j), order)) {
			lista->setValor(j + 1, lista->getValor(j));
			lista->setValor(j, tmp);
		}
		else {
			lista->setValor(j + 1, tmp);
		}
	}
}



Orden::~Orden()
{

}
