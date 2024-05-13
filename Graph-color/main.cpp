//
//  main.cpp
//  Graph-color
//
//  Created by Marceli Gosztyła on 11/05/2024.
//

#include <iostream>
#include <queue>
#include <sstream>
#include <algorithm>
#include <vector>


using namespace std;

class Graph {
    int V; //liczba wierzchołków
    vector<vector<int> > adj; // lista sąsiedztwa
    
public:
    Graph(int V); //Konstruktor
    void addEdge(int v, int w); //dodawanie krawędzi do grafu
    vector<int> greedyColoring(); // algorytm kolorowania grafu
};

Graph::Graph(int V) {
    this ->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // graf nieskierowany, więc dodajemy krawędź w drugą stronę
}

vector<int> Graph::greedyColoring() {
    vector<int> result(V, -1); // Tablica wynikowa, w której przechowujemy kolory przypisane do wierzchołków
    vector<bool> available(V, false); // Tablica do śledzenia użytych kolorów przez sąsiadów
    
    result[0] = 0; // Przypisujemy pierwszy wierzchołek koloru 0
    
    // Przypisanie kolorów pozostałym V-1 wierzchołkom
    for(int u = 1; u < V; u++) {
        // Wybieramy kolor dla wierzchołka u, których nie jest używany przez sąsiadów
        for (int i : adj[u])
            if (result[i] != -1)
                available[result[i]] = true;
        
        int cr;
        for (cr = 0; cr < V; cr++)
            if (available[cr] == false)
                break;
        
        result[u] = cr; // Przypisujemy wybrany kolor
        
        // Resetujemy tablicę avialable dla następnych wierzchołków
        for (int i : adj[u])
            if (result[i] != -1)
                available[result[i]] = false;
    }
    return result;
    // Wyświetlenie wyników
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Użycie: " << argv[0] << " liczba_wiercholkow krawedzie" << endl;
        return 1;
    }
    
    int V = atoi(argv[1]);
    if (V <= 0) {
        cout << "Liczba wierzcholkow musi byc dodatnia." << endl;
        return 1;
    }
    
    Graph g(V);
    
    if (argc != V + 2) {
        cout << "Podano nieprawidlowa liczbe krawedzi." << endl;
        return 1;
    }
    
    for (int i = 2; i < argc; ++i) {
        stringstream ss(argv[i]);
        int u, v;
        ss >> u >> v;
        g.addEdge(u, v);
    }
    
    vector<int> colors = g.greedyColoring();
    
    cout << "Kolorowanie grafu: \n";
    for(int i = 0; i < V; ++i)
        cout << "Wierzcholek " << i << " ---> Kolor " << colors[i] << "\n";
    
    return 0;
}
