#include "cliente.hpp"
#include "oppedidos.hpp"
#include "miscs.hpp"

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
    ofstream fileSalvar("listas/listaPedidos.txt", ios::app);

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

    listaPedidos.push_back(
        make_tuple(cliente(nomePedido, telefonePedido, enderecoPedido), itensPedido, valorEntrega, valorTotal));

    imprimePedido(get<0>(listaPedidos.back()), itensPedido, valorPedido, valorEntrega, valorTotal);

    itensPedido.clear(); // esvasia vetor com itens para próximo pedido

    return true;
}

void imprimePedido(cliente c, vector<tuple<string, string, string, float>> clientePedido, float valorPedido, float valorEntrega, float valorTotal)
{
    string arquivoPedido = "pedido-" + to_string(listaPedidos.size()) + "_cliente-" + c.mostraNome();
    string caminhoArquivo = "pedidos/" + arquivoPedido + ".txt";

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
                filePedido << get<0>(clientePedido[i]) << "                 R$" << fixed << setprecision(2)
                           << get<3>(clientePedido[i]) << endl
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

// imprime na impressora padrao
#ifdef _WIN32
    string comando = "notepad /p \"" + caminhoArquivo + "\"";
#else
    string comando = "lp \"" + caminhoArquivo + "\"";
#endif

    system(comando.c_str());
}

bool reimprimirPedido(int id)
{
    string arquivoPedido = "pedido-" + to_string(id + 1) + "_cliente-" + get<0>(listaPedidos[id]).mostraNome();
    string caminhoArquivo = "pedidos/" + arquivoPedido + ".txt";

// imprime na impressora padrao
#ifdef _WIN32
    string comando = "notepad /p \"" + caminhoArquivo + "\"";
#else
    string comando = "lp \"" + caminhoArquivo + "\"";
#endif

    system(comando.c_str());

    return true;
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
        cout << "Item: " << get<0>(pedido) << "                 R$" << fixed << setprecision(2) << get<3>(pedido)
             << endl
             << "Com: " << get<1>(pedido) << endl
             << "Sem: " << get<2>(pedido) << endl
             << "-----------------------------------------" << endl;
    }

    cout << "Valor pedido: " << fixed << setprecision(2) << (get<3>(listaPedidos[id]) - get<2>(listaPedidos[id]))
         << endl
         << "Taxa de entrega: " << fixed << setprecision(2) << get<2>(listaPedidos[id]) << endl
         << "Valor total: " << fixed << setprecision(2) << get<3>(listaPedidos[id]);

    cout << endl;
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
        fs::remove_all("pedidos/");
        remove("listas/listaPedidos.txt");
        cout << "Pasta removida" << endl;
        fs::create_directory("pedidos/");
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
        string caminhoArquivo = "pedidos/" + arquivoPedido + ".txt";

        remove((caminhoArquivo).c_str());

        listaPedidos.erase(listaPedidos.begin() + id);

        // atualiza listaPedidos
        ofstream fileExclui("listas/listaPedidos.txt");

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