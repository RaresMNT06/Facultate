#pragma once

/* Declaratii pentru functiile de test ale aplicatiei
   Implementarile sunt in teste.cpp
   Toate functiile ruleaza asertiuni - crapa programul daca un test esueaza */

   /* Ruleaza toate testele pentru clasa Masina
	  @param: - ; @return: - */
void testMasina();

/* Ruleaza toate testele pentru clasa Repository
   @param: - ; @return: - */
void testRepository();

/* Ruleaza toate testele pentru clasa Service
   @param: - ; @return: - */
void testService();

/* Ruleaza toate testele pentru cerinta 9 (Lista de spalare) si inchiriere/returnare
   @param: - ; @return: - */
void testListaSpalare();

/* Ruleaza toate testele pentru iteratia 2 (RepoDictionar, Undo, Persistenta)
   @param: - ; @return: - */
void testIteratia2();

/* Ruleaza toate testele aplicatiei (Masina + Repository + Service + Lista spalare + Iteratia 2)
   Se apeleaza din main la pornirea aplicatiei
   @param: - ; @return: - */
void runAllTests();