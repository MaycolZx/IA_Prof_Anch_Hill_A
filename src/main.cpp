#include "drawMatrix.h"
#include "graphNodeEdgeM.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    myRenderG glfwRunMatrix;
    CGraph graph;
    graph.InsertNode();
    graph.ConnectNodes();
    graph.nodes[1][1]->estado = false;

    graph.destruirDeMaycol(20);
    int valor;
    cout << "Seleccione una opcion: \n1. BSF: \n2. : \n3. HillClimbing: \n4. A*: \nLa opcion es: ";
    cin >> valor;


    while (true)
    {
        if (valor == 1) {
            cout << "Amplitud " << endl;
            break;
        }
        else if (valor == 2) {
            cout << "Amplitud " << endl;
            break;
        }
        else if (valor == 3) {
            vector <CNode*> bHillClimbing = graph.HillClimbing(graph.nodes[5][5], graph.nodes[19][19]);
            glfwRunMatrix.initGlfw();
            glfwRunMatrix.initWindowsC();
            glfwRunMatrix.runDerMatrixB(graph.nodes, bHillClimbing);
            break;
        }
        else if (valor == 4) {
            vector <CNode*> lAstar = graph.Astar(5, 5, 19, 19, 100);
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

    //NodoInicial = Negro
    //Todos Nodos lista = Azul
    //Ruta = Rojo

    return 0;
}