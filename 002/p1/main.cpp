#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


void print(vector <int> );
bool isSafe(vector <int>);

int main(int argc, char** argv){
    vector<vector<int>> m;
    fstream in;
    in.open(argv[1], ios::in);
    int n;
    char line[255];
    while(in.getline(line, 255)){
        istringstream iss(line);

        vector<int> v;
        while (iss >> n)
            v.push_back(n);
        m.push_back(v);
    }
    in.close();
    //visualizza
    /*
    for(int i=0;i< m.size();i++)
        print(m[i]);
    */
    int ctr=0;
    for(int i=0;i<m.size();i++){
        if(isSafe(m[i]))
            ctr++;
    }
    cout << ctr;
    return 0;
}
void print(vector <int> v){
    for(int i=0;i<v.size();i++)
        cout << v[i] << " ";
    cout << endl;
}
bool isSafe(vector <int>v){
    bool isDesc= false;
    isDesc= v[0]>v[1];
    for(int i=0; i<v.size()-1;i++){
        int diff= isDesc ? v[i]-v[i+1] : v[i+1]-v[i];
        if((diff)<1 || diff>3)
            return false;
    }
    return true;
}