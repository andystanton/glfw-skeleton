#include "skeleton.hpp"

int main()
{
    Skeleton skeleton("GLFW Skeleton", 640.f, 480.f);

    skeleton.setup();

    while (skeleton.isActive())
    {
        skeleton.loop();
    }

    skeleton.teardown();

    return 0;
}
