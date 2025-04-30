#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    fstream fin("data.csv");
    vector<vector<int>> floordata(7);
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
        floordata[day - 1].push_back(floor);
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < floordata[i].size(); j++)
        {
            cout << floordata[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}