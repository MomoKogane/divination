#include"divination.h"
#include<ctime>
#include<fstream>

//����Ԫ�ر�
unordered_map<int,string> Divination::element_table = {
    {0,"��"},{1,"ɽ"},{2,"ˮ"},{3,"��"},
    {4,"��"},{5,"��"},{6,"��"},{7,"��"}
};

//���������
unordered_map<int,string>Divination::divination_table = {
    {0,"��"},{1,"��"},{2,"��"},{3,"��"},
    {4,"��"},{5,"��"},{6,"��"},{7,"Ǭ"}
};

//��������ӳ���
vector<vector<string>> Divination:: divination_map={
    {"��","ǫ","ʦ","��","��","����","��","̩"},
    {"��","��","��","��","��","��","��","����"},
    {"��","�","��","��","��","�ȼ�","��","��"},
    {"��","��","��","��","��","����","����","С��"},
    {"ԥ","С��","��","��","��","��","����","��׳"},
    {"��","��","δ��","��","���","��","�","����"},
    {"��","��","��","���","��","��","��","��"},
    {"��","��","��","��","����","ͬ��","��","��"}
};

//����ռ��
void Divination::run(){
    init();
    analyze();
    consolidate();
    output_result("ռ�����.txt");
}

//��ȡ���
string Divination::get_result()
{
    return result;
};

//����
void Divination::debug()
{
    //printf("first=%d,second=%d\n",first,second);
    result+="first="+to_string(first)+",second="+to_string(second)+"\n";
}

//��ȡ��ǰʱ��
string Divination::getTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return buf;
}

//��سռ��
int Divination::single_gram(){
    int start=48;
    int cal_result=1;
    int count=3;//����ɵ�һس
    while (count--)
    {
        uniform_int_distribution<int> uni(1, start-1);
        int left=uni(rng);
        int temp=((left - 1) % 4 + 1) + ((start - left - 1) % 4 + 1);
        //��Ϊһ��
        cal_result+=temp;
        start-=temp;
    }
    //printf("��س��%d\n",cal_result);
    //result+="��س��"+to_string((49-cal_result)/4)+"\n";
    return (49-cal_result)/4;
}

//��ʼ��
void Divination::init()
{
    first=second=0;
    visited.resize(6,false);//��ʼ��
    result="";
    auto seed_func = []() -> unsigned int {
        return static_cast<unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count() & 0xFFFFFFFF);
    };
    rng.seed(seed_func());
    divinate_time=getTime();
}

//�������
void Divination::analyze()
{
    int temp1=0,temp2=0;//temp1Ϊ���䣬temp2Ϊ��
    for(int i=0;i<6;i++){
        temp1=temp2=0;//��ʼ��
        int gram=single_gram();
        result+="��"+to_string(i+1)+"��س��";
        // ����gram��ֵ��ִ�в�ͬ�Ĳ���
        switch (gram)
        {
            // ���gram��ֵΪ6
            case 6:
                // ��temp1��ֵΪ0
                temp1=0;
                // ��temp2��ֵΪ1
                temp2=1;
                // ��visited[i]��ֵΪtrue
                visited[i]=true;
                // ��"����"��ӵ�result��
                result+="����\n";
                // ����switch���
                break;
            // ���gram��ֵΪ7
            case 7:
                // ��temp1��ֵΪ1
                temp1=1;
                // ��temp2��ֵΪ1
                temp2=1;
                // ��"����"��ӵ�result��
                result+="����\n";
                // ����switch���
                break;
            // ���gram��ֵΪ8
            case 8:
                // ��temp1��ֵΪ0
                temp1=0;
                // ��temp2��ֵΪ0
                temp2=0;
                // ��"����"��ӵ�result��
                result+="����\n";
                // ����switch���
                break;
            // ���gram��ֵΪ9
            case 9:
                // ��temp1��ֵΪ1
                temp1=1;
                // ��temp2��ֵΪ0
                temp2=0;
                // ��visited[i]��ֵΪtrue
                visited[i]=true;
                // ��"����"��ӵ�result��
                result+="����\n";
                // ����switch���
                break;
            // Ĭ�������
            default:
                // ����switch���
                break;
        }
        //printf("��%d��س��%d\n",i+1,gram);
        first=first*2+temp1;
        second=second*2+temp2;
        //debug();
    }
};

//�������
void Divination::output_gram(int gram){
    //��ȡ����
    int up=gram%8;
    //��ȡ����
    int down=gram/8;
    //������Ժ�������ͬ
    if(up==down){
        //������Ժ����Զ�Ӧ������
        //printf("%sΪ%s��",element_table[up].c_str(),divination_table[down].c_str());
        result+=element_table[up]+"Ϊ"+divination_table[down]+"��";
    }else{
        //������Ժ����Զ�Ӧ������
        //printf("%s%s%s��",element_table[up].c_str(),element_table[down].c_str(),divination_map[up][down].c_str());
        result+=element_table[up]+element_table[down]+divination_map[up][down]+"��";
    }
};

//���Ͻ��
void Divination::consolidate()
{
    //printf("���ν��Ϊ��\n");
    result+="���ν��Ϊ��\n";
    if(first==second)
        //��ʱ˵��û�б�س
    {
        output_gram(first);
        printf("\n");
        result+="\n";
    }
    else
    {
        //printf("��");
        result+="��";
        output_gram(first);
        //printf("��سΪ");
        result+="��سΪ";
        output_gram(second);
        //printf("\n");
        result+="\n";
    }
};

//������
void Divination::output_result(string filename)
{
    //����һ������ļ�������׷�Ӻ����ģʽ���ļ�
    ofstream outfile(filename,ios_base::app | ios_base::out);
    //���ռ��ʱ��
    outfile<<"ռ��ʱ��Ϊ��"+divinate_time<<"\n";
    //������
    outfile<<result<<endl;
    //�ر��ļ���
    outfile.close();
}