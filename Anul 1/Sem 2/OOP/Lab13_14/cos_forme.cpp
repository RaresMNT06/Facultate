#include "cos_forme.h"

#include <QPainter>
#include <QPaintEvent>
#include <QRandomGenerator>
#include <QColor>

/* Constructor - inregistreaza fereastra ca observer
   @param service: referinta la service ; @param parent: parintele Qt
   @return: - */
CosForme::CosForme(Service& service, QWidget* parent)
    : QWidget(parent), service{ service } {
    setWindowTitle("Cos Forme - vizualizare desenata");
    resize(500, 400);

    // Ne inregistram ca observer la service
    service.addObserver(this);
}

/* Destructor - de-inregistreaza din observatori
   IMPORTANT: fara asta, Service ar avea pointer la obiect distrus
   @param: - ; @return: - */
CosForme::~CosForme() {
    service.removeObserver(this);
}

/* Override Observer::update()
   Cere Qt sa redeseneze fereastra (apeleaza paintEvent automat)
   QWidget::update() programeaza un repaint - paintEvent va fi apelat curand
   @param: - ; @return: - */
void CosForme::update() {
    // QWidget::update() forteaza redesenarea ferestrei
    // (NU confundam cu Observer::update() - acelasi nume, dar functii diferite)
    QWidget::update();
}

/* Suprascris din QWidget - apelat automat de Qt cand trebuie sa desenam
   Aici facem desenul propriu-zis cu QPainter

   Desenez:
   - Fundal alb pentru contrast
   - Mesaj text in coltul stanga sus cu numarul de masini
   - Cate un cerc colorat la pozitie random pentru fiecare masina din cos

   @param event: evenimentul (neutilizat) ; @return: - */
void CosForme::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    // Cream painterul - 'this' = desenam pe aceasta fereastra
    QPainter p{ this };

    // Activam anti-aliasing pentru cercuri mai netede
    p.setRenderHint(QPainter::Antialiasing, true);

    // Fundal alb
    p.fillRect(rect(), Qt::white);

    // Aflam cate masini sunt in cos
    size_t nrMasini = service.lungimeListaSpalate();

    // Afisam textul cu numarul de masini (sus stanga)
    p.setPen(Qt::black);
    QFont font = p.font();
    font.setPointSize(12);
    font.setBold(true);
    p.setFont(font);
    p.drawText(10, 25, QString("Cos: %1 masini").arg(nrMasini));

    // Daca cosul e gol, afisam mesaj si iesim
    if (nrMasini == 0) {
        p.setPen(Qt::gray);
        font.setPointSize(14);
        font.setBold(false);
        p.setFont(font);
        p.drawText(rect(), Qt::AlignCenter, "Cosul este gol");
        return;
    }

    // Folosim un seed bazat pe nrMasini pentru ca desenul sa fie consistent
    // (cand redesenam aceeasi situatie, vedem aceleasi pozitii)
    // Daca vrem complet random la fiecare repaint, scoatem seed-ul
    QRandomGenerator generator(static_cast<quint32>(nrMasini * 31));

    // Culori predefinite pentru cercuri (rotam prin ele)
    QColor culori[] = {
        QColor(255, 100, 100),  // rosu
        QColor(100, 255, 100),  // verde
        QColor(100, 100, 255),  // albastru
        QColor(255, 200, 100),  // portocaliu
        QColor(255, 100, 255),  // magenta
        QColor(100, 255, 255),  // turcoaz
        QColor(255, 255, 100),  // galben
        QColor(200, 100, 255)   // violet
    };
    int nrCulori = sizeof(culori) / sizeof(culori[0]);

    // Desenam un cerc pentru fiecare masina din cos
    int marginSus = 50;  // lasam loc pentru text sus
    for (size_t i = 0; i < nrMasini; ++i) {
        // Pozitie random in interiorul ferestrei
        // Lasam marginSus pixeli sus pentru text si 60 pe alte parti pentru cerc
        int x = generator.bounded(30, width() - 60);
        int y = generator.bounded(marginSus, height() - 60);

        // Diametru random intre 30 si 60 pixeli
        int diametru = generator.bounded(30, 60);

        // Culoare rotativa
        QColor culoare = culori[i % nrCulori];

        // Setam culoarea de umplere si o margine subtire neagra
        p.setBrush(culoare);
        p.setPen(QPen(Qt::black, 1));

        // Desenam elipsa (= cerc cand latimea = inaltimea)
        p.drawEllipse(x, y, diametru, diametru);
    }
}
