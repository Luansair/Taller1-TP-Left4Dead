// Copyright [2023] pgallino

#include "../include/server.h"

#define VALID_ARGC 2

int main(int argc, char *argv[]) {
    using std::cerr;
    using std::endl;

    if (argc != VALID_ARGC) {
        cerr << "Bad program call. Expected "
             << argv[0]
             << " <servname>" << endl;
        return EXIT_FAILURE;
    }

    try {
    const char* servname = argv[1];
    Server server(servname);
    server.init();
    } catch (const std::exception& err) {
        cerr << "An exception was caught in the main thread: "
             << err.what()
             << endl;
        return EXIT_FAILURE;
    } catch (...) {
        cerr << "An unknown exception was caught in the main thread."
             << endl;
        return EXIT_FAILURE;
    }
}


