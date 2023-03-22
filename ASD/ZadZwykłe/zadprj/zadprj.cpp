#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <functional>

using namespace std;

struct project {
    int id; // nr projektu
    int programmers; // liczba programistów potrzebna do wykonania zadania
    int countProjectsPointing = 0; // zlicza projekty, które od tego projektu zależą

    vector<int> enables; // Jakie projekty zależą są od nas zależne
};

// debug
void printProjectsInfo( project projects[], int n ) {
    for ( int i = 1; i <= n; i++ ) {
        cout << "ID: " << projects[i].id << " Programmers: " << projects[i].programmers << '\n';
        cout << "Counter: " << projects[i].countProjectsPointing << '\n';
        cout << "Enables: ";
        for (int enable : projects[i].enables) {
            cout << enable << ' ';
        }
        cout << '\n';
    }
}

// debug
void printPQ_Info(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq) {
    cout << "Zawartość kolejki (ULEGNIE USUNIĘCIU PO WYKONANIU FUNKCJI):\n";
    unsigned long long n = pq.size();
    for ( int i = 0; i < n; i++ ) {
        cout << pq.top().first << ' ' << pq.top().second << '\n';
        pq.pop();
    }
    cout << "KOLEJKA PUSTA\n";
}

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; // liczba projektów
    int m; // liczba zależności (krawędzi w grafie)
    int k; // minimalna liczba projektów do zrealizowania

    cin >> n >> m >> k;

    project projects[n+1]; // tablica wszystkich projektów
    vector<int> ProjectsNotDependingOn; // tablica projektów, które nie zależą od żadnego innego projektu

    for ( int i = 1; i <= n; i++ ) {
        cin >> projects[i].programmers;
        projects[i].id = i;
    }

    for ( int i = 1; i <= m; i++ ) {
        int idBeforeStartingNeeds;
        int idMustBeDoneFirst;

        cin >> idBeforeStartingNeeds >> idMustBeDoneFirst;
        projects[idMustBeDoneFirst].enables.push_back(idBeforeStartingNeeds);
        projects[idBeforeStartingNeeds].countProjectsPointing++;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    for ( int i = 1; i <= n; i++ ) {
        if ( projects[i].countProjectsPointing == 0 ) {
            pair<int, int> tmp = {projects[i].programmers, projects[i].id};
            pq.push(tmp);
        }
    }

    // debug
//    printProjectsInfo(projects, n);
//    printPQ_Info(pq);

    // Główna pętla programu
    int max = 0;
    int countChosenProjects = 0;
    while ( countChosenProjects < k ) {
        pair<int, int> v = pq.top();
        pq.pop();
        countChosenProjects++;
        if ( v.first > max ) {
            max = v.first;
        }

        for ( int index_enable : projects[v.second].enables ) {
            projects[index_enable].countProjectsPointing--;
            if (projects[index_enable].countProjectsPointing == 0 ) {
                pair<int, int> tmp = {projects[index_enable].programmers, projects[index_enable].id};
                pq.push(tmp);
            }
        }
    }

    cout << max << '\n';

    return 0;
}
