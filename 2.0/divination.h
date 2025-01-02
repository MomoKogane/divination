#include<iostream>
#include<unordered_map>
#include<vector>
#include<chrono>
#include<random>
#include<thread>

using namespace std;

class Divination
{
public: 
    void run();    
    string get_result(); 
private:
    int first=0,second=0;//变爻前的第一个和第二个卦
    static unordered_map<int,string> element_table;
    static unordered_map<int,string> divination_table;
    static vector<vector<string>>divination_map;
    void init();//初始化
    void analyze();
    void output_gram(int gram);
    void consolidate();
    int single_gram();//卜爻并进行初始计算，返回商数。
    vector<bool> visited;//标记某个爻是否变了
    void debug();
    string getTime();
    string result;
    string divinate_time;
    void output_result(string filename);
    mt19937 rng;
};