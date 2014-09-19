#include "Skeleton.hpp"

#include "util/cli/CLIParser.hpp"

int main(int argc, char ** argv)
{
    Configuration c = CLIParser(argc, argv).getConfiguration();

    LoggerFactory::configure(c.getBoolValue("no-colour"));

    Skeleton skeleton("GLFW Skeleton", 640, 480);

    skeleton.setup();

    while (skeleton.isActive())
    {
        skeleton.loop();
    }

    skeleton.teardown();

    return 0;
}
