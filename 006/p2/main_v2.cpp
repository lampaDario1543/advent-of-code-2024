//algorithm slow af, i hate it
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

struct cell
{
    int row;
    int col;
    int dir;
    //sta roba l'ho fatta ma non me la ricordavo
    bool operator==(const cell &other) const
    {
        return row == other.row && col == other.col;
    }
};

int flen(fstream &, string, int &);
void visualizza(char **, const int, const int);
void getFirstPos(char **, const int, const int, cell &);
bool isInLoop(char **, const int, const int, cell &, const cell, int **ctr);
int getObs(char **, const int, const int);
bool checkCtr(int **ctr, const int ROW, const int COL);
void goAhead(char **m, const int ROW, const int COL, cell &c, vector<cell> &v);
bool isInMatrix(const cell &, const vector<cell> &);
bool checkNext(const cell &, const cell &);

void push_unique(vector<cell> &v, const cell &new_cell);

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
    ctr = getObs(m, row, col);
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
bool isInLoop(char **m, const int ROW, const int COL, cell &c, const cell firstPoint, int **ctr)
{
    ++ctr[c.row][c.col];
    if (checkCtr(ctr, ROW, COL))
    {
        m[c.row][c.col] = '.';
        return true;
    }
    // visualizza(m, ROW, COL);
    switch (c.dir)
    {
    case 0:
        if ((c.row - 1) == -1)
        {
            m[c.row][c.col] = '.';
            return false;
        }
        if (m[c.row - 1][c.col] == '#' || m[c.row - 1][c.col] == 'O')
            ++c.dir;
        else
        {
            m[c.row][c.col] = '.';
            --c.row;
            m[c.row][c.col] = '^';
        }
        break;
    case 1:
        if ((c.col + 1) == COL)
        {
            m[c.row][c.col] = '.';
            return false;
        }
        if (m[c.row][c.col + 1] == '#' || m[c.row][c.col + 1] == 'O')
            ++c.dir;
        else
        {
            m[c.row][c.col] = '.';
            ++c.col;
            m[c.row][c.col] = '>';
        }
        break;
    case 2:
        if ((c.row + 1) == ROW)
        {
            m[c.row][c.col] = '.';
            return false;
        }
        if (m[c.row + 1][c.col] == '#' || m[c.row + 1][c.col] == 'O')
            ++c.dir;
        else
        {
            m[c.row][c.col] = '.';
            ++c.row;
            m[c.row][c.col] = 'V';
        }
        break;
    case 3:
        if ((c.col - 1) == -1)
        {
            m[c.row][c.col] = '.';
            return false;
        }
        if (m[c.row][c.col - 1] == '#' || m[c.row][c.col - 1] == 'O')
            c.dir = 0;
        else
        {
            m[c.row][c.col] = '.';
            --c.col;
            m[c.row][c.col] = '<';
        }
        break;
    default:
        cout << "WTF." << endl;
        break;
    }
    return isInLoop(m, ROW, COL, c, firstPoint, ctr);
}

int getObs(char **m, const int ROW, const int COL)
{
    int count = 0;
    cell startingPoint;
    getFirstPos(m, ROW, COL, startingPoint);
    cell c = startingPoint;

    vector<cell> allPos;
    goAhead(m, ROW, COL, c, allPos);
    cout << "Il percorso e' lungo: " << allPos.size() << endl;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cout << "Checking: " << i << " " << j << endl;
            cell nowPos = {i, j, 0};
            if (m[i][j] != '#' && !(i == startingPoint.row && j == startingPoint.col) && isInMatrix(nowPos, allPos))
            {
                c = startingPoint;
                m[i][j] = 'O';
                int **ctr = new int *[ROW];
                for (int k = 0; k < ROW; k++)
                {
                    ctr[k] = new int[COL];
                    for (int l = 0; l < COL; l++)
                        ctr[k][l] = 0;
                }
                if (isInLoop(m, ROW, COL, c, startingPoint, ctr))
                    ++count;
                for (int k = 0; k < ROW; k++)
                    delete[] ctr[k];
                delete[] ctr;
                m[i][j] = '.';
            }
        }
    }
    return count;
}
bool checkCtr(int **ctr, const int ROW, const int COL)
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (ctr[i][j] > 10) // 10 è come se fosse la tolleranza, più è alto più è attendibile, ma così è più lento.
                return true;
        }
    }
    return false;
}

void goAhead(char **m, const int ROW, const int COL, cell &c, vector<cell> &v)
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
            push_unique(v, c);
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
            push_unique(v, c);
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
            push_unique(v, c);
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
            v.push_back(c);
            m[c.row][c.col] = 'X';
            --c.col;
            m[c.row][c.col] = '<';
        }
        break;
    default:
        cout << "WTF." << endl;
        break;
    }
    return goAhead(m, ROW, COL, c, v);
}
bool isInMatrix(const cell &c, const vector<cell> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (c == v[i] || checkNext(c, v[i]))
            return true;
    }
    return false;
}
bool checkNext(const cell &c, const cell &v)
{
    switch (c.dir)
    {
    case 0:
        if (c.row - 1 == v.row && c.col == v.col)
            return true;
        break;
    case 1:
        if (c.row == v.row && c.col + 1 == v.col)
            return true;
        break;
    case 2:
        if (c.row + 1 == v.row && c.col == v.col)
            return true;
        break;
    case 3:
        if (c.row == v.row && c.col - 1 == v.col)
            return true;
        break;
    }
    return false;
}
void push_unique(vector<cell> &v, const cell &new_cell)
{
    if (find(v.begin(), v.end(), new_cell) == v.end())
    {
        v.push_back(new_cell);
    }
}