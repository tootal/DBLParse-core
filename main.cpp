#include <iostream>
#include <cxxopts.hpp>

int main(int argc, char *argv[]) {
    cxxopts::Options options("DBLParse-core", "The core of DBLParse");
    options.allow_unrecognised_options();
    options.add_options()("h,help", "Show help");

    auto result = options.parse(argc, argv);
    if (result["help"].as<bool>()) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    std::cout << options.help() << std::endl;
    return 0;
}
