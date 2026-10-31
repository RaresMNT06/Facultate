Laborator 1 - MAP: Expresii cu numere complexe

1. DESCRIEREA PROIECTARII
Programul primeste din linia de comanda o expresie n1 op n2 op ... op nk, unde ni sunt
numere complexe de forma a+b*i, iar op este unul din operatorii + - * /.
Parserul verifica expresia si construieste un obiect Expression, care calculeaza rezultatul.

Clase:
- ComplexNumber, Expression
- Operation (interfata), Addition, Subtraction, Multiplication, Division, OperationFactory
- ExpressionParser (interfata), CommandLineParser, NumberParser (interfata),
  AlgebraicFormParser, InvalidExpressionException
- Main

2. PRINCIPII SOLID

S - Single Responsibility
Fiecare clasa are un singur rol: ComplexNumber retine datele numarului, fiecare operatie
face un singur calcul, AlgebraicFormParser transforma un text intr-un numar,
CommandLineParser verifica structura expresiei, OperationFactory furnizeaza operatiile,
Expression calculeaza rezultatul, iar Main doar asambleaza componentele.
In diagrama: clase mici, fiecare cu putine metode.

O - Open/Closed
O operatie noua (ex: putere) se adauga printr-o clasa noua care implementeaza Operation,
fara a modifica Expression sau ComplexNumber. O forma noua de scriere a numerelor se
adauga printr-o clasa noua care implementeaza NumberParser, fara a modifica
CommandLineParser.
In diagrama: realizarile interfetelor Operation si NumberParser.

L - Liskov Substitution
Oricare dintre Addition, Subtraction, Multiplication, Division poate fi folosita oriunde
se asteapta o Operation, iar Expression functioneaza corect cu oricare dintre ele.
In diagrama: Expression este legata doar de interfata Operation.

I - Interface Segregation
Interfetele sunt mici: ExpressionParser si NumberParser au cate o singura metoda,
Operation are doua (apply si getSymbol).

D - Dependency Inversion
Expression depinde de interfata Operation, iar CommandLineParser de interfata NumberParser,
nu de clase concrete. Main creeaza clasele concrete o singura data (la asamblare), apoi
lucreaza doar prin interfata ExpressionParser. CommandLineParser primeste dependentele
prin constructor.
In diagrama: asocierile principale merg catre interfete (Operation, NumberParser).

3. SABLOANE DE PROIECTARE

Singleton
OperationFactory are constructor privat, un atribut static instance si o metoda statica
getInstance(), deci exista o singura instanta in program.
In diagrama: stereotipul <<singleton>>, atributul si metoda subliniate (statice).

Factory
OperationFactory.getOperation(symbol) intoarce operatia potrivita simbolului
(+ -> Addition etc.), fara ca restul aplicatiei sa creeze direct clasele concrete.
In diagrama: dependentele <<create>> spre cele 4 operatii si agregarea spre Operation.

Strategy
Interfata Operation defineste o familie de algoritmi interschimbabili (Addition,
Subtraction, Multiplication, Division). Expression primeste una si o aplica fara sa
stie care este.
In diagrama: Expression -> Operation, iar cele 4 clase realizeaza Operation.

4. VALIDARE
Expresia este invalida daca numarul de argumente este par sau mai mic decat 3, daca
operatorul nu este unul din + - * /, daca operatorii nu sunt toti la fel sau daca un
numar nu respecta forma a+b*i. In aceste cazuri se arunca InvalidExpressionException.

5. RESTRICTII
Se folosesc doar array-uri simple (ComplexNumber[], Operation[]), fara colectii
generice, fara lambda-uri si fara stream-uri.