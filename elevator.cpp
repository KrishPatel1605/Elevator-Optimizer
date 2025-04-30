#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

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
    vector<vector<int>> floordata,freq;
    int noOfFloors;

public:
    ProcessData(vector<vector<int>> data)
    {
        floordata=data;
        noOfFloors=-1;
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
        cout<<noOfFloors<<endl;
        for(int i=0;i<7;i++)
        {
            for(int j=0;j<=noOfFloors;j++)
            {
                cout<<freq[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void calNoOfFloors()
    {
        int temp;
        for(int i=0;i<7;i++)
        {
            noOfFloors=max(noOfFloors,*max_element(floordata[i].begin(),floordata[i].end()));
        }
    }

    void calculateFrequency()
    {
        if(noOfFloors<0)
        {
            calNoOfFloors();
        }
        freq.resize(7);
        for(int i=0;i<7;i++)
        {
            freq[i].resize(noOfFloors+1,0);
            for(int j=0;j<floordata[i].size();j++)
            {
                freq[i][floordata[i][j]]++;
            }
        }
    }
};

int main()
{
    FetchFloorData data;
    data.read("data.csv");
    ProcessData processor(data.getData());
    processor.calculateFrequency();
    processor.print();
    return 0;
}