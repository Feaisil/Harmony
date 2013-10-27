#include <iostream>
#include "core/board.hpp"

int main( int argc, char** argv)
{
    harmony::core::board::Board testboard(5);
    harmony::core::board::Position balance;
    std::cout << balance << std::endl;
    testboard(balance, harmony::core::common::Element::Aether);
    std::cout << balance << std::endl;
    testboard(balance, harmony::core::common::Element::Earth);
    std::cout << balance << std::endl;
    testboard(balance, harmony::core::common::Element::Aether);
    std::cout << balance << std::endl;
    testboard(balance, harmony::core::common::Element::Aether);
    std::cout << balance << std::endl;
    testboard(balance, harmony::core::common::Element::Aether);
    std::cout << balance << std::endl;
    testboard(balance, harmony::core::common::Element::Aether);
    std::cout << balance << std::endl;
    testboard(balance, harmony::core::common::Element::Aether);
    std::cout << balance << std::endl;
    testboard(balance, harmony::core::common::Element::Aether);
    std::cout << balance << std::endl;
    return EXIT_SUCCESS;
}

