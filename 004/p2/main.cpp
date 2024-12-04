#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int flen(fstream &, string, int &);
bool checkSecDiagonal(char **m,const int R, const int C);

int main()
{
    string filename="../input.txt";
    fstream in(filename, ios::in);
    string line = "";
    int ctr = 0;
    int col=0;
    int row=0;
    row = flen(in, filename,col);
    cout << "Row= " << row << " Col= " << col << endl;
    char **m= new char*[row];
    int i=0;
    for (i = 0; i < row; i++)
        m[i] = new char[col];
    i=0;
    while (getline(in, line))
    {
        for (int j = 0; j < col; j++)
            m[i][j] = line[j];
        ++i;
    }
    for(i=0; i<row-2; i++){
        for(int j=0; j<col-2; j++){
            string s="";
            s+=m[i][j];
            s+=m[i+1][j+1];
            s+=m[i+2][j+2];
            if(s=="SAM" || s=="MAS"){
                if(checkSecDiagonal(m, i, j))
                    ++ctr;
            }
        }
    }
    cout << ctr << endl;
    in.close();
    for(i=0; i<row; i++)
        delete[] m[i];
    delete[] m;
    return 0;
}


int flen(fstream &in, string filename, int &col){
    int row=0;
    string line;
    while (getline(in, line))
        ++row;
    col=line.length();
    in.close();
    in.open(filename, ios::in);
    return row;
}

int howManyInAString(string line)
{
    int ctr=0;
    int xmas = 0;
    int samx = 0;
    bool flag = true;
    while (flag)
    {
        if (line.find("MAS", samx) != string::npos)
        {
            samx = line.find("MAS", samx) + 1;
            flag = true;
            ++ctr;
        }
        else
            flag = false;
        if (line.find("SAM", xmas) != string::npos)
        {
            xmas = line.find("SAM", xmas) + 1;
            flag = true;
            ++ctr;
        }
    }
    return ctr;
}