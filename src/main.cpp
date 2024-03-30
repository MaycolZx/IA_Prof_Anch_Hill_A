#include <GLFW/glfw3.h>
#include <iostream>

const int center = 10;
const int height_Windows = 600;
const int weight_Windows = 800;
const int numeroNodos[2] = {10,10};

void drawSquare(float x, float y, float size) {
    glBegin(GL_QUADS);
    glVertex2f(x - size/2, y - size/2);
    glVertex2f(x + size/2, y - size/2);
    glVertex2f(x + size/2, y + size/2);
    glVertex2f(x - size/2, y + size/2);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2, float lineWidth) {
    glLineWidth(lineWidth); // Establecer el grosor de la línea
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW\n";
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(weight_Windows, height_Windows, "Malla Cuadricular", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW\n";
        glfwTerminate();
        return -1;
    }
    // Establecer la ventana como contexto actual
    glfwMakeContextCurrent(window);

    // Ciclo principal de renderizado
    while (!glfwWindowShouldClose(window)) {
        // Establecer el color de fondo
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Dibujar los cuadrados
        glColor3f(0.0f, 0.0f, 0.0f); // Color blanco
        float initialX = -1.0f; // Coordenada X inicial del primer cuadrado
        float size = 0.04f; // Tamaño de los cuadrados
        float spacing = 0.08f; // Espaciado entre cuadrados
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < numeroNodos[1]; j++) {
                std::cout<<i<<","<<j<<" ";
                drawSquare(initialX + i * spacing, j*spacing, size);
            }
        }

        // Dibujar la línea entre los cuadrados
        glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
        drawLine(initialX + size/2, 0.0f, initialX + 10 * spacing - size/2, 0.0f,5.0f);

        // Intercambiar buffers y verificar eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpiar y terminar GLFW
    glfwTerminate();
    return 0;
}
