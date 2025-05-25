#include "miscs.hpp"

std::string printData()
{
    time_t DataHora = time(0);
    char *data = ctime(&DataHora);

    return std::string(data);
}

void limpatela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool criarBackup()
{
    if (!fs::exists("backups/"))
    {
        fs::create_directory("backups");
        fs::create_directory("backups/clientes");
        fs::create_directory("backups/pedidos");
        fs::create_directory("backups/listas");
    }

    if (fs::exists("clientes") || fs::exists("pedidos") || fs::exists("listas"))
    {
        fs::copy("clientes", "backups/clientes", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        fs::copy("pedidos", "backups/pedidos", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        fs::copy("listas", "backups/listas", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        fs::copy("listas", "backups/listas", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
    }

    return true;
}

bool restaurarBackup()
{
    fs::remove_all("pedidos/");
    fs::remove_all("clientes/");
    fs::remove_all("listas/");

    fs::create_directory("clientes");
    fs::create_directory("pedidos");
    fs::create_directory("listas");

    fs::copy("backups/clientes", "clientes", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
    fs::copy("backups/pedidos", "pedidos", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
    fs::copy("backups/listas", "listas", fs::copy_options::recursive | fs::copy_options::overwrite_existing);
    fs::copy("backups/listas", "listas", fs::copy_options::recursive | fs::copy_options::overwrite_existing);

    return true;
}