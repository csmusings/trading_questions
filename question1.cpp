//
//
// Created by Greg on 2019-04-17.
//

#include <condition_variable>
#include <future>
#include <numeric>
#include <thread>
#include <chrono>
#include <vector>
#include <numeric>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <memory>
#include <fstream>
#include <mutex>
#include <queue>
#include <math.h>
#include <map>
#include <algorithm>
#include <random>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
using namespace std::chrono;
using namespace std;

int count( int coins[], int m, int n )
{
    int i, j, x, y;
    int table[n + 1][m];
    for (i = 0; i < m; i++)
        table[0][i] = 1;
    for (i = 1; i < n + 1; i++)
    {
        for (j = 0; j < m; j++)
        {
            x = (i - coins[j] >= 0) ? table[i - coins[j]][j] : 0;
            y = (j >= 1) ? table[i][j - 1] : 0;
            table[i][j] = x + y;
        }
    }
    return table[n][m - 1];
}

auto start = high_resolution_clock::now();
int main()
{
    const int u1=1;
    const int u5=5;
    const int u10=10;
    const int u20=20;
    const int u50=50;
    const int u100=100;
    int coins[] = {u1, u5, u10, u20,u50, u100};
    int m = sizeof(coins)/sizeof(coins[0]);
    int n = 500;
    int possible_combinations = count(coins, m, n);
    auto stop = high_resolution_clock::now();
    cout << "There were " << possible_combinations << " ways to make U500 and it took " <<
    duration_cast<microseconds>(stop-start).count() << " microseconds to calculate" << endl;
    return 0;
}

