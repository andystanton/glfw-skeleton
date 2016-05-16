#include "Skeleton.hpp"
#include "util/cli/CLIParser.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char ** argv)
{
    Skeleton skeleton("GLFW Skeleton", 640, 480);

    skeleton.setup();

    while (skeleton.isActive())
    {
        skeleton.loop();
    }

    skeleton.teardown();

    return 0;
}
