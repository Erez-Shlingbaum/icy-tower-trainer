#include <iostream>
#include <ranges>
#include "os_utils.hpp"

int main()
{
	auto p = OS::get_running_processes();

	auto result = std::find_if(p.begin(), p.end(), [](const auto& process)
	{
		return std::string_view{process.szExeFile} == "icytower13.exe";
	});

	if (result == p.end()) { std::cout << "sad"; }
	else { std::cout << result->th32ProcessID; }

	return 0;
}
