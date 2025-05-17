#include "cliente.hpp"

/////////////////////////////
// funcoes operacoes arquivos
bool carregarPathClientes(string path, vector<string> &diretorio);
bool carregarClientes(const vector<string> &diretorio);
bool carregarDiretoriosEPastas();
void imprimePedido(cliente c, vector<tuple<string, string, string, float>> clientePedido, float valorPedido, float valorEntrega, float valorTotal);
// bool carregarPathPedidos(string path, vector<string> &diretorio);
// bool carregarPedidos(const vector<string> &diretorio);
/////////////////////////////

/////////////////////////////
// funcoes operacoes sistema
bool fazerPedido(string telefone);
void fecharpedidos();
void mostrarPedidos();
bool cadastrarCliente(tuple<string, string, tuple<string, string, string, string>> *cadastroAtual = nullptr);
bool editarPedido();
void excluirPedido();
void mostrarClientesCadastrados();
void mostrarPedidoDetalhado(int id);
bool excluirCliente(string telefone);
/////////////////////////////

/////////////////////////////
// funcoes gui
int menu();
void limpatela();
string printData();
/////////////////////////////

/////////////////////////////
// vetores
vector<cliente> listaClientes;
vector<string> diretorioClientes;
// vector<string> diretorioPedidos;
// ⮮⮮        cliente               item,   com,    sem,    valor ⮯⮯
vector<tuple<cliente, vector<tuple<string, string, string, float>>, float, float>> listaPedidos;
/////////////////////////////

int main()
{
    if (!carregarDiretoriosEPastas())
    {
        cout << "Algo de errado aconteceu ao iniciar o sistema...";
        return 0;
    }

    int opcaoMenu;

    do
    {
        opcaoMenu = menu();

        switch (opcaoMenu)
        {
        case 1: // fazer pedido
            limpatela();
            {
                string opcaoCadastro;

                cout << "-----------------------------------------" << endl
                     << "Insira o nome ou telefone do cadastro: ";
                getline(cin, opcaoCadastro);
                if (opcaoCadastro.empty())
                {
                    cout << "-----------------------------------------" << endl
                         << "Opcao invalida" << endl
                         << "Pressione enter para voltar ao menu...";
                    cin.get();
                    break;
                }

                string nomeCliente;

                bool cadastrado = false;

                for (size_t i = 0; i < listaClientes.size(); i++)
                {
                    if (listaClientes[i].mostraTelefone() == opcaoCadastro)
                    {
                        cadastrado = true;
                        nomeCliente = listaClientes[i].mostraNome() + ".txt";
                        opcaoCadastro = listaClientes[i].mostraTelefone();
                        break;
                    }

                    if (listaClientes[i].mostraNome() == opcaoCadastro)
                    {
                        cadastrado = true;
                        nomeCliente = listaClientes[i].mostraNome() + ".txt";
                        opcaoCadastro = listaClientes[i].mostraTelefone();
                        break;
                    }
                }

                if (!cadastrado)
                {
                    cout << "-----------------------------------------" << endl
                         << "Nao foi encontrado nenhum cadastro com este numero" << endl
                         << "Voce deseja cadastrar este cliente? (s/n): ";
                    string confirma;
                    getline(cin, confirma);

                    if (confirma.empty())
                    {
                        cout << endl
                             << "Opcao invalida" << endl
                             << endl
                             << "Pressione enter para voltar ao menu...";
                        cin.get();
                        break;
                    }

                    if (confirma == "n")
                    {
                        cout << endl
                             << "Pressione enter para voltar ao menu...";
                        cin.get();
                        break;
                    }

                    if (cadastrarCliente())
                    {
                        cout << "-----------------------------------------" << endl
                             << "Cadastro realizado com sucesso!" << endl;
                        opcaoCadastro = listaClientes.back().mostraTelefone();
                    }
                    else
                    {
                        cout << "-----------------------------------------" << endl
                             << "O cadastro nao foi completado!" << endl;
                        cout << endl
                             << "Pressione enter para voltar ao menu...";
                        cin.get();
                        break;
                    }
                }

                bool clienteExiste = false;

                for (auto &c : listaClientes)
                {
                    if (c.mostraTelefone() == opcaoCadastro)
                    {
                        clienteExiste = true;
                        break;
                    }
                }

                if (!clienteExiste)
                {
                    cout << "Cliente nao encontrado após tentativa de cadastro!" << endl;
                }
                else if (!fazerPedido(opcaoCadastro))
                {
                    limpatela();
                    cout << "O pedido não foi completado!" << endl;
                }
                else
                {
                    limpatela();
                    cout << "Pedido foi feito com sucesso!" << endl;
                }
            }

            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 2: // mostrar pedidos
            limpatela();
            if (listaPedidos.empty())
            {
                cout << "Nenhum pedido foi feito ainda." << endl;
            }
            else
            {
                cout << "Pedidos feitos: " << endl
                     << "-----------------------------------------" << endl;

                mostrarPedidos();

                cout << "Foram feitos " << listaPedidos.size() << " pedidos" << endl
                     << endl;

                string opcao;
                cout << "Para saber mais informacoes sobre um pedido insira o id, para voltar ao menu pressione enter" << endl
                     << "ID: ";

                getline(cin, opcao);

                if (!opcao.empty())
                {
                    try
                    {
                        int id = stoi(opcao);

                        if (id >= 0 && id < listaPedidos.size())
                        {
                            mostrarPedidoDetalhado(id);
                        }
                        else
                        {
                            cout << "Nenhum pedido encontrado com este id. Tente novamente..." << endl;
                            break;
                        }
                    }
                    catch (exception &e)
                    {
                        cout << "Opcao invalida, tente novamente..." << endl;
                        break;
                    }
                }
            }
            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 3: // cadastrar cliente
            if (cadastrarCliente())
            {
                cout << "Cadastro realizado com sucesso!" << endl;
            }
            else
            {
                cout << "O cadastro nao foi completado!" << endl;
            }

            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 4: // excluir pedidos
            limpatela();

            excluirPedido();

            cout << "Pressione enter para voltar ao menu" << endl;
            cin.get();

            break;

        case 5: // mostrar clientes
            limpatela();

            mostrarClientesCadastrados();

            cout << "Pressione enter para voltar ao menu" << endl;
            cin.get();
            break;

        case 6: // excluir clientes
            limpatela();
            {
                string clienteDel;

                cout << "Insira o nome ou numero do cliente a ser excluido: ";
                getline(cin, clienteDel);

                bool cadastrado = false;

                for (size_t i = 0; i < listaClientes.size(); i++)
                {
                    if (listaClientes[i].mostraTelefone() == clienteDel || listaClientes[i].mostraNome() == clienteDel)
                    {
                        cadastrado = true;
                        break;
                    }
                }

                if (!cadastrado)
                {
                    cout << "Cadastro nao encontrado" << endl
                         << "Pressione enter para voltar ao menu...";
                    cin.get();
                    break;
                }

                for (size_t i = 0; i < listaClientes.size(); i++)
                {
                    if (listaClientes[i].mostraTelefone() == clienteDel)
                    {
                        cout << "-----------------------------------------" << endl
                             << "Nome: " << listaClientes[i].mostraNome() << endl
                             << "Telefone: " << listaClientes[i].mostraTelefone() << endl
                             << "Bairro: " << get<0>(listaClientes[i].mostraEndereco()) << endl
                             << "Rua: " << get<1>(listaClientes[i].mostraEndereco()) << endl
                             << "Numero: " << get<2>(listaClientes[i].mostraEndereco()) << endl
                             << "Complemento: " << get<3>(listaClientes[i].mostraEndereco()) << endl
                             << "-----------------------------------------" << endl;
                    }
                }

                string confirma;
                cout << "Excluir cadastro? (s/n): ";
                getline(cin, confirma);

                if (confirma.empty())
                {
                    cout << "Opcao invalida" << endl
                         << endl
                         << "Pressione enter para voltar ao menu...";
                    cin.get();
                    break;
                }

                if (confirma == "n")
                {
                    break;
                }

                limpatela();

                if (excluirCliente(clienteDel) == true)
                {
                    cout << "Cliente excluido com sucesso!" << endl;
                }
            }

            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 7: // editar cliente
            limpatela();
            {
                string clienteEditar;

                cout << "Número ou nome do cliente para editar: ";
                getline(cin, clienteEditar);

                bool cadastrado = false;

                tuple<string, string, tuple<string, string, string, string>> cadastroAtual;

                for (size_t i = 0; i < listaClientes.size(); i++)
                {
                    if (listaClientes[i].mostraTelefone() == clienteEditar || listaClientes[i].mostraNome() == clienteEditar)
                    {
                        get<0>(cadastroAtual) = listaClientes[i].mostraNome();
                        get<1>(cadastroAtual) = listaClientes[i].mostraTelefone();
                        get<2>(cadastroAtual) = listaClientes[i].mostraEndereco();

                        cadastrado = true;
                        break;
                    }
                }

                if (!cadastrado)
                {
                    cout << "Cadastro nao encontrado" << endl
                         << "Pressione enter para voltar ao menu...";
                    cin.get();
                    break;
                }

                cadastrarCliente(&cadastroAtual);
            }
            break;

        case 0: // encerra programa
            limpatela();

            cout << "Criando backup do sistema..." << endl;

            if (!fs::exists("../backups/"))
            {
                fs::create_directory("../backups");
                fs::create_directory("../backups/clientes");
                fs::create_directory("../backups/pedidos");
                fs::create_directory("../backups/listas");
            }

            if (fs::exists("../clientes") || fs::exists("../pedidos"))
            {
                fs::copy("../clientes", "../backups/clientes", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                fs::copy("../pedidos", "../backups/pedidos", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                fs::copy("../arquivos/listaClientes.txt", "../backups/listas", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                fs::copy("../arquivos/listaPedidos.txt", "../backups/listas", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
            }
            
            cout << "Backups criados com sucesso..." << endl

                 << "Encerrando sistema..." << endl;
            return 0;
        }
    } while (opcaoMenu != 0);
}

bool fazerPedido(string telefone)
{
    limpatela();

    string nomePedido, telefonePedido;
    tuple<string, string, string, string> enderecoPedido;
    // ⮮⮮        item     com     sem    valor    ⮯⮯
    vector<tuple<string, string, string, float>> itensPedido;

    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].mostraTelefone() == telefone)
        {
            nomePedido = listaClientes[i].mostraNome();
            telefonePedido = listaClientes[i].mostraTelefone();
            enderecoPedido = listaClientes[i].mostraEndereco();

            cout << "-----------------------------------------" << endl
                 << "Nome: " << listaClientes[i].mostraNome() << endl
                 << "Telefone: " << listaClientes[i].mostraTelefone() << endl
                 << "Bairro: " << get<0>(listaClientes[i].mostraEndereco()) << endl
                 << "Rua: " << get<1>(listaClientes[i].mostraEndereco()) << endl
                 << "Numero: " << get<2>(listaClientes[i].mostraEndereco()) << endl
                 << "Complemento: " << get<3>(listaClientes[i].mostraEndereco()) << endl
                 << "-----------------------------------------" << endl;
        }
    }

    string confirma;
    cout << "Fazer pedido neste cadastro? (s/n): ";
    getline(cin, confirma);

    if (confirma.empty())
    {
        cout << "Opcao invalida" << endl
             << endl
             << "Pressione enter para voltar ao menu...";
        cin.get();
        return false;
    }

    if (confirma == "n")
    {
        return false;
    }

    string item, adicionarIngrediente, retirarIngrediente;
    float valorItem, valorPedido, valorEntrega, valorTotal;

    limpatela();

    string adicionarItem = "s";

    while (adicionarItem == "s")
    {

        cout << "-----------------------------------------" << endl
             << "Insira o item a ser adicionado: ";
        getline(cin, item);
        cout << "Com: ";
        getline(cin, adicionarIngrediente);
        cout << "Sem: ";
        getline(cin, retirarIngrediente);
        cout << "-----------------------------------------" << endl
             << "Valor do item: R$ ";
        cin >> valorItem;
        cin.ignore();

        itensPedido.push_back(make_tuple(item, adicionarIngrediente, retirarIngrediente, valorItem));

        cout << endl
             << "Você deseja adicionar mais item ao pedido? (s/n): ";
        getline(cin, adicionarItem);

        limpatela();
    }

    valorPedido = get<3>(itensPedido[0]);

    for (size_t i = 1; i < itensPedido.size(); i++)
    {
        valorPedido += get<3>(itensPedido[i]);
    }

    cout << "Insira o valor da entrega: ";
    cin >> valorEntrega;
    cin.ignore();

    valorTotal = valorPedido + valorEntrega;

    // salva pedido em um .txt
    ofstream fileSalvar("listaPedidos.txt", ios::app);

    if (fileSalvar.is_open())
    {
        fileSalvar << "Nome: " << nomePedido << " | Telefone: " << telefonePedido;
        for (auto &itens : itensPedido)
        {
            fileSalvar << " | Item: " << get<0>(itens) << " | Com: " << get<1>(itens) << " | Sem: " << get<2>(itens)
                       << " | Valor item: " << fixed << setprecision(2) << get<3>(itens);
        }
        fileSalvar << " | Taxa de entrega: " << fixed << setprecision(2) << valorEntrega << fixed << setprecision(2)
                   << " | Valor total: " << valorTotal << endl;
    }

    listaPedidos.push_back(make_tuple(cliente(nomePedido, telefonePedido, enderecoPedido), itensPedido, valorEntrega, valorTotal));

    imprimePedido(get<0>(listaPedidos.back()), itensPedido, valorPedido, valorEntrega, valorTotal);

    itensPedido.clear(); // esvasia vetor com itens para próximo pedido

    return true;
}

void imprimePedido(cliente c, vector<tuple<string, string, string, float>> clientePedido, float valorPedido, float valorEntrega, float valorTotal)
{
    string arquivoPedido = "pedido-" + to_string(listaPedidos.size()) + "_cliente-" + c.mostraNome();
    string caminhoArquivo = "../pedidos/" + arquivoPedido + ".txt";

    // cria file com dados do pedido para impressao
    ofstream filePedido(caminhoArquivo);
    if (filePedido.is_open())
    {
        for (size_t i = 0; i < 2; i++)
        {
            filePedido << "Data: " << printData() << endl
                       << "Nome: " << c.mostraNome() << endl
                       << "Telefone: " << c.mostraTelefone() << endl
                       << "Bairro: " << get<0>(c.mostraEndereco()) << endl
                       << "Rua: " << get<1>(c.mostraEndereco()) << endl
                       << "Numero: " << get<2>(c.mostraEndereco()) << endl
                       << "Complemento: " << get<3>(c.mostraEndereco()) << endl
                       << "-----------------------------------" << endl;

            for (size_t i = 0; i < clientePedido.size(); i++)
            {
                filePedido << get<0>(clientePedido[i]) << "                 R$" << fixed << setprecision(2) << get<3>(clientePedido[i]) << endl
                           << "Com: " << fixed << setprecision(2) << get<1>(clientePedido[i]) << endl
                           << "Sem: " << fixed << setprecision(2) << get<2>(clientePedido[i]) << endl
                           << "-----------------------------------" << endl;
            }

            filePedido << "Valor do pedido: R$ " << fixed << setprecision(2) << valorPedido << endl
                       << "Valor da entrega: R$ " << fixed << setprecision(2) << valorEntrega << endl
                       << "Valor total: R$ " << fixed << setprecision(2) << valorTotal << endl;
            if (i < 1)
            {
                filePedido << endl
                           << "." << endl
                           << endl;
            }
        }
    }
    filePedido.close();

    /*// imprime na impressora padrao
    #ifdef _WIN32
        string comando = "notepad /p \"" + caminhoArquivo + "\"";
    #else
        string comando = "lp \"" + caminhoArquivo + "\"";
    #endif

        system(comando.c_str());*/
}

void mostrarPedidos()
{
    for (size_t i = 0; i < listaPedidos.size(); i++)
    {
        cout << "[" << i << "] Nome: " << get<0>(listaPedidos[i]).mostraNome()
             << ", telefone: " << get<0>(listaPedidos[i]).mostraTelefone() << endl
             << "-----------------------------------------" << endl;
    }
}

void mostrarPedidoDetalhado(int id)
{
    limpatela();
    cout << "Numero do pedido: " << id << endl
         << "Nome: " << get<0>(listaPedidos[id]).mostraNome() << endl
         << "Telefone: " << get<0>(listaPedidos[id]).mostraTelefone() << endl
         << "Bairro: " << get<0>(get<0>(listaPedidos[id]).mostraEndereco()) << endl
         << "Rua: " << get<1>(get<0>(listaPedidos[id]).mostraEndereco()) << endl
         << "Numero: " << get<2>(get<0>(listaPedidos[id]).mostraEndereco()) << endl
         << "Complemento: " << get<3>(get<0>(listaPedidos[id]).mostraEndereco()) << endl
         << "-----------------------------------------" << endl;

    for (auto &pedido : get<1>(listaPedidos[id]))
    {
        cout << "Item: " << get<0>(pedido) << "                 R$" << fixed << setprecision(2) << get<3>(pedido) << endl
             << "Com: " << get<1>(pedido) << endl
             << "Sem: " << get<2>(pedido) << endl
             << "-----------------------------------------" << endl;
    }

    cout << "Valor pedido: " << fixed << setprecision(2) << (get<3>(listaPedidos[id]) - get<2>(listaPedidos[id])) << endl
         << "Taxa de entrega: " << fixed << setprecision(2) << get<2>(listaPedidos[id]) << endl
         << "Valor total: " << fixed << setprecision(2) << get<3>(listaPedidos[id]);

    cout << endl;
}

bool cadastrarCliente(tuple<string, string, tuple<string, string, string, string>> *cadastroAtual)
{
    limpatela();

    string tempNome, tempTelefone, tempBairro, tempRua, tempNumero, tempComplemento;

    cout << "-----------------------------------------" << endl
         << "Insira os dados do cliente: " << endl
         << "Nome: ";
    getline(cin, tempNome);

    bool novoCadastro = (cadastroAtual == nullptr);

    if (novoCadastro)
    {
        for (auto &cliente : listaClientes)
        {
            if (cliente.mostraNome() == tempNome)
            {
                cout << "Ja existe um cadastro com este nome" << endl;
                return false;
            }
        }
    }

    cout << "Telefone: ";
    getline(cin, tempTelefone);

    if (novoCadastro)
    {
        for (auto &cliente : listaClientes)
        {
            if (cliente.mostraTelefone() == tempTelefone)
            {
                cout << "Ja existe um cadastro com este telefone" << endl;
                return false;
            }
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

    if (novoCadastro)
    {
        if (tempNome.empty() || tempTelefone.empty() || tempBairro.empty() || tempRua.empty() || tempNumero.empty() || tempComplemento.empty())
        {
            limpatela();
            cout << "-----------------------------------------" << endl
                 << "Algum(ns) dos dados cadastrados esta(ao) invalido(s)" << endl;
            return false;
        }
    }
    string nomeFinal = tempNome.empty() ? (novoCadastro ? "" : get<0>(*cadastroAtual)) : tempNome;
    string telefoneFinal = tempTelefone.empty() ? (novoCadastro ? "" : get<1>(*cadastroAtual)) : tempTelefone;
    string bairroFinal = tempBairro.empty() ? (novoCadastro ? "" : get<0>(get<2>(*cadastroAtual))) : tempBairro;
    string ruaFinal = tempRua.empty() ? (novoCadastro ? "" : get<1>(get<2>(*cadastroAtual))) : tempRua;
    string numeroFinal = tempNumero.empty() ? (novoCadastro ? "" : get<2>(get<2>(*cadastroAtual))) : tempNumero;
    string complementoFinal = tempComplemento.empty() ? (novoCadastro ? "" : get<3>(get<2>(*cadastroAtual))) : tempComplemento;

    limpatela();
    cout << "Revisão dos dados: " << endl
         << endl;
    cout << "Nome: " << nomeFinal << endl;
    cout << "Telefone: " << telefoneFinal << endl;
    cout << "Bairro: " << bairroFinal << endl;
    cout << "Rua: " << ruaFinal << endl;
    cout << "Numero: " << numeroFinal << endl;
    cout << "Complemento: " << complementoFinal << endl;

    string confirma;
    cout << endl
         << "Os dados estao corretos? (s/n): ";
    getline(cin, confirma);

    if (confirma != "s")
    {
        limpatela();
        cout << "Operacao cancelada." << endl;
        return false;
    }

    if (novoCadastro)
    {
        listaClientes.push_back(cliente(nomeFinal, telefoneFinal, make_tuple(bairroFinal, ruaFinal, numeroFinal, complementoFinal)));
    }
    else
    {
        string nomeAntigo = get<0>(*cadastroAtual);

        ifstream inFile("listaClientes.txt");
        ofstream tempFile("tempLista.txt");
        string linha;

        if (inFile.is_open() && tempFile.is_open())
        {
            while (getline(inFile, linha))
            {
                if (linha.find("Nome: " + nomeAntigo + " ") == string::npos)
                    tempFile << linha << endl;
            }
            inFile.close();
            tempFile.close();
            remove("listaClientes.txt");
            rename("tempLista.txt", "listaClientes.txt");
        }

        remove(("../clientes/" + nomeAntigo + ".txt").c_str());

        get<0>(*cadastroAtual) = nomeFinal;
        get<1>(*cadastroAtual) = telefoneFinal;
        get<0>(get<2>(*cadastroAtual)) = bairroFinal;
        get<1>(get<2>(*cadastroAtual)) = ruaFinal;
        get<2>(get<2>(*cadastroAtual)) = numeroFinal;
        get<3>(get<2>(*cadastroAtual)) = complementoFinal;
    }

    ofstream fileCliente("../clientes/" + nomeFinal + ".txt");
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

    ofstream fileLista("listaClientes.txt", ios::app);
    if (fileLista.is_open())
    {
        fileLista << "Nome: " << nomeFinal
                  << " | Telefone: " << telefoneFinal
                  << " | Bairro: " << bairroFinal
                  << " | Rua: " << ruaFinal
                  << " | Numero: " << numeroFinal
                  << " | Complemento: " << complementoFinal << endl;
        fileLista.close();
    }
    
    return true;
}

void excluirPedido()
{
    size_t opc;

    cout << "1. Exluir todos os pedidos" << endl
         << "2. Exluir um unico pedido" << endl
         << "3. Voltar ao menu" << endl
         << "Insira a opcao: ";

    cin >> opc;
    cin.ignore();

    switch (opc)
    {
    case 1:
        fs::remove_all("../pedidos/");
        remove("listaPedidos.txt");
        cout << "Pasta removida" << endl;
        
        fs:: create_directory("../pedidos/");
        return;

    case 2:
    {
        limpatela();

        mostrarPedidos();

        if (!listaPedidos.size() > 0)
        {
            return;
        }

        cout << "Insira o numero do pedido a ser excluido: ";
        size_t id;
        cin >> id;
        cin.ignore();

        if (id > listaPedidos.size())
        {
            cout << "Nao existe pedido com este id..." << endl;
            return;
        }

        string arquivoPedido = "pedido-" + to_string(id + 1) + "_cliente-" + get<0>(listaPedidos[id]).mostraNome();
        string caminhoArquivo = "../pedidos/" + arquivoPedido + ".txt";

        remove(("../pedidos/" + caminhoArquivo).c_str());

        listaPedidos.erase(listaPedidos.begin() + id);

        // atualiza listaPedidos
        ofstream fileExclui("listaPedidos.txt");

        if (fileExclui.is_open())
        {
            for (auto &c : listaPedidos)
            {
                fileExclui << "Nome: " << get<0>(c).mostraNome() << " | Telefone: " << get<0>(c).mostraTelefone();

                for (auto &itens : get<1>(listaPedidos[id]))
                {
                    fileExclui << " | Item: " << get<0>(itens) << " | Com: " << get<1>(itens)
                               << " | Sem: " << get<2>(itens) << " | Valor item: " << fixed << setprecision(2)
                               << get<3>(itens);
                }
                fileExclui << " | Taxa de entrega: R$ " << fixed << setprecision(2) << get<2>(c)
                           << " | Valor total: R$ " << fixed << setprecision(2) << get<3>(c);
            }
        }

        fileExclui.close();
    }
        return;

    case 3:
        return;
    }
}

bool excluirCliente(string delCliente)
{
    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].mostraTelefone() == delCliente)
        {
            string nomeArquivoCliente = listaClientes[i].mostraNome() + ".txt";

            remove(("../clientes/" + nomeArquivoCliente).c_str());

            listaClientes.erase(listaClientes.begin() + i);

            ofstream fileExclui("listaClientes.txt");

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
    if (listaClientes.empty())
    {
        cout << "Nenhum cliente cadastrado ainda." << endl;
    }
    else
    {
        cout << "Clientes cadastrados: " << endl
             << "-----------------------------------------" << endl;

        for (size_t i = 0; i < listaClientes.size(); i++)
        {
            cout << "[" << i << "] Nome: " << listaClientes[i].mostraNome()
                 << ", telefone: " << listaClientes[i].mostraTelefone() << endl
                 << "-----------------------------------------" << endl;
        }

        cout << "Foram cadastrados " << listaClientes.size() << " clientes" << endl
             << endl;

        string opcao;
        cout << "Para saber mais informacoes sobre um cliente insira o id, para voltar ao menu pressione enter" << endl
             << "ID: ";

        getline(cin, opcao);

        if (!opcao.empty())
        {
            try
            {
                int id = stoi(opcao);

                if (id >= 0 && id < listaClientes.size())
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
                else
                {
                    cout << "Nenhum pedido encontrado com este id. Tente novamente..." << endl;
                    return;
                }
            }
            catch (exception &e)
            {
                cout << "Opcao invalida, tente novamente..." << endl;
                return;
            }
        }
    }
}

bool carregarPathClientes(string path, vector<string> &diretorio)
{
    ifstream fileCarrega(path);
    string linha;

    if (!fileCarrega.is_open())
    {
        return false;
    }

    while (getline(fileCarrega, linha))
    {
        if (!linha.empty())
            diretorio.push_back(linha);
    }

    fileCarrega.close();
    return true;
}

bool carregarClientes(const vector<string> &diretorio)
{
    for (auto &linha : diretorio)
    {
        size_t posNome = linha.find("Nome:");
        size_t posTel = linha.find("Telefone:");
        size_t posBairro = linha.find("Bairro:");
        size_t posRua = linha.find("Rua:");
        size_t posNum = linha.find("Numero:");
        size_t posComp = linha.find("Complemento:");

        string tempNome = linha.substr(posNome + 6, posTel - posNome - 9);
        string tempTelefone = linha.substr(posTel + 10, posBairro - posTel - 13);
        string tempBairro = linha.substr(posBairro + 7, posRua - posBairro - 10);
        string tempRua = linha.substr(posRua + 5, posNum - posRua - 8);
        string tempNum = linha.substr(posNum + 8, posComp - posNum - 11);
        string tempComp = linha.substr(posComp + 13);

        listaClientes.push_back(cliente(tempNome, tempTelefone, tuple<string, string, string, string>(tempBairro, tempRua, tempNum, tempComp)));
    }

    return true;
}

/*bool carregarPathPedidos(string path, vector<string> &diretorio)
{
    ifstream fileCarrega(path);
    string linha;

    if (!fileCarrega.is_open())
        return false;

    while (getline(fileCarrega, linha))
    {
        if (!linha.empty())
            diretorio.push_back(linha);
    }

    fileCarrega.close();
    return true;
}

bool carregarPedidos(const vector<string> &diretorio)
{
    for (auto &linha : diretorio)
    {
        size_t posNome = linha.find("Nome:");
        size_t posTel = linha.find("Telefone:");
        size_t posItem = linha.find("Item:");
        size_t posTaxa = linha.find("Taxa de entrega:");
        size_t posTotal = linha.find("Valor total:");

        string nome = linha.substr(posNome + 6, posTel - posNome - 9);
        string telefone = linha.substr(posTel + 10, posItem - posTel - 13);

        vector<tuple<string, string, string, float>> itens;
        size_t pos = posItem;

        while (true)
        {
            size_t nextItem = linha.find("Item:", pos);
            if (nextItem == string::npos) break;
            pos = nextItem + 6;

            size_t barra = linha.find(" | ", pos);
            string item = linha.substr(pos, barra - pos);
            pos = barra + 3;

            // Com:
            if (linha.find("Com:", pos) != pos) break;
            pos += 5;
            barra = linha.find(" | ", pos);
            string com = linha.substr(pos, barra - pos);
            pos = barra + 3;

            // Sem:
            if (linha.find("Sem:", pos) != pos) break;
            pos += 5;
            barra = linha.find(" | ", pos);
            string sem = linha.substr(pos, barra - pos);
            pos = barra + 3;

            // Valor item:
            if (linha.find("Valor item:", pos) != pos) break;
            pos += 13;
            barra = linha.find(" | ", pos);
            string valorStr;
            if (barra == string::npos)
            {
                valorStr = linha.substr(pos);
                pos = linha.length();
            }
            else
            {
                valorStr = linha.substr(pos, barra - pos);
                pos = barra + 3;
            }

            float valor = stof(valorStr);
            itens.push_back(make_tuple(item, com, sem, valor));
        }

        float taxaEntrega = 0, valorTotal = 0;

        if (posTaxa != string::npos)
        {
            size_t posValor = posTaxa + 18;
            size_t barra = linha.find(" | ", posValor);
            string taxaStr = linha.substr(posValor, barra - posValor);
            taxaEntrega = stof(taxaStr);
        }

        if (posTotal != string::npos)
        {
            size_t posValor = posTotal + 13;
            string totalStr = linha.substr(posValor);
            valorTotal = stof(totalStr);
        }

        cliente tempCliente(nome, telefone, make_tuple("", "", "", ""));
        listaPedidos.push_back(make_tuple(tempCliente, itens, taxaEntrega, valorTotal));
    }

    return true;
}
*/

bool carregarDiretoriosEPastas()
{
    // cria pasta clientes
    if (!fs::exists("../clientes"))
    {
        fs::create_directory("../clientes");
    }

    // cria pasta pedidos
    if (!fs::exists("../pedidos"))
    {
        fs::create_directory("../pedidos");
    }

    // Carregar clientes
    if (!carregarPathClientes("listaClientes.txt", diretorioClientes))
    {
        fstream("listaClientes.txt", ios::app).close();
    }
    else
    {
        carregarClientes(diretorioClientes);
    }

    // Carregar pedidos
    /*  if (!carregarPathPedidos("listaPedidos.txt", diretorioPedidos))
      {
          fstream("listaPedidos.txt", ios::app).close();
      }
      else
      {
          carregarPedidos(diretorioPedidos);
      }
  */
    return true;
}

string printData()
{
    time_t DataHora = time(0);
    char *data = ctime(&DataHora);

    return string(data);
}

int menu()
{
    limpatela();

    size_t op;

    do
    {
        cout << "------------------------------" << endl;
        cout << "1. Fazer Pedido" << endl;
        cout << "2. Mostrar Pedidos" << endl;
        cout << "3. Cadastrar Cliente" << endl;
        cout << "4. Excluir Pedidos" << endl;
        cout << "5. Mostrar Clientes" << endl;
        cout << "6. Excluir Cliente" << endl;
        cout << "7. Editar Cliente" << endl;
        cout << "0. Fechar Sistema" << endl;
        cout << "------------------------------" << endl;
        cout << "Escolha uma Opcao: ";
        cin >> op;

        limpatela();

        if (cin.fail() || op > 7)
        {
            cout << "Opcao invalida, tente novamente..." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = -1;
            cin.get();
        }
        else
        {
            cin.get();
        }

    } while (op < 0 || op > 7);

    return op;
}

void limpatela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
