#include <fstream>
#include <string>

class FileHandler {
public:
    // Write a string to a file
    static void writeToFile(const std::string& filename, const std::string& data) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << data;
            file.close();
        } else {
            throw std::runtime_error("Unable to open file for writing: " + filename);
        }
    }

    // Read a string from a file
    static std::string readFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string data((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
            file.close();
            return data;
        } else {
            throw std::runtime_error("Unable to open file for reading: " + filename);
        }
    }
};
