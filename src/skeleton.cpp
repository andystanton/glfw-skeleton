#include "skeleton.hpp"

void skeleton::initGL()
{
    cout << "Initialising OpenGL" << endl;

    // Initialise GLFW
    cout << " - Initialising GLFW";
    if (!glfwInit())
    {
        cout << skeleton::fail << endl;
        throw "Failed to initialise GLFW";
    }
    cout << skeleton::ok << endl;

    // Create window with GLFW
    cout << " - Creating window with GLFW";
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    skeleton::window = glfwCreateWindow(
        skeleton::width,
        skeleton::height,
        skeleton::appName.c_str(),
        nullptr,
        nullptr
    );

    if (skeleton::window == nullptr)
    {
        glfwTerminate();
        cout << skeleton::fail << endl;
        throw "Failed to create window with GLFW.";
    }
    cout << ok << endl;

    // Make window the current OpenGL context
    cout << " - Making window the current OpenGL context";
    glfwMakeContextCurrent(skeleton::window);
    cout << skeleton::ok << endl;

    // Initialise GLEW
    cout << " - Initialising GLEW";
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        cout << skeleton::fail << endl;
        throw "Failed to initialise GLEW";
    }
    cout << skeleton::ok << endl;

    // Set GLFW Options
    cout << " - Setting GLFW Options";
    glfwSetInputMode(skeleton::window, GLFW_STICKY_KEYS, GL_TRUE);
    cout << skeleton::ok << endl;

    // Set OpenGL Options
    cout << " - Setting OpenGL Options";
    glClearColor(0.3f, 0.2f, 0.2f, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    cout << skeleton::ok << endl;
}

void skeleton::drawSkull(float x, float y)
{
    glm::vec2 skullPos = { x, y };
    glm::vec4 skullColour = { 1.f, 1.f, 1.f, 0.4f };

    float skullScale = 0.75f;

    glUniformMatrix4fv(skeleton::matrixId, 1, GL_FALSE, &skeleton::MVP[0][0]);

    glUniform2fv(skeleton::posId, 1, &skullPos[0]);
    glUniform4fv(skeleton::colourId, 1, &skullColour[0]);
    glUniform1f(skeleton::scaleId, skullScale);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, skeleton::vertexbuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));

    glDrawArrays(GL_TRIANGLES, 0, sizeof(skeleton::skullVertices) / sizeof(GLfloat));

    glDisableVertexAttribArray(0);
}

void skeleton::setup(const string & appName, float width, float height)
{
    skeleton::width = width;
    skeleton::height = height;
    skeleton::appName = appName;

    cout << endl << "Running \033[1m" << skeleton::appName << "\033[0m" << endl;

    try
    {
        initGL();
    }
    catch (const char * error)
    {
        cerr << error << endl;
        exit(-1);
    }

    glGenVertexArrays(1, &skeleton::vertexArrayId);
    glBindVertexArray(skeleton::vertexArrayId);

    try {
        skeleton::programId = shaderhelper::createProgram("skull.vertexshader", "skull.fragmentshader");
    }
    catch (const string & error)
    {
        cerr << error << endl;
        teardown();
        exit(-1);
    }

    skeleton::posId         = glGetUniformLocation(programId, "skullPos");
    skeleton::colourId      = glGetUniformLocation(programId, "skullColour");
    skeleton::scaleId       = glGetUniformLocation(programId, "skullScale");
    skeleton::matrixId      = glGetUniformLocation(programId, "MVP");

    glm::mat4 projection    = glm::ortho(0.f, skeleton::width, 0.f, skeleton::height, 0.0f, 1.0f);
    glm::mat4 view          = glm::lookAt(
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    glm::mat4 model         = glm::mat4(1.0f);

    skeleton::MVP = projection * view * model;

    glGenBuffers(1, &skeleton::vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, skeleton::vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skeleton::skullVertices), skeleton::skullVertices, GL_STATIC_DRAW);
}

void skeleton::loop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(skeleton::programId);

    drawSkull(skeleton::width / 2, skeleton::height / 2);

    glfwSwapBuffers(skeleton::window);
    glfwPollEvents();
}

void skeleton::teardown()
{
    cout << "Cleaning up OpenGL" << endl;

    cout << " - Deleting OpenGL resources";
    glDeleteBuffers(1, &skeleton::vertexbuffer);
    glDeleteProgram(skeleton::programId);
    glDeleteVertexArrays(1, &skeleton::vertexArrayId);
    cout << ok << endl;

    cout << " - Terminating GLFW";
    glfwTerminate();
    cout << ok << endl;
}

bool skeleton::isActive()
{
    return glfwGetKey(skeleton::window, GLFW_KEY_ESCAPE) != GLFW_PRESS
        && glfwWindowShouldClose(skeleton::window) == 0;
}
