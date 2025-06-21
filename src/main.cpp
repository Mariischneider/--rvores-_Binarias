#include "Node.hpp"
#include <iostream>
#include <string>
#include <filesystem> 

namespace fs = std::filesystem;


Node* buildTree(const std::string& path);

// soma recursiva dos tamanhos de arquivos em um diretorio
size_t getTotalSize(Node* node) {
    if (!node || !node->isDirectory) return node->size;
    size_t total = 0;
    for (Node* child : node->children)
        total += getTotalSize(child);
    return total;
}



int main()
{
    std::string path;
    std::cout << "Digite o caminho inicial(ou deixe vazio para usar o atual): ";
    std::getline(std::cin, path);

    Node* root = buildTree(path);

    if (root) {
        std::string absPath = fs::absolute(path).string();
        std::cout << absPath << " (" << root->children.size()
                  << " filhos, " << getTotalSize(root) << " bytes)\n";
                    

    } else {
        std::cerr << "Não foi possível construir a árvore.\n";
    }

    return 0;
}
