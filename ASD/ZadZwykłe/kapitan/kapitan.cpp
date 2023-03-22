#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct island {
    int id; // nr wyspy
    int x; // współrzędna x
    int y; // współrzędna y

    int iSortedX; // nr wyspy w sortowaniu po 'x'
    int iSortedY; // nr wyspy w sortowaniu po 'y'
};

struct vertex {
    int id;
    int x;
    int y;
    bool visited = false;

    // Wektor zawiera sąsiadów wierzchołka - pary (odległość, id)
    vector<pair<int, int>> neighbours;
};

template <class T> bool ComparatorX(T a, T b)
{
    return a.x < b.x;
}

template <class T> bool ComparatorY(T a, T b)
{
    return a.y < b.y;
}

int distVertices( const vertex& a, const vertex& b ) {
    return min( abs(a.x - b.x), abs(a.y - b.y));
}

/*
 * Inicjalizuje wierzchołki w grafie (wraz z sąsiadami).
 * Obecnie pozwala na duplikacje krawędzi w grafie.
 * TODO: Spr, czy można pozwolić na duplikacje krawędzi
 */
void initVertices( vertex vertices[], island islands[], island islandsSortedX[], island islandsSortedY[], int n ) {
    for ( int i = 0; i < n; i++ ) {
        vertices[i].id = i;
        vertices[i].x = islands[i].x;
        vertices[i].y = islands[i].y;
    }

    for ( int i = 0; i < n; i++ ) {
        // Wyspa na zachód od nas
        if ( islands[i].iSortedX != 0 ) {
            int west = islandsSortedX[islands[i].iSortedX - 1].id;
            int dist = distVertices(vertices[i], vertices[west]);

            pair<int, int> tmp = {dist, west};

            vertices[i].neighbours.push_back(tmp);
        }

        // Wyspa na wschód od nas
        if ( islands[i].iSortedX != n - 1 ) {
            int east = islandsSortedX[islands[i].iSortedX + 1].id;
            int dist = distVertices(vertices[i], vertices[east]);

            pair<int, int> tmp = {dist, east};

            vertices[i].neighbours.push_back(tmp);
        }

        // Wyspa na północ od nas
        if ( islands[i].iSortedY != n - 1 ) {
            int north = islandsSortedY[islands[i].iSortedY + 1].id;
            int dist = distVertices(vertices[i], vertices[north]);

            pair<int, int> tmp = {dist, north};

            vertices[i].neighbours.push_back(tmp);
        }

        // Wyspa na południe od nas
        if ( islands[i].iSortedY != 0 ) {
            int south = islandsSortedY[islands[i].iSortedY - 1].id;
            int dist = distVertices(vertices[i], vertices[south]);

            pair<int, int> tmp = {dist, south};

            vertices[i].neighbours.push_back(tmp);
        }
    }
}

int dijkstra( vertex vertices[], int n ) {
    // Minimalny całkowity czas, jaki kapitan musi spędzić przy sterze to 'distanceFromSource[n-1]'
    int distanceFromSource[n];
    distanceFromSource[0] = 0;
    vertices[0].visited = true;

    for ( int i = 1; i < n; i++ ) {
        distanceFromSource[i] = INT_MAX;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pair<int, int> start = {0, 0};
    pq.push(start);

    while ( !pq.empty() ) {
        pair<int, int> v = pq.top();
        pq.pop();
        for ( pair<int, int> neighbour : vertices[v.second].neighbours ) {
            int alt = distanceFromSource[v.second] + neighbour.first;
            if ( alt < distanceFromSource[neighbour.second]) {
                distanceFromSource[neighbour.second] = alt;
                if ( !vertices[neighbour.second].visited ) {
                    pq.push(neighbour);
                }
            }
        }
    }

    return distanceFromSource[n-1];
}

// debug
void printVerticesInfo( vertex vertices[], int n) {
    for ( int i = 0; i < n; i++ ) {
        cout << "Nr wierzchołka: " << vertices[i].id + 1
        << ", (" << vertices[i].x << ", " << vertices[i].y << ")\n";
        cout << "Sąsiedzi: ";
        for ( pair<int, int> neighbour : vertices[i].neighbours ) {
            cout << neighbour.second + 1 << " (dist: " << neighbour.first << "), ";
        }
        cout << '\n';
    }
}

// debug
void printIslandsInfo( island islands[], int n ) {
    for ( int i = 0; i < n; i++ ) {
        cout << "Wyspa: " << islands[i].id + 1 << ", x: " << islands[i].x << ", y: " << islands[i].y
        << '\n';
    }
}

// debug
void printIslandsInfoFULL( island islands[], int n ) {
    for ( int i = 0; i < n; i++ ) {
        cout << "Wyspa: " << islands[i].id + 1 << "\nx: " << islands[i].x << ", y: " << islands[i].y
             << ", Odwiedzona: " << '\n';
        cout << "Nr w kolejności po 'x': " << islands[i].iSortedX + 1 << '\n';
        cout << "Nr w kolejności po 'y': " << islands[i].iSortedY + 1 << '\n';
    }
}

int main() {
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; // liczba wysp na morzu
    cin >> n;

    island islands[n]; // wyspy na morzu
    island islandsSortedX[n]; // wyspy posortowane po współrzędnej x
    island islandsSortedY[n]; // wyspy posortowane po współrzędnej y
    for ( int i = 0; i < n; i++ ) {
        cin >> islands[i].x >> islands[i].y;
        islands[i].id = i;

        islandsSortedX[i].x = islands[i].x;
        islandsSortedX[i].y = islands[i].y;
        islandsSortedX[i].id = islands[i].id;

        islandsSortedY[i].x = islands[i].x;
        islandsSortedY[i].y = islands[i].y;
        islandsSortedY[i].id = islands[i].id;
    }
    island * lastX = &(islandsSortedX[n-1]);
    lastX++;
    island * lastY = &(islandsSortedY[n-1]);
    lastY++;
    sort(islandsSortedX, lastX, ComparatorX<island>);
    sort(islandsSortedY, lastY, ComparatorY<island>);

    for ( int i = 0; i < n; i++ ) {
        islands[islandsSortedX[i].id].iSortedX = i;
        islands[islandsSortedY[i].id].iSortedY = i;
    }

    vertex vertices[n]; // Wyspy jako wierzchołki grafu, na którym skorzystamy z alg. Dijkstry
    initVertices( vertices, islands, islandsSortedX, islandsSortedY, n );

    cout << dijkstra(vertices, n ) << '\n'; // Minimalny czas kapitana przy sterze statku

    //debug
//    cout << "\nWierzchołki w grafie:\n";
//    printVerticesInfo(vertices, n);

//    cout << "\nWyspy w kolejności ich numerów:\n";
//    printIslandsInfoFULL(islands, n);
//
//    cout << "\nWyspy posortowane po 'x'\n";
//    printIslandsInfo(islandsSortedX, n);
//
//    cout << "\nWyspy posortowane po 'y'\n";
//    printIslandsInfo(islandsSortedY, n);

    return 0;
}
