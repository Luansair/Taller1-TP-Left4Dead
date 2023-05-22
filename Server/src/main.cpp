// Copyright [2023] pgallino

#include "../include/accepter.h"

#define VALID_ARGC 2
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main(int argc, char *argv[]) { try {
    const char *servname = NULL;

    if (argc == VALID_ARGC) {
        servname = argv[1];
    } else {
        std::cerr << "Bad program call. Expected "
                << argv[0]
                << " <servname>\n";
        return EXIT_FAILURE;
    }
    Accepter accepter(servname);
    accepter.start();
    std::string entrada;
    do {
        getline(std::cin, entrada);
    } while (entrada != "q");
    accepter.close();
    accepter.join();

    return EXIT_SUCCESS;
} catch (const std::exception& err) {
    std::cerr
        << "Something went wrong and an exception was caught: "
        << err.what()
        << "\n";
    return EXIT_FAILURE;
} catch (...) {
    std::cerr << "Something went wrong and an unknown exception was caught.\n";
    return EXIT_FAILURE;
} }
