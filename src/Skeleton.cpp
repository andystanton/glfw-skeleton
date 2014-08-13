#include "Skeleton.hpp"

Skeleton::Skeleton(const string & appName, unsigned int width, unsigned int height)
{
    this->appName = appName;
    this->width = width;
    this->height = height;
}

Skeleton::~Skeleton()
{

}

void Skeleton::initGL()
{
    cout << "Initialising OpenGL" << endl;

    // Initialise GLFW
    cout << " - Initialising GLFW";
    if (!glfwInit())
    {
        cout << FAIL << endl;
        throw "Failed to initialise GLFW";
    }
    cout << OK << endl;

    // Create window with GLFW
    cout << " - Creating window with GLFW";
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(
        width,
        height,
        appName.c_str(),
        nullptr,
        nullptr
    );

    if (window == nullptr)
    {
        glfwTerminate();
        cout << FAIL << endl;
        throw "Failed to create window with GLFW.";
    }
    cout << OK << endl;

    // Make window the current OpenGL context
    cout << " - Making window the current OpenGL context";
    glfwMakeContextCurrent(window);
    cout << OK << endl;

    // Initialise GLEW
    cout << " - Initialising GLEW";
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        cout << FAIL << endl;
        throw "Failed to initialise GLEW";
    }
    cout << OK << endl;

    // Set GLFW Options
    cout << " - Setting GLFW Options";
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    cout << OK << endl;

    // Set OpenGL Options
    cout << " - Setting OpenGL Options";
    glClearColor(0.3f, 0.2f, 0.2f, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    cout << OK << endl;
}

void Skeleton::drawSkull(float x, float y, float scale, glm::vec4 colour)
{
    glm::vec2 pos = { x, y };

    glUniformMatrix4fv(matrixId, 1, GL_FALSE, & mvp[0][0]);

    glUniform2fv(posId, 1, &pos[0]);
    glUniform4fv(colourId, 1, &colour[0]);
    glUniform1f(scaleId, scale);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));

    glDrawArrays(GL_TRIANGLES, 0, sizeof(SKULL_VERTICES) / sizeof(GLfloat));

    glDisableVertexAttribArray(0);
}

void Skeleton::setup()
{
    cout << endl << "Running \033[1m" << appName << "\033[0m" << endl;

    try
    {
        initGL();
    }
    catch (const char * error)
    {
        cerr << error << endl;
        exit(-1);
    }

    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    try {
        programId = shaderhelper::createProgram("skull.vertexshader", "skull.fragmentshader");
    }
    catch (const string & error)
    {
        cerr << error << endl;
        teardown();
        exit(-1);
    }

    posId         = glGetUniformLocation(programId, "skullPos");
    colourId      = glGetUniformLocation(programId, "skullColour");
    scaleId       = glGetUniformLocation(programId, "skullScale");
    matrixId      = glGetUniformLocation(programId, "mvp");

    glm::mat4 projection = glm::ortho(
        0.f,  static_cast<float>(width),
        0.f,  static_cast<float>(height),
        0.0f, 1.0f
    );
    glm::mat4 view = glm::lookAt(
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    glm::mat4 model = glm::mat4(1.0f);

    mvp = projection * view * model;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SKULL_VERTICES), SKULL_VERTICES, GL_STATIC_DRAW);
}

void Skeleton::loop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programId);

    drawSkull(
        static_cast<float>(width) / 2,
        static_cast<float>(height) / 4,
        1.5f,
        colourhelper::rgbaHexToVec4("FFFFFF", 0.4f)
    );

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Skeleton::teardown()
{
    cout << "Cleaning up OpenGL" << endl;

    cout << " - Deleting OpenGL resources";
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programId);
    glDeleteVertexArrays(1, &vertexArrayId);
    cout << OK << endl;

    cout << " - Terminating GLFW";
    glfwTerminate();
    cout << OK << endl;
}

bool Skeleton::isActive()
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0;
}

const string Skeleton::OK(" ... \033[1;32mOK\033[0m");

const string Skeleton::FAIL(" ... \033[1;31mFail\033[0m");

const GLfloat Skeleton::SKULL_VERTICES[] =
{
    // top of skull
     60, 50,
     60,  0,
    -60,  0,
    -60, 50,
     60, 50,
    -60,  0,

    // left of eyes
    -60,   0,
    -40,   0,
    -60, -30,
    -60, -30,
    -40,   0,
    -40, -30,

    // centre of eyes
    -10,   0,
     10,   0,
    -10, -30,
    -10, -30,
     10,   0,
     10, -30,

    // right of eyes
     60,   0,
     40,   0,
     60, -30,
     60, -30,
     40,   0,
     40, -30,

    // left of nose
    -60, -30,
      0, -30,
    -10, -40,
    -10, -40,
    -60, -40,
    -60, -30,

    // right of nose
      0, -30,
     60, -30,
     10, -40,
     10, -40,
     60, -30,
     60, -40,

    // jaw
    -30, -40,
     30, -40,
    -30, -55,
    -30, -55,
     30, -40,
     30, -55,
};
