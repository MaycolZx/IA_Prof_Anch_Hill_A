#pragma once
#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

struct CEdge;

struct CNode {
  CNode(int x, int y, float x1, float y1) {
    valuex = x;
    valuey = y;
    value_x = x1;
    value_y = y1;
  }

  list<CEdge *> edges;
  int valuex;
  int valuey;
  float value_x;
  float value_y;
  bool estado = true;
  vector<CNode *> camino_desde_inicial;
  float distancia_objetivo;
};

struct CEdge {
  CEdge(CNode *a, CNode *b, float distance) {
    nodes[0] = a;
    nodes[1] = b;
    distancia = distance;
    nodes[0]->edges.push_back(this);
    nodes[1]->edges.push_back(this);
  }

  ~CEdge() {}

  CNode *nodes[2];
  float distancia;
};

class CGraph {
public:
  float spacing = 0.05f;

  bool InsertNode() {
    float x_pr = -1;
    float y_pr = 1;

    for (int i = 0; i < 20; ++i) {
      vector<CNode *> t1;
      for (int j = 0; j < 20; ++j) {

        CNode *node = new CNode(i, j, x_pr, y_pr);
        t1.push_back(node);
        x_pr = x_pr + 0.1;
        // x_pr = x_pr + (j*spacing);
      }
      x_pr = -1;
      nodes.push_back(t1);
      y_pr = y_pr - 0.1;
      // y_pr = y_pr - (i * spacing);
    }
    return true;
  }

  bool InsertEdge(CNode *a, CNode *b, float dist) {
    new CEdge(a, b, dist);
    return true;
  }

  bool ConnectNodes() {
    int numRows = nodes.size();
    int numCols = nodes[0].size();

    // Loop through each node to connect with its adjacent nodes
    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numCols; ++j) {
        // Connect with right node if it exists
        if (j + 1 < numCols) {
          InsertEdge(nodes[i][j], nodes[i][j + 1], 10);
        }

        // Connect with bottom node if it exists
        if (i + 1 < numRows) {
          InsertEdge(nodes[i][j], nodes[i + 1][j], 10);
        }

        // Connect with diagonal node (bottom right) if it exists
        if (i + 1 < numRows && j + 1 < numCols) {
          InsertEdge(nodes[i][j], nodes[i + 1][j + 1], 10 * sqrt(2));
        }

        // Connect with diagonal node (top right) if it exists
        if (i - 1 >= 0 && j + 1 < numCols) {
          InsertEdge(nodes[i][j], nodes[i - 1][j + 1], 10 * sqrt(2));
        }
      }
    }
    return true;
  }
  // Destruir nodos
  void destruirDeBerly(float percent) {

    int numNodesToChange =
        int(nodes.size() * nodes[0].size() * percent / 100.0);
    vector<CNode *> allNodes;
    for (auto &row : nodes) {
      for (auto &node : row) {
        allNodes.push_back(node);
      }
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(allNodes.begin(), allNodes.end(), g);

    for (int i = 0; i < numNodesToChange; ++i) {
      allNodes[i]->estado = false;
    }
  }
  // BFS
  vector<CNode *> BFS(CNode *start, CNode *end) {
    unordered_map<CNode *, CNode *> parent;
    queue<CNode *> q;
    q.push(start);
    parent[start] = nullptr;
    while (!q.empty()) {
      CNode *current = q.front();
      q.pop();
      if (current == end) {
        vector<CNode *> path;
        for (CNode *node = end; node != nullptr; node = parent[node]) {
          path.push_back(node);
        }
        reverse(path.begin(), path.end());
        return path;
      }
      for (auto &edge : current->edges) {
        CNode *neighbor =
            (edge->nodes[0] == current) ? edge->nodes[1] : edge->nodes[0];
        if (!parent.count(neighbor) && neighbor->estado) {
          parent[neighbor] = current;
          q.push(neighbor);
        }
      }
    }
    // Si no se encuentra el nodo final, devolver un camino vacío
    return vector<CNode *>();
  }

  // vector<CNode*> BFS(CNode* start, CNode* end)
  // {
  //     vector<CNode*> path;
  //     unordered_map<CNode*, bool> visited;
  //     queue<CNode*> q;
  //
  //     // Marcar el nodo inicial como visitado y agregarlo al camino
  //     visited[start] = true;
  //     path.push_back(start);
  //     q.push(start);
  //
  //     while (!q.empty())
  //     {
  //         CNode* current = q.front();
  //         q.pop();
  //
  //         for (auto& edge : current->edges)
  //         {
  //             CNode* neighbor = (edge->nodes[0] == current) ? edge->nodes[1]
  //             : edge->nodes[0]; if (!visited[neighbor] && neighbor->estado)
  //             {
  //                 visited[neighbor] = true;
  //                 path.push_back(neighbor);
  //                 q.push(neighbor);
  //                 if (neighbor == end) {
  //                     return path; // Devolver el camino si se encuentra el
  //                     nodo final
  //                 }
  //             }
  //         }
  //     }
  //     // Si no se encuentra el nodo final, vaciar el vector de camino y
  //     devolverlo vacío path.clear(); return path;
  // }
  // DFS
  void DFSUtil(CNode *current, CNode *end,
               unordered_map<CNode *, bool> &visited, vector<CNode *> &path) {
    if (current == end) {
      return;
    }

    for (auto &edge : current->edges) {
      CNode *neighbor =
          (edge->nodes[0] == current) ? edge->nodes[1] : edge->nodes[0];
      if (!visited[neighbor] && neighbor->estado) {
        visited[neighbor] = true;
        path.push_back(neighbor);
        DFSUtil(neighbor, end, visited, path);
        if (path.back() == end) {
          return;
        }
      }
    }

    // Si no se encuentra el nodo final, eliminar el nodo actual del camino
    path.pop_back();
  }
  vector<CNode *> DFS(CNode *start, CNode *end) {
    vector<CNode *> path;
    unordered_map<CNode *, bool> visited;

    // Marcar el nodo inicial como visitado y agregarlo al camino
    visited[start] = true;
    path.push_back(start);

    // Llamar a la función DFS recursiva
    DFSUtil(start, end, visited, path);

    // Devolver el camino encontrado
    return path;
  }

  // A*
  int heuristica(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx * dx + dy * dy;
  }

  vector<CNode *> Astar(int startx, int starty, int endx, int endy,
                        int iterationLimit) {
    vector<pair<int, int>> path;
    vector<CNode *> pathv;
    int iterations = 0;

    // nodo para la funcion
    struct NodeAstar {
      int x, y, g, h, f; // g = costo desde el inicio, h = distancia restante
                         // estimada, f = costo total
      bool operator<(const NodeAstar &other) const { return f > other.f; }
    };

    if (!nodes[starty][startx]->estado || !nodes[endy][endx]->estado) {
      cout << "Nodo inicial o nodo objetivo no valido" << endl;
      return pathv;
    }

    // conjunto de nodos cerrados para evitar duplicados
    vector<vector<bool>> closedSet(nodes.size(),
                                   vector<bool>(nodes[0].size(), false));

    // cola de prioridad para almacenar los nodos abiertos, osea las opciones a
    // donde se puede mover
    priority_queue<NodeAstar> openSet;

    // nodo inicial
    NodeAstar starNode{startx, starty, heuristica(startx, starty, endx, endy),
                       0};
    openSet.push(starNode);

    // registro de los padres de los nodos
    vector<vector<pair<int, int>>> cameFrom(
        nodes.size(), vector<pair<int, int>>(nodes[0].size(), {-1, -1}));

    while (!openSet.empty() &&
           (iterationLimit == -1 || iterations < iterationLimit)) {
      // obtener nodo con menor costo total estimado de la cola
      NodeAstar current = openSet.top();
      openSet.pop();
      int x = current.x;
      int y = current.y;

      // comprobar si llegó al objetivo

      if (x == endx && y == endy) {
        while (x != startx || y != starty) { // reconstruir el camino desde el
                                             // objetivo hasta el inicio
          path.push_back({x, y});
          auto prev = cameFrom[y][x];
          x = prev.first;
          y = prev.second;
        }
        path.push_back({startx, starty}); // añadir el nodo inicial al camino
        reverse(path.begin(),
                path.end()); // el camino empieza desde el nodo inicial

        for (int i = 0; i < path.size(); i++) {
          for (int j = 0; j < nodes.size(); j++) {
            for (int k = 0; k < nodes[0].size(); k++) {
              if (nodes[j][k]->valuex == path[i].first &&
                  nodes[j][k]->valuey == path[i].second) {
                pathv.push_back(nodes[j][k]);
              }
            }
          }
        }

        return pathv;
      }

      // marcar actual como visitado
      closedSet[y][x] = true;

      // crear sucesores
      for (size_t i = 0; i < dirX.size(); i++) {
        int newx = x + dirX[i];
        int newy = y + dirY[i];

        // ver si valen
        if (newx >= 0 && newx < nodes[0].size() && newy >= 0 &&
            newy < nodes.size() && nodes[newy][newx]->estado) {
          int Gscore =
              current.g +
              10; // costo al sucesor (falta setear a 10 o 10 raiz de 2)

          // si tiene costo menor y esta en el closedset no entra ya que es un
          // nodo ya visitado
          if (closedSet[newy][newx] && Gscore >= current.g)
            continue;

          if (!closedSet[newy][newx] || Gscore < current.g) {
            // calcular heuristica del sucesor
            int h = heuristica(newx, newy, endx, endy);

            // agregar sucesor al conjunto abierto y actualizar sus valores
            NodeAstar neighbor{newx, newy, Gscore, h, Gscore + h};
            openSet.push(neighbor);

            // registrar al padre del sucesor
            cameFrom[newy][newx] = {x, y};
          }
        }
      }
      iterations++;
    }
    cout << "no se encontró camino" << endl;
    return pathv;
  }

  // HillClimbing

  float DistanciaEuclidiana(CNode *a, CNode *b) {
    float dx = a->value_x - b->value_x;
    float dy = a->value_y - b->value_y;
    return sqrt(dx * dx + dy * dy);
  }

  vector<CNode *> HillClimbing(CNode *nodo_inicial, CNode *nodo_objetivo) {
    vector<CNode *> L;
    L.push_back(nodo_inicial);

    while (!L.empty()) {
      CNode *n = L.front();
      L.erase(L.begin());

      if (n == nodo_objetivo) {
        return n->camino_desde_inicial;
      }

      vector<pair<float, CNode *>> hijos_ordenados;
      for (CEdge *edge : n->edges) {
        CNode *hijo = (edge->nodes[0] == n) ? edge->nodes[1] : edge->nodes[0];

        if (hijo->estado == false ||
            find(n->camino_desde_inicial.begin(), n->camino_desde_inicial.end(),
                 hijo) != n->camino_desde_inicial.end()) {
          continue;
        }

        float distancia = DistanciaEuclidiana(hijo, nodo_objetivo);
        hijos_ordenados.push_back({distancia, hijo});
      }

      sort(hijos_ordenados.begin(), hijos_ordenados.end());

      for (auto &par : hijos_ordenados) {
        CNode *hijo = par.second;
        hijo->camino_desde_inicial = n->camino_desde_inicial;
        hijo->camino_desde_inicial.push_back(n);
        L.insert(L.begin(), hijo);
      }
    }

    return vector<CNode *>();
  }
  void LimpiarCaminos() {
    for (auto &row : nodes) {
      for (auto &node : row) {
        node->camino_desde_inicial.clear();
      }
    }
  }

  void print() { cout << nodes[0][0]->estado << endl; }

public:
  vector<vector<CNode *>> nodes;
  vector<int> dirX = {-1, 0, 1, -1, 1, -1, 0, 1};
  vector<int> dirY = {-1, -1, -1, 0, 0, 1, 1, 1};
};
