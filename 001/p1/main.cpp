#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

void sort(vector <int> &v1);

int main(){
    vector<int> v1;
    vector<int> v2;
    fstream in;
    in.open("input.txt", ios::in);
    int n,n2;
    while(in >> n >> n2){
        v1.push_back(n);
        v2.push_back(n2);
    }
    in.close();
    sort(v1);
    sort(v2);
    int s=0;
    /*
    //visualizza
    for(int i=0;i< v1.size();i++)
        cout << v1[i] << " " << v2[i]<<endl;
    */
    for(int i=v1.size()-1;i>=0;i--){
        s+=abs(v1[i]-v2[i]);
        v1.pop_back();
        v2.pop_back();
    }
    cout << s;
    return 0;
}

void sort(vector <int> &v){
    for(int i=0;i< v.size()-1;i++){
        for(int j=i+1; j<v.size();j++){
            if(v[i]>v[j]){
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}