#include "cliente.hpp"


cliente::cliente(string c_nome, string c_telefone, tuple<string, string, string, string> c_endereco)
{
    trocaNome(c_nome);
    trocaTelefone(c_telefone);
    trocaEndereco(c_endereco);
}

void cliente::trocaNome(string novoNome)
{
    c_nome = novoNome;
}

void cliente::trocaTelefone(string novoTelefone)
{
    c_telefone = novoTelefone;
}

void cliente::trocaEndereco(tuple<string, string, string, string> novoEndereco)
{
    c_endereco = make_tuple(get<0>(novoEndereco), get<1>(novoEndereco), get<2>(novoEndereco), get<3>(novoEndereco));
}

string cliente::mostraNome()
{
    return c_nome;
}

string cliente::mostraTelefone()
{
    return c_telefone;
}

tuple<string, string, string, string> cliente::mostraEndereco()
{
    return c_endereco;
}
