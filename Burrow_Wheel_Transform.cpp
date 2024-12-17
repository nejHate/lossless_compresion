#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>


std::string ReadFile(char* filename){

    std::ifstream file;
    file.open(filename, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open()){
        std::cout << "Cant open selected file" << std::endl;
        return std::string{};
    }

    std::streampos size = file.tellg(); // Get the file size
    if (size <= 0) { // Handle empty or invalid files
        std::cout << "Error: File size is 0 or invalid." << std::endl;
        file.close();
        return std::string{};
    }

    //return_string = new char[size];
    std::string return_string;
    return_string.resize(size);
    file.seekg (0, std::ios::beg);
    file.read(&return_string[0], size);
    file.close();
    return return_string;
}

void SaveFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename, std::ios::out); // Open file in write mode
    if (!file) {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        return; // Return false if file opening fails
    }

    file << content; // Write the content to the file
    file.close();    // Close the file
}

std::vector<u_int64_t> SortString(const std::string& str) {
    std::vector<u_int64_t> indices(str.size());
    
    // Initialize indices with the position of each character
    for (u_int64_t i = 0; i < str.size(); ++i) {
        indices[i] = i;
    }

    // Sort indices based on substrings starting at each index
    std::stable_sort(indices.begin(), indices.end(), [&str](u_int64_t a, u_int64_t b) {
        // Compare substrings starting at index 'a' and 'b'
        size_t len = str.size();
        for (size_t i = 0; i < len; ++i) {
            char char_a = str[(a + i) % len];
            char char_b = str[(b + i) % len];
            if (char_a != char_b) {
                return char_a < char_b;
            }
        }
        return false; // Equal strings
    });

    return indices;
}

std::string BurrowWheelTransform(std::string& input_string){
    std::vector<u_int64_t> sorted_indexes = SortString(input_string);


    std::string output_string;
    for (u_int64_t i = 0; i < input_string.size(); i++) {
        if(sorted_indexes[i] == 0){
            std::cout << "the string start in this location: " << i << std::endl;
        }
        // Add the character that precedes the start of this rotation
        output_string += input_string[(sorted_indexes[i] + input_string.size() - 1) % input_string.size()];
    }
    SaveFile(std::string {"Burrow-Wheel-Transform.txt"}, output_string);
    return output_string;
}

std::string ReverseBurrowWheelTransform(std::string input_string, int start_index){

    std::string sorted_string = input_string;
    std::sort(sorted_string.begin(), sorted_string.end());
    std::vector<uint64_t> letter_ptr;
    int64_t unsorted_string_ptr = 0;
    char c = sorted_string[0];
    for (int i = 0; i < sorted_string.size(); i++){

        if(c != sorted_string[i]){
            unsorted_string_ptr = 0;
            c = sorted_string[i];
        }
        while(c != input_string[unsorted_string_ptr]){

            unsorted_string_ptr++;
        }
        letter_ptr.push_back(unsorted_string_ptr);
        unsorted_string_ptr++;
    }

    std::string output_string;
    for(int i = 0; i < input_string.size(); i++){
        start_index = letter_ptr[start_index];
        output_string.push_back(input_string[start_index]);
    }
    return output_string;
}

void RunLengthEncoding(std::string input_string){
    (void) input_string;
    return;
}

int main(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    char input_file_name[] = "original.txt\0";

    std::string input_string = ReadFile(input_file_name);
    std::cout << "File is " << input_string.size() << " bytes lenght" << std::endl;
    //input_string = "abcdefg";
    std::string output_string = BurrowWheelTransform(input_string);
    std::cout << "output string 1: " << output_string;
    std::cout << std::endl << "# # # # # # # # # #" << std::endl;
    input_string = ReverseBurrowWheelTransform(output_string, 2422);
    std::cout << "output string 2: " << input_string << std::endl;
    //input_string = BurrowWheelTransform(output_string);
    //std::cout << input_string << std::endl;

    std::cout << "Task completed" << std::endl;
    
}
