#include <iostream>

void init_array(uint* array, size_t array_size);
void print_array(uint* array, size_t array_size);

int main()
{
    // Task 1
    {
        uint* array;
        size_t array_size;

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
