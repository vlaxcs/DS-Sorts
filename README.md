1. Numere din [1, 10^9], naturale pe int, distribuite aleatoriu.
2. Numere din [1, 10^10 ~ 2,147,483,647 / INT_MAX], naturale pe int, distribuite în prima jumătate de la [1, 10^4], apoi [10^4, 10^9].
3. Numere din [1, 10^11 ~ 4,294,967,295 / UINT_MAX], naturale pe unsigned int, distribuite în prima jumătate de la [1, 10^4], apoi [10^4, 10^9].
4. Numere din [1, 10^19 ~ 18,446,744,073,709,551,615 / ULLONG_MAX], naturale pe unsigned long long.
5. Numere din [1, 10^43 ~ 3.40282e+38 / FLT_MAX], reale pe float din float.h.
6. Secvență de 4.000.000 de 1 și 0, pe poziții aleatorii distribuite 'Gauss'.
7. Secvență de 4.000.000 de 1 și 0, ordonate în sens crescător.
8. Secvență de 4.000.000 de 1 și 0, ordonate în sens descrescător.
9. Numere din [-10^4, 10^4], întregi pe float, distribuite aleatoriu.
10. Numere din [-10^4, 10^4], reale pe float, distribuite aleatoriu.


Bibliografie:
Heapsort 1 https://brilliant.org/wiki/heap-sort/
Heapsort 2 https://www.programiz.com/dsa/heap-sort
AVL Sort 1 https://www.cs.mcgill.ca/~jeromew/COMP251material/COMP251_Lecture4_W2017.pdf
AVL Sort 2 https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/83cdd705cd418d10d9769b741e34a2b8_MIT6_006F11_lec06.pdf
// radixsort.setbase
// radixsort negative numbers
// lambda asc/desc