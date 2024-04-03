#pragma once
#include "graphNodeEdgeM.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

const float center = 0.025;
const float weight_Windows = 600;
const int height_Windows = 600;
const float numeroNodos[2] = { 20,20 };

void drawSquare(float x, float y, float size) {
    glBegin(GL_QUADS);
    glVertex2f(x - size / 2, y - size / 2);
    glVertex2f(x + size / 2, y - size / 2);
    glVertex2f(x + size / 2, y + size / 2);
    glVertex2f(x - size / 2, y + size / 2);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2, float lineWidth) {
    glLineWidth(lineWidth); // Establecer el grosor de la línea
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

class myRenderG
{
public:
    myRenderG();
    ~myRenderG();
    void initGlfw();
    void runDerMatrixB(vector<vector<CNode*>> nodes , vector<CNode*> l_Astar);
    void initWindowsC();
private:
    GLFWwindow* window;
};

myRenderG::myRenderG(){
    window = nullptr;
}
myRenderG::~myRenderG(){
    glfwDestroyWindow(window);
}

void myRenderG::initGlfw() {
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void myRenderG::initWindowsC() {
    window = glfwCreateWindow(weight_Windows, height_Windows, "Malla Cuadricular", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
}

void myRenderG::runDerMatrixB(vector<vector<CNode*>> nodes, vector<CNode*> l_Astar) {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Color background
        glClear(GL_COLOR_BUFFER_BIT);

        //glColor3f(0.0f, 0.0f, 0.0f); //Color de los cuadrados
        //float initialX = -1.0f;
        //float initialY = 1.0f;
        //float size = 0.02f;
        //float spacing = 0.1f;

        /*for (int i = 0; i < numeroNodos[0]; i++) {
            for (int j = 0; j < numeroNodos[1]; j++) {
                drawSquare(initialX + (i * spacing) + center, initialY - center - (j * spacing), size);
            }
        }*/

        float size = 0.02f;
        float spacing = 0.01f;

        for (auto f = nodes.begin(); f != nodes.end(); f++) {
            for (auto g = (*f).begin(); g != (*f).end(); g++) {
                if ((*g)->estado == true) {
                    glColor3f(1.0f, 0.0f, 0.0f); //Color de los cuadrados
                    drawSquare((*g)->value_x + center, (*g)->value_y -center, size);
                    for (auto edge : (*g)->edges)
                    {
                        if (edge->nodes[0]->estado && edge->nodes[1]->estado) {
                            glColor3f(0.0f, 0.0f, 0.0f);
                            drawLine(edge->nodes[0]->value_x + center, edge->nodes[0]->value_y- center, edge->nodes[1]->value_x + center, edge->nodes[1]->value_y-center, 1.0f);
                        }     
                    }
                }
            }
        }
        if (!l_Astar.empty()) {
            for (int i = 0; i < l_Astar.size()-1; i++) {
                //cout << "(" << l_Astar[i]->valuex << "-" << l_Astar[i]->valuey << ") ; (" << l_Astar[i + 1]->valuex<< "-"<<l_Astar[i+1]->valuey<<endl;
                glColor3f(0.0f, 0.0f, 1.0f);
                drawLine(l_Astar[i]->value_x + center, l_Astar[i]->value_y - center, l_Astar[i + 1]->value_x + center, l_Astar[i + 1]->value_y - center, 3.0f);
            }
            cout << endl << "\n";
        }
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}

