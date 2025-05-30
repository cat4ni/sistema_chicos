#include "opclientes.hpp"
#include "cliente.hpp"
#include "miscs.hpp"

bool cadastrarCliente()
{
    limpatela();

    string tempNome, tempTelefone, tempBairro, tempRua, tempNumero, tempComplemento;

    cout << "-----------------------------------------" << endl << "Insira os dados do cliente: " << endl << "Nome: ";
    getline(cin, tempNome);

    for (auto &cliente : listaClientes)
    {
        if (cliente.mostraNome() == tempNome)
        {
            cout << "Ja existe um cadastro com este nome" << endl;
            return false;
        }
    }

    cout << "Telefone: ";
    getline(cin, tempTelefone);

    for (auto &cliente : listaClientes)
    {
        if (cliente.mostraTelefone() == tempTelefone)
        {
            cout << "Ja existe um cadastro com este telefone" << endl;
            return false;
        }
    }

    cout << "Bairro: ";
    getline(cin, tempBairro);

    cout << "Rua: ";
    getline(cin, tempRua);

    cout << "Numero da casa: ";
    getline(cin, tempNumero);

    cout << "Complemento: ";
    getline(cin, tempComplemento);

    if (tempNome.empty() || tempTelefone.empty() || tempBairro.empty() || tempRua.empty() || tempNumero.empty() ||
        tempComplemento.empty())
    {
        limpatela();
        cout << "-----------------------------------------" << endl
             << "Algum(ns) dos dados cadastrados esta(ao) invalido(s)" << endl;
        return false;
    }

    limpatela();
    cout << "Revisão dos dados: " << endl << endl;
    cout << "Nome: " << tempNome << endl;
    cout << "Telefone: " << tempTelefone << endl;
    cout << "Bairro: " << tempBairro << endl;
    cout << "Rua: " << tempRua << endl;
    cout << "Numero: " << tempNumero << endl;
    cout << "Complemento: " << tempComplemento << endl;

    string confirma;
    cout << endl << "Os dados estao corretos? (s/n): ";
    getline(cin, confirma);

    if (confirma != "s")
    {
        limpatela();
        cout << "Operacao cancelada." << endl;
        return false;
    }

    listaClientes.push_back(
        cliente(tempNome, tempTelefone, make_tuple(tempBairro, tempRua, tempNumero, tempComplemento)));

    ofstream fileCliente("clientes/" + tempNome + ".txt");
    if (fileCliente.is_open())
    {
        fileCliente << "Nome: " << tempNome << endl
                    << "Telefone: " << tempTelefone << endl
                    << "Bairro: " << tempBairro << endl
                    << "Rua: " << tempRua << endl
                    << "Numero: " << tempNumero << endl
                    << "Complemento: " << tempComplemento << endl;
        fileCliente.close();
    }

    ofstream fileLista("listas/listaClientes.txt", ios::app);
    if (fileLista.is_open())
    {
        fileLista << "Nome: " << tempNome << " | Telefone: " << tempTelefone << " | Bairro: " << tempBairro
                  << " | Rua: " << tempRua << " | Numero: " << tempNumero << " | Complemento: " << tempComplemento
                  << endl;
        fileLista.close();
    }

    return true;
}

bool editarCliente(tuple<string, string, tuple<string, string, string, string>> &cadastroAtual)
{
    limpatela();

    string tempNome, tempTelefone, tempBairro, tempRua, tempNumero, tempComplemento;

    cout << "-----------------------------------------" << endl << "Edite as informacoes do cliente: " << endl;

    cout << "Nome: ";
    getline(cin, tempNome);

    cout << "Telefone: ";
    getline(cin, tempTelefone);

    cout << "Bairro: ";
    getline(cin, tempBairro);

    cout << "Rua: ";
    getline(cin, tempRua);

    cout << "Numero da casa: ";
    getline(cin, tempNumero);

    cout << "Complemento: ";
    getline(cin, tempComplemento);

    string nomeAntigo = get<0>(cadastroAtual);
    string telefoneAntigo = get<1>(cadastroAtual);

    string nomeFinal = tempNome.empty() ? get<0>(cadastroAtual) : tempNome;
    string telefoneFinal = tempTelefone.empty() ? get<1>(cadastroAtual) : tempTelefone;
    string bairroFinal = tempBairro.empty() ? get<0>(get<2>(cadastroAtual)) : tempBairro;
    string ruaFinal = tempRua.empty() ? get<1>(get<2>(cadastroAtual)) : tempRua;
    string numeroFinal = tempNumero.empty() ? get<2>(get<2>(cadastroAtual)) : tempNumero;
    string complementoFinal = tempComplemento.empty() ? get<3>(get<2>(cadastroAtual)) : tempComplemento;

    limpatela();

    cout << "Revisão dos dados: " << endl << endl;
    cout << "Nome: " << nomeFinal << endl;
    cout << "Telefone: " << telefoneFinal << endl;
    cout << "Bairro: " << bairroFinal << endl;
    cout << "Rua: " << ruaFinal << endl;
    cout << "Numero: " << numeroFinal << endl;
    cout << "Complemento: " << complementoFinal << endl;

    string confirma;
    cout << endl << "Os dados estão corretos? (s/n): ";
    getline(cin, confirma);

    if (confirma != "s")
    {
        limpatela();
        cout << "Operação cancelada." << endl;
        return false;
    }

    if (!excluirCliente(telefoneAntigo))
    {
        cout << "Erro ao excluir cadastro antigo." << endl;
        return false;
    }

    cliente clienteAtualizado(nomeFinal, telefoneFinal,
                              make_tuple(bairroFinal, ruaFinal, numeroFinal, complementoFinal));
    listaClientes.push_back(clienteAtualizado);

    ofstream fileCliente("clientes/" + nomeFinal + ".txt");
    if (fileCliente.is_open())
    {
        fileCliente << "Nome: " << nomeFinal << endl
                    << "Telefone: " << telefoneFinal << endl
                    << "Bairro: " << bairroFinal << endl
                    << "Rua: " << ruaFinal << endl
                    << "Numero: " << numeroFinal << endl
                    << "Complemento: " << complementoFinal << endl;
        fileCliente.close();
    }
    else
    {
        cout << "Erro ao salvar arquivo do cliente." << endl;
        return false;
    }

    ofstream fileLista("listas/listaClientes.txt");
    if (fileLista.is_open())
    {
        for (auto &c : listaClientes)
        {
            fileLista << "Nome: " << c.mostraNome() << " | Telefone: " << c.mostraTelefone()
                      << " | Bairro: " << get<0>(c.mostraEndereco()) << " | Rua: " << get<1>(c.mostraEndereco())
                      << " | Numero: " << get<2>(c.mostraEndereco()) << " | Complemento: " << get<3>(c.mostraEndereco())
                      << endl;
        }
        fileLista.close();
    }
    else
    {
        cout << "Erro ao salvar listaClientes.txt." << endl;
        return false;
    }

    return true;
}

bool excluirCliente(string delCliente)
{
    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].mostraTelefone() == delCliente || listaClientes[i].mostraNome() == delCliente)
        {
            string nomeArquivoCliente = listaClientes[i].mostraNome() + ".txt";

            remove(("clientes/" + nomeArquivoCliente).c_str());

            listaClientes.erase(listaClientes.begin() + i);

            ofstream fileExclui("listas/listaClientes.txt");

            if (fileExclui.is_open())
            {
                for (size_t i = 0; i < listaClientes.size(); i++)
                {
                    fileExclui << "Nome: " << listaClientes[i].mostraNome()
                               << " | Telefone: " << listaClientes[i].mostraTelefone()
                               << " | Bairro: " << get<0>(listaClientes[i].mostraEndereco())
                               << " | Rua: " << get<1>(listaClientes[i].mostraEndereco())
                               << " | Numero: " << get<2>(listaClientes[i].mostraEndereco())
                               << " | Complemento: " << get<3>(listaClientes[i].mostraEndereco()) << endl;
                }
            }
            fileExclui.close();

            return true;
        }
    }

    return false;
}

void mostrarClientesCadastrados()
{
    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        cout << "[" << i << "] Nome: " << listaClientes[i].mostraNome()
             << ", telefone: " << listaClientes[i].mostraTelefone() << endl
             << "-----------------------------------------" << endl;
    }
}

void mostrarClientesDetalhado(int id)
{
    limpatela();
    cout << "-----------------------------------------" << endl
         << "Nome: " << listaClientes[id].mostraNome() << endl
         << "Telefone: " << listaClientes[id].mostraTelefone() << endl
         << "Bairro: " << get<0>(listaClientes[id].mostraEndereco()) << endl
         << "Rua: " << get<1>(listaClientes[id].mostraEndereco()) << endl
         << "Numero: " << get<2>(listaClientes[id].mostraEndereco()) << endl
         << "Complemento: " << get<3>(listaClientes[id].mostraEndereco()) << endl
         << "-----------------------------------------" << endl;
}