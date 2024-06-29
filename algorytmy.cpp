//
//  test.cpp
//  Graph_color
//
//  Created by Marceli Gosztyła on 17/06/2024.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <list>
#include <unordered_set>
#include <algorithm>
#include <random>

using namespace std;

class Graph {
    int V; // liczba wierzchołków
    vector<vector<int>> adj; // lista sąsiedztwa

public:
    Graph(int V); // konstruktor
    void addEdge(int v, int w); // dodawanie krawędzi do grafu
    int objectiveFunction(const vector<int>& colors); // funkcja celu
    void generateAllColorings(int V, int maxColors, vector<vector<int>>& allColorings); // generowanie wszystkich kolorowań
    int getNumVertices() const; // metoda dostępowa do V
    vector<int> generateRandomSolution(); // generowanie losowego rozwiązania
    vector<vector<int>> generateNeighbors(const vector<int>& colors); // generowanie sąsiadów
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // graf nieskierowany, więc dodajemy krawędź w obie strony
}

int Graph::objectiveFunction(const vector<int>& colors) {
    int conflicts = 0;
    for (int u = 0; u < V; ++u) {
        for (int v : adj[u]) {
            if (colors[u] == colors[v]) {
                conflicts++;
            }
        }
    }
    return conflicts / 2; // ponieważ każda krawędź jest liczona dwukrotnie
}

void Graph::generateAllColorings(int V, int maxColors, vector<vector<int>>& allColorings) {
    int totalColorings = pow(maxColors, V);
    for (int i = 0; i < totalColorings; ++i) {
        vector<int> coloring(V);
        int num = i;
        for (int j = 0; j < V; ++j) {
            coloring[j] = num % maxColors;
            num /= maxColors;
        }
        allColorings.push_back(coloring);
    }
}

int Graph::getNumVertices() const {
    return V;
}

vector<int> Graph::generateRandomSolution() {
    vector<int> colors(V);
    for (int i = 0; i < V; ++i) {
        colors[i] = rand() % V; // losowy kolor z zakresu 0 do V-1
    }
    return colors;
}

vector<vector<int>> Graph::generateNeighbors(const vector<int>& colors) {
    vector<vector<int>> neighbors;
    for (int u = 0; u < V; ++u) {
        for (int c = 0; c < V; ++c) {
            if (c != colors[u]) {
                vector<int> new_colors = colors;
                new_colors[u] = c;
                neighbors.push_back(new_colors);
            }
        }
    }
    return neighbors;
}


// Algorytm pełnego przeglądu (Brute Force)
vector<int> bruteForceColoring(Graph& g, int maxColors) {
    int V = g.getNumVertices(); // uzyskujemy liczbę wierzchołków za pomocą metody dostępnej
    vector<vector<int>> allColorings;
    g.generateAllColorings(V, maxColors, allColorings);

    vector<int> bestColoring;
    int minConflicts = INT_MAX;

    for (const auto& coloring : allColorings) {
        int conflicts = g.objectiveFunction(coloring);
        if (conflicts < minConflicts) {
            minConflicts = conflicts;
            bestColoring = coloring;
        }
    }

    return bestColoring;
}
// Algorytmy wspinaczkowe
vector<int> hillClimbingDeterministic(Graph& g) {
    vector<int> current_solution = g.generateRandomSolution();
    int current_cost = g.objectiveFunction(current_solution);
    bool improved = true;

    while (improved) {
        improved = false;
        vector<vector<int>> neighbors = g.generateNeighbors(current_solution);

        for (const auto& neighbor : neighbors) {
            int neighbor_cost = g.objectiveFunction(neighbor);
            if (neighbor_cost < current_cost) {
                current_solution = neighbor;
                current_cost = neighbor_cost;
                improved = true;
            }
        }
    }

    return current_solution;
}

vector<int> hillClimbingRandom(Graph& g) {
    vector<int> current_solution = g.generateRandomSolution();
    int current_cost = g.objectiveFunction(current_solution);
    bool improved = true;

    while (improved) {
        improved = false;
        vector<vector<int>> neighbors = g.generateNeighbors(current_solution);
        int random_index = rand() % neighbors.size();
        const auto& random_neighbor = neighbors[random_index];
        int neighbor_cost = g.objectiveFunction(random_neighbor);

        if (neighbor_cost < current_cost) {
            current_solution = random_neighbor;
            current_cost = neighbor_cost;
            improved = true;
        }
    }

    return current_solution;
}
// Algorytm Tabu
vector<int> tabuSearch(Graph& g, int maxColors, int tabuSize, int maxIterations) {
    int V = g.getNumVertices();
    vector<int> current_solution = g.generateRandomSolution();
    int current_cost = g.objectiveFunction(current_solution);

    vector<int> best_solution = current_solution;
    int best_cost = current_cost;

    list<vector<int>> tabu_list;
    unordered_set<string> tabu_set;

    auto vectorToString = [](const vector<int>& vec) -> string {
        string s;
        for (int v : vec) {
            s += to_string(v) + ",";
        }
        return s;
    };

    for (int iter = 0; iter < maxIterations; ++iter) {
        vector<vector<int>> neighbors = g.generateNeighbors(current_solution);
        vector<int> best_neighbor;
        int best_neighbor_cost = INT_MAX;

        for (const auto& neighbor : neighbors) {
            int neighbor_cost = g.objectiveFunction(neighbor);
            string neighbor_str = vectorToString(neighbor);

            if (neighbor_cost < best_neighbor_cost && tabu_set.find(neighbor_str) == tabu_set.end()) {
                best_neighbor = neighbor;
                best_neighbor_cost = neighbor_cost;
            }
        }

        current_solution = best_neighbor;
        current_cost = best_neighbor_cost;

        if (current_cost < best_cost) {
            best_solution = current_solution;
            best_cost = current_cost;
        }

        tabu_list.push_back(current_solution);
        tabu_set.insert(vectorToString(current_solution));

        if (tabu_list.size() > tabuSize) {
            string oldest_solution = vectorToString(tabu_list.front());
            tabu_list.pop_front();
            tabu_set.erase(oldest_solution);
        }

        cout << "Iteracja " << iter << ": liczba konfliktów = " << current_cost << endl;

        if (current_cost == 0) {
            break;
        }
    }

    return best_solution;
}

//Algorytm Symulowanego wyżarzania
vector<int> simulatedAnnealing(Graph& g, int maxColors, double initialTemp, double coolingRate, int maxIterations) {
    int V = g.getNumVertices();
    vector<int> current_solution = g.generateRandomSolution();
    int current_cost = g.objectiveFunction(current_solution);

    vector<int> best_solution = current_solution;
    int best_cost = current_cost;

    double temperature = initialTemp;

    auto generateNeighbor = [&](const vector<int>& colors) -> vector<int> {
        vector<int> neighbor = colors;
        int u = rand() % V;
        int new_color = rand() % maxColors;
        neighbor[u] = new_color;
        return neighbor;
    };

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> d(0, 1);

    auto acceptanceProbability = [](int current_cost, int neighbor_cost, double temperature) -> double {
        if (neighbor_cost < current_cost) {
            return 1.0;
        }
        return exp((current_cost - neighbor_cost) / temperature);
    };

    for (int iter = 0; iter < maxIterations; ++iter) {
        vector<int> neighbor = generateNeighbor(current_solution);
        int neighbor_cost = g.objectiveFunction(neighbor);

        double ap = acceptanceProbability(current_cost, neighbor_cost, temperature);
        double random_value = ((double) rand() / (RAND_MAX));

        if (ap > random_value) {
            current_solution = neighbor;
            current_cost = neighbor_cost;
        }

        if (current_cost < best_cost) {
            best_solution = current_solution;
            best_cost = current_cost;
        }

        temperature *= coolingRate;

        cout << "Iteracja " << iter << ": liczba konfliktów = " << current_cost << endl;

        if (current_cost == 0) {
            break;
        }
    }

    return best_solution;
}


// Funkcja główna
int main(int argc, char* argv[]) {
    srand(time(0)); // inicjalizacja generatora liczb losowych

    if (argc < 2 || (argc - 2) % 2 != 0) {
        cout << "Użycie: " << argv[0] << " liczba_wierzcholkow krawedzie" << endl;
        return 1;
    }

    int V = atoi(argv[1]);
    if (V <= 0) {
        cout << "Liczba wierzchołków musi być dodatnia." << endl;
        return 1;
    }

    Graph g(V);

    for (int i = 2; i < argc; i += 2) {
        int u = atoi(argv[i]);
        int v = atoi(argv[i + 1]);
        g.addEdge(u, v);
    }

    cout << "Podaj maksymalną liczbę kolorów: ";
    int maxColors;
    cin >> maxColors;

    cout << "Wybierz algorytm:\n1. Pełny przegląd\n2. Wspinaczkowy klasyczny\n3. Wspinaczkowy losowy\n4. Tabu Search\n5. Symulowane wyżarzanie\n";
    int choice;
    cin >> choice;

    vector<int> solution;
    if (choice == 1) {
        solution = bruteForceColoring(g, maxColors);
    } else if (choice == 2) {
        solution = hillClimbingDeterministic(g);
    } else if (choice == 3) {
        solution = hillClimbingRandom(g);
    } else if (choice == 4) {
        cout << "Podaj rozmiar listy Tabu: ";
        int tabuSize;
        cin >> tabuSize;
        cout << "Podaj maksymalną liczbę iteracji: ";
        int maxIterations;
        cin >> maxIterations;
        solution = tabuSearch(g, maxColors, tabuSize, maxIterations);
    } else if (choice == 5) {
        cout << "Podaj początkową temperaturę: ";
        double initialTemp;
        cin >> initialTemp;
        cout << "Podaj współczynnik chłodzenia: ";
        double coolingRate;
        cin >> coolingRate;
        cout << "Podaj maksymalną liczbę iteracji: ";
        int maxIterations;
        cin >> maxIterations;
        solution = simulatedAnnealing(g, maxColors, initialTemp, coolingRate, maxIterations);
    } else {
        cout << "Nieprawidłowy wybór." << endl;
        return 1;
    }

    cout << "Kolorowanie grafu:\n";
    for (int i = 0; i < V; ++i)
        cout << "Wierzchołek " << i << " ---> Kolor " << solution[i] << "\n";

    cout << "Liczba konfliktów: " << g.objectiveFunction(solution) << "\n";

    return 0;
}
