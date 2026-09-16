//
// Created by x3r1x on 9/16/26.
//

#include <iostream>
#include <cmath>

int main()
{
    float a = 0.0f;
    float b = 0.0f;
    float c = 0.0f;

    std::cin >> a >> b >> c;

    const float disc = b * b - 4 * a * c;

    if (disc > 0)
    {
        const int x1 = (-b + sqrt(disc)) / (2 * a);
        const int x2 = (-b - sqrt(disc)) / (2 * a);

        std::cout << "The answers are: " << x1 << " and " << x2 << std::endl;
    }
    else if (disc == 0)
    {
        std::cout << "The answer is: " << -b / (2 * a) << std::endl;
    }
    else
    {
        std::cout << "There are no distinctive roots" << std::endl;
    }

    return 0;
}