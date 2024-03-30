#include "../include/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 200;
const int GRID_SIZE = 20;

void drawGrid() {
    // Dibujar líneas verticales
    for (int i = -WINDOW_WIDTH / 2; i <= WINDOW_WIDTH / 2; i += WINDOW_WIDTH / GRID_SIZE) {
        glBegin(GL_LINES);
        glColor3f(0.8f, 0.8f, 0.8f);  // Color de las líneas de la malla
        glVertex2f(i, -WINDOW_HEIGHT / 2);
        glVertex2f(i, WINDOW_HEIGHT / 2);
        glEnd();
    }

    // Dibujar líneas horizontales
    for (int j = -WINDOW_HEIGHT / 2; j <= WINDOW_HEIGHT / 2; j += WINDOW_HEIGHT / GRID_SIZE) {
        glBegin(GL_LINES);
        glColor3f(0.8f, 0.8f, 0.8f);  // Color de las líneas de la malla
        glVertex2f(-WINDOW_WIDTH / 2, j);
        glVertex2f(WINDOW_WIDTH / 2, j);
        glEnd();
    }
}

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW\n";
        return -1;
    }

    // Crear una ventana de 200x200
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Malla Cuadricular", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW\n";
        glfwTerminate();
        return -1;
    }

    // Establecer el contexto de la ventana como actual
    glfwMakeContextCurrent(window);

    // Ciclo principal de renderizado
    while (!glfwWindowShouldClose(window)) {
        // Establecer el color de fondo
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Dibujar la malla cuadriculada
        drawGrid();

        // Intercambiar buffers y verificar eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpiar y terminar GLFW
    glfwTerminate();
    return 0;
}
