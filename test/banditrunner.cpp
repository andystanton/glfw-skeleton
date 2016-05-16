#include <bandit/bandit.h>
#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
    return bandit::run(argc, argv);
}
