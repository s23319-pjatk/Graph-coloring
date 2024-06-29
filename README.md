# Graph-coloring
MHE - Metaheuristic, in this case i'll try to make graph coloring.

Kolorowanie grafu polega na przypisaniu kolorów do wierzchołków w taki sposób, aby żadne dwa sąsiednie wierzchołki nie miały tego samego koloru. Minimalna liczba kolorów potrzebnych do pokolorowania grafu, aby spełnić tę właściwość, nazywana jest liczbą chromatyczną grafu.

Folder (Graph-color i Problem_optymalizacyjny) są początkowymi nieudanymi eksperymentami ktore moga sie nie kompilowac.

Głowny plik to "algorytmy.cpp" w którym znajduje się Klasa graph z metodą dostępowa V, Algorytm Kolorowania Grafu (Algorytm pełnego przeglądu (Brute Force)), Algorytmy Wspinaczkowe:
1. Klasyczny algorytm wspinaczkowy: W tej wersji, dla każdego bieżącego rozwiązania wybieramy najlepszego sąsiada, który ma najmniejszy konflikt (czyli najmniej kolizji kolorów).
2.Algorytm wspinaczkowy z losowym wyborem sąsiada: W tej wersji, dla każdego bieżącego rozwiązania losowo wybieramy sąsiada i przechodzimy do niego, jeśli poprawia rozwiązanie.
Algorytm Tabu i Algorytm Symulowanego wyżarzania - Jest to metoda optymalizacji metaheurystycznej, która stara się znaleźć rozwiązanie minimalizujące liczbę konfliktów kolorowania grafu.

!Kompilacja i uruchomienie!
Skorzystaj z poniższego polecenia do kompilacji programu:

g++ -std=c++11 main.cpp -o main

Uruchomienie programu:

./main 4 0 1 1 2 2 3

Po uruchomieniu programu zostaniesz poproszony o podanie maksymalnej liczby kolorów, wyboru algorytmu oraz odpowiednich parametrów (np. pełny przegląd, wspinaczkowy klasyczny, wspinaczkowy losowy, rozmiaru listy Tabu, początkowej temperatury, współczynnika chłodzenia). Program przeprowadzi kolorowanie grafu zgodnie z wybranym algorytmem i wyświetli wyniki.

na koniec male podsumowanie,
Te kody pozwalają na:
Tworzenie i zarządzanie grafem.
Generowanie różnych rozwiązań problemu kolorowania grafu.
Stosowanie różnych algorytmów optymalizacyjnych do minimalizacji liczby konfliktów kolorowania grafu.
Interakcję z użytkownikiem poprzez linię komend, umożliwiającą elastyczne wprowadzanie parametrów i wybór algorytmów.
Program może być użyty do testowania różnych podejść do kolorowania grafu i porównywania ich efektywności w kontekście minimalizacji liczby konfliktów.
