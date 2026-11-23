#include <iostream>

using namespace std;

const int maxMoisture = 100;
const int openLimit = 60;
const int pulseLimit = 85;
const int pulseStep = 20;
const int pulseWater = 5;
const int maxCount = 8;

const int exitCode = 0;
const int statusCode = 1;
const int openCode = 2;
const int closeCode = 3;
const int pulseCode = 4;

bool allowed(bool opened, int moisture, int limit)
{
    return !opened && moisture < limit;
}

int addMoisture(int moisture)
{
    moisture += pulseStep;
    if (moisture > maxMoisture)
    {
        return maxMoisture;
    }
    return moisture;
}

void showStatus(bool opened, int moisture, int water)
{
    cout << "Valve open: " << opened << "\n";
    cout << "Moisture: " << moisture << "%\n";
    cout << "Water used: " << water << " L\n";
}

int main()
{
    int moisture = 0;
    bool opened = false;
    int count = 0;
    int water = 0;

    cout << "Moisture: ";
    if (!(cin >> moisture))
    {
        cout << "Input error\n";
        return 1;
    }
    if (moisture < 0 || moisture > maxMoisture)
    {
        cout << "Invalid moisture\n";
        return 2;
    }

    cout << boolalpha;
    while (count < maxCount)
    {
        int code = 0;
        cout << "Action 0/1/2/3/4: ";
        if (!(cin >> code))
        {
            cout << "Input error\n";
            return 1;
        }

        if (code == exitCode)
        {
            break;
        }

        switch (code)
        {
        case statusCode:
            cout << "Status\n";
            break;

        case openCode:
            if (!allowed(opened, moisture, openLimit))
            {
                cout << "Open denied\n";
                continue;
            }
            opened = true;
            cout << "Valve opened\n";
            break;

        case closeCode:
            opened = false;
            cout << "Valve closed\n";
            break;

        case pulseCode:
            if (!allowed(opened, moisture, pulseLimit))
            {
                cout << "Pulse denied\n";
                continue;
            }
            moisture = addMoisture(moisture);
            water += pulseWater;
            cout << "Pulse completed\n";
            break;

        default:
            cout << "Unknown action\n";
            continue;
        }

        ++count;
        showStatus(opened, moisture, water);
    }

    cout << "Operations: " << count << "\n";
    cout << "Total water: " << water << " L\n";
    return 0;
}
