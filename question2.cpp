#include <future>
#include <thread>
#include <chrono>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include <iostream>
#include <random>
using namespace std::chrono;
using namespace std;
auto start = high_resolution_clock::now();

//function to return 1 if Gregor wins one game 0 otherwise using mathematical simulation
int one_round(){
    std::random_device rd;
    std::mt19937 gen( rd());
    std::uniform_int_distribution<> g_range( 0, 5);
    std::uniform_int_distribution<> o_range( 0, 9);
    int g_dice[] = {1,2,3,4,5};
    int o_dice[] = {1,2,3,4,5,6,7,8,9,10};
    int g_n = 8;
    int o_n = 4;
    int g_total = 0;
    int o_total = 0;
    for (int i = 0; i < g_n; i++){
        g_total += g_dice[g_range(gen)];
    }
    for (int i = 0; i < o_n; i++){
        o_total += o_dice[g_range(gen)];
    }
    if (g_total > o_total) return 1;
    else return 0;
}

//function to run the game in a loop get to an average
double main_loop(int number_complete_games){
    double percent_one;
    for (int i = 0; i < number_complete_games; i++){
        percent_one += one_round();
    }
    return (double)percent_one/(double)number_complete_games;
}

int main()
{
    int number_of_games = 50000;
    //I use async here to to spawn new threads for performance. 
    auto my_future1 = std::async(main_loop, number_of_games);
    auto my_future2 = std::async(main_loop, number_of_games);
    auto my_future3 = std::async(main_loop, number_of_games);
    auto my_future4 = std::async(main_loop, number_of_games);
    auto my_future5 = std::async(main_loop, number_of_games);
    auto my_future6 = std::async(main_loop, number_of_games);
    auto my_future7 = std::async(main_loop, number_of_games);
    auto my_future8 = std::async(main_loop, number_of_games);
    auto my_future9 = std::async(main_loop, number_of_games);
    auto my_future10 = std::async(main_loop, number_of_games);
    double average_percent_won = 100*(my_future10.get() + my_future9.get() + my_future8.get() + my_future7.get() + my_future6.get() + my_future1.get() + my_future2.get() + my_future3.get() + my_future4.get() + my_future5.get())/10.0;
    auto stop = high_resolution_clock::now();
    cout << "The probability that Gregor wins is " << std::setprecision(3) << average_percent_won << "%" << endl;
    auto time_spent = double(duration_cast<std::chrono::microseconds>(stop-start).count())/1'000'000;
    cout << "Number of seconds it took was " << time_spent <<  endl;
    return 0;
}
