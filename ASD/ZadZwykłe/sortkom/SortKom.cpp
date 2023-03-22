#include <iostream>

using namespace std;

int main()
{
    // Magiczne linijki do przyspieszania wejścia/wyjścia
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    int a[n]; // oryginalny ciąg liczb z zadania

    for ( int i = 0; i < n; i++ ) {
        cin >> a[i];
    }

    int T[n][n];

    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            T[i][j] = 0;
        }
    }

    for ( int i = 0; i < n - 1; i++ ) {
        T[i][i] = 1;
        T[i+1][i] = (a[i] < a[i+1]);
        T[i][i+1] = T[i+1][i];
    }
    T[n-1][n-1] = 1;

    //debug
//    cout << "\n";
//    for ( int i = 0; i < n; i++ ) {
//        for ( int j = 0; j < n; j++ ) {
//            cout << T[i][j] << " ";
//        }
//        cout << "\n";
//    }

    for ( int k = 2; k < n; k++ ) {
        for ( int i = 0; i + k < n; i++ ) {
            T[i][i+k] = T[i+1][i+k] * (a[i] < a[i+1]) + T[i+k][i+1] * (a[i] < a[i+k]);
            T[i+k][i] = T[i+k-1][i] * (a[i+k] > a[i+k-1]) + T[i][i+k-1] * (a[i] < a[i+k]);

            T[i][i+k] %= 1000000000; // 10^9
            T[i+k][i] %= 1000000000; // 10^9
        }
    }

    /*
    // Wersja I
            T[i][i+k] = T[i+1][i+k] * (a[i] < a[i+1]) + T[i+k][i+1] * (a[i] < a[i+k]); // ?
            T[i+k][i] = T[i+k-1][i] * (a[i+k] > a[i+k-1]) + T[i][i+k-1] * (a[i] < a[i+k]); // ?

            // Wersja II
            //

            T[i][i+k] %= 1000000000; // 10^9
            T[i+k][i] %= 1000000000; // 10^9
    */

    //debug
//    cout << "\n";
//    for ( int i = 0; i < n; i++ ) {
//        for ( int j = 0; j < n; j++ ) {
//            cout << T[i][j] << " ";
//        }
//        cout << "\n";
//    }

    int result = T[0][n-1] + T[n-1][0];
    if ( n - 1 == 0 )
        result = T[0][0];
    result %= 1000000000; // 10^9

    cout << result;

    return 0;
}
