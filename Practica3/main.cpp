/********************/
/*    PR�CTICA 3    */
/*   N�STOR P�REZ   */
/*   RA�L  SANCHO   */
/********************/

#include "impresionListasContiguas.h"
#include "ListaContigua.h"
#include "Orden.h"

int main(int argc, char* argv[]) {
	ListaContigua lista;
	Orden sorter;

	for (unsigned i = 0; i < 5; ++i)
		lista.insertarAlFinal(i);

	imprimirListaContigua(&lista);

	try {
		std::cout << "Insertion sort DESC:\n";
		sorter.insertionSort(&lista, DESC);
		imprimirListaContigua(&lista);
		std::cout << "Insertion sort ASC:\n";
		sorter.insertionSort(&lista, ASC);
		imprimirListaContigua(&lista);

		std::cout << "Selection sort DESC:\n";
		sorter.selectionSort(&lista, DESC);
		imprimirListaContigua(&lista);
		std::cout << "Selection sort ASC:\n";
		sorter.selectionSort(&lista, ASC);
		imprimirListaContigua(&lista);
	}
	catch (const std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}