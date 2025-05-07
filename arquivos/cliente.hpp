#include <cstdio>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

class cliente
{
private:
    string c_nome, c_telefone;
    // ⮮⮮ endereco = bairro, rua, telefone, complemento ⮯⮯
    tuple<string, string, string, string> c_endereco;

public:
    cliente(string c_nome, string c_telefone, tuple<string, string, string, string> c_endereco);

    void trocaNome(string novoNome);
    void trocaTelefone(string novoTelefone);
    void trocaEndereco(tuple<string, string, string, string> novoEndereco);

    string mostraNome();
    string mostraTelefone();
    tuple<string, string, string, string> mostraEndereco();
};