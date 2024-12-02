#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int getOcc(vector <int>, int);

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
    int score=0;
    //visualizza
    /*for(int i=0;i< v1.size();i++)
        cout << v1[i] << " " << v2[i]<<endl;
    */
    for(int i=0;i<v1.size();i++)
        score+=(v1[i]*getOcc(v2, v1[i]));
    cout << score;
    return 0;
}
int getOcc(vector <int>v, int n){
    int ctr=0;
    for(int i=0;i<v.size();i++){
        if(v[i]==n)
            ctr++;
    }
    return ctr;
}