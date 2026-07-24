#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Tests.h" 
#include "UI/Consola.h"

void adaugaDateDefault(MasinaService* service) {
	//adaugam 5 masini pentru a avea date la pornire
	adaugaMasinaService(service, "CJ 01 ABC", "Dacia Duster", "SUV");
	adaugaMasinaService(service, "B 99 XYZ", "VW Golf", "Sedan");
	adaugaMasinaService(service, "IS 20 RRR", "Audi A4", "Berlina");
	adaugaMasinaService(service, "CJ 77 WOO", "Renault Megane", "Sedan");
	adaugaMasinaService(service, "B 101 KKK", "Skoda Octavia", "Berlina");
}



int main() {
	
	ruleazaToateTestele();

	
	
	MyRepo* repo = creeazaRepo();
	MasinaService* service = creeazaService(repo);
	
	adaugaDateDefault(service);
	
	Consola* ui = creeazaConsola(service);

	printf("Daca vezi acest mesaj, inseamna ca toate testele au trecut!!!\n");
	printf("Aplicatia pentru inchirieri masini a pornit\n");
	

	
	ruleazaConsola(ui);

	distrugeConsola(ui);
	distrugeService(service);
	

	if (_CrtDumpMemoryLeaks())
		printf("Exista Memory Leaks!");
	else
		printf("Nu exista Memory Leaks!");

	return 0;
}