#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

void init_array(uint* array, size_t array_size);
void print_array(uint* array, size_t array_size);
void init_matrix(int** matrix, size_t const rows, size_t const cols);
void print_matrix(int** matrix, size_t const rows, size_t const cols);

int main()
{
    // Task 1
    {
        uint* array;
        size_t array_size;

        std::cout << "Task 1:\n";
        std::cout << "Enter size of your array:\n-> ";
        std::cin >> array_size;

        if (!array_size) {
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
    }

    return 0;
}

void init_array(uint* array, size_t array_size)
{
    if (array_size > 2 << sizeof(uint))
        array_size = 2 << sizeof(uint);
    for (size_t i = 0; i < array_size; i++)
        array[i] = 1 << i;
}

void print_array(uint* array, size_t array_size)
{
    for (size_t i = 0; i < array_size; i++)
        std::cout << array[i] << " ";
    std::cout << '\n';
}

void init_matrix(int** matrix, size_t const rows, size_t cols)
{
    std::srand(std::time(nullptr));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = std::rand();
        }
    }
}

void print_matrix(int** matrix, size_t const rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << '\n';
    }
}
