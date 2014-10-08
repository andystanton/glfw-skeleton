#include <bandit/bandit.h>

#include "util/cli/CLIParser.hpp"

using namespace bandit;

using std::string;
using std::vector;

go_bandit([](){
    describe("the CLI Parser", []() {
        it("creates a configuration from options formatted '--key=value'", []() {
            vector<string> lines = {
                    "glfw-skeleton",
                    "--key=value"
            };

            CLIParser parser(lines);

            AssertThat(parser.getConfiguration().getValue("key"), Equals("value"));
        });

        it("creates a configuration from options formatted '-key=value'", []() {
            vector<string> lines = {
                    "glfw-skeleton",
                    "-key=value"
            };

            CLIParser parser(lines);

            AssertThat(parser.getConfiguration().getValue("key"), Equals("value"));
        });

        it("creates a configuration from options formatted 'switch'", []() {
            vector<string> lines = {
                    "glfw-skeleton",
                    "switch"
            };

            CLIParser parser(lines);

            AssertThat(parser.getConfiguration().getValue("switch"), Equals("true"));
        });

        it("creates a configuration from options formatted '-switch'", []() {
            vector<string> lines = {
                    "glfw-skeleton",
                    "-switch"
            };

            CLIParser parser(lines);

            AssertThat(parser.getConfiguration().getValue("switch"), Equals("true"));
        });
    });
});
