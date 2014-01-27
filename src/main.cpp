#include <GLFW/glfw3.h>

void reshape(GLFWwindow* window, int width, int height ) {
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW );
    glLoadIdentity();
}

void drawSkullAt(float pos_x, float pos_y) {
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 1.f);

            glVertex2f(pos_x + 60, pos_y + 40);
            glVertex2f(pos_x - 60, pos_y + 40);
            glVertex2f(pos_x - 60, pos_y - 50);
            glVertex2f(pos_x + 60, pos_y - 50);
    
            glVertex2f(pos_x - 30, pos_y + 40);
            glVertex2f(pos_x + 30, pos_y + 40);
            glVertex2f(pos_x + 30, pos_y + 55);
            glVertex2f(pos_x - 30, pos_y + 55);
    
            glColor3f(0.f, 0.f, 0.f);
            
            glVertex2f(pos_x - 40, pos_y - 0);
            glVertex2f(pos_x - 10, pos_y - 0);
            glVertex2f(pos_x - 10, pos_y + 30);
            glVertex2f(pos_x - 40, pos_y + 30);
            
            glVertex2f(pos_x + 40, pos_y - 0);
            glVertex2f(pos_x + 10, pos_y - 0);
            glVertex2f(pos_x + 10, pos_y + 30);
            glVertex2f(pos_x + 40, pos_y + 30);
        glEnd();
    
        glBegin(GL_TRIANGLES);
            glVertex2f(pos_x, pos_y + 30);
            glVertex2f(pos_x + 10, pos_y + 40);
            glVertex2f(pos_x - 10, pos_y + 40);
        glEnd();
    glPopMatrix();
}

int main(void) {
    GLFWwindow* window;
    
    const int width=640, height=480;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, height, "GLFW Skeleton", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    reshape(window, width, height);
    
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glfwSetWindowSizeCallback(window, reshape);
    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* e.g. */
        drawSkullAt(width/2, height/2);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}