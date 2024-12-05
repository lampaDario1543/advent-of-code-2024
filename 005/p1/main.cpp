#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void print(vector<int>);
bool isLegit(vector<int>, vector<vector<int>>);

int main(int argc, char **argv)
{
    vector<vector<int>> rules;
    vector<vector<int>> updates;
    fstream in, in2;
    in.open(argv[1], ios::in);
    in2.open(argv[2], ios::in);
    int n;
    string line;
    while (getline(in, line))
    {
        istringstream iss(line);
        vector<int> v;
        char c;
        int n2;
        while (iss >> n >> c >> n2)
        {
            v.push_back(n);
            v.push_back(n2);
        }
        rules.push_back(v);
    }
    in.close();
    while (getline(in2, line))
    {
        unsigned int col = 0;
        while ((col = line.find(",")) != string::npos)
            line.replace(col, 1, " ");
        istringstream iss(line);
        vector<int> v;
        while (iss >> n)
            v.push_back(n);
        updates.push_back(v);
    }
    in2.close();
    // visualizza
    /*
    for(int i=0;i< rules.size();i++)
        print(rules[i]);
        */
    /*
   for(int i=0;i< updates.size();i++)
       print(updates[i]);
   */
    int sum = 0;
    for (unsigned int i = 0; i < updates.size(); i++)
    {
        if (isLegit(updates[i], rules))
        {
            int mid = updates[i][updates[i].size() / 2];
            sum += mid;
        }
    }
    cout << "Sum= " << sum;
    return 0;
}
void print(vector<int> v)
{
    for (unsigned int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

bool isLegit(vector<int> update, vector<vector<int>> rules)
{
    for (vector<int> rule : rules)
    {
        int before = rule[0];
        int after = rule[1];
        auto found = find(update.begin(), update.end(), before);
        if (found != update.end())
        {
            int index = std::distance(update.begin(), found);
            for (int i = index; i >= 0; i--)
            {
                if (update[i] == after)
                    return false;
            }
        }
    }
    return true;
}