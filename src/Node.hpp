#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <memory>


using namespace std;

// Estrutura de no da arvore

struct Node {
    std::string name;     
    std::string path;     
    bool isDirectory;     // true se for diretório, false se for arquivo
    size_t size;          // (0 se for pasta)
    std::vector<Node*> children; // (apenas se for diretório)

    Node(std::string name, std::string path, bool isDir, size_t size = 0)
        : name(name), path(path), isDirectory(isDir), size(size) {}
};
