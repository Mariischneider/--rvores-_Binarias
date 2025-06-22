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

//imprime arvore
void printTree(Node* node, const std::string& prefix = "", bool isLast = true){
    if(!node) return;

    std::cout << prefix;
    if(!prefix.empty()){
        std::cout << (isLast ? "└── " : "├── ");

    }
    std::cout << node->name;

    if(node->isDirectory){
        std::cout << " (" << node->children.size()
                  << " filhos, " << getTotalSize(node) << " bytes)";
    } else{
        std::cout << " (" << node->size << " bytes";
    }

    std::cout << std::endl;

    for(size_t i = 0; i < node->children.size();++i){
        bool last = (i == node->children.size() - 1);
        printTree(node->children[i], prefix + (isLast ? "    " : "|   "), last);
    }
}



int main()
{
    std::string path;
    std::cout << "Digite o caminho inicial(ou deixe vazio para usar o atual): ";
    std::getline(std::cin, path);

    if(path.empty()) path = ".";

    Node* root = buildTree(path);

    if (root) {
        std::string absPath = fs::absolute(path).string();
        std::cout << absPath << " (" << root->children.size()
                  << " filhos, " << getTotalSize(root) << " bytes)\n";
                    
        printTree(root);
    } else {
        std::cerr << "Não foi possível construir a árvore.\n";
    }

    return 0;
}
