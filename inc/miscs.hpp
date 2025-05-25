#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdio>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "cliente.hpp"

using namespace std;
namespace fs = std::filesystem;

extern vector<cliente> listaClientes;
extern vector<tuple<cliente, vector<tuple<string, string, string, float>>, float, float>> listaPedidos;
extern vector<string> diretorioClientes;
extern vector<string> diretorioPedidos;

void limpatela();
string printData();
bool criarBackup();
bool restaurarBackup();

#endif