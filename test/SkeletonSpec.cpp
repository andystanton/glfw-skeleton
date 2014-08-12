#include <bandit/bandit.h>

#include "Skeleton.hpp"

using namespace bandit;

go_bandit([](){
    describe("the skeleton application", []() {

        Skeleton skeleton("GLFW Skeleton", 640.f, 480.f);

        it("contains an array of indices that make up the skull", [&]() {
            // there are 7 quads split into 2 triangles that have
            // 3 vertices made up of 2 GLfloat components (x and y)

            const unsigned long expected = 7 * 2 * 3 * 2 * sizeof(GLfloat);

            AssertThat(sizeof(Skeleton::skullVertices), Equals(expected));
        });
    });
});
