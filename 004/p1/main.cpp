#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int howManyInAString(string);
int flen(fstream &, string, int &);
void visualizza(char **, const int, const int);
string convertToString(char *a, const int);
char *getVertical(char **m, const int, const int);
char *getDiagonal(char **m, const int, const int, const int);
char *getDiagonalSec(char **m, const int, const int, const int);
char *getDiagonalSecBelow(char **m, const int, const int, const int);
char *getMainDiagonalBelow(char **m, const int, const int, const int);

int main()
{
    string filename = "../input.txt";
    fstream in(filename, ios::in);
    string line = "";
    int ctr = 0;
    int col = 0;
    int row = 0;
    row = flen(in, filename, col);
    cout << "Row= " << row << " Col= " << col << endl;
    char **m = new char *[row];
    int i = 0;
    for (i = 0; i < row; i++)
        m[i] = new char[col];
    i = 0;
    while (getline(in, line))
    {
        for (int j = 0; j < col; j++)
            m[i][j] = line[j];
        ++i;
    }
    // controllo le orizzontali
    for (i = 0; i < row; i++)
    {
        string line = convertToString(m[i], col);
        ctr += howManyInAString(line);
        line.clear();
    }
    // controllo le verticali
    for (i = 0; i < col; i++)
    {
        string line;
        char *v = getVertical(m, i, row);
        line = convertToString(v, row);
        ctr += howManyInAString(line);
        delete[] v;
    }
    // controllo le diagonali principali
    for (int i = 0; i < col; i++)
    {
        char *v = getDiagonal(m, row, col, i);
        line = convertToString(v, row - i);
        ctr += howManyInAString(line);
        delete[] v;
    }
    for (int i = 1; i < row; i++)
    {
        char *v = getMainDiagonalBelow(m, row, col, i);
        line = convertToString(v, row - i);
        ctr += howManyInAString(line);
        delete[] v;
    }
    // controllo le diagonali secondarie:
    for (int i = 0; i < col; i++)
    {
        char *v = getDiagonalSec(m, row, col, i);
        line = convertToString(v, i + 1);
        ctr += howManyInAString(line);
        delete[] v;
    }
    for (int i = 1; i < row; i++)
    {
        char *v = getDiagonalSecBelow(m, row, col, i);
        line = convertToString(v, row - i);
        ctr += howManyInAString(line);
        delete[] v;
    }
    cout << ctr << endl;
    in.close();
    // visualizza(m, row, col);
    for (i = 0; i < row; i++)
        delete[] m[i];
    delete[] m;
    return 0;
}

int flen(fstream &in, string filename, int &col)
{
    int row = 0;
    string line;
    while (getline(in, line))
        ++row;
    col = line.length();
    in.close();
    in.open(filename, ios::in);
    return row;
}

int howManyInAString(string line)
{
    int ctr = 0;
    int xmas = 0;
    int samx = 0;
    bool flag = true;
    while (flag)
    {
        if (line.find("SAMX", samx) != string::npos)
        {
            samx = line.find("SAMX", samx) + 1;
            flag = true;
            ++ctr;
        }
        else
            flag = false;
        if (line.find("XMAS", xmas) != string::npos)
        {
            xmas = line.find("XMAS", xmas) + 1;
            flag = true;
            ++ctr;
        }
    }
    return ctr;
}

void visualizza(char **m, const int row, const int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cout << m[i][j];
        cout << endl;
    }
    cout << endl;
}

string convertToString(char *a, const int size)
{
    string s = "";
    for (int i = 0; i < size; i++)
        s = s + a[i];
    return s;
}

char *getVertical(char **m, const int COL, const int DIM)
{
    char *v = new char[DIM];
    for (int i = 0; i < DIM; i++)
        v[i] = m[i][COL];
    return v;
}
char *getDiagonal(char **m, const int ROW, const int COL, const int I)
{
    char *v = new char[ROW - I];
    for (int i = 0; i < ROW - I; i++)
        v[i] = m[i][I + i];
    return v;
}

char *getMainDiagonalBelow(char **m, const int ROW, const int COL, const int I)
{
    char *v = new char[ROW - I];
    for (int i = 0; i < ROW - I; i++)
        v[i] = m[I + i][i];
    return v;
}
char *getDiagonalSec(char **m, const int ROW, const int COL, const int I)
{
    char *v = new char[I + 1];
    int k = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if ((i + j) == I)
            {
                v[k] = m[i][j];
                ++k;
            }
        }
    }
    return v;
}
char *getDiagonalSecBelow(char **m, const int ROW, const int COL, const int I)
{
    char *v = new char[ROW - I];
    int k = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if ((i + j) == ROW + I - 1)
            {
                v[k] = m[i][j];
                ++k;
            }
        }
    }
    return v;
}