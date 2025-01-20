#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>
#include <cstring>

using namespace std;

// ---------------------- Problem 1: Resource Allocation (Greedy Algorithm) ----------------------
int maximizeHouseholdsServed(vector<int>& demands, int availableResources) {
    sort(demands.begin(), demands.end());
    int householdsServed = 0;
    for (int demand : demands) {
        if (availableResources >= demand) {
            availableResources -= demand;
            householdsServed++;
        } else {
            break;
        }
    }
    return householdsServed;
}

// Detailed function for resource allocation with logging
void detailedResourceAllocation() {
    vector<int> demands = {5, 10, 15, 20, 25};
    int availableResources = 50;
    cout << "Starting Resource Allocation Process...\n";
    cout << "Available Resources: " << availableResources << "\n";
    cout << "Demands: ";
    for (int d : demands) cout << d << " ";
    cout << "\n";

    int served = maximizeHouseholdsServed(demands, availableResources);
    cout << "Maximum households served: " << served << "\n";
    cout << "Remaining Resources: " << availableResources << "\n";
}

// ---------------------- Problem 2: Crime Prediction (Dynamic Programming) ----------------------
int predictCrimes(vector<int>& crimeRates, int n) {
    vector<int> dp(n + 1, 0);
    dp[1] = crimeRates[0];
    for (int i = 2; i <= n; ++i) {
        dp[i] = max(dp[i - 1], dp[i - 2] + crimeRates[i - 1]);
    }
    return dp[n];
}

// Detailed function for crime prediction with logging
void detailedCrimePrediction() {
    vector<int> crimeRates = {1, 2, 3, 1, 5};
    cout << "Starting Crime Prediction Process...\n";
    cout << "Crime Rates: ";
    for (int rate : crimeRates) cout << rate << " ";
    cout << "\n";

    int prediction = predictCrimes(crimeRates, crimeRates.size());
    cout << "Maximum crime prevention score: " << prediction << "\n";
}

// ---------------------- Problem 3: Path Optimization (Dijkstra's Algorithm) ----------------------
void dijkstra(vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INT_MAX) {
            cout << i << ": INF\n";
        } else {
            cout << i << ": " << dist[i] << "\n";
        }
    }
}

// Detailed function for path optimization with logging
void detailedPathOptimization() {
    vector<vector<pair<int, int>>> graph = {
        {{1, 4}, {2, 1}},
        {{2, 6}},
        {{3, 1}},
        {}
    };
    cout << "Starting Path Optimization Process...\n";
    dijkstra(graph, 0);
}

// ---------------------- Problem 4: Job Matching (Bipartite Graph Matching) ----------------------
bool bpm(vector<vector<int>>& bpGraph, int u, vector<bool>& seen, vector<int>& matchR) {
    for (int v = 0; v < bpGraph[0].size(); v++) {
        if (bpGraph[u][v] && !seen[v]) {
            seen[v] = true;
            if (matchR[v] < 0 || bpm(bpGraph, matchR[v], seen, matchR)) {
                matchR[v] = u;
                return true;
            }
        }
    }
    return false;
}

int maxBPM(vector<vector<int>>& bpGraph) {
    int m = bpGraph.size();
    int n = bpGraph[0].size();
    vector<int> matchR(n, -1);
    int result = 0;
    for (int u = 0; u < m; u++) {
        vector<bool> seen(n, false);
        if (bpm(bpGraph, u, seen, matchR)) {
            result++;
        }
    }
    return result;
}

// Detailed function for job matching with logging
void detailedJobMatching() {
    vector<vector<int>> bpGraph = {
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 1}
    };
    cout << "Starting Job Matching Process...\n";
    int matches = maxBPM(bpGraph);
    cout << "Maximum job matches: " << matches << "\n";
}

// ---------------------- Problem 5: Disease Spread Control (BFS) ----------------------
void bfs(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// Detailed function for disease spread control with logging
void detailedDiseaseControl() {
    vector<vector<int>> diseaseGraph = {
        {1, 2}, {0, 3}, {0, 3}, {1, 2}
    };
    cout << "Starting Disease Spread Control Process...\n";
    cout << "Disease spread starting from node 0: ";
    bfs(diseaseGraph, 0);
    cout << "\n";
}

// ---------------------- Main Function ----------------------
#include <iostream>
using namespace std;

int slumsection() {
    int choice;

    do {
        cout << "\n--- Problem Solver Menu ---\n";
        cout << "1. Resource Allocation (Greedy Algorithm)\n";
        cout << "2. Crime Prediction (Dynamic Programming)\n";
        cout << "3. Path Optimization (Dijkstra's Algorithm)\n";
        cout << "4. Job Matching (Bipartite Graph Matching)\n";
        cout << "5. Disease Spread Control (BFS)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                detailedResourceAllocation();
                break;
            case 2:
                detailedCrimePrediction();
                break;
            case 3:
                detailedPathOptimization();
                break;
            case 4:
                detailedJobMatching();
                break;
            case 5:
                detailedDiseaseControl();
                break;
            case 6:
                cout << "Exiting the program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
//int main()
//{
//    slumsection();
//}

