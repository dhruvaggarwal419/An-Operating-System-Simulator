#include <bits/stdc++.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;

namespace py = pybind11;

tuple<bool, vector<int>> bankersAlgorithm(int n, int m, 
    const vector<vector<int>>& allocation,
    const vector<vector<int>>& max_matrix,
    const vector<int>& available) {
    vector<vector<int>> need(n, vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            need[i][j] = max_matrix[i][j] - allocation[i][j];
            if (need[i][j] < 0) 
                return {false, {}};
        }
    }

    vector<int> work = available;
    vector<bool> finish(n, false);
    vector<int> safe_sequence;
    int count = 0;

    while(count < n){
        bool found = false;
        for(int i=0; i<n; i++){
            if(!finish[i]){
                bool can_allocate = true;
                for(int j=0; j<m; j++){
                    if(need[i][j] > work[j]){
                        can_allocate = false;
                        break;
                    }
                }
                if(can_allocate){
                    for(int j=0; j<m; j++){
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                    safe_sequence.push_back(i); 
                }
            }
        }
        if(!found) break;
    }
    bool is_safe = (count == n);
    return {is_safe, safe_sequence};
}

PYBIND11_MODULE(deadlock_python, m) {
    m.doc() = "Banker's Algorithm Implementation";
    m.def("check_safety", &bankersAlgorithm, "Check if system is in safe state",
          py::arg("n"), py::arg("m"), py::arg("allocation"), py::arg("max_matrix"), py::arg("available"));
}