#include <GLFW/glfw3.h>

void drawSkullAt(float pos_x, float pos_y) {
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 1.f);

            glVertex2f(pos_x + 60, pos_y - 40);
            glVertex2f(pos_x - 60, pos_y - 40);
            glVertex2f(pos_x - 60, pos_y + 50);
            glVertex2f(pos_x + 60, pos_y + 50);
    
            glVertex2f(pos_x - 30, pos_y - 40);
            glVertex2f(pos_x + 30, pos_y - 40);
            glVertex2f(pos_x + 30, pos_y - 55);
            glVertex2f(pos_x - 30, pos_y - 55);
    
            glColor3f(0.f, 0.f, 0.f);
            
            glVertex2f(pos_x - 40, pos_y + 0);
            glVertex2f(pos_x - 10, pos_y + 0);
            glVertex2f(pos_x - 10, pos_y - 30);
            glVertex2f(pos_x - 40, pos_y - 30);
            
            glVertex2f(pos_x + 40, pos_y + 0);
            glVertex2f(pos_x + 10, pos_y + 0);
            glVertex2f(pos_x + 10, pos_y - 30);
            glVertex2f(pos_x + 40, pos_y - 30);
        glEnd();
    
        glBegin(GL_TRIANGLES);
            glVertex2f(pos_x, pos_y - 30);
            glVertex2f(pos_x + 10, pos_y - 40);
            glVertex2f(pos_x - 10, pos_y - 40);
        glEnd();
    glPopMatrix();
}

void reshape(GLFWwindow* window, int width, int height ) {
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION );
    glLoadIdentity();
    glScalef(1.0, -1.0, 1.0);
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW );
    glLoadIdentity();
}

int main(void) {
    GLFWwindow* window;
    
    const int width=640, height=480;
    
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, height, "GLFW Skeleton", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    reshape(window, width, height);
    
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glfwSetWindowSizeCallback(window, reshape);
    
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        drawSkullAt(width/2, height/2);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
