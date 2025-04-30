#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <climits>

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

class ProcessData
{
private:
    vector<vector<int>> floordata, freq;
    int noOfFloors;

public:
    ProcessData(vector<vector<int>> data)
    {
        floordata = data;
        noOfFloors = -1;
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
        cout << noOfFloors << endl;
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j <= noOfFloors; j++)
            {
                cout << freq[i][j] << " ";
            }
            cout << endl;
        }
    }

    void calNoOfFloors()
    {
        int temp;
        for (int i = 0; i < 7; i++)
        {
            noOfFloors = max(noOfFloors, *max_element(floordata[i].begin(), floordata[i].end()));
        }
    }

    void calculateFrequency()
    {
        if (noOfFloors < 0)
        {
            calNoOfFloors();
        }
        freq.resize(7);
        for (int i = 0; i < 7; i++)
        {
            freq[i].resize(noOfFloors + 1, 0);
            int size = floordata[i].size();
            for (int j = 0; j < size; j++)
            {
                freq[i][floordata[i][j]]++;
            }
        }
    }

    vector<vector<int>> getFrequency()
    {
        return freq;
    }
};

class Algorithm
{
private:
    vector<vector<int>> freq, BestFloors;
    int noOfFloors;

public:
    Algorithm(vector<vector<int>> f)
    {
        freq = f;
        noOfFloors = freq[0].size() - 1;
        BestFloors.resize(7);
    }

    void calculateBestFloors(int noOfElevators)
    {
        for (int i = 0; i < 7; i++)
        {
            BestFloors[i].resize(noOfElevators, 0);
        }
        if (noOfElevators == 2)
        {
            for (int d = 0; d < 7; d++)
            {
                int MinTime = INT_MAX;
                for (int i = 0; i <= noOfFloors; i++)
                {
                    for (int j = i + 1; j <= noOfFloors; j++)
                    {
                        int time = 0;
                        for (int m = 0; m <= noOfFloors; m++)
                        {
                            int disti = abs(m - i);
                            int distj = abs(m - j);
                            time += min(disti, distj) * freq[d][m];
                        }
                        if (MinTime > time)
                        {
                            MinTime = time;
                            BestFloors[d][0] = i;
                            BestFloors[d][1] = j;
                        }
                    }
                }
            }
        }
    }

    void print()
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << BestFloors[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<vector<int>> getBestFloors()
    {
        return BestFloors;
    }
};

int main()
{
    FetchFloorData data;
    data.read("data.csv");
    ProcessData processor(data.getData());
    processor.calculateFrequency();
    Algorithm algo(processor.getFrequency());
    algo.calculateBestFloors(2);
    algo.print();
    return 0;
}