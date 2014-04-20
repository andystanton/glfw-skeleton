#include "BanditWithGmock.h"

#include <Multiplier.h>
#include <Adder.h>
#include "MockAdder.h"

using namespace bandit;
using ::testing::Return;

go_bandit([](){
    describe("an adder", [](){
      Adder adder = Adder();
      it("adds two numbers together", [&](){
        AssertThat(adder.add(4, 7), Equals(11));
      });
    });

    describe("a multiplier", [](){
      Multiplier multiplier = Multiplier();

      it("multiplies two numbers together", [&](){
        AssertThat(multiplier.multiply(4, 7), Equals(28));
      });
    });

    describe("a scenario using mocks", []() {
      MockAdder adder;
      Given(adder, add(3, 4)).WillByDefault(Return(7));
      Verify(adder, add(3, 4)).Times(1);

      it ("mocks things correctly", [&]() {
        AssertThat(adder.add(3, 4), Equals(7));
      });
    });
});


int main(int argc, char* argv[]) {
    return bandit_with_gmock::run(argc, argv);
}