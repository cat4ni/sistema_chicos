#ifndef OPCLIENTES_HPP
#define OPCLIENTES_HPP

#include "miscs.hpp"

bool cadastrarCliente();
bool editarCliente(tuple<string, string, tuple<string, string, string, string>> &cadastroAtual);
void mostrarClientesCadastrados();
void mostrarClientesDetalhado(int id);
bool excluirCliente(string telefone);

#endif