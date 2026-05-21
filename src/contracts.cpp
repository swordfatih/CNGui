#include <contracts>

#include <exception>

void handle_contract_violation(std::contracts::contract_violation const&)
{
    std::terminate();
}
