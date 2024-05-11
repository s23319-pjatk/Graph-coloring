//
//  main.cpp
//  Graph-color
//
//  Created by Marceli Gosztyła on 11/05/2024.
//

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>


using namespace std;

class Graph {
    int V; //liczba wierzchołków
    list<int> *adj; // lista sąsiedztwa
    
public:
    Graph(int V); //Konstruktor
    void addEdge(int v, int w); //dodawanie krawędzi do grafu
    void greedyColoring(); // algorytm kolorowania grafu
};

Graph::Graph(int V) {
    this ->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // graf nieskierowany, więc dodajemy krawędź w drugą stronę
}

void Graph::greedyColoring() {
    vector<int> result(V, -1); // Tablica wynikowa, w której przechowujemy kolory przypisane do wierzchołków
    result[0] = 0; // Przypisujemy pierwszy wierzchołek koloru 0
    // Tablica do śledzenia użytych kolorów przez sąsiadów
    
    vector<bool> available(V, false);
    
    // Przypisanie kolorów pozostałym V-1 wierzchołkom
    for(int u = 1; u < V; u++) {
        // Wybieramy kolor dla wierzchołka u, których nie jest używany przez sąsiadów
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it)
            if (result[*it] != -1)
                available[result[*it]] = true;
        
        int cr;
        for (cr =0; cr< V; cr++)
            if (available[cr] == false)
                break;
        
        result[u] = cr; // Przypisujemy wybrany kolor
        
        // Resetujemy tablicę avialable dla następnych wierzchołków
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it)
            if (result[*it] != -1)
                available[result[*it]] = false;
    }
    
    // Wyświetlenie wyników
    cout << "Kolorowanie grafu:\n";
    for (int u = 0; u < V; u++)
        cout << "Wierzcholek " << u << " ---> Kolor " << result[u] << "\n";
}

int main() {
    int V = 6;
    Graph g(V);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(<#int v#>, <#int w#>)
    cout << "Wyniki kolorowania grafu:\n";
    
    g.greedyColoring();
    
    return 0;
}
