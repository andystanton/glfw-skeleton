#define ELPP_NO_DEFAULT_LOG_FILE

#include "Skeleton.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char ** argv) {
    string applicationPath = * pathhelper::getApplicationPath();

    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::Format, "%datetime{%H:%m:%s,%g} %level %loc %msg");
    defaultConf.setGlobally(el::ConfigurationType::Filename, applicationPath + "/logs/glfw-skeleton.log");
    defaultConf.setGlobally(el::ConfigurationType::MaxLogFileSize, "2097152");
    defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "false");
    defaultConf.setGlobally(el::ConfigurationType::ToFile, "true");

    defaultConf.set(el::Level::Trace, el::ConfigurationType::Enabled, "false");
    defaultConf.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
    defaultConf.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    defaultConf.set(el::Level::Warning, el::ConfigurationType::Enabled, "true");
    defaultConf.set(el::Level::Error, el::ConfigurationType::Enabled, "true");
    defaultConf.set(el::Level::Fatal, el::ConfigurationType::Enabled, "true");

    el::Loggers::setDefaultConfigurations(defaultConf, true);

    Skeleton skeleton("GLFW Skeleton", 640, 480);

    skeleton.setup();

    while (skeleton.isActive()) {
        skeleton.loop();
    }

    skeleton.teardown();

    return 0;
}
