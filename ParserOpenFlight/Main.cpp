#include "include/ParserOpenFlight.hpp"


int main(int argc, char* argv[])
{
    std::string filename = "Model_3_ver164.flt";

    if (argc >= 2) {
        filename = argv[1];
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        std::cerr << "Usage: " << argv[0] << " [path_to_file.flt]\n";
        std::cout << "\nPress Enter to exit...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return 1;
    }

    ParserOpenFlight::parse_records(file);

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}