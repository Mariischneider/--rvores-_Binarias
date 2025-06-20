#include "Node.hpp"
#include <sys/stat.h> // stat 

Node* buildTree(const std::string& path) {
    struct stat info;
    // verifica se eh um caminho valido
    if(stat(path.c_str(), &info) != 0){
        std:: cerr << "Erro ao acessar" << path << std::endl;
        return nullptr;
    } 

    //se for pasta o tamanho eh 0 senao tamnho em bytes
    bool isDir = S_ISDIR(info.st_mode);
    size_t size = isDir ? 0 : info.st_size;
    std::string name = path.substr(path.find_last_of("/") + 1);


    Node* node = new Node(name, path, isDir, size);

    return node;

}