#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#define PI 3.14159265358979f

int winW = 1200, winH = 800, moonSides = 6;
float zoom = 1.f, moonAngle = 0.8f, orbitRadius = 0.28f, t = 0.f;

float asp() { return (float)winW / winH; }
float mx()  { return (cosf(moonAngle) * orbitRadius * zoom) / asp(); }
float my()  { return sinf(moonAngle) * orbitRadius * zoom; }

// 🔹 Fungsi gambar lingkaran / shape
void shape(float x, float y, float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= seg; i++) {
        float a = 2.f * PI * i / seg;
        glVertex2f(x + cosf(a)*r/asp(), y + sinf(a)*r);
    }
    glEnd();
}

// 🔹 Render Dunia (Sederhana)
void drawWorld() {
    // Background
    glBegin(GL_QUADS);
    glColor3f(0.02f, 0.02f, 0.08f);
    glVertex2f(-1,-1); glVertex2f(1,-1);
    glColor3f(0.05f, 0.05f, 0.15f);
    glVertex2f(1,1); glVertex2f(-1,1);
    glEnd();

    // 🌞 Matahari (polos)
    glColor3f(1.f, 0.8f, 0.2f);
    shape(0.55f * zoom, 0.f, 0.13f * zoom, 50);

    // 🌍 Bumi (polos)
    glColor3f(0.2f, 0.5f, 1.f);
    shape(0.f, 0.f, 0.085f * zoom, 50);

    // Orbit bulan
    glColor3f(0.7f, 0.7f, 1.f);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<100;i++){
        float a = 2*PI*i/100;
        glVertex2f(cosf(a)*orbitRadius*zoom/asp(), sinf(a)*orbitRadius*zoom);
    }
    glEnd();

    // 🌙 Bulan
    glColor3f(0.7f, 0.7f, 0.8f);
    shape(mx(), my(), 0.05f * zoom, moonSides);
}

int main() {
    glfwInit();
    GLFWwindow* win = glfwCreateWindow(winW, winH, "Simple Solar System", 0, 0);
    glfwMakeContextCurrent(win);
    gladLoadGL();

    double prev = glfwGetTime();

    while(!glfwWindowShouldClose(win)) {
        double now = glfwGetTime();
        float dt = now - prev;
        prev = now;

        // animasi orbit bulan
        moonAngle += 0.5f * dt;

        glClear(GL_COLOR_BUFFER_BIT);
        drawWorld();

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
}