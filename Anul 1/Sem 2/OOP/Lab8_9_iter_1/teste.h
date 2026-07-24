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

/* Ruleaza toate testele aplicatiei (Masina + Repository + Service + Lista spalare)
   Se apeleaza din main la pornirea aplicatiei
   @param: - ; @return: - */
void runAllTests();