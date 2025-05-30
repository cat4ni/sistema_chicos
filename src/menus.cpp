#include "menus.hpp"
#include "miscs.hpp"

int menuPedidos()
{
    limpatela();

    size_t op;

    do
    {
        cout << "------------------------------" << endl
             << "1. Fazer Pedido" << endl
             << "2. Mostrar Pedido" << endl
             << "3. Reimprimir Pedido" << endl
             << "4. Cancelar Pedido" << endl
             << "5. Editar Pedido" << endl
             << "0. Voltar ao Menu Principal" << endl
             << "------------------------------" << endl
             << "Escolha uma opcao: ";
        cin >> op;
        cin.ignore();

        limpatela();

        if (cin.fail() || op > 5 && op != 0)
        {
            cout << "Opcao invalida, tente novamente..." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = static_cast<size_t>(-1);
        }

    } while (op < 0 || op > 5);

    return op;
}

int menuClientes()
{
    limpatela();

    size_t op;

    do
    {
        cout << "------------------------------" << endl
             << "1. Cadastrar Cliente" << endl
             << "2. Mostrar Clientes " << endl
             << "3. Excluir Cliente" << endl
             << "4. Editar Cliente" << endl
             << "0. Voltar ao Menu Principal" << endl
             << "------------------------------" << endl
             << "Escolha uma opcao: ";
        cin >> op;
        cin.ignore();

        limpatela();

        if (cin.fail() || op > 4 && op != 0)
        {
            cout << "Opcao invalida, tente novamente..." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = static_cast<size_t>(-1);
        }

    } while (op < 0 || op > 4);

    return op;
}

int menuPrincipal()
{
    limpatela();

    size_t op;

    do
    {
        cout << "------------------------------" << endl
             << "1. Operacoes Pedidos" << endl
             << "2. Operacoes Clientes" << endl
             << "3. Criar cópia dos dados" << endl
             << "4. Restaurar dados" << endl
             << "0. Fechar Sistema" << endl
             << "------------------------------" << endl
             << "Escolha uma Opcao: ";
        cin >> op;
        cin.ignore();

        limpatela();

        if (cin.fail() || op > 4)
        {
            cout << "Opcao invalida, tente novamente..." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = static_cast<size_t>(-1);
        }

    } while (op < 0 || op > 4);

    return op;
}