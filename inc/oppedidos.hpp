#ifndef OPPEDIDOS_HPP
#define OPPEDIDOS_HPP

#include "miscs.hpp"

bool fazerPedido(string telefone);
void imprimePedido(cliente c, vector<tuple<string, string, string, float>> clientePedido, float valorPedido,
                   float valorEntrega, float valorTotal);
bool reimprimirPedido(int id);
void fecharpedidos();
void mostrarPedidos();
bool editarPedido(tuple<cliente, vector<tuple<string, string, string, float>>, float, float> &pedido, int id);
void excluirPedido();
void mostrarPedidoDetalhado(int id);

#endif