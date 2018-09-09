#include "RepoManager.hpp"
#include <iostream>


int main(int argc, char* argv[]) {
    RepoManager repoManager;

    try {
        repoManager.init("C:/Users/James/Documents/gistory");

        std::cout << "Number of commits: " 
            << repoManager.numberOfRevisions()
            << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 1;
}
