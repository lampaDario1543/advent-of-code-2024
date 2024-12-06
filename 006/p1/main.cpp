#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct cell
{
    int row;
    int col;
    int dir;
};

int flen(fstream &, string, int &);
void visualizza(char **, const int, const int);
void getFirstPos(char **, const int, const int, cell &);
void goAhead(char **, const int, const int, cell &);
void goAhead(char **, const int, const int);
int count(char **m, const int ROW, const int COL);

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
    in.close();
    // visualizza(m, row, col);
    goAhead(m, row, col);
    ctr = count(m, row, col);
    ++ctr; // adding one for the last pos.
    cout << ctr << endl;
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

void getFirstPos(char **m, const int ROW, const int COL, cell &c)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (m[i][j] == '^')
            {
                c.row = i;
                c.col = j;
                c.dir = 0;
            }
        }
    }
}

void goAhead(char **m, const int ROW, const int COL)
{
    cell c;
    getFirstPos(m, ROW, COL, c);
    return goAhead(m, ROW, COL, c);
}
void goAhead(char **m, const int ROW, const int COL, cell &c)
{
    // visualizza(m, ROW, COL);
    switch (c.dir)
    {
    case 0:
        if ((c.row - 1) == -1)
            return;
        if (m[c.row - 1][c.col] == '#')
            ++c.dir;
        else
        {
            m[c.row][c.col] = 'X';
            --c.row;
            m[c.row][c.col] = '^';
        }
        break;
    case 1:
        if ((c.col + 1) == COL)
            return;
        if (m[c.row][c.col + 1] == '#')
            ++c.dir;
        else
        {
            m[c.row][c.col] = 'X';
            ++c.col;
            m[c.row][c.col] = '>';
        }
        break;
    case 2:
        if ((c.row + 1) == ROW)
            return;
        if (m[c.row + 1][c.col] == '#')
            ++c.dir;
        else
        {
            m[c.row][c.col] = 'X';
            ++c.row;
            m[c.row][c.col] = 'V';
        }
        break;
    case 3:
        if ((c.col - 1) == -1)
            return;
        if (m[c.row][c.col - 1] == '#')
            c.dir = 0;
        else
        {
            m[c.row][c.col] = 'X';
            --c.col;
            m[c.row][c.col] = '<';
        }
        break;
    default:
        cout << "WTF." << endl;
        break;
    }
    return goAhead(m, ROW, COL, c);
}

int count(char **m, const int ROW, const int COL)
{
    int ctr = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (m[i][j] == 'X')
                ++ctr;
        }
    }
    return ctr;
}