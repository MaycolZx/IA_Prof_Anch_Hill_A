#include "drawMatrix.h"
#include "graphNodeEdgeM.h"
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void funcion01(int valor) { cout << valor; }

int main() {
  myRenderG glfwRunMatrix;
  CGraph graph;
  graph.InsertNode();
  graph.ConnectNodes();
  graph.nodes[1][1]->estado = false;

  graph.destruirDeMaycol(20);
  int valor;
  cout << "Seleccione una opcion: \n1. DSF: \n2. BFS: \n3. HillClimbing: \n4. "
          "A*: \nLa opcion es: ";
  cin >> valor;

  while (true) {
    if (valor == 1) {
      CNode *startNode = graph.nodes[0][0];
      CNode *endNode = graph.nodes[19][19];
      vector<CNode *> dfsPath = graph.DFS(startNode, endNode);
      // std::vector<int> evenNumbers;
      // std::thread generateThread([&evenNumbers, 1, 20]() {
      //     evenNumbers = generateEvenNumbers(1, 20);
      //     });
      // std::thread thread1([&dfsPath, startNode, endNode ]);
      // std::thread thread2(funcion01, 6);
      glfwRunMatrix.initGlfw();
      glfwRunMatrix.initWindowsC();
      glfwRunMatrix.runDerMatrixB(graph.nodes, dfsPath);
      // thread1.join();
      // thread2.join();
      for (auto node : dfsPath) {
        cout << "(" << node->valuex << ", " << node->valuey << ") -> ";
      }
      break;
    } else if (valor == 2) {
      CNode *startNode = graph.nodes[0][0];
      CNode *endNode = graph.nodes[19][19];
      vector<CNode *> bfsPath = graph.BFS(startNode, endNode);
      glfwRunMatrix.initGlfw();
      glfwRunMatrix.initWindowsC();
      glfwRunMatrix.runDerMatrixB(graph.nodes, bfsPath);

      for (auto node : bfsPath) {
        cout << "(" << node->valuex << ", " << node->valuey << ") -> ";
      }
      break;
    } else if (valor == 3) {
      vector<CNode *> bHillClimbing =
          graph.HillClimbing(graph.nodes[5][5], graph.nodes[19][19]);
      glfwRunMatrix.initGlfw();
      glfwRunMatrix.initWindowsC();
      glfwRunMatrix.runDerMatrixB(graph.nodes, bHillClimbing);
      break;
    } else if (valor == 4) {
      vector<CNode *> lAstar = graph.Astar(5, 5, 19, 19, 100);
      glfwRunMatrix.initGlfw();
      glfwRunMatrix.initWindowsC();
      glfwRunMatrix.runDerMatrixB(graph.nodes, lAstar);
      break;
    }
  }

  /*for (auto f = graph.nodes.begin(); f != graph.nodes.end(); f++) {
      for (auto g = (*f).begin(); g != (*f).end(); g++) {
          cout << (*g)->value_x << " y su valor es " << (*g)->value_y << "\n";
      }
  }*/

  // NodoInicial = Negro
  // Todos Nodos lista = Azul
  // Ruta = Rojo

  return 0;
}
