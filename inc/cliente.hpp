#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

class cliente
{
private:
    string c_nome, c_telefone;
    // ⮮⮮ bairro  rua    telefone complemento ⮯⮯
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

#endif
