#include"divination.h"
#include<ctime>
#include<fstream>

//定义元素表
unordered_map<int,string> Divination::element_table = {
    {0,"地"},{1,"山"},{2,"水"},{3,"风"},
    {4,"雷"},{5,"火"},{6,"泽"},{7,"天"}
};

//定义卦象表
unordered_map<int,string>Divination::divination_table = {
    {0,"坤"},{1,"艮"},{2,"坎"},{3,"巽"},
    {4,"震"},{5,"离"},{6,"兑"},{7,"乾"}
};

//定义卦象映射表
vector<vector<string>> Divination:: divination_map={
    {"坤","谦","师","升","复","明夷","临","泰"},
    {"剥","艮","蒙","蛊","颐","贲","损","大畜"},
    {"比","蹇","坎","井","屯","既济","节","需"},
    {"观","渐","涣","巽","益","家人","中孚","小畜"},
    {"豫","小过","解","恒","震","丰","归妹","大壮"},
    {"晋","旅","未济","鼎","噬嗑","离","睽","大有"},
    {"萃","咸","困","大过","随","革","泽","夬"},
    {"否","退","讼","姤","无妄","同人","履","天"}
};

//运行占卜
void Divination::run(){
    init();
    analyze();
    consolidate();
    output_result("占卜结果.txt");
}

//获取结果
string Divination::get_result()
{
    return result;
};

//调试
void Divination::debug()
{
    //printf("first=%d,second=%d\n",first,second);
    result+="first="+to_string(first)+",second="+to_string(second)+"\n";
}

//获取当前时间
string Divination::getTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return buf;
}

//单爻占卜
int Divination::single_gram(){
    int start=48;
    int cal_result=1;
    int count=3;//三变可得一爻
    while (count--)
    {
        uniform_int_distribution<int> uni(1, start-1);
        int left=uni(rng);
        int temp=((left - 1) % 4 + 1) + ((start - left - 1) % 4 + 1);
        //此为一变
        cal_result+=temp;
        start-=temp;
    }
    //printf("单爻：%d\n",cal_result);
    //result+="单爻："+to_string((49-cal_result)/4)+"\n";
    return (49-cal_result)/4;
}

//初始化
void Divination::init()
{
    first=second=0;
    visited.resize(6,false);//初始化
    result="";
    auto seed_func = []() -> unsigned int {
        return static_cast<unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count() & 0xFFFFFFFF);
    };
    rng.seed(seed_func());
    divinate_time=getTime();
}

//分析结果
void Divination::analyze()
{
    int temp1=0,temp2=0;//temp1为不变，temp2为变
    for(int i=0;i<6;i++){
        temp1=temp2=0;//初始化
        int gram=single_gram();
        result+="第"+to_string(i+1)+"个爻：";
        // 根据gram的值，执行不同的操作
        switch (gram)
        {
            // 如果gram的值为6
            case 6:
                // 将temp1赋值为0
                temp1=0;
                // 将temp2赋值为1
                temp2=1;
                // 将visited[i]赋值为true
                visited[i]=true;
                // 将"老阴"添加到result中
                result+="老阴\n";
                // 跳出switch语句
                break;
            // 如果gram的值为7
            case 7:
                // 将temp1赋值为1
                temp1=1;
                // 将temp2赋值为1
                temp2=1;
                // 将"少阳"添加到result中
                result+="少阳\n";
                // 跳出switch语句
                break;
            // 如果gram的值为8
            case 8:
                // 将temp1赋值为0
                temp1=0;
                // 将temp2赋值为0
                temp2=0;
                // 将"少阴"添加到result中
                result+="少阴\n";
                // 跳出switch语句
                break;
            // 如果gram的值为9
            case 9:
                // 将temp1赋值为1
                temp1=1;
                // 将temp2赋值为0
                temp2=0;
                // 将visited[i]赋值为true
                visited[i]=true;
                // 将"老阳"添加到result中
                result+="老阳\n";
                // 跳出switch语句
                break;
            // 默认情况下
            default:
                // 跳出switch语句
                break;
        }
        //printf("第%d个爻：%d\n",i+1,gram);
        first=first*2+temp1;
        second=second*2+temp2;
        //debug();
    }
};

//输出卦象
void Divination::output_gram(int gram){
    //获取上卦
    int up=gram%8;
    //获取下卦
    int down=gram/8;
    //如果上卦和下卦相同
    if(up==down){
        //输出上卦和下卦对应的卦象
        //printf("%s为%s卦",element_table[up].c_str(),divination_table[down].c_str());
        result+=element_table[up]+"为"+divination_table[down]+"卦";
    }else{
        //输出上卦和下卦对应的卦象
        //printf("%s%s%s卦",element_table[up].c_str(),element_table[down].c_str(),divination_map[up][down].c_str());
        result+=element_table[up]+element_table[down]+divination_map[up][down]+"卦";
    }
};

//整合结果
void Divination::consolidate()
{
    //printf("本次结果为：\n");
    result+="本次结果为：\n";
    if(first==second)
        //此时说明没有变爻
    {
        output_gram(first);
        printf("\n");
        result+="\n";
    }
    else
    {
        //printf("从");
        result+="从";
        output_gram(first);
        //printf("变爻为");
        result+="变爻为";
        output_gram(second);
        //printf("\n");
        result+="\n";
    }
};

//输出结果
void Divination::output_result(string filename)
{
    //创建一个输出文件流，以追加和输出模式打开文件
    ofstream outfile(filename,ios_base::app | ios_base::out);
    //输出占卜时间
    outfile<<"占卜时间为："+divinate_time<<"\n";
    //输出结果
    outfile<<result<<endl;
    //关闭文件流
    outfile.close();
}