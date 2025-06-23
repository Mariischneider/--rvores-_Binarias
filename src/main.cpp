#include "Node.hpp"
#include <iostream>
#include <string>
#include <filesystem> 

namespace fs = std::filesystem;


Node* buildTree(const std::string& path);

// Função recursiva: percorre a arvore e coleta arquivos maiores que N
void buscarArquivosMaiores(Node* node, size_t N, std::vector<Node*>& resultado) {
    if (!node) return;

    if (!node->isDirectory && node->size > N) {
        resultado.push_back(node);
    }

    for (Node* filho : node->children) {
        buscarArquivosMaiores(filho, N, resultado);
    }
}

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

//mostra arquivos maior do que N
void listarArquivosMaioresQue(Node* root, size_t N) {
    std::vector<Node*> encontrados;
    buscarArquivosMaiores(root, N, encontrados);

    std::cout << "\nArquivos com mais do que N bytes (N=" << N << "):\n";
    for (Node* arq : encontrados) {
        std::cout << arq->path << " (" << arq->size << " bytes)\n";
    }

    if (encontrados.empty()) {
        std::cout << "Nenhum arquivo encontrado.\n";
    }
}

void exibirMenu(Node* root){
    int opcao;
    do{
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Exibir a árvore completa\n";
        std::cout << "2. Listar arquivos com mais do que N bytes\n";
        std::cout << "3. Mostrar maior arquivos(s)\n";
        std::cout << "4. Pasta com mais arquivos diretamente\n";
        std::cout << "5. Arquivos por extensão\n";
        std::cout << "6. Pasta vazias\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opção\n";
        std::cin >> opcao;

        switch (opcao)
        {
            case 1:
            std::cout << "\nÁrvore de arquivos:\n";
            printTree(root);
            break;
        case 2: {
            size_t N;
            std::cout << "Digite o valor N (em bytes): ";
            std::cin >> N;
            listarArquivosMaioresQue(root, N);
            break;
        }
        case 3:
            break;
        case 4:
            break;
        case 5: {
            std::string ext;
            std::cout << "Digite a extensão (ex: .txt): ";
            std::cin >> ext;
            break;
        }
        case 6:
            break;
        case 0:
            std::cout << "Encerrando...\n";
            break;
        default:
            std::cout << "Opção inválida!\n";
        }
    } while (opcao !=0); 
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
                    
        exibirMenu(root);
    } else {
        std::cerr << "Não foi possível construir a árvore.\n";
    }

    return 0;
}
