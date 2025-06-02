#include "cliente.hpp"
#include "menus.hpp"
#include "miscs.hpp"
#include "opclientes.hpp"
#include "oppedidos.hpp"

/////////////////////////////
// funcoes operacoes arquivos
bool carregarPathClientes(string path, vector<string> &diretorio);
bool carregarClientes(const vector<string> &diretorio);
bool carregarDiretoriosEPastas();
bool carregarPathPedidos(string path, vector<string> &diretorio);
bool carregarPedidos(const vector<string> &diretorio);
/////////////////////////////

/////////////////////////////
// vetores
vector<cliente> listaClientes;
vector<string> diretorioClientes;
vector<string> diretorioPedidos;
//                         ⮮⮮        item     com     sem    valor    ⮯⮯
vector<tuple<cliente, vector<tuple<string, string, string, float>>, float, float>> listaPedidos;
/////////////////////////////

int main()
{
    if (!carregarDiretoriosEPastas())
    {
        cout << "Algo de errado aconteceu ao iniciar o sistema...";
        return 0;
    }

    size_t opcaoMenu;
    size_t menu;

    do
    {
        opcaoMenu = menuPrincipal();

        if (opcaoMenu == 1)
        {
            do
            {
                menu = menuPedidos();

                switch (menu)
                {
                case 1: // fazer pedido
                {
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

                            if (confirma != "s")
                            {
                                cout << endl << "Pressione enter para voltar ao menu...";
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
                                cout << endl << "Pressione enter para voltar ao menu...";
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

                    cout << endl << "Pressione enter para voltar ao menu...";
                    cin.get();
                }
                break;
                case 2: // mostrar pedidos
                {
                    limpatela();
                    if (listaPedidos.empty())
                    {
                        cout << "Nenhum pedido foi feito ainda." << endl;
                    }
                    else
                    {
                        cout << "Pedidos feitos: " << endl << "-----------------------------------------" << endl;

                        mostrarPedidos();

                        cout << "Foram feitos " << listaPedidos.size() << " pedidos" << endl << endl;

                        string opcao;
                        cout << "Para saber mais informacoes sobre um pedido insira o id, para voltar ao menu "
                                "pressione enter"
                             << endl
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
                    cout << endl << "Pressione enter para voltar ao menu...";
                    cin.get();
                }
                break;
                case 3: // reimprimir pedido
                {
                    int id;

                    mostrarPedidos();

                    cout << "Insira o numero do pedido que deseja imprimir: ";
                    cin >> id;
                    cin.ignore();

                    mostrarPedidoDetalhado(id);

                    cout << endl << "Voce deseja imprimir este pedido? (s/n): ";
                    string confirma;
                    getline(cin, confirma);

                    if (confirma == "s")
                    {
                        if (reimprimirPedido(id))
                        {
                            cout << "Imprimindo pedido..." << endl;
                        }
                    }
                    else
                    {
                        cout << "Operacao cancelada..." << endl;
                    }

                    cout << "Pressione enter para voltar ao menu...";
                    cin.get();
                }
                break;
                case 4: // excluir pedidos
                {
                    limpatela();

                    excluirPedido();

                    cout << "Pressione enter para voltar ao menu" << endl;
                    cin.get();
                }
                break;

                case 5: // editar pedido
                {
                    limpatela();

                    if (listaPedidos.empty())
                    {
                        cout << "Nenhum pedido foi feito ainda." << endl;
                    }
                    else
                    {
                        cout << "Pedidos feitos:" << endl;
                        cout << "-----------------------------------------" << endl;
                        mostrarPedidos();
                        cout << "Foram feitos " << listaPedidos.size() << " pedidos" << endl << endl;

                        string opcao;
                        cout << "Digite o ID do pedido para editar ou pressione Enter para voltar: ";
                        getline(cin, opcao);

                        if (!opcao.empty())
                        {
                            try
                            {
                                int id = stoi(opcao);
                                if (id >= 0 && id < listaPedidos.size())
                                {
                                    if (editarPedido(listaPedidos[id], id))
                                    {
                                        cout << "Pedido editado com sucesso" << endl;
                                    }
                                    else
                                    {
                                        cout << "Edicao cancelada" << endl;
                                    }
                                }
                                else
                                {
                                    cout << "ID invalido" << endl;
                                }
                            }
                            catch (exception &e)
                            {
                                cout << "Entrada invalida." << endl;
                            }
                        }
                    }

                    cout << endl << "Pressione Enter para voltar ao menu...";
                    cin.get();
                }
                break;

                    break;
                case 0:
                    break;
                }

            } while (menu != 0);
        }

        if (opcaoMenu == 2)
        {
            do
            {
                menu = menuClientes();
                switch (menu)
                {
                case 1: // cadastrar cliente
                {
                    if (cadastrarCliente())
                    {
                        cout << "Cadastro realizado com sucesso!" << endl;
                    }
                    else
                    {
                        cout << "O cadastro nao foi completado!" << endl;
                    }

                    cout << endl << "Pressione enter para voltar ao menu...";
                    cin.get();
                }
                break;

                case 2: // mostrar clientes
                {
                    limpatela();

                    if (listaClientes.empty())
                    {
                        cout << "Nenhum cliente cadastrado ainda." << endl;
                    }
                    else
                    {
                        cout << "Clientes cadastrados: " << endl << "-----------------------------------------" << endl;

                        mostrarClientesCadastrados();

                        cout << "Foram cadastrados " << listaClientes.size() << " clientes" << endl << endl;

                        string opcao;
                        cout << "Para saber mais informacoes sobre um cliente insira o id, para voltar ao menu "
                                "pressione enter"
                             << endl
                             << "ID: ";
                        getline(cin, opcao);

                        if (!opcao.empty())
                        {
                            try
                            {
                                int id = stoi(opcao);

                                if (id >= 0 && id < listaClientes.size())
                                {
                                    mostrarClientesDetalhado(id);
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

                    cout << "Pressione enter para voltar ao menu" << endl;
                    cin.get();
                }
                break;

                case 3: // excluir clientes
                {
                    limpatela();

                    string clienteDel;

                    mostrarClientesCadastrados();

                    cout << "Insira o nome ou numero do cliente a ser excluido: ";
                    getline(cin, clienteDel);

                    bool cadastrado = false;
                    size_t id;

                    for (id = 0; id < listaClientes.size(); id++)
                    {
                        if (listaClientes[id].mostraTelefone() == clienteDel ||
                            listaClientes[id].mostraNome() == clienteDel)
                        {
                            cadastrado = true;
                            break;
                        }
                    }

                    if (!cadastrado)
                    {
                        cout << "Cadastro nao encontrado" << endl << "Pressione enter para voltar ao menu...";
                        cin.get();
                        break;
                    }

                    mostrarClientesDetalhado(id);

                    string confirma;
                    cout << "Excluir cadastro? (s/n): ";
                    getline(cin, confirma);

                    limpatela();

                    if (confirma != "s")
                    {
                        cout << "Operacao cancelada..." << endl;
                    }
                    else
                    {
                        if (excluirCliente(clienteDel))
                        {
                            cout << "Cliente excluido com sucesso!" << endl;
                        }
                        else
                        {
                            cout << "Algo de errado ocorreu ao tentar excluir o cadastro!" << endl;
                        }
                    }
                    cout << endl << "Pressione enter para voltar ao menu...";
                    cin.get();
                }
                break;

                case 4: // editar cliente
                {
                    limpatela();

                    string clienteEditar;

                    cout << "Número ou nome do cliente para editar: ";
                    getline(cin, clienteEditar);

                    bool cadastrado = false;

                    tuple<string, string, tuple<string, string, string, string>> cadastroAtual;

                    for (size_t i = 0; i < listaClientes.size(); i++)
                    {
                        if (listaClientes[i].mostraTelefone() == clienteEditar ||
                            listaClientes[i].mostraNome() == clienteEditar)
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
                        cout << "Cadastro nao encontrado" << endl << "Pressione enter para voltar ao menu...";
                        cin.get();
                        break;
                    }

                    editarCliente(cadastroAtual);
                }
                break;

                case 0:
                    break;
                }

            } while (menu != 0);
        }

        if (opcaoMenu == 3)
        {
            limpatela();

            cout << "Criando backup..." << endl << endl;

            if (!criarBackup())
            {
                cout << "Algo de errado aconteceu ao tentar cirar o backup..." << endl << endl;
            }
            else
            {
                cout << "Backup criado com sucesso..." << endl << endl;
            }

            cout << "Pressione enter para voltar ao menu...";
            cin.get();
        }

        if (opcaoMenu == 4)
        {
            cout << "Você tem certeza que deseja restaurar o último backup?" << endl
                 << "Isto ira substituir todos os dados atuais" << endl
                 << "Rstaurar? (s/n): ";

            string confirma;
            getline(cin, confirma);

            limpatela();

            if (confirma != "s")
            {
                cout << "Operacao cancelada..." << endl;
            }
            else
            {
                cout << "Restaurando dados..." << endl << endl;
                if (!restaurarBackup())
                {
                    cout << "Algo de errado aconteceu ao tentar restaurar o backup..." << endl << endl;
                }
                else
                {
                    cout << "Dados restaurados com sucesso..." << endl << endl;
                }
            }

            cout << endl << "Pressione enter para voltar ao menu...";
            cin.get();
        }

        if (opcaoMenu == 0)
        {
            return 0;
        }

    } while (!opcaoMenu == 0);

    return 0;
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

        listaClientes.push_back(cliente(tempNome, tempTelefone,
                                        tuple<string, string, string, string>(tempBairro, tempRua, tempNum, tempComp)));
    }

    return true;
}

bool carregarPathPedidos(string path, vector<string> &diretorio)
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
            if (nextItem == string::npos)
                break;
            pos = nextItem + 6;

            size_t barra = linha.find(" | ", pos);
            string item = linha.substr(pos, barra - pos);
            pos = barra + 3;

            // Com:
            if (linha.find("Com:", pos) != pos)
                break;
            pos += 5;
            barra = linha.find(" | ", pos);
            string com = linha.substr(pos, barra - pos);
            pos = barra + 3;

            // Sem:
            if (linha.find("Sem:", pos) != pos)
                break;
            pos += 5;
            barra = linha.find(" | ", pos);
            string sem = linha.substr(pos, barra - pos);
            pos = barra + 3;

            // Valor item:
            if (linha.find("Valor item:", pos) != pos)
                break;
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

bool carregarDiretoriosEPastas()
{
    // esvazia todos vetores
    listaClientes.clear();
    diretorioClientes.clear();
    listaPedidos.clear();
    diretorioPedidos.clear();

    // cria pasta listas
    if (!fs::exists("listas"))
    {
        fs::create_directory("listas");
    }

    // cria pasta clientes
    if (!fs::exists("clientes"))
    {
        fs::create_directory("clientes");
    }

    // cria pasta pedidos
    if (!fs::exists("pedidos"))
    {
        fs::create_directory("pedidos");
    }

    // Carregar clientes
    if (!carregarPathClientes("listas/listaClientes.txt", diretorioClientes))
    {
        fstream("listas/listaClientes.txt", ios::app).close();
    }
    else
    {
        carregarClientes(diretorioClientes);
    }

    // Carregar pedidos
    if (!carregarPathPedidos("listas/listaPedidos.txt", diretorioPedidos))
    {
        fstream("listas/listaPedidos.txt", ios::app).close();
    }
    else
    {
        carregarPedidos(diretorioPedidos);
    }

    return true;
}
