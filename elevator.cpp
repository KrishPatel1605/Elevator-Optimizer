#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class FetchFloorData
{
private:
    vector<vector<int>> floordata;

public:
    FetchFloorData()
    {
        floordata.resize(7);
    }

    void read(string filename)
    {
        ifstream fin(filename);

        string line;

        getline(fin, line); // skips the header in csv file

        while (getline(fin, line))
        {
            stringstream s(line);
            vector<string> row;
            string word;

            while (getline(s, word, ','))
            {
                row.push_back(word);
            }

            int day = stoi(row[1]);
            int floor = stoi(row[3]);

            floordata[day - 1].push_back(floor);
        }
    }

    void print()
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < floordata[i].size(); j++)
            {
                cout << floordata[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<vector<int>> getData()
    {
        return floordata;
    }
};

int main()
{
    FetchFloorData data;
    data.read("data.csv");
    data.print();
    return 0;
}