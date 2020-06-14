#include <boost/filesystem.hpp>
#include <fstream>
#include <regex>

namespace filesystem = boost::filesystem;

int main(int argc, char **argv)
{
	const std::regex register_class("^REGISTER_CLASS\\((.*)\\)");
	const std::regex register_class_as("^REGISTER_CLASS_AS\\(.*, (.*)\\)");

	std::vector<std::string> registered_classes;

	for (int i = 2; i < argc; ++i)
	{
		filesystem::path path(argv[i]);

		for (const auto& entry : filesystem::recursive_directory_iterator(path))
		{
			if (filesystem::is_regular_file(entry.status()) && entry.path().extension() == ".cpp")
			{
				auto file_path = entry.path();

				std::ifstream file_input(file_path.string());

				std::string input_string;

				while (std::getline(file_input, input_string))
				{
					std::smatch regex_match;
					if (std::regex_search(input_string, regex_match, register_class) ||
						std::regex_search(input_string, regex_match, register_class_as))
					{
						registered_classes.push_back(regex_match[1]);
					}
				}
			}
		}
	}

	filesystem::path output_path(argv[1]);
	filesystem::create_directories(output_path);

	std::ofstream file_out(output_path.append("register_reflection.h").string());

	for (auto& registered_class : registered_classes)
	{
		file_out << "extern void RegisterReflection" << registered_class << "();" << std::endl;
	}

	file_out << std::endl;
	file_out << "void RegisterReflection()" << std::endl;
	file_out << "{" << std::endl;

	for (auto& registered_class : registered_classes)
	{
		file_out << "\tRegisterReflection" << registered_class << "();" << std::endl;
	}

	file_out << "}" << std::endl;

    file_out.close();

    return 0;
}
