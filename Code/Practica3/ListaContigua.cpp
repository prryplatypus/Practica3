#include "ListaContigua.h"

using namespace std;

bool ListaContigua::isLlena() {
	return (n == capacidad);
}

ListaContigua::ListaContigua() {
	vector = NULL; // No hay que reservar memoria ya que la ListaContigua se crea vac�a en un principio
	n=0;
	capacidad=0;
}

ListaContigua::ListaContigua(ListaContigua &lista) {
	this->n = lista.getN();
	this->capacidad = lista.getCapacidad();
	this->vector = (DATA_TYPE*)malloc(sizeof(DATA_TYPE) * capacidad);
	assert(this->vector != nullptr);
	memcpy(this->vector, lista.vector, sizeof(DATA_TYPE) * n);
}

DATA_TYPE *ListaContigua::getContent()
{
	return this->vector;
}

DATA_TYPE ListaContigua::getValor(int posicion) {
	assert(posicion >= 0 && posicion <= n-1);
	return (vector[posicion]);
}

void ListaContigua::setValor(int posicion, DATA_TYPE nuevoValor) {
	assert(posicion >= 0 && posicion <= n-1);
	vector[posicion] = nuevoValor;
}

unsigned ListaContigua::getN() {
	return (n);
}

unsigned ListaContigua::getCapacidad() {
	return (capacidad);
}

void ListaContigua::insertarAlFinal (DATA_TYPE nuevoValor) {
	insertar(n, nuevoValor);
}

void ListaContigua::eliminarAlFinal () {
	eliminar(n - 1);
}

void ListaContigua::insertar(int posicion, DATA_TYPE nuevoValor) {
	assert(posicion >= 0 && posicion <= n);

	// Si la ListaContigua est� ya llena, antes de insertar ampliamos su capacidad en INCREMENTO
	if (isLlena()) {
		vector = (DATA_TYPE*)realloc(vector, sizeof(DATA_TYPE)*(capacidad + INCREMENTO));
		capacidad += INCREMENTO;
	}

	// Dejamos hueco para el nuevo elemento, desplazando a la derecha los que hay a partir de posicion hasta el final
	memmove(&vector[posicion + 1], &vector[posicion], sizeof(DATA_TYPE)*(n - posicion));

	// Metemos el nuevo elemento
	n++;
	setValor(posicion, nuevoValor);
}

void ListaContigua::eliminar(int posicion) {
	assert(posicion >= 0 && posicion <= n - 1);

	// Tapamos el hueco dejado por el elemento eliminado. Para ello, desplazamos a la izquierda los
	// elementos que hay a partir de posicion+1 hasta el final
	memmove(&vector[posicion], &vector[posicion + 1], sizeof(DATA_TYPE)*(n - posicion - 1));
	n--;

	// Si la capacidad sobrante es demasiada (2*INCREMENTO), la reducimos en INCREMENTO unidades
	if (capacidad - n == 2 * INCREMENTO) {
		vector = (DATA_TYPE *)realloc(vector, sizeof(DATA_TYPE)*(capacidad - INCREMENTO));
		capacidad -= INCREMENTO;
	}

}

void ListaContigua::concatenar(ListaContigua *listaAConcatenar) {
	assert(listaAConcatenar != NULL);
	
	// Tama�o de la lista a concatenar. Por convenci�n, cuando tenemos
	// dos listas, el tama�o de una es "n" y el de la otra es "m"
	int m = listaAConcatenar->getN(); 
	
	// Primero vamos a ampliar la capacidad para asegurarnos de que los
	// nuevos elementos quepan. Para curarnos en salud, ampliamos la 
	// capacidad en el tama�o de la listaAConcatenar
	// Complejidad temporal O(n) 
	// Complejidad espacial O(m+n)
	vector = (DATA_TYPE *)realloc(vector, sizeof(DATA_TYPE)*(capacidad + m));
	capacidad += m;

	// Vamos insertando al final elemento a elemento. F�jate en que insertar un elemento al final
	// es O(1) si no tenemos que ampliar la capacidad (la cual ya est� ampliada)
	// Complejidad temporal O(m)
	// Complejidad espacial O(1)
	for (int i = 0; i < m; i++) {
		insertarAlFinal(listaAConcatenar->getValor(i));
	}
}

int ListaContigua::buscar(DATA_TYPE elementoABuscar) {
	int posicion = 0; // Posici�n actual en donde buscamos
	bool encontrado = false; // Nos indica si hemos encontrado o no el elemento

	// Buscamos el elemento hasta que lo encontremos o hasta que lleguemos al final
	while (!encontrado && posicion < n) {
		if (vector[posicion] == elementoABuscar) encontrado = true;
		posicion++;
	}

	// Devolvemos la posici�n si lo hemos encontrado, o -1 en caso contrario
	if (encontrado) return (posicion - 1);
	else return (-1);
}


ListaContigua::~ListaContigua() {
	free(vector);
}


