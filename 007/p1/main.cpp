// first try: 279894458 too low
// second try: 26049698234 too low
// third try: 4122618559853
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

void print(vector<int>);
void print(vector<char>);
long long int getResolvedRes(vector<vector<long long int>>, vector<long long int>);
bool isSolvable(vector<long long int>, long long int);

void generateCombinations(vector<string> &ops, const string chars, const int);

int main()
{
    vector<vector<long long int>> equations;
    vector<long long int> res;
    fstream in;
    in.open("../input.txt", ios::in);
    if (in.fail())
        exit(0);
    string line;
    while (getline(in, line))
    {
        istringstream iss(line);
        vector<long long int> v;
        long long int n;
        char c;
        iss >> n >> c;
        res.push_back(n);
        while (iss >> n)
            v.push_back(n);
        equations.push_back(v);
    }
    in.close();
    /*
    for (int i = 0; i < equations.size(); i++)
        print(equations[i]);
    print(res);*/
    long long int ctr = 0;
    ctr = getResolvedRes(equations, res);
    cout << "Ctr= " << ctr << endl;
    return 0;
}

void print(vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}
void print(vector<char> v)
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

long long int getResolvedRes(vector<vector<long long int>> eq, vector<long long int> res)
{
    long long int sum = 0L;
    for (int i = 0; i < eq.size(); i++)
    {
        if (isSolvable(eq[i], res[i]))
            sum += res[i];
    }
    return sum;
}
bool isSolvable(vector<long long int> eq, long long int res)
{
    long long int sum = 0;
    /*
    for(int i=0;i<eq.size();i++){
        //provo somma totale:
        sum+=eq[i];
        //provo moltiplicazione totale:
        molt*=eq[i]; // se c'è uno zero moltiplico anche per quello.
    }
    if(sum==res || molt==res)
        return true;
    */
    vector<string> ops;
    string chars = "+*";
    // ogni volta genere tutte le combinazioni, ma mi sa che è una cazzata perché rallenta.
    // provo unacombinazione di somma e moltiplicazione:
    generateCombinations(ops, chars, eq.size());
    for (int i = 0; i < ops.size(); i++)
    {
        sum = eq[0];
        //        cout << ops[i] << endl;
        for (int j = 0; j < ops[i].length() - 1; j++)
        {
            if (ops[i][j] == '+')
                sum += eq[j + 1];
            else
                sum *= eq[j + 1];
        }
        if (sum == res)
            return true;
    }
    return false;
}
void generateCombinations(vector<string> &ops, const string chars, const int N)
{
    const int PER = pow(chars.size(), N);
    for (int i = 0; i < PER; i++)
    {
        int temp = i;
        string s = "";
        for (int j = 0; j < N; j++)
        {
            s += chars[temp % chars.size()];
            temp /= chars.size();
        }
        ops.push_back(s);
    }
}