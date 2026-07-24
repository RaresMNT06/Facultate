#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include "service.h"
#include "repo.h"

class Simulare_oop : public QMainWindow {
	Q_OBJECT
	public:
        /* Constructor - initializeaza UI si incarca datele*/
		Simulare_oop(QWidget* parent = nullptr);
        /*Destructor*/
		~Simulare_oop();

    private slots:

            /*Se filtreaza dupa genul dat*/
		    void filtreaza();
            /*Se sorteaza dupa titlu*/
		    void sorteaza();
            /*Se da reset la lista anterioara*/
		    void reset();
            /* La selectie afiseaza descrierea filmului in QTextEdit
                @param item: elementul selectat
               */

		    void selectieFilm(QListWidgetItem* item);

    private:
        QListWidget* lista;
        QTextEdit* descriere;
        QPushButton* btnFiltreaza;
        QPushButton* btnSorteaza;
        QPushButton* btnReset;
        QLineEdit* inputFiltru;

        Repository* repo;
        Service* srv;

        /* Afiseaza filmele in lista
            @param filme: vectorul de filme de afisat
         */
        void afiseaza(const std::vector<Film>& filme);
       
};





