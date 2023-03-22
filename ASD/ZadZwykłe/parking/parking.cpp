#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int id;
    bool CarParked = false;
    bool visited = false;

    vector<int> neighbours;
};

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // liczba miejsc parkingowych
    int m; // liczba połączeń między miejscami

    cin >> n >> m;

    Node node[n + 1];

    for ( int i = 1; i <= n; i++ ) {
        node[i].id = i;

        int k;
        cin >> k;
        if ( k ) {
            node[i].CarParked = true;
        }
    }

    for ( int i = 0; i < m; i++ ) {
        int a, b;
        cin >> a >> b;
        node[a].neighbours.push_back(b);
        node[b].neighbours.push_back(a);
    }

    queue<int> q;
    priority_queue<int, vector<int>, greater<int>> canLeave; // id aut zaparkowanych, które mogą wyjechać z parkingu

    q.push(1);

    while ( !q.empty() ) {
        Node * currNode = &node[q.front()];
        q.pop();

        if ( currNode->CarParked ) {
            canLeave.push(currNode->id);
            continue;
        }

        for ( int k : currNode->neighbours ) {
            if ( !node[k].visited ) {
                q.push(k);
                node[k].visited = true;
            }
        }
    }

    while ( !canLeave.empty() ) {
        cout << canLeave.top() << '\n';
        canLeave.pop();
    }

    return 0;
}
