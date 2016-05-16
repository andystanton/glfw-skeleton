#include <bandit/bandit.h>

#include "util/colorhelper.hpp"

using namespace bandit;

go_bandit([](){
    describe("the colour helper", []() {
        const float EPSILON = 0.000001f;

        it("converts decimal rgb values to a glm vec4 representing the colour with full opacity", [&]() {
            glm::vec4 outputColour = colorhelper::rgbDecToVec4(0.5f, 0.3f, 0.2f);

            AssertThat(outputColour[0], EqualsWithDelta(0.5f, EPSILON));
            AssertThat(outputColour[1], EqualsWithDelta(0.3f, EPSILON));
            AssertThat(outputColour[2], EqualsWithDelta(0.2f, EPSILON));
            AssertThat(outputColour[3], EqualsWithDelta(1.0f, EPSILON));
        });

        it("converts decimal rgba values to a glm vec4 representing the colour", [&]() {
            glm::vec4 outputColour = colorhelper::rgbaDecToVec4(0.5f, 0.3f, 0.2f, 0.8f);

            AssertThat(outputColour[0], EqualsWithDelta(0.5f, EPSILON));
            AssertThat(outputColour[1], EqualsWithDelta(0.3f, EPSILON));
            AssertThat(outputColour[2], EqualsWithDelta(0.2f, EPSILON));
            AssertThat(outputColour[3], EqualsWithDelta(0.8f, EPSILON));
        });

        it("converts a hex rgb string to a glm vec4 representing the colour with full opacity", [&]() {
            glm::vec4 outputColour = colorhelper::rgbHexToVec4("3300FF");

            AssertThat(outputColour[0], EqualsWithDelta(0.2f, EPSILON));
            AssertThat(outputColour[1], EqualsWithDelta(0.f, EPSILON));
            AssertThat(outputColour[2], EqualsWithDelta(1.0f, EPSILON));
            AssertThat(outputColour[3], EqualsWithDelta(1.0f, EPSILON));
        });

        it("converts a hex rgb string and a decimal alpha value to a glm vec4 representing the colour", [&]() {
            glm::vec4 outputColour = colorhelper::rgbaHexToVec4("6699CC", 0.5f);

            AssertThat(outputColour[0], EqualsWithDelta(0.4f, EPSILON));
            AssertThat(outputColour[1], EqualsWithDelta(0.6f, EPSILON));
            AssertThat(outputColour[2], EqualsWithDelta(0.8f, EPSILON));
            AssertThat(outputColour[3], EqualsWithDelta(0.5f, EPSILON));
        });
    });
});
