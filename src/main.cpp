#include <iostream>
#include <boost/program_options.hpp>

#include "operations/operations.hpp"

int main(int argc, char **argv) {
    int variable_a, variable_b;

    namespace po = boost::program_options;

    po::options_description visible("Supported options");
    visible.add_options()
            ("help,h", "Print this help message.");

    po::options_description hidden("Hidden options");
    hidden.add_options()
            ("a", po::value<int>(&variable_a)->default_value(0), "Variable A.")
            ("b", po::value<int>(&variable_b)->default_value(0), "Variable B.");

    po::positional_options_description p;
    p.add("a", 1);
    p.add("b", 1);

    po::options_description all("All options");
    all.add(visible).add(hidden);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(all).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << "Usage:\n  add [a] [b]\n" << visible << std::endl;
        return EXIT_SUCCESS;
    }

    int result = operations::add(variable_a, variable_b);
    std::cout << result << std::endl;
    return EXIT_SUCCESS;
}
