#include "Node.hpp"
#include <iostream>
#include <string>


Node* buildTree(const std::string& path);


int main()
{
    std::string path;
    std::cout << "Digite o caminho inicial(ou deixe vazio para usar o atual): ";
    std::getline(std::cin, path);

    Node* root = buildTree(path);

    
    return 0;
}