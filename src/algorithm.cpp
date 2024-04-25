#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int> > &processes, vector<vector<int> > &max, vector<int> &available, vector<int> &sequence)
{
    int n = processes.size();
    int m = processes[0].size();

    // Calculate need matrix from input
    vector<vector<int> > need(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j]-processes[i][j]; // calculate need
        }
    }

    vector<bool> finish(n, false);
    bool found = false;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for(int w = 0; w < n; w++)
        {
            if (!finish[w])
            {
                bool canFinish = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[w][j] > available[j])
                    {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish)
                {
                    for (int j = 0; j < m; j++)
                    {
                        available[j] += processes[w][j]; // Release resources when process finishes
                    }
                    finish[w] = true;
                    found = true;
                    sequence[count] = w; 
                    count++;
                }
            }
        }
    }
    if (!found)
    {
        return false; // System is not in safe state
    }

    return true;
}

int main()
{
    string filename = "bankers_input.txt"; // Input file name

    // Read data from file
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    int n, m; // Number of processes and resources
    inputFile >> n >> m;
    vector<vector<int> > processes(n, vector<int>(m, 0)); // Allocation
    vector<int> available(m, 0);

    string line;
    getline(inputFile, line); // Skip the first line (optional header)

    // Read processes and available resources
    for (int i = 0; i < n; i++)
    {
        getline(inputFile, line);
        stringstream ss(line);

        for (int j = 0; j < m; j++)
        { // Read Allocation
            int value;
            ss >> value;
            processes[i][j] = value;
        }
    }

    vector<vector<int> > max(n, vector<int>(m, 0)); // Max,

    getline(inputFile, line);

    for (int i = 0; i < n; i++)
    {
        getline(inputFile, line);
        stringstream ss(line);

        for (int j = 0; j < m; j++)
        { // Read max
            int value;
            ss >> value;
            max[i][j] = value;
        }
    }

    getline(inputFile, line);
    stringstream ss(line);

    // Read available resources
    for (int i = 0; i < m; i++)
    {
        int value;
        ss >> value;
        available[i] = value;
    }

    inputFile.close();

    vector<int> sequence(n, 0);

    if (isSafe(processes, max, available, sequence))
    {
        cout << "\nSystem is in safe state.\nSafe sequence: ";
        for(int i = 0; i < n; i++)
            cout << "Process " << sequence[i] << " ";
    }
    else
    {
        cout << "\nSystem is not in safe state.\n";
    }

    return 0;
}
