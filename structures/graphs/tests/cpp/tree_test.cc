#include "tree.hh"
#include "validator.hh"
#include "logger.hh"

// #include "structures_director.hh"
// #include "graph_builder.hh"
// #include "weighted_graph_builder.hh"

#include <iostream>
#include <memory>
#include <map>

using namespace prb17::utils::structures;
static prb17::utils::logger logger{"tree_test"};
//Map that relates the json file test config file to each test function defined in this file
template<typename T>
bool basicTreePrint(prb17::utils::parsers::json_parser jp) {
    tree<T> t = tree<T>{2};
    return true;
}

template<typename T>
static std::map<std::string, std::function<bool(prb17::utils::parsers::json_parser)> > graph_tests = {
    {"basicTreePrint", &basicTreePrint<T>}
};

#define MIN_NUM_ARGS 2
int main(int argc, char** argv) {
    if (argc < MIN_NUM_ARGS) {
        throw prb17::utils::exception("This test requires a config file to be provided");
    }
    prb17::utils::structures::array<std::string> test_files{};
    for (int i=1; i<argc; i++) {
        //TODO: test if string is a valid file name/path
        logger.debug("adding test file to validator: '{}'", &argv[i][0]);
        test_files.add(&argv[i][0]);
    }
    prb17::utils::validator validator{test_files};
    
    validator.add_tests(&graph_tests<std::string>);
    validator.add_tests(&graph_tests<int>);
    validator.add_tests(&graph_tests<uint>);
    validator.add_tests(&graph_tests<char>);
    validator.add_tests(&graph_tests<bool>);
    validator.add_tests(&graph_tests<float>);
    validator.add_tests(&graph_tests<double>);

    logger.info("Starting validation tests of tree_tests");
    validator.validate();
    logger.info("Finished validation tests of tree_tests");
}