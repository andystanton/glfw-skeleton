#include "Skeleton.hpp"

int main(int argc, char ** argv)
{
    Skeleton skeleton("GLFW Skeleton", 640, 480);

    while (skeleton.isActive()) {
        skeleton.loop();
    }

    return 0;
}
