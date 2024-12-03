#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    fstream in("../input.txt", ios::in);
    char c;
    regex toFind(R"((mul\(\d+,\d+\))|(do\(\))|(don't\(\)))");
    smatch match;
    string line = "";
    long int sum = 0L;
    bool toDo = true;
    while (getline(in, line))
    {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), toFind);
        auto words_end = std::sregex_iterator();

        for (sregex_iterator i = words_begin; i != words_end; ++i)
        {
            smatch match = *i;
            string found = match.str();
            if (found == "do()")
            {
                toDo = true;
                continue;
            }
            else if (found == "don't()")
            {
                toDo = false;
                continue;
            }
            else if (toDo)
            {
                found = match.str().substr(4, match.str().size() - 5);
                for (int i = 0; i < found.size(); i++)
                {
                    long long int a = 0, b = 0;
                    if (found[i] == ',')
                    {
                        a = stoi(found.substr(0, i));
                        b = stoi(found.substr(i + 1, found.size() - (i + 1)));
                        sum += (a * b);
                        break;
                    }
                }
            }
        }
    }
    in.close();
    cout << sum << endl;
    return 0;
}