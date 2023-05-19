#include <iostream>

#include "../include/client.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Expected 3 arguments, got: " << argc <<
        "\nUsage: ./Client <ip> <port>"
        "\nExample: ./Client 111.0.2.0 8080" << std::endl;
        return EXIT_FAILURE;
    }
    try {
        Client client(argv[1], argv[2]);
        client.init();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}