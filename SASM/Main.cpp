#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include <format>

// Int to hex string
std::string int_to_hstring(int num) {
    return std::format("{:x}", num); 
}
// Int to binary string
std::string int_to_bstring(int num) {
    std::bitset<32> bits(num); // Adjust size (32) as needed for different integer sizes
    std::string binaryString = bits.to_string();

    // Remove leading zeros
    size_t firstOne = binaryString.find('1');
    if (firstOne != std::string::npos) {
        return binaryString.substr(firstOne);
    }
    return "0";
}

int interpret_line(std::string line){

    int result = 0;
    std::istringstream lineStream(line);
    std::string firstWord;

    if (lineStream >> firstWord) {
        
    }
    std::string temp_word;
    if (firstWord == "ADD"){

        lineStream >> temp_word;
        int t = std::stoi(temp_word);
        result += t;

    }
    else if (firstWord == "SUB"){
        
        result += 1;
        result = result << 4;

        lineStream >> temp_word;
        int t = std::stoi(temp_word);
        result += t;

    }
    else if (firstWord == "COPY"){

        result += 1;
        result = result << 6;
        lineStream >> temp_word;
        int t = std::stoi(temp_word);
        t = t << 3;
        result += t;

        lineStream >> temp_word;
        t = std::stoi(temp_word);
        result += t;

    }
    else if (firstWord == "JUMP"){

        result += 2;
        result = result << 6;

        lineStream >> temp_word;
        int t = std::stoi(temp_word);
        result += t;
    }
    else if (firstWord == "LOAD"){
        result += 3;
        result = result << 6;
        lineStream >> temp_word;
        int t = std::stoi(temp_word);
        result += t << 2;

    }
    else if (firstWord == "STORE"){
        result += 3;
        result = result << 6;
        result += 1 << 5;
        lineStream >> temp_word;
        int t = std::stoi(temp_word);
        result += t << 2;
    }
    else {
        throw "empty line";
    }
    return result;
}
int compile(std::string input_filename, std::string output_filename){

    std::ifstream source_file(input_filename);
    if (!source_file.is_open()) {
        std::cerr << "Unable to open file: " << input_filename << std::endl;
        return 1;
    }
    std::ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        std::cerr << "Unable to open file: " << output_filename << std::endl;
        return 1;
    }

    std::string line;

      while (std::getline(source_file, line)) {
        try
        {
            output_file << int_to_hstring(interpret_line(line));
            output_file << " ";
        }
        catch(...)
        {
            std::cerr << "empty line" << '\n';
        }
        

    }
}
int main(){

    compile("test.sasm", "out.hex");
    return 0;
}
