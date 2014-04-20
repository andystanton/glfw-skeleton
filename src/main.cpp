#include <GLFW/glfw3.h>

void drawSkullAt(float pos_x, float pos_y) {
    glPushMatrix();
        glTranslatef(pos_x, pos_y, 0);
        glBegin(GL_QUADS);
            glColor3f(1.f, 1.f, 1.f);

            // top of skull
            glVertex2f( 60, 50);
            glVertex2f( 60,  0);
            glVertex2f(-60,  0);
            glVertex2f(-60, 50);

            // left of eyes
            glVertex2f(-40,   0);
            glVertex2f(-40, -30);
            glVertex2f(-60, -30);
            glVertex2f(-60,   0);

            // centre of eyes
            glVertex2f( 10,   0);
            glVertex2f( 10, -30);
            glVertex2f(-10, -30);
            glVertex2f(-10,   0);

            // right of eyes
            glVertex2f( 60,   0);
            glVertex2f( 60, -30);
            glVertex2f( 40, -30);
            glVertex2f( 40,   0);

            // left of nose
            glVertex2f(  0, -30);
            glVertex2f(-10, -40);
            glVertex2f(-60, -40);
            glVertex2f(-60, -30);

            // right of nose
            glVertex2f( 60, -30);
            glVertex2f( 60, -40);
            glVertex2f( 10, -40);
            glVertex2f(  0, -30);

            // jaw
            glVertex2f(-30, -40);
            glVertex2f( 30, -40);
            glVertex2f( 30, -55);
            glVertex2f(-30, -55);
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
        glClearColor(0.109803922, 0.109803922, 0.109803922, 1.0);
        
        drawSkullAt(width/2, height/2);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
