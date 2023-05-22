// Copyright [2023] pgallino

#include "../include/server.h"

#define VALID_ARGC 2

int main(int argc, char *argv[]) {
    using std::cerr;
    using std::endl;

    const char *servname = NULL;
    if (argc != VALID_ARGC) {
        cerr << "Bad program call. Expected "
             << argv[0]
             << " <servname>" << endl;
        return EXIT_FAILURE;
    }

    try {
    Server server(servname);
    server.init();
    } catch (const std::exception& err) {
        cerr << "Something went wrong and an exception was caught: "
             << err.what()
             << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "Something went wrong and an unknown exception was caught."
             << endl;
        return EXIT_FAILURE;
    }
}


