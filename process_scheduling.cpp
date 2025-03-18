#include <iostream>
#include <bits/stdc++.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;
namespace py = pybind11;

typedef pair<int, int> P;
typedef pair<int, pair<int, int>> S;
typedef pair<int, pair<int, pair<int, int>>> T;

vector<vector<int>> FCFS_scheduling(vector<P> &, int);
void print(vector<vector<int>>, int);
vector<vector<int>> SJFS_No_Premption_scheduling(vector<P> &, int);
vector<vector<int>> LJFS_No_Premption_scheduling(vector<P> &, int);
vector<vector<int>> SJFS_Premption_scheduling(vector<P> &, int);
vector<vector<int>> LJFS_Premption_scheduling(vector<P> &, int);
vector<vector<int>> Priority_No_Premption_scheduling(vector<P> &, vector<int> &, int);
vector<vector<int>> Priority_Premption_scheduling(vector<P> &, vector<int> &, int);
vector<vector<int>> Round_Robin_scheduling(vector<P> &, int, int);
vector<vector<int>> HRRN_scheduling(vector<P> &, int);

int main()
{
    int n;
    // int time_q;
    cout << "Enter the number of processes : ";
    cin >> n;
    // cout << "Enter the time quanta : ";
    // cin >> time_q;
    vector<P> processes(n);
    // vector<int> priority(n);
    // cout << "Enter " << n << " arrival time, burst time and priority time of the processes" << endl;
    cout << "Enter " << n << " arrival time and burst time of the processes" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i].first;
        cin >> processes[i].second;
        // cin >> priority[i];
    }
    vector<vector<int>> process = SJFS_Premption_scheduling(processes, n);
    // cout << "Time Quanta is : " << time_q << endl;
    print(process, n);
    return 0;
}

vector<vector<int>> FCFS_scheduling(vector<P> &processes, int n)
{
    vector<S> process;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    startTime[0] = process[0].first;
    completionTime[0] = startTime[0] + process[0].second.second;
    for (int i = 1; i < n; i++)
    {
        startTime[i] = max(completionTime[i - 1], process[i].first);
        completionTime[i] = startTime[i] + process[i].second.second;
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - process[i].second.second;
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(process[i].second.second);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        ans.push_back(temp);
    }
    return ans;
}

void print(vector<vector<int>> process, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Process Name : P" << process[i][0] << endl;
        cout << "Arrival Time : " << process[i][1] << endl;
        cout << "Burst Time : " << process[i][2] << endl;
        cout << "Response Time : " << process[i][3] << endl;
        cout << "Turn Around Time : " << process[i][4] << endl;
        cout << "Waiting Time : " << process[i][5] << endl;
        // cout << "Priority : " << process[i][6] << endl;
    }
}

vector<vector<int>> SJFS_No_Premption_scheduling(vector<P> &processes, int n)
{
    vector<S> process;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    int currentTime = 0;
    int totalCompleted = 0;
    vector<bool> isCompleted(n, false);
    isCompleted[0] = false;
    while (totalCompleted < n)
    {
        int minProcess = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && process[i].first <= currentTime && minProcess > process[i].second.second)
            {
                minProcess = process[i].second.second;
                minIndex = i;
            }
        }
        if (minIndex == -1)
        {
            currentTime++;
        }
        else
        {
            startTime[minIndex] = currentTime;
            completionTime[minIndex] = currentTime + process[minIndex].second.second;
            currentTime = completionTime[minIndex];
            isCompleted[minIndex] = true;
            totalCompleted++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - process[i].second.second;
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(process[i].second.second);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        ans.push_back(temp);
    }
    return ans;
}

vector<vector<int>> LJFS_No_Premption_scheduling(vector<P> &processes, int n)
{
    vector<S> process;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    int currentTime = 0;
    int totalCompleted = 0;
    vector<bool> isCompleted(n, false);
    isCompleted[0] = false;
    while (totalCompleted < n)
    {
        int maxProcess = INT_MIN;
        int maxIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && process[i].first <= currentTime && maxProcess < process[i].second.second)
            {
                maxProcess = process[i].second.second;
                maxIndex = i;
            }
        }
        if (maxIndex == -1)
        {
            currentTime++;
        }
        else
        {
            startTime[maxIndex] = currentTime;
            completionTime[maxIndex] = currentTime + process[maxIndex].second.second;
            currentTime = completionTime[maxIndex];
            isCompleted[maxIndex] = true;
            totalCompleted++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - process[i].second.second;
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(process[i].second.second);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        ans.push_back(temp);
    }
    return ans;
}

vector<vector<int>> SJFS_Premption_scheduling(vector<P> &processes, int n)
{
    vector<int> burstCopy(n);
    vector<S> process;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        burstCopy[i] = process[i].second.second;
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n, -1);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    int currentTime = 0;
    int totalCompleted = 0;
    vector<bool> isCompleted(n, false);
    isCompleted[0] = false;
    while (totalCompleted < n)
    {
        int minProcess = INT_MAX;
        int minIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && process[i].first <= currentTime && minProcess > process[i].second.second)
            {
                minProcess = process[i].second.second;
                minIndex = i;
            }
        }
        if (minIndex == -1)
        {
            currentTime++;
        }
        else
        {
            if (startTime[minIndex] == -1)
            {
                startTime[minIndex] = currentTime;
            }
            currentTime++;
            process[minIndex].second.second--;
            if (process[minIndex].second.second == 0)
            {
                isCompleted[minIndex] = true;
                completionTime[minIndex] = currentTime + process[minIndex].second.second;
                totalCompleted++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - burstCopy[i];
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(burstCopy[i]);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        ans.push_back(temp);
    }
    return ans;
}

vector<vector<int>> LJFS_Premption_scheduling(vector<P> &processes, int n)
{
    vector<int> burstCopy(n);
    vector<S> process;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        burstCopy[i] = process[i].second.second;
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n, -1);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    int currentTime = 0;
    int totalCompleted = 0;
    vector<bool> isCompleted(n, false);
    isCompleted[0] = false;
    while (totalCompleted < n)
    {
        int maxProcess = INT_MIN;
        int maxIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && process[i].first <= currentTime && maxProcess < process[i].second.second)
            {
                maxProcess = process[i].second.second;
                maxIndex = i;
            }
        }
        if (maxIndex == -1)
        {
            currentTime++;
        }
        else
        {
            if (startTime[maxIndex] == -1)
            {
                startTime[maxIndex] = currentTime;
            }
            currentTime++;
            process[maxIndex].second.second--;
            if (process[maxIndex].second.second == 0)
            {
                isCompleted[maxIndex] = true;
                completionTime[maxIndex] = currentTime + process[maxIndex].second.second;
                totalCompleted++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - burstCopy[i];
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(burstCopy[i]);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        ans.push_back(temp);
    }
    return ans;
}

vector<vector<int>> Priority_No_Premption_scheduling(vector<P> &processes, vector<int> &priority, int n)
{
    vector<T> process;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, {processes[i].second, priority[i]}}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    int currentTime = 0;
    int totalCompleted = 0;
    vector<bool> isCompleted(n, false);
    isCompleted[0] = false;
    while (totalCompleted < n)
    {
        int maxPriority = INT_MIN;
        int maxIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && process[i].first <= currentTime && maxPriority < process[i].second.second.second)
            {
                maxPriority = process[i].second.second.second;
                maxIndex = i;
            }
        }
        if (maxIndex == -1)
        {
            currentTime++;
        }
        else
        {
            startTime[maxIndex] = currentTime;
            completionTime[maxIndex] = currentTime + process[maxIndex].second.second.first;
            currentTime = completionTime[maxIndex];
            isCompleted[maxIndex] = true;
            totalCompleted++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - process[i].second.second.first;
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(process[i].second.second.first);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        temp.push_back(process[i].second.second.second);
        ans.push_back(temp);
    }
    return ans;
}

vector<vector<int>> Priority_Premption_scheduling(vector<P> &processes, vector<int> &priority, int n)
{
    vector<T> process;
    vector<int> burstCopy(n);
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, {processes[i].second, priority[i]}}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        burstCopy[i] = process[i].second.second.first;
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n, -1);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    int currentTime = 0;
    int totalCompleted = 0;
    vector<bool> isCompleted(n, false);
    isCompleted[0] = false;
    while (totalCompleted < n)
    {
        int maxPriority = INT_MIN;
        int maxIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && process[i].first <= currentTime && maxPriority < process[i].second.second.second)
            {
                maxPriority = process[i].second.second.second;
                maxIndex = i;
            }
        }
        if (maxIndex == -1)
        {
            currentTime++;
        }
        else
        {
            if (startTime[maxIndex] == -1)
            {
                startTime[maxIndex] = currentTime;
            }
            currentTime++;
            process[maxIndex].second.second.first--;
            if (process[maxIndex].second.second.first == 0)
            {
                isCompleted[maxIndex] = true;
                completionTime[maxIndex] = currentTime + process[maxIndex].second.second.first;
                totalCompleted++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - burstCopy[i];
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(burstCopy[i]);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        temp.push_back(process[i].second.second.second);
        ans.push_back(temp);
    }
    return ans;
}

vector<vector<int>> Round_Robin_scheduling(vector<P> &processes, int n, int time_q)
{
    queue<int> q;
    vector<S> process;
    vector<int> burstCopy(n);
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        burstCopy[i] = process[i].second.second;
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n, -1);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    int currentTime = process[0].first, i = 0;
    int totalCompleted = 0;
    while (i < n && process[i].first <= currentTime)
    {
        q.push(i);
        i++;
    }
    while (!q.empty())
    {
        int top = q.front();
        q.pop();
        if (startTime[top] == -1)
        {
            startTime[top] = currentTime;
        }
        if (process[top].second.second <= time_q)
        {
            currentTime += process[top].second.second;
            completionTime[top] = currentTime;
            process[top].second.second = 0;
            totalCompleted++;
        }
        else
        {
            process[top].second.second -= time_q;
            currentTime += time_q;
        }
        while (i < n && process[i].first <= currentTime)
        {
            q.push(i);
            i++;
        }
        if (process[top].second.second != 0)
        {
            q.push(top);
        }
        while(q.empty() && totalCompleted < n) {
            currentTime++;
            while (i < n && process[i].first <= currentTime)
            {
                q.push(i);
                i++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - burstCopy[i];
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(burstCopy[i]);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        ans.push_back(temp);
    }
    return ans;
}

vector<vector<int>> HRRN_scheduling(vector<P> &processes, int n)
{
    vector<S> process;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> turnAroundTime(n);
    vector<int> responseTime(n);
    vector<int> startTime(n);
    vector<int> completionTime(n);
    vector<int> waitingTime(n);
    startTime[0] = process[0].first;
    completionTime[0] = startTime[0] + process[0].second.second;
    int totalCompleted = 1;
    vector<bool> isCompleted(n, false);
    isCompleted[0] = true;
    int currentTime = completionTime[0];
    while (totalCompleted < n)
    {
        int maxIndex = -1;
        float maxHighRespRatio = -1.0;
        float currentHighRespRatio = 0;
        for (int i = 0; i < n; i++)
        {
            if (!isCompleted[i] && currentTime >= process[i].first)
            {
                currentHighRespRatio = (((currentTime - process[i].first) + process[i].second.second) * (1.0)) / process[i].second.second;
                if (maxHighRespRatio < currentHighRespRatio)
                {
                    maxIndex = i;
                    maxHighRespRatio = currentHighRespRatio;
                }
            }
        }
        if (maxIndex == -1)
        {
            currentTime++;
        }
        else
        {
            isCompleted[maxIndex] = true;
            totalCompleted++;
            startTime[maxIndex] = currentTime;
            completionTime[maxIndex] = startTime[maxIndex] + process[maxIndex].second.second;
            currentTime = completionTime[maxIndex];
        }
    }
    for (int i = 0; i < n; i++)
    {
        responseTime[i] = startTime[i] - process[i].first;
        turnAroundTime[i] = completionTime[i] - process[i].first;
        waitingTime[i] = turnAroundTime[i] - process[i].second.second;
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        vector<int> temp;
        temp.push_back(process[i].second.first);
        temp.push_back(process[i].first);
        temp.push_back(process[i].second.second);
        temp.push_back(responseTime[i]);
        temp.push_back(turnAroundTime[i]);
        temp.push_back(waitingTime[i]);
        ans.push_back(temp);
    }
    return ans;
}

PYBIND11_MODULE(process_scheduling, m)
{
    m.def("FCFS_scheduling", &FCFS_scheduling);
    m.def("SJFS_No_Premption_scheduling", &LJFS_No_Premption_scheduling);
    m.def("LJFS_No_Premption_scheduling", &LJFS_No_Premption_scheduling);
    m.def("SJFS_Premption_scheduling", &LJFS_Premption_scheduling);
    m.def("LJFS_Premption_scheduling", &LJFS_Premption_scheduling);
    m.def("Priority_No_Premption_scheduling", &Priority_No_Premption_scheduling);
    m.def("Priority_Premption_scheduling", &Priority_Premption_scheduling);
    m.def("Round_Robin_scheduling", &Round_Robin_scheduling);
    m.def("HRRN_scheduling", &HRRN_scheduling);
}