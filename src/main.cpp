#include "Skeleton.hpp"

int main()
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
