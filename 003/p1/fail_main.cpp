#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    fstream in("../input.txt", ios::in);
    char c;
    string str = "";
    long long int sum = 0L;
    char ctr = 0;
    bool check = false;
    while (in >> c)
    {
        if (check)
        {
            check = false;
            for (int i = 0; i < str.size(); i++)
            {
                long long int a = 0, b = 0;
                if (str[i] == ','){
                    //cout << "str= " << str << endl;
                    //cout << "(i+1)= " << (i + 1) << "str.size()-i-2= " << str.size() << endl;
                    //cout << str.substr(0, i) << " " << str.substr(i + 1, str.size()) << endl;
                    a=stoi(str.substr(0, i));
                    b=stoi(str.substr(i+1, str.size() - (i + 1)));
                    cout << "a*b= "<< a*b << endl;
                    sum += (a * b);
                    cout <<"a: "<< a << " b:" << b << endl;
                    break;
                }
            }
            str = "";
        }
        if (c == 'm'){
            str.clear();
            str = "m";
        }
        else
            str += c;
        if (str == "mul(")
        {
            str = "";
            while (in >> c && ((c >= '0' && c <= '9') || c == ','))
            {
                str += c;
            }
            if (c == ')')
                check = true;
        }
    }
    in.close();
    cout << sum << endl;
    return 0;
}