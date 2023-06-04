#include <iostream>

#include "../include/client.h"

constexpr char red_color[6] = "\033[31m";
constexpr char reset_color[5] = "\033[0m";

int main(int argc, char* argv[]) {
    using std::cerr;
    using std::endl;
    using std::exception;

    if (argc != 3) {
        cerr << "Expected 3 arguments, got: " << argc <<
        "\nUsage: ./Client <ip> <port>"
        "\nExample: ./Client 111.0.2.0 8080" << endl;
        return EXIT_FAILURE;
    }
    try {
        Client client(argv[1], argv[2]);
        client.start();
    } catch (const exception& e) {
        cerr << red_color << "An Exception was caught: " << reset_color <<
        e.what() << endl;
    } catch (...) {
        cerr << "Unknown exception." << endl;
    }
}