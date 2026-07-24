#include "TestScurt.h"
#include <assert.h>
#include "Multime.h"
#include "IteratorMultime.h"
#include "exception"
void testAll() { //apelam fiecare functie sa vedem daca exista
	Multime m;
	assert(m.vida() == true);
	assert(m.dim() == 0); //adaug niste elemente
	assert(m.adauga(5)==true);
	assert(m.adauga(1)==true);
	assert(m.adauga(10)==true);
	assert(m.adauga(7)==true);
	assert(m.adauga(1)==false);
	assert(m.adauga(10)==false);
	assert(m.adauga(-3)==true);
	assert(m.dim() == 5);
	assert(m.cauta(10) == true);
	assert(m.cauta(16) == false);
	assert(m.sterge(1) == true);
	assert(m.sterge(6) == false);
	assert(m.dim() == 4);


	IteratorMultime im = m.iterator();
	im.prim();
	int s = 0;
	while (im.valid()) {
		TElem e = im.element();
		s += e;
		im.urmator();
	}
	assert(s == 19);

	Multime mTest;
	mTest.adauga(50);
	mTest.adauga(60);

	IteratorMultime itTest = mTest.iterator();
	assert(itTest.valid() == true);


	TElem elSters = itTest.elimina();
	assert(mTest.cauta(elSters) == false);
	assert(mTest.dim() == 1);


	assert(itTest.valid() == true);
	itTest.elimina();


	assert(itTest.valid() == false);
	assert(mTest.dim() == 0);


	try {
		itTest.elimina();
		assert(false);
	} catch (std::exception&) {
		assert(true);
	}

}
