#include <iostream>
#include <ranges>
#include "os_utils.hpp"

int main()
{
    std::vector<PROCESSENTRY32> process_list = OS::get_running_processes();

    auto result = std::find_if(process_list.begin(), process_list.end(), [](const auto &process) {
        return std::string_view{process.szExeFile} == "icytower13.exe";
    });

    if (result == process_list.end())
    {
        std::cout << "Icytower not found" << std::endl;
    }
    else
    {
        std::cout << result->th32ProcessID << std::endl;
    }

    return 0;
}
