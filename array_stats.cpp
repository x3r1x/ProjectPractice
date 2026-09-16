//
// Created by x3r1x on 9/16/26.
//

#include <iostream>
#include <vector>

static bool IsArraySizeCorrect(int* size)
{
    std::cin >> *size;

    if (*size <= 0)
    {
        std::cout << "The number should be positive!" << std::endl;
        return false;
    }

    return true;
}

static void ReadArray(const int size, std::vector<int>* array)
{
    for (int i = 0; i < size; i++)
    {
        int number = 0;

        std::cin >> number;
        array->push_back(number);
    }
}

static void CountAndPrintStatistics(const std::vector<int>* array)
{
    int sum = 0;
    int min = (*array)[0];
    int max = (*array)[0];

    for (const int number : *array)
    {
        sum += number;

        if (number > max)
        {
            max = number;
        }
        if (number < min)
        {
            min = number;
        }
    }

    const float average = static_cast<float>(sum) / array->size();

    std::cout << "Sum of all elements is " << sum << std::endl;
    std::cout << "Average of all elements is " << average << std::endl;
    std::cout << "Max of all elements is " << max << std::endl;
    std::cout << "Min of all elements is " << min << std::endl;
}

int main()
{
    int N = 0;
    std::vector<int> array;

    if (!IsArraySizeCorrect(&N))
    {
        return 1;
    }

    ReadArray(N, &array);
    CountAndPrintStatistics(&array);

    return 0;
}