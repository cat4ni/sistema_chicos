#ifndef OPCLIENTES_HPP
#define OPCLIENTES_HPP

#include "miscs.hpp"

bool cadastrarCliente();
bool editarCliente(tuple<string, string, tuple<string, string, string, string>> &cadastroAtual);
void mostrarClientesCadastrados();
bool excluirCliente(string telefone);

#endif