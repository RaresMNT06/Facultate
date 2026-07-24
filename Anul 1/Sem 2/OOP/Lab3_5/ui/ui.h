#ifndef UI_H
#define UI_H

#include "../service/service_participant.h"

typedef struct {
    Service* service;
} UI;

/* Initializeaza interfata utilizator prin legarea la service */
void init_ui(UI* ui, Service* s);
/* @param: ui, s; @return: - */

/* Porneste bucla principala a meniului interactiunii */
void run_ui(UI* ui);
/* @param: ui; @return: - */

/* Interfata pentru adaugarea unui participant (citeste ID, Nume, Prenume, Scor) */
void ui_adauga(UI* ui);
/* @param: ui; @return: - */

/* Interfata pentru actualizarea scorului unui participant identificat prin ID */
void ui_actualizeaza(UI* ui);
/* @param: ui; @return: - */

/* Interfata pentru stergerea unui participant identificat prin ID */
void ui_sterge(UI* ui);
/* @param: ui; @return: - */

/* Interfata pentru filtrarea si afisarea participantilor sub un prag de scor */
void ui_filtrare(UI* ui);
/* @param: ui; @return: - */

/* Interfata pentru sortarea listei dupa nume sau scor */
void ui_sorteaza(UI* ui);
/* @param: ui; @return: - */

#endif