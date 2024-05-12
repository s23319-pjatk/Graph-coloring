//  Graph-color


#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graph {
    int V; //liczba wierzchołków
    list<pair<int, int> > *adj; // lista sąsiedztwa z wagami krawędzi
    
public:
    Graph(int V); //Konstruktor
    void addEdge(int v, int w, int weight); //dodawanie krawędzi do grafu
    void printMST(vector<pair<int, int> > &parent); // wyświetlanie MST
    int calculateMSTCost(vector<pair<int, int> > &parent); // oblicznaie kosztu MST
    vector<pair<int, int> > generateRandomSolution(); // generowanie losowego rozwiązania
    vector<pair<int, int> > getNeighborhood(vector<pair<int, int> > &solution); // generowanie sąsiedztwa
};

Graph::Graph(int V) {
    this ->V = V;
    adj = new list<pair<int, int> > [V];
}

void Graph::addEdge(int v, int w, int weight) {
    adj[v].push_back(make_pair(w, weight));
    adj[w].push_back(make_pair(v, weight)); // graf nieskierowany, więc dodajemy krawędź w obie strony
}

void Graph::printMST(vector<pair<int, int> > &parent) {
    cout << "Minimalne drzewo rozpinające:\n";
    for (int i = 1; i < V; ++i)
        cout << "Krawędź: " << parent[i].first << " - " << i << " Waga: " << parent[i].second << endl;
}

int Graph::calculateMSTCost(vector<pair<int, int> > &parent) {
    int cost = 0;
    for (int i = 1; i <V; ++i)
        cost += parent[i].second;
    return cost;
}

vector<pair<int, int> > Graph::generateRandomSolution(){
    vector<pair<int, int> > randomSolution;
    vector<bool> visited(V, false);
    
    srand(time(0)); // inicjalizacja generatora liczb losowych
    
    int startVertex = rand() % V; // losowy startowy wierzchołek
    visited[startVertex] = true;
    
    for (int i = 0; i< V - 1; ++i) {
        int v = -1;
        int w = -1;
        int weight = -1;
    
        // Losowanie kolejnego wierzchołka, który nie jest jeszcze w drzewie
        while (true) {
            v = rand() % V;
            if (!visited[v])
                break;
        }
        //Losowanie wagi krawędzi
        weight = rand() % 10 + 1; //zakładamy wagi od 1 do 10
        
        // Dodawanie krawędzi do rozwiązania
        randomSolution.push_back(make_pair(startVertex, v));
        
        // Zaznaczenie odwiedzenia wierzchołka
        visited[v] = true;
    }
    return randomSolution;
}

vector<pair<int, int> > Graph::getNeighborhood(vector<pair<int, int> > &solution) {
    // W tej implementacji zostanie zwrócone puste sąsiedztwo, ale można ją rozwinąć w bardziej zaawansowane strategie.
    
    vector<pair<int, int> > neighborhood;
    return neighborhood;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Użycie: " << argv[0] << " liczba_wierzcholkow" << endl;
        return 1;
    }
    
    int V = atoi(argv[1]);
    if (V <= 0) {
        cout << "Liczba wierzcholkow musi byc dodatnia." << endl;
        return 1;
    }
    
    Graph g(V);
    // Dodajemy krawędzie do grafu (tutaj można dodawać własną logikę)
    
    // Generujemy losowe rozwiązanie
    vector<pair<int, int> > randomSolution = g.generateRandomSolution();
    
    cout << "Losowe rozwiązanie :\n";
    for (auto edge : randomSolution)
        cout << "Krawedz: " << edge.first << " - " << edge.second << endl;
    
    // Obliczamy koszt MST
    vector<pair<int, int> > parent;
    int MSTCost = g.calculateMSTCost(parent);
    
    cout << "Koszt MST: " << MSTCost << endl;
    
    return 0;
}
