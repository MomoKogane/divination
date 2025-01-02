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
    int first=0,second=0;//��سǰ�ĵ�һ���͵ڶ�����
    static unordered_map<int,string> element_table;
    static unordered_map<int,string> divination_table;
    static vector<vector<string>>divination_map;
    void init();//��ʼ��
    void analyze();
    void output_gram(int gram);
    void consolidate();
    int single_gram();//��س�����г�ʼ���㣬����������
    vector<bool> visited;//���ĳ��س�Ƿ����
    void debug();
    string getTime();
    string result;
    string divinate_time;
    void output_result(string filename);
    mt19937 rng;
};