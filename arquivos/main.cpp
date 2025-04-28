#include "cliente.hpp"

/////////////////////////////
// funcoes operacoes arquivos
bool carregarPathClientes(string path, vector<string> &diretorio);
bool carregarClientes(const vector<string> &diretorio);
bool carregarDiretoriosEPastas();
/////////////////////////////

/////////////////////////////
// funcoes operacoes sistema
bool fazerPedido(string telefone);
void mostrarPedidos();
bool cadastrarCliente();
void fecharPedidos();
void mostrarClientesCadastrados();
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
// item, adicionarIngrediente, removerIngrediente, valor
vector<tuple<string, string, string, float>> itensPedido;
vector<string> listaPedidos;
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

                cout << "Insira o telefone do cadastro: ";
                getline(cin, opcaoCadastro);

                bool cadastrado = false;

                string nomeCliente;

                for (size_t i = 0; i < listaClientes.size(); i++)
                {
                    if (listaClientes[i].mostraTelefone() == opcaoCadastro)
                    {
                        cadastrado = true;
                        nomeCliente = listaClientes[i].mostraNome() + ".txt";
                        break;
                    }
                }

                if (!cadastrado)
                {
                    cout << "Nao foi encontrado nenhum cadastro com este numero" << endl
                         << "Para cadastrar pressione enter";
                    cin.get();
                    cout << endl;

                    if (cadastrarCliente() == true)
                    {
                        cout << "Cadastro realizado com sucesso!" << endl;
                    }
                    else
                    {
                        cout << "O cadastro nao foi completado!" << endl;
                    }
                    opcaoCadastro = listaClientes.back().mostraTelefone();
                }

                if (!fazerPedido(opcaoCadastro))
                {
                    limpatela();
                    cout << "O pedido não foi completado!" << endl;
                }
                else
                {
                    limpatela();
                    cout << "Pedido foi feito com sucesso!" << endl;
                    system(("notepad-plus-plus \"../clientes/" + nomeCliente + "\"").c_str());
                }
            }

            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 2: // mostrar pedidos
            limpatela();
            cout << "teste 2";

            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 3: // cadastrar cliente
            limpatela();

            if (cadastrarCliente() == true)
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

        case 4: // fechar caixa
            limpatela();

            cout << listaClientes[0].mostraTelefone();

            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 5: // mostrar clientes
            limpatela();

            mostrarClientesCadastrados();

            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 6: // excluir clientes
            limpatela();
            {
                string telefoneDel;

                cout << "Insira o numero de telefone do cliente a ser excluido: ";
                getline(cin, telefoneDel);

                for (size_t i = 0; i < listaClientes.size(); i++)
                {
                    if (listaClientes[i].mostraTelefone() == telefoneDel)
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

                if (confirma == "n")
                {
                    break;
                }

                if (excluirCliente(telefoneDel) == true)
                {
                    cout << endl
                         << "Cliente excluido com sucesso!" << endl;
                }
                else
                {
                    cout << "Cliente nao encontrado!" << endl;
                }
            }

            cout << endl
                 << "Pressione enter para voltar ao menu...";
            cin.get();
            break;

        case 0: // encerra programa
            limpatela();

            cout << "Encerrando sistema..." << endl;
            return 0;
        }

    } while (opcaoMenu != 0);
}

bool fazerPedido(string telefone)
{
    limpatela();

    string arquivoPedido;
    string nomePedido;
    string telefonePedido;
    tuple<string, string, string, string> enderecoPedido;

    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].mostraTelefone() == telefone)
        {
            nomePedido = listaClientes[i].mostraNome();
            telefonePedido = listaClientes[i].mostraTelefone();
            enderecoPedido = listaClientes[i].mostraEndereco();

            arquivoPedido = "pedido-" + to_string(listaPedidos.size()) + "_cliente-" + nomePedido;

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
        cout << "Insira o item a ser adicionado: ";
        getline(cin, item);
        cout << "Com: ";
        getline(cin, adicionarIngrediente);
        cout << "Sem: ";
        getline(cin, retirarIngrediente);
        cout << "-------------------------------------" << endl
             << "Valor do item: R$ ";
        cin >> valorItem;
        cin.ignore();

        itensPedido.push_back(make_tuple(item, adicionarIngrediente, retirarIngrediente, valorItem));

        cout << endl
             << "Você deseja adicionar mais item ao pedido? (s/n):";
        getline(cin, adicionarItem);
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

    // cria file com dados do pedido para impressao
    ofstream filePedido("../pedidos/" + arquivoPedido + ".txt");
    if (filePedido.is_open())
    {
        filePedido << "Data: " << printData() << endl
                   << endl
                   << "Nome: " << nomePedido << endl
                   << "Telefone" << telefonePedido
                   << "Bairro: " << get<0>(enderecoPedido) << endl
                   << "Rua: " << get<1>(enderecoPedido) << endl
                   << "Numero: " << get<2>(enderecoPedido) << endl
                   << "Complemento: " << get<3>(enderecoPedido) << endl
                   << endl
                   << "-------------------------------------------------" << endl;

        for (size_t i = 0; i < itensPedido.size(); i++)
        {
            filePedido << get<0>(itensPedido[i]) << "           R$" << get<3>(itensPedido[i]) << endl
                       << "Com: " << get<1>(itensPedido[i]) << endl
                       << "Sem: " << get<2>(itensPedido[i]) << endl
                       << "-------------------------------------------------" << endl;
        }

        filePedido << endl
                   << endl
                   << "Valor do pedido: R$ " << valorPedido << endl
                   << "Valor da entrega: R$ " << valorEntrega << endl
                   << "Valor total: R$ " << valorTotal << endl;
    }

    itensPedido.clear(); // esvasia vetor com itens para próximo pedido
    return true;
}

void mostrarPedidos()
{
}

bool cadastrarCliente()
{
    tuple<string, string, string, string> tempEndereco;
    string tempNome, tempTelefone, tempBairro, tempRua, tempNumero, tempComplemento;

    cout << "Insira os dados do cliente: " << endl;
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

    if (tempNome.empty() || tempTelefone.empty() || tempBairro.empty() || tempRua.empty() || tempNumero.empty() || tempComplemento.empty())
    {
        limpatela();
        cout << endl
             << "Algum(ns) dos dados cadastrados esta(ao) invalido(s)";
        return false;
    }

    tempEndereco = make_tuple(tempBairro, tempRua, tempNumero, tempComplemento);

    limpatela();

    cout << "Revisão dos dados: " << endl
         << endl
         << "Nome: " << tempNome << endl
         << "Telefone: " << tempTelefone << endl
         << "Bairro: " << get<0>(tempEndereco) << endl
         << "Rua: " << get<1>(tempEndereco) << endl
         << "Numero: " << get<2>(tempEndereco) << endl
         << "Complemento: " << get<3>(tempEndereco) << endl;

    string confirma;
    cout << endl
         << "Confirmar cadastro? (s/n): ";
    getline(cin, confirma);

    if (confirma == "n")
    {
        return false;
    }

    limpatela();

    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].mostraTelefone() == tempTelefone)
        {
            return false;
        }
    }

    listaClientes.push_back(cliente(tempNome, tempTelefone, tempEndereco));

    ofstream fileCliente("../clientes/" + tempNome + ".txt");
    if (fileCliente.is_open())
    {
        fileCliente << "Nome: " << tempNome << endl
                    << "Telefone: " << tempTelefone << endl
                    << "Bairro: " << get<0>(tempEndereco) << endl
                    << "Rua: " << get<1>(tempEndereco) << endl
                    << "Numero: " << get<2>(tempEndereco) << endl
                    << "Complemento: " << get<3>(tempEndereco) << endl;
    }
    fileCliente.close();

    ofstream fileLista("listatodosclientes.txt", ios::app);
    if (fileLista.is_open())
    {
        fileLista << "Nome: " << tempNome
                  << " | Telefone: " << tempTelefone
                  << " | Bairro: " << get<0>(tempEndereco)
                  << " | Rua: " << get<1>(tempEndereco)
                  << " | Numero: " << get<2>(tempEndereco)
                  << " | Complemento: " << get<3>(tempEndereco) << endl;
    }
    fileLista.close();

    return true;
}

void fecharPedidos()
{
}

bool excluirCliente(string delTelefone)
{
    string nomeArquivoCliente;

    for (size_t i = 0; i < listaClientes.size(); i++)
    {
        if (listaClientes[i].mostraTelefone() == delTelefone)
        {
            nomeArquivoCliente = listaClientes[i].mostraNome() + ".txt";

            remove(("../clientes/" + nomeArquivoCliente).c_str());

            listaClientes.erase(listaClientes.begin() + i);

            ofstream fileExclui("listatodosclientes.txt");

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
        cout << "Lista de Clientes cadastrados: " << endl
             << endl
             << "-----------------------------------------" << endl;

        for (size_t i = 0; i < listaClientes.size(); i++)
        {
            cout << "Nome: " << listaClientes[i].mostraNome() << endl
                 << "Telefone: " << listaClientes[i].mostraTelefone() << endl
                 << "Bairro: " << get<0>(listaClientes[i].mostraEndereco()) << endl
                 << "Rua: " << get<1>(listaClientes[i].mostraEndereco()) << endl
                 << "Numero: " << get<2>(listaClientes[i].mostraEndereco()) << endl
                 << "Complemento: " << get<3>(listaClientes[i].mostraEndereco()) << endl
                 << "-----------------------------------------" << endl;
        }

        cout << endl
             << "Existem " << listaClientes.size() << " clientes cadastrados" << endl
             << endl;
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
    for (const auto &linha : diretorio)
    {
        size_t posNome = linha.find("Nome:");
        size_t posTel = linha.find("Telefone:");
        size_t posBairro = linha.find("Bairro:");
        size_t posRua = linha.find("Rua:");
        size_t posNum = linha.find("Numero:");
        size_t posComp = linha.find("Complemento:");

        string tempNome = linha.substr(posNome + 6, posTel - posNome - 8);
        string tempTelefone = linha.substr(posTel + 10, posBairro - posTel - 13);
        string tempBairro = linha.substr(posBairro + 7, posRua - posBairro - 9);
        string tempRua = linha.substr(posRua + 5, posNum - posRua - 7);
        string tempNum = linha.substr(posNum + 8, posComp - posNum - 10);
        string tempComp = linha.substr(posComp + 13);

        listaClientes.push_back(cliente(tempNome, tempTelefone, tuple<string, string, string, string>(tempBairro, tempRua, tempNum, tempComp)));
    }

    return true;
}

bool carregarDiretoriosEPastas()
{
    if (!fs::exists("../clientes"))
    {
        fs::create_directory("../clientes");
    }

    if (!fs::exists("../pedidos"))
    {
        fs::create_directory("../pedidos");
    }

    if (!carregarPathClientes("listatodosclientes.txt", diretorioClientes))
    {
        ofstream("listatodosclientes.txt", ios::app).close();
    }
    else
    {
        carregarClientes(diretorioClientes);
    }

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
        cout << "4. Fechar Pedidos" << endl;
        cout << "5. Mostrar Clientes" << endl;
        cout << "6. Excluir Cliente" << endl;
        cout << "0. Fechar Sistema" << endl;
        cout << "------------------------------" << endl;
        cout << "Escolha uma Opcao: ";
        cin >> op;

        limpatela();

        if (cin.fail() || op > 6)
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

    } while (op < 0 || op > 6);

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
