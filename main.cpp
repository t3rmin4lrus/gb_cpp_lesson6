#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

void init_array(uint* const array, size_t const array_size);
void print_array(uint const* const array, size_t array_size);
void init_matrix(int** const matrix, size_t const rows, size_t const cols);
void print_matrix(int const* const* const matrix, size_t const rows, size_t const cols);
void concatenate_files(std::string const& filename_in_1, std::string const& filename_in_2, std::string const& filename_out);
bool is_word_in_file(std::string const& word, std::string const& filename);

int main()
{
    // Task 1
    {
        uint* array;
        size_t array_size;

        std::cout << "Task 1:\n";
        std::cout << "Enter size of your array:\n-> ";
        std::cin >> array_size;

        if (array_size <= 0) {
            std::cerr << "Enter positive, non-null size for your array\n";
            return 1;
        }

        array = new (std::nothrow) uint[array_size];

        if (array != nullptr) {
            init_array(array, array_size);
            print_array(array, array_size);

            delete[] array;
            array = nullptr;
        } else {
            std::cerr << "Couldn't allocate memory for your array\n";
            return 1;
        }
    } // Task 1

    // Task 2
    {
        int** matrix;
        size_t const M = 4;
        size_t const N = 4;

        matrix = new int*[M];
        for (size_t i = 0; i < M; i++)
            matrix[i] = new int[N];

        init_matrix(matrix, M, N);
        std::cout << "\nTask 2:\n";
        print_matrix(matrix, M, N);

        for (size_t i = 0; i < M; i++)
            delete[] matrix[i];
        delete[] matrix;
        matrix = nullptr;
    } // Task 2

    // Task 3
    {
        std::string filename_1;
        std::string filename_2;

        std::cout << "\nTask 3:\nEnter the names of two files to be created:\n-> ";
        std::cin >> filename_1 >> filename_2;

        std::ofstream file_1(filename_1);
        std::ofstream file_2(filename_2);

        std::srand(std::time(nullptr));
        for (size_t i = 0; i < 100; i++) {
            file_1 << i << '\n';
        }
        for (size_t i = 0; i < 120; i++) {
            file_2 << std::rand() << '\n';
        }

        file_1.close();
        file_2.close();

        // Task 4
        {
            std::string filename_cat;

            std::cout << "\nTask 4:\nEnter the name of the file to be created by concatenating two previous files together\n-> ";
            std::cin >> filename_cat;

            concatenate_files(filename_1, filename_2, filename_cat);
        } // Task 4
    } // Task 3

    // Task 5
    {
        std::string word;
        std::string filename;

        std::cout << "\nTask 5:\nEnter the word to search in file\n-> ";
        std::cin >> word;
        std::cout << "\nEnter the name of the file for searching the word\n-> ";
        std::cin >> filename;

        // Tests:
        // filename = "test.txt";
        // word = "Vladislav"; // true
        // word = "float";     // false

        if (is_word_in_file(word, filename)) {
            std::cout << "Found word "
                      << word
                      << " in file "
                      << filename
                      << '\n';
        } else {
            std::cout << "Didn't find word "
                      << word
                      << " in file "
                      << filename
                      << '\n';
        }
    } // Task 5

    return 0;
}

void init_array(uint* const array, size_t array_size)
{
    if (array_size > 2 << sizeof(uint))
        array_size = 2 << sizeof(uint);
    for (size_t i = 0; i < array_size; i++)
        array[i] = 1 << i;
}

void print_array(uint const* const array, size_t const array_size)
{
    for (size_t i = 0; i < array_size; i++)
        std::cout << array[i] << " ";
    std::cout << '\n';
}

void init_matrix(int** const matrix, size_t const rows, size_t const cols)
{
    std::srand(std::time(nullptr));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = std::rand();
        }
    }
}

void print_matrix(int const* const* const matrix, size_t const rows, size_t const cols)
{
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\n';
    }
}

void concatenate_files(std::string const& filename_in_1, std::string const& filename_in_2, std::string const& filename_out)
{
    std::string line_buf;

    std::ifstream file_in_1(filename_in_1);
    std::ifstream file_in_2(filename_in_2);
    std::ofstream file_out(filename_out);

    if (file_in_1.is_open()) {
        while (!file_in_1.eof()) {
            std::getline(file_in_1, line_buf);
            file_out << line_buf << '\n';
        }
        file_in_1.close();
    }

    if (file_in_2.is_open()) {
        while (!file_in_2.eof()) {
            std::getline(file_in_2, line_buf);
            file_out << line_buf << '\n';
        }
        file_in_2.close();
    }
    file_out.close();
}

bool is_word_in_file(std::string const& word, std::string const& filename)
{
    std::string line_buf;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "File does not exist\n";
        return false;
    }
    while (!file.eof()) {
        std::getline(file, line_buf);
        if (line_buf.find(word) != std::string::npos) {
            return true;
        }
    }

    return false;
}
