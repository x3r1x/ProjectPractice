//
// Created by x3r1x on 9/16/26.
//

#include <iostream>

using namespace std;

static void ReadNumbers(int* sum, int* count)
{
    int number;

    while (cin >> number && number != 0)
    {
        *sum += number;
        *count += 1;
    }
}

static void PrintPattern(const int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "*";
    }

    cout << endl;
}

int main()
{
    int sum = 0;
    int count = 0;

    ReadNumbers(&sum, &count);

    if (count == 0)
    {
        cout << "No numbers given!" << endl;
        return 1;
    }

    PrintPattern(count);

    return 0;
}