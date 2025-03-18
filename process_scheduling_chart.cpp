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
    int time_q;
    cout << "Enter the number of processes : ";
    cin >> n;
    cout << "Enter the time quanta : ";
    cin >> time_q;
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
    vector<vector<int>> process = FCFS_scheduling(processes, n);
    cout << "Time Quanta is : " << time_q << endl;
    print(process, n);
    return 0;
}

vector<vector<int>> FCFS_scheduling(vector<P> &processes, int n)
{
    vector<S> process;
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> startTime(n);
    vector<int> completionTime(n);
    startTime[0] = process[0].first;
    completionTime[0] = startTime[0] + process[0].second.second;
    ans.push_back({1, startTime[0], completionTime[0]});
    for (int i = 1; i < n; i++)
    {
        startTime[i] = max(completionTime[i - 1], process[i].first);
        completionTime[i] = startTime[i] + process[i].second.second;
        ans.push_back({i+1, startTime[i], completionTime[i]});
    }
    return ans;
}

void print(vector<vector<int>> process, int n)
{
    for (int i = 0; i < process.size(); i++)
    {
        cout << "Process Name : P" << process[i][0] << " ";
        cout << "Start Time : " << process[i][1] << " ";
        cout << "Completion Time : " << process[i][2] << endl;
    }
}

vector<vector<int>> SJFS_No_Premption_scheduling(vector<P> &processes, int n)
{
    vector<S> process;
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> startTime(n);
    vector<int> completionTime(n);
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
            ans.push_back({minIndex+1, startTime[minIndex], completionTime[minIndex]});
            currentTime = completionTime[minIndex];
            isCompleted[minIndex] = true;
            totalCompleted++;
        }
    }
    return ans;
}

vector<vector<int>> LJFS_No_Premption_scheduling(vector<P> &processes, int n)
{
    vector<S> process;
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> startTime(n);
    vector<int> completionTime(n);
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
            ans.push_back({maxIndex+1, startTime[maxIndex], completionTime[maxIndex]});
            currentTime = completionTime[maxIndex];
            isCompleted[maxIndex] = true;
            totalCompleted++;
        }
    }
    return ans;
}

vector<vector<int>> SJFS_Premption_scheduling(vector<P> &processes, int n)
{
    vector<int> burstCopy(n);
    vector<vector<int>> ans;
    vector<S> process;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes [i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        burstCopy[i] = process[i].second.second;
        process[i].second.first = i;
    }
    vector<int> startTime(n, -1);
    vector<int> completionTime(n);
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
            if (!ans.empty() && ans.back()[0] == 0 && ans.back()[2] == currentTime) {
                ans.back()[2] = currentTime + 1;
            } else {
                ans.push_back({0, currentTime, currentTime + 1});
            }                                 
            currentTime++;
        }
        else
        {
            if (startTime[minIndex] == -1)
            {
                startTime[minIndex] = currentTime;
            }
            if (!ans.empty() && ans.back()[0] == (minIndex + 1) && ans.back()[2] == currentTime) {
                ans.back()[2] = ans.back()[2] + 1;
            } else {
                ans.push_back({minIndex + 1, currentTime, currentTime + 1});
            }
            currentTime++;
            process[minIndex].second.second--;
            if (process[minIndex].second.second == 0)
            {
                isCompleted[minIndex] = true;
                completionTime[minIndex] = currentTime;
                totalCompleted++;
            }
        }
    }
    return ans;
}

vector<vector<int>> LJFS_Premption_scheduling(vector<P> &processes, int n)
{
    vector<int> burstCopy(n);
    vector<vector<int>> ans;
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
    vector<int> startTime(n, -1);
    vector<int> completionTime(n);
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
            if (!ans.empty() && ans.back()[0] == 0 && ans.back()[2] == currentTime) {
                ans.back()[2] = currentTime + 1;
            } else {
                ans.push_back({0, currentTime, currentTime + 1});
            }
            currentTime++;
        }
        else
        {
            if (startTime[maxIndex] == -1)
            {
                startTime[maxIndex] = currentTime;
            }
            if (!ans.empty() && ans.back()[0] == (maxIndex + 1) && ans.back()[2] == currentTime) {
                ans.back()[2] = ans.back()[2] + 1;
            } else {
                ans.push_back({maxIndex + 1, currentTime, currentTime + 1});
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
    return ans;
}

vector<vector<int>> Priority_No_Premption_scheduling(vector<P> &processes, vector<int> &priority, int n)
{
    vector<T> process;
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, {processes[i].second, priority[i]}}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> startTime(n);
    vector<int> completionTime(n);
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
            ans.push_back({maxIndex+1, startTime[maxIndex], completionTime[maxIndex]});
            isCompleted[maxIndex] = true;
            totalCompleted++;
        }
    }
    return ans;
}

vector<vector<int>> Priority_Premption_scheduling(vector<P> &processes, vector<int> &priority, int n)
{
    vector<T> process;
    vector<vector<int>> ans;
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
    vector<int> startTime(n, -1);
    vector<int> completionTime(n);
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
            if (!ans.empty() && ans.back()[0] == 0 && ans.back()[2] == currentTime) {
                ans.back()[2] = currentTime + 1;
            } else {
                ans.push_back({0, currentTime, currentTime + 1});
            }
            currentTime++;
        }
        else
        {
            if (startTime[maxIndex] == -1)
            {
                startTime[maxIndex] = currentTime;
            }
            if (!ans.empty() && ans.back()[0] == (maxIndex + 1) && ans.back()[2] == currentTime) {
                ans.back()[2] = ans.back()[2] + 1;
            } else {
                ans.push_back({maxIndex + 1, currentTime, currentTime + 1});
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
    return ans;
}

vector<vector<int>> Round_Robin_scheduling(vector<P> &processes, int n, int time_q)
{
    queue<int> q;
    vector<vector<int>> ans;
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
            if (!ans.empty() && ans.back()[0] == (top + 1)) {
                ans.back()[2] = ans.back()[2] + process[top].second.second;
            } else {
                ans.push_back({top + 1, currentTime, currentTime + process[top].second.second});
            }
            currentTime += process[top].second.second;
            completionTime[top] = currentTime;
            process[top].second.second = 0;
            totalCompleted++;
        }
        else
        {
            process[top].second.second -= time_q;
            if (!ans.empty() && ans.back()[0] == (top + 1) && ans.back()[2] == currentTime) {
                ans.back()[2] = ans.back()[2] + time_q;
            } else {
                ans.push_back({top + 1, currentTime, currentTime + time_q});
            }
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
            if (!ans.empty() && ans.back()[0] == 0 && ans.back()[2] == currentTime) {
                ans.back()[2] = currentTime + 1;
            } else {
                ans.push_back({0, currentTime, currentTime + 1});
            }
            currentTime++;
            while (i < n && process[i].first <= currentTime)
            {
                q.push(i);
                i++;
            }
        }
    }
    return ans;
}

vector<vector<int>> HRRN_scheduling(vector<P> &processes, int n)
{
    vector<S> process;
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        process.push_back({processes[i].first, {i, processes[i].second}});
    }
    sort(process.begin(), process.end());
    for (int i = 0; i < n; i++)
    {
        process[i].second.first = i;
    }
    vector<int> startTime(n);
    vector<int> completionTime(n);
    startTime[0] = process[0].first;
    completionTime[0] = startTime[0] + process[0].second.second;
    ans.push_back({1, startTime[0], completionTime[0]});
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
            ans.push_back({maxIndex+1, startTime[maxIndex], completionTime[maxIndex]});
            currentTime = completionTime[maxIndex];
        }
    }
    return ans;
}

PYBIND11_MODULE(process_scheduling_chart, m)
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