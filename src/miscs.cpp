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