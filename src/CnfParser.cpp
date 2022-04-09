//
// Created by PC on 2019/2/17.
#include "Global.h"

HeadNode* CreateClause(int& VARNUM, string& filename/*, int unique_flag*/) {
    //FileOpen
    string HFilePath = R"(D:\VS_project\SAT_DPLL\)";
    string path = HFilePath + filename;
    ifstream fis(path);
    if (!fis) {
        cout << "File can not open." << endl;
        return nullptr;
        // exit;
    }
    char ch;
    char buf[100];
    fis >> ch;
    while (ch != 'p') {
        fis.getline(buf, 100);
        fis >> ch;
    }
    string cnf;
    int VarNum, ClauseNum;
    fis >> cnf >> VarNum >> ClauseNum;
    fis.get();

    /*and write into 2 dimensional link lists*/
    //loading the initial node
    HeadNode* HEAD = new HeadNode;
    HeadNode* headRear = HEAD;
    HeadNode* END = new HeadNode;
    for (int i = 0; i < ClauseNum; i++) {
        //load on the data lists
        int temp;
        fis >> temp;
        //load the first data node
        DataNode* front = new DataNode;
        front->data = temp;
        headRear->right = front;
        headRear->Num++;
        //the >2th data loading
        fis >> temp;
        while (temp != 0) {
            DataNode* rear = new DataNode;
            front->next = rear;
            rear->data = temp;
            front = front->next;
            headRear->Num++;
            fis >> temp;
        }
        front->next = nullptr;
        fis.get();//换行符
        HeadNode* tp = new HeadNode;
        headRear->down = tp;
        END = headRear;
        headRear = headRear->down;
    }
    END->down = nullptr;

    //output link lists
    HeadNode* Phead = HEAD;
    DataNode* front;
    
    //cout << "验证唯一性步骤(For1)；选择输出步骤(For2)" << endl;
    
    /*if (unique_flag == 1) {
        while (Phead != nullptr) {
            front = Phead->right;
            while (front != nullptr) {
                cout << front->data << " ";
                front = front->next;
            }
            cout << endl;
            Phead = Phead->down;
        }
    }*/
   // if(unique_flag == 2) {
   // cout << "**********************************CnfParser**********************************\n";
    cout << "Whether to print Cnffile? Y/N" << endl;//选择是否输出cnf文件：Y输出，N不输出
    char judge_cnfshow;
    cin >> judge_cnfshow;
    while (judge_cnfshow != 'N')
    {
        if (judge_cnfshow == 'Y') {
            while (Phead != nullptr) {
                front = Phead->right;
                while (front != nullptr) {
                    cout << front->data << " ";
                    front = front->next;
                }
                cout << endl;
                Phead = Phead->down;
            }
        }

        judge_cnfshow = 'N';
    }
    cout << "\nTest successfuly!" << endl;
   // }

    VARNUM = VarNum;
    return HEAD;
}