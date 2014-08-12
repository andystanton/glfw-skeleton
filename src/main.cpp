#include "skeleton.hpp"

int main()
{
    skeleton::setup("GLFW Skeleton", 640.f, 480.f);

    while (skeleton::isActive())
    {
        skeleton::loop();
    }

    skeleton::teardown();

    return 0;
}
