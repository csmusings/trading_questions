#include <string>
#include <chrono>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>
#define M 5
#define N 5
using namespace std;
//used this tutorial https://www.topcoder.com/community/competitive-programming/tutorials/assignment-problem-and-hungarian-algorithm/

//True if bipartite matching found
bool find_b_matching(int b_graph[M][N], int u, vector<bool> seen, vector<int> matched_right);

// Returns maximum number
// of matching from M to N
int calc_b_matching(int b_graph[M][N]);

//make graph entries negative
void init_graph(int b_graph[M][N]){
    for (int i = 0; i < M; i++){
        for (int j=0; j<N; j++){
            b_graph[i][j] = b_graph[i][j]*-1;
        }
    }

}
//desgined to return the total value but does run fast enough. Calls maximum bipartite method - similar to Ford Fulkerson, and also uses approximation for minimum vertex cover. 
int calc_max_possible_value(int left_max_positive, int left_min_location, int favint[M][N], int b_graph[M][N]) {
    int maxMatches = 0;
    while (maxMatches < M + N) {
        left_max_positive = INFINITY;
        for (int i = 0; i < M; i++) {
            if (b_graph[i][0] < left_max_positive) {
                left_max_positive = b_graph[i][0];
                left_min_location = i;
            }
        }
        for (int j = 0; j < N; j++) {
            b_graph[left_min_location][j] -= left_max_positive;
        }
        maxMatches = calc_b_matching(b_graph);
        std::copy(&b_graph[0][0], &b_graph[0][0] + M * N, &favint[0][0]);
        vector<int> vertex_cover{};
        while (vertex_cover.size() < maxMatches) {
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (favint[i][j] == 0) {
                        if (favint[i][j] == 0 &&
                            std::find(vertex_cover.begin(), vertex_cover.end(), i) == vertex_cover.end()) {
                            vertex_cover.push_back(i);
                            for (int j2 = 0; j2 < N; j2++) {
                                if (j2 != j) {
                                    favint[i][j2] = -1;
                                }
                            }
                            for (int i2 = 0; i2 < M; i2++) {
                                if (i2 != i) {
                                    favint[i2][j] = 3;//-1;
                                }
                            }
                        }
                        if (favint[i][j] == 0 &&
                            std::find(vertex_cover.begin(), vertex_cover.end(), j) == vertex_cover.end())
                            vertex_cover.push_back(j);
                        for (int j2 = 0; j2 < N; j2++) {
                            if (j2 != j) {
                                favint[i][j2] = -1;
                            }
                        }
                        for (int i2 = 0; i2 < M; i2++) {
                            if (i2 != i) {
                                favint[i2][j] = -1;
                            }
                        }
                    }
                }
            }
            left_max_positive = INFINITY;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (std::find(vertex_cover.begin(), vertex_cover.end(), i) != vertex_cover.end() &&
                        std::find(vertex_cover.begin(), vertex_cover.end(), j) != vertex_cover.end())
                        left_max_positive = min(left_max_positive, b_graph[i][j]);
                }
            }
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    auto i_result = std::find(vertex_cover.begin(), vertex_cover.end(), i);
                    auto j_result = std::find(vertex_cover.begin(), vertex_cover.end(), j);
                    if (i_result == vertex_cover.end() && j_result == vertex_cover.end()) {
                        b_graph[i][j] = b_graph[i][j] - left_max_positive;
                    } else if (i_result != vertex_cover.end() && j_result == vertex_cover.end()) {
                        b_graph[i][j] = b_graph[i][j] + left_max_positive;
                    } else {

                    }
                }
            }
        }
    }
//return answer once found
return 1;
}

int main()
{
    int left_max_positive = INFINITY;
    int left_min_location = 0;
    int right_max_positive = INFINITY; // not used it, trying to get left working
    int right_max_location = 0;// not used it, trying to get left working
    int favint[M][N];
    int b_graph[M][N] = {{7,53,183,439,863},{497,383,563,79,973},{287,63,343,169,583}, {627,343,773,959,943}, {767,473,103,699,303} };
    init_graph(b_graph);
    int max_possible_sum = calc_max_possible_value( left_max_positive,  left_min_location,  favint,  b_graph);
    int maxMatches = 0;
    return 0;
}

bool find_b_matching(int b_graph[M][N], int u, vector<bool> seen, vector<int> matched_right)
{
    for (int v = 0; v < N; v++)
    {
        if (b_graph[u][v] == 0 && !seen[v])
        {
            seen[v] = true;
            if (matched_right[v] < 0 || find_b_matching(b_graph, matched_right[v],
                                                        seen, matched_right))
            {
                matched_right[v] = u;
                return true;
            }
        }
    }
    return false;
}

int calc_b_matching(int b_graph[M][N])
{
    //Array to track which values on left hand side have been matched with right hand side where , i represents index assigned.
    vector<int> matched_right(N,0);
    int result = 0;
    for (int u = 0; u < M; u++)
    {
        vector<bool> seen(N,0);
        if (find_b_matching(b_graph, u, seen, matched_right))
            result++;
    }
    return result;
}
