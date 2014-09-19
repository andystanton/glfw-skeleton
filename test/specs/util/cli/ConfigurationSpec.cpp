#include <bandit/bandit.h>

#include "util/cli/CLIParser.hpp"

using namespace bandit;

using std::string;
using std::map;

go_bandit([]() {
    describe("the Configuration", []() {
        it("is an interface to a map", []() {
            map<string, string> configMap = {
                    {"key1", "value1"},
                    {"key2", "value2"},
            };

            Configuration c(configMap);

            AssertThat(c.containsKey("key1"), Equals(true));
            AssertThat(c.containsKey("key2"), Equals(true));


        });

        it("should return string values", []() {
            map<string, string> configMap = {
                    {"key1", "value1"},
                    {"key2", "value2"},
            };

            Configuration c(configMap);

            AssertThat(c.getValue("key1"), Equals("value1"));
            AssertThat(c.getValue("key2"), Equals("value2"));
        });

        it("should return boolean values", []() {
            map<string, string> configMap = {
                    {"key1", "true"},
                    {"key2", "false"},
                    {"key3", "non-boolean-value"},
            };

            Configuration c(configMap);

            AssertThat(c.getBoolValue("key1"), Equals(true));
            AssertThat(c.getBoolValue("key2"), Equals(false));
            AssertThat(c.getBoolValue("key3"), Equals(false));
        });

        it("should return int values", []() {
            map<string, string> configMap = {
                    {"key1", "1"},
                    {"key2", "123"},
                    {"key3", "-214"},
                    {"key4", "0"},
            };

            Configuration c(configMap);

            AssertThat(c.getIntValue("key1"), Equals(1));
            AssertThat(c.getIntValue("key2"), Equals(123));
            AssertThat(c.getIntValue("key3"), Equals(-214));
            AssertThat(c.getIntValue("key4"), Equals(0));
        });
    });
});
