#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string str; int kol; char tmp;
    ifstream input("input.txt");
    ofstream output("output.txt");
    while (!input.eof())
    {
        getline(input, str);
        char tmp = str[0]; kol = 1;
        for (int i = 1; i < size(str); ++i)
        {
            if (tmp != str[i])
            {
                if (kol > 1) output << to_string(kol);
                output << str[i - 1];
                tmp = str[i]; kol = 0;
            }
            if (tmp == str[i])
            {
                kol++;
            }
        }
        if (kol > 1) output << to_string(kol);
        output << str[size(str) - 1];
    }
    input.close();
    output.close();
}