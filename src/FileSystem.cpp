#include "Node.hpp"
#include <sys/stat.h> // stat 
#include <dirent.h>   // opendir, readdir, closedir


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

    //se for diretorio procura os filhos
    if(isDir) {
        DIR* dir = opendir(path.c_str());
        if(!dir){
            std::cerr << "Erro ao abrir diretorio: " << path << std::endl;
            return node;
        }

        struct dirent* entry;
        while((entry = readdir(dir)) != nullptr){
            std::string entryName = entry->d_name;

            //ignora . e ..
            if(entryName == "." || entryName == "..")
               continue;
            std::string fullPath = path + "/" + entryName;

            //chamada recursiva
            Node* child = buildTree(fullPath);
            if(child)
               node->children.push_back(child);
        }

        closedir(dir);

    }

    return node;

}