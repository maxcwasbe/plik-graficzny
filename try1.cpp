
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>

using namespace std;

vector<int> PixVal;

void Numbercatcher(string PixInfline)
{
    stringstream tmp;
    string temp;
    int found;
    tmp << PixInfline;
    while (!tmp.eof())
    {
        tmp >> temp;
        if (stringstream(temp) >> found)
        {
            PixVal.push_back(found);
        }
    }
}

unsigned long CRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int main()
{
start:
    string line, test, path, answer;
    int type = 0, width = 0, height = 0, uniq = 0, notuniq = 0, max = 0, x = 0;
    fstream file;
    vector<string> PixInf;
    vector<int> PixMax;
    vector<int> temp;


    PixInf.clear();
    PixMax.clear();
    PixVal.clear();
    temp.clear();
    line.clear();
    test.clear();
    path.clear();
    answer.clear();


    cout << "input path to your image (use double \\): ";
    cin >> path;

    file.open(path, ios::in); 
    if (file.good()) 
    {

        while (!file.eof())
        {
            getline(file, line);
            if (line[0] == '#')
                continue;
            else
                PixInf.push_back(line);
        }
        file.close();


        if (PixInf[0][1] == '1' || PixInf[0][1] == '4')
            type = 1;
        if (PixInf[0][1] == '2' || PixInf[0][1] == '5')
            type = 2;
        if (PixInf[0][1] == '3' || PixInf[0][1] == '6')
            type = 3;
        PixInf.erase(PixInf.begin());


        for (int i = 0; i <= PixInf.size() - 1; i++)
        {
            Numbercatcher(PixInf[i]);
        }


        width = PixVal[0];
        PixVal.erase(PixVal.begin());
        height = PixVal[0];
        PixVal.erase(PixVal.begin());


        if (type == 2 || type == 3)
        {
            PixVal.erase(PixVal.begin());
        }


        if (type == 3)
        {
            for (int i = 0; i <= (PixVal.size() / 3) - 1; i++)
            {
                temp.push_back(CRGB(PixVal[x], PixVal[x + 1], PixVal[x + 2]));
                x += 3;
            }
            PixVal = temp;
        }


        temp = PixVal;
        sort(temp.begin(), temp.end());
        temp.erase(unique(temp.begin(), temp.end()), temp.end());
        uniq = temp.size();


        for (int i = 0; i <= temp.size() - 1; i++)
        {
            PixMax.push_back(temp[i]);
            PixMax.push_back(count(PixVal.begin(), PixVal.end(), temp[i]));
        }

        x = 0;
        for (int i = 0; i <= (PixMax.size() / 2) - 1; i++)
        {
            if (PixMax[x + 1] > max)
            {
                max = PixMax[x + 1];
                notuniq = PixMax[x];
            }
            x += 2;
        }


        cout << "width= " << width << " pixels." << endl;
        cout << "height= " << height << " pixels." << endl;
        cout << "the most common color is: " << hex << notuniq << dec << " and it appears " << max << " times." << endl;
        cout << "total number of unique colors is: " << uniq << "." << endl;


        while (true)
        {
            cout << "do you want to continue? (Y/N): ";
            cin >> answer;
            if (answer == "Y")
            {
                goto start;
            }
            if (answer == "N")
            {
                cout << "bye bye";
                return 0;
            }
            cout << "write only Y or N" << endl;
        }
    }
    else
    {
        cout << "invalid path." << endl;
    }

    return 404;
}
