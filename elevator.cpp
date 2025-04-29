#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <typeinfo>

using namespace std;

int main()
{
    fstream fin("data.csv");
    vector<vector<int>> floore1(7), floore2(7);
    vector<string> row;
    string line, word;

    getline(fin, line);

    while (getline(fin, line))
    {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        int day = stoi(row[1]);
        int floor = stoi(row[3]);
        if (row[0] == "E1")
        {
            floore1[day - 1].push_back(floor);
        }
        else if (row[0] == "E2")
        {
            floore2[day - 1].push_back(floor);
        }
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            cout << floore1[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}