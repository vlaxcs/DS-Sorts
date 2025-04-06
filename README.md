# Algoritmi de sortare - Structuri de Date

<hr>

## **Temă de laborator**
- Universitatea din București
- Facultatea de Matematică și Informatică
- Licență ~ Informatică IF
- Structuri de Date ~ Semestrul II
- Acest proiect a fost realizat de [Minciunescu Vlad - 151](https://github.com/vlaxcs/), [Ghiță Radu-Ioachim - 152](https://github.com/KoNickss), [Pascariu Carlo-Alexandru - 152](https://github.com/alexandrucarlo)

<hr>

## 1. Teste utilizate

- #### Tipul de date BOOL
  - Secvență de 4.000.000 de 1 și 0, pe poziții aleatorii distribuite 'Gauss'. 
  - Secvență de 4.000.000 de 1 și 0, ordonate în sens crescător.
  - Secvență de 4.000.000 de 1 și 0, ordonate în sens descrescător.

- #### Tipul de date INT
  - Toate cele de mai sus.
  - Numere din [1, 10^9], naturale pe int, distribuite aleatoriu.
  - Numere din [1, 10^10 ~ 2,147,483,647 / INT_MAX], naturale pe int, distribuite în prima jumătate de la [1, 10^4], apoi [10^4, 10^9].
  - Numere din [1, 10^11 ~ 4,294,967,295 / UINT_MAX], naturale pe unsigned int, distribuite în prima jumătate de la [1, 10^4], apoi [10^4, 10^9].

- #### Tipul de date ULL (Unsigned Long Long)
  - Toate cele de mai sus.
  - Numere din [1, 10^19 ~ 18,446,744,073,709,551,615 / ULLONG_MAX], naturale pe unsigned long long.

- #### Tipul de date FLOAT
  - Toate cele de mai sus.
  - Numere din [1, 10^43 ~ 3.40282e+38 / FLT_MAX], reale pe float din float.h.
  - Numere din [-10^4, 10^4], întregi pe float, distribuite aleatoriu.
  - Numere din [-10^4, 10^4], reale pe float, distribuite aleatoriu.

<hr>

## 2. Configurație de testare

CPU: AMD Ryzen 7 2700

## 3. Algoritmi de sortare analizați

- ### Merge Sort

- ### Shell Sort

- ### Radix Sort

- ### Heap Sort

- ### Tim Sort

- ### AVL Sort

- ### Default Sort (STL)

<hr>

## 4. Concluzii

Link la sheet în google docs !!!!!!!!!

### Mențiuni
- Nu am putut împărți proiectul în sorces/headers, deoarece am avut nevoie de template pentru fiecare algoritm în parte (acesta a fost util pentru a le putea testa pentru mai multe tipuri de date).

### Bibliografie:
[^1]: [Heapsort - Brilliant](https://brilliant.org/wiki/heap-sort/)
[^2]: [Heapsort - Programiz](https://www.programiz.com/dsa/heap-sort)
[^3]: [AVL Sort - MCGILL CS](https://www.cs.mcgill.ca/~jeromew/COMP251material/COMP251_Lecture4_W2017.pdf)
[^4]: [AVL Sort - MIT](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/83cdd705cd418d10d9769b741e34a2b8_MIT6_006F11_lec06.pdf)


Scoruri
Scor per Test (% din MAX pe acel TEST)
Scor general = (Scor per Test) / Nr. Teste