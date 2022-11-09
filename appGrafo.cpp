// =================================================================
//
// File: appGrafo.cpp
// Author: David René Langarica Hernández - A01708936
// Description: Archivo para la actividad 4.1 con la generación de
//              la clase Grafo y la implementación de métodos para
//              el mismo. (Grafo no ponderado)
//
// =================================================================

#ifndef GRAPH
#define GRAPH

#include <bits/stdc++.h>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

// =================================================================
// Definición de la clase Graph
// =================================================================

class Graph {
   private:
    std::vector<bool> visited;

   public:
    Graph(){};

    void loadGraph(int, int, std::vector<std::list<int>>&, std::vector<std::vector<int>>&);
    void DFS(int, std::vector<std::vector<int>>&);
    void BFS(int, std::vector<std::list<int>>&);
};

// =================================================================
// Carga los arcos del grafo y los almacena en una Matriz de Adyacencia
// y en una std::lista de Adyacencia
//
// @returns
// @Complexity O(n), el ciclo depende del número de esquinas en el grafo.
// =================================================================

void Graph::loadGraph(int nvertices, int nedges, std::vector<std::list<int>>& adlist, std::vector<std::vector<int>>& admatrix) {
    int from[nedges] = {0, 0, 0, 2, 2};
    int to[nedges] = {1, 3, 2, 1, 4};

    visited.resize(nvertices, false);

    for (int i = 0; i < nedges; i++) {
        adlist[from[i]].push_back(to[i]);
        adlist[to[i]].push_back(from[i]);

        admatrix[to[i]][from[i]] = 1;
        admatrix[from[i]][to[i]] = 1;
    }
};

// =================================================================
// Imprime el Recorrido de DFS (Profundidad) a partir de nodo inicial.
//
// @returns
// @Complexity O(n), el ciclo depende del número de vertices en el grafo.
// =================================================================

void Graph::DFS(int ini_node, std::vector<std::vector<int>>& admatrix) {
    std::cout << ini_node << " ";

    visited[ini_node] = true;

    for (int i = 0; i < admatrix[ini_node].size(); i++) {
        if (admatrix[ini_node][i] == 1 && (!visited[i])) {
            DFS(i, admatrix);
        }
    }
};

// =================================================================
// Imprima el Recorrido de BFS (Anchura) a partir de nodo inicial.
//
// @returns
// @Complexity O(n^2), se anidan ciclos, uno de ellos depende de que
// la std::queue 'pending' no esté vacía y el otro
// =================================================================

void Graph::BFS(int ini_node, std::vector<std::list<int>>& adlist) {
    std::queue<int> pending;

    int temp_size = visited.size();

    for (int i = 0; i < temp_size; i++) {
        visited[i] = false;
    }

    pending.push(ini_node);
    visited[ini_node] = true;

    while (!pending.empty()) {
        int temp = pending.front();
        std::cout << temp << " ";
        pending.pop();

        for (auto adjacent : adlist[temp]) {
            if (!visited[adjacent]) {
                visited[adjacent] = true;
                pending.push(adjacent);
            }
        }
    }
};

#endif


// =================================================================
// Main
// =================================================================

int main() {
    int nvertices = 5;
    int nedges = 5;

    Graph grafo;

    std::vector<std::list<int>> adlist;
    adlist.resize(nvertices);

    std::vector<bool> visited(nvertices, false);
    std::vector<std::vector<int>> admatrix(nvertices, std::vector<int>(nvertices, 0));

    grafo.loadGraph(nvertices, nedges, adlist, admatrix);
    std::cout << "DFS: ";
    grafo.DFS(0, admatrix);

    std::cout << '\n'
         << "BFS: ";
    grafo.BFS(0, adlist);

    return 0;
};