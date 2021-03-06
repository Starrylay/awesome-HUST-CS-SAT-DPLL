//
// Created by PC on 2019/2/18.
//
#include "Global.h"

status IsEmptyClause(HeadNode* LIST) {
    HeadNode* PHead = LIST;
    while (PHead != nullptr) {
        if(PHead->Num == 0)
            return TRUE;
        PHead = PHead->down;
    }
    return FALSE;
}

HeadNode* IsSingleClause(HeadNode* Pfind) {
    while (Pfind != nullptr ) {
        if(Pfind->Num == 1)
            return Pfind;
        Pfind = Pfind->down;
    }
    return nullptr;
}

HeadNode* Duplication(HeadNode* LIST) { //此处检验传参正常，开始检查复制有无逻辑错误
    HeadNode* SrcHead = LIST;
    HeadNode* ReHead = new HeadNode;//新链表的头节点
    ReHead->Num = SrcHead->Num;//复制第一个头节点
    HeadNode* Phead = ReHead;//Phead创建头节点
    DataNode *ReData = new DataNode;//新链表的数据节点
    DataNode *FirstSrcData = SrcHead->right;//用于创建第一行的第一个数据节点
    ReData->data = FirstSrcData->data;//新链表的第一个数据节点的数值
    Phead->right = ReData;
    for (FirstSrcData = FirstSrcData->next;FirstSrcData != nullptr; FirstSrcData = FirstSrcData->next) {//第一行链表复制完成
        DataNode *NewDataNode = new DataNode;
        NewDataNode->data = FirstSrcData->data;
        ReData->next = NewDataNode;
        ReData = ReData->next;
    }
    //此下行数节点的复制 >=2th
    for(SrcHead = SrcHead->down; SrcHead != nullptr ; SrcHead = SrcHead->down) {
        HeadNode* NewHead = new HeadNode;
        DataNode* NewData = new DataNode;
        NewHead->Num = SrcHead->Num;
        Phead->down = NewHead;
        Phead = Phead->down;
        DataNode* SrcData = SrcHead->right;
        NewData->data = SrcData->data;
        Phead->right = NewData;//第一个数据节点
        for (SrcData = SrcData->next;SrcData != nullptr; SrcData = SrcData->next) {//此行剩下的数据节点
            DataNode* node = new DataNode;
            node->data = SrcData->data;
            NewData->next = node;
            NewData = NewData->next;
        }
        NewData->next = nullptr;
    }
    Phead->down = nullptr;

    return ReHead;
}

HeadNode* ADDSingleClause(HeadNode* LIST,int Var) { //所加的单子句位于链表的头
    HeadNode* AddHead = new HeadNode;
    DataNode* AddData = new DataNode;
    AddData->data = Var;
    AddData->next = nullptr;
    AddHead->right = AddData;
    AddHead->Num = 1;
    AddHead->down = LIST;
    LIST = AddHead;
    return LIST;
}

void DeleteDataNode(int temp,HeadNode *&LIST) {
    DataNode* p_rear = nullptr;
   // HeadNode* p_pHeadNode = nullptr;
    for (HeadNode* pHeadNode = LIST; pHeadNode != nullptr ; pHeadNode = pHeadNode->down)
        for (DataNode *rear = pHeadNode->right; rear != nullptr ; rear = rear->next) {
            if (rear->data == temp)  //相等删除整行
            {
               // p_pHeadNode= pHeadNode->down;
                DeleteHeadNode(pHeadNode, LIST);
              //  pHeadNode->down = p_pHeadNode;
                break;
            }
                
            else if (abs(rear->data) == abs(temp)) { //仅仅是绝对值相等铲除该节点
                if(rear == pHeadNode->right) { //头节点删除
                    pHeadNode->right = rear->next;
                    pHeadNode->Num--;
                }
                else{ //删除普通节点
                    for (DataNode* front = pHeadNode->right; front != nullptr; front= front->next)
                        if(front->next == rear) {
                            front->next = rear->next;
                            delete rear;
                            rear = front;
                            pHeadNode->Num--;
                        }
                }
            }
        }
}

void DeleteHeadNode(HeadNode *Clause,HeadNode *&LIST) {
    if (!Clause) return;
    if (Clause == LIST) {
        LIST = Clause->down;
        FreeHeadNode(Clause);//释放整行内存
    }
       
    else {
        for (HeadNode *front = LIST; front != nullptr; front = front->down)
            if (front->down == Clause) {
                front->down = Clause->down;
               FreeHeadNode(Clause);//释放整行内存
            }
    }
}
void FreeHeadNode(HeadNode* Clause) {
   
        DataNode* p1_DataNode = Clause->right;
        DataNode* p2_DataNode = Clause->right;
        Clause->right = nullptr;
        //Clause->down = nullptr;
        while (p2_DataNode != nullptr) {
            p1_DataNode = p2_DataNode->next;
            delete p2_DataNode;
            p2_DataNode = p1_DataNode;
        }
        //delete Clause;
}

void show(struct consequence *result,int VarNum) {
    cout<<"V ";
    for(int i = 0; i < VarNum; i++) {
        if (result[i].value == TRUE)
            cout<<i+1<<" ";
        else if(result[i].value == FALSE)
            cout<<-(i+1)<<" ";
        else
            cout<<(i+1)<<" ";//剩下一堆可true可false，就索性输出true
    }
    cout<<endl;
}
int Choose_max(HeadNode* LIST) {
    HeadNode* p_head = LIST;
    DataNode* p_data = LIST->right;
    //  Count* Result_fre = new Count;
    Count Result_fre[CHOOSE_SOLUTION];
    Count* p_count = Result_fre;
    int flag_count = 0;
    int max_count = 0;
    int max_num = 0;
    while (p_head != nullptr) {
        p_data = p_head->right;
        while (p_data != nullptr) {
            p_count = Result_fre;
            flag_count = 0;
            while (p_count->num) {
                if (p_count->num == abs(p_data->data)) {
                    (p_count->count)++;
                    flag_count = 1;
                }
                p_count++;
            }
            if (flag_count == 0) {
                p_count->num = abs(p_data->data);
                (p_count->count)++;
            }
            p_data = p_data->next;
        }
        p_head = p_head->down;
    }
    p_count = Result_fre;
    while (p_count->num) {
        if (p_count->count > max_count) {
            max_num = p_count->num;
        }
        p_count++;
    }
    return max_num;
}
status DPLL2(HeadNode *LIST,consequence *result) {
    //单子句规则
    //int choose_dpll=0;
    //int Var = 0;
    HeadNode* Pfind = LIST;
    HeadNode* SingleClause = IsSingleClause(Pfind);
    while (SingleClause != nullptr) {
        SingleClause->right->data > 0 ? result[abs(SingleClause->right->data)-1].value = TRUE : result[abs(SingleClause->right->data)-1].value = FALSE;
        int temp = SingleClause->right->data;
        DeleteHeadNode(SingleClause,LIST);//删除单子句这一行
        DeleteDataNode(temp,LIST);//删除相等或相反数的节点
        if(!LIST) return TRUE;
        else if(IsEmptyClause(LIST)) return FALSE;
        Pfind = LIST;
        SingleClause = IsSingleClause(Pfind);//回到头节点继续进行检测是否有单子句
    }
    //分裂策略
   
   // if (choose_dpll == 1) {
   //   int Var = LIST->right->data;//选取变元
 //   }
   // else if (choose_dpll == 2) {
   int Var = Choose_max(LIST);
  //  }
    HeadNode* replica = Duplication(LIST);//存放LIST的副本replica
    HeadNode *temp1 = ADDSingleClause(LIST,Var);//装载变元成为单子句
    if(DPLL2(temp1,result)) return TRUE;
    else {
        HeadNode *temp2 = ADDSingleClause(replica,-Var);
        if (DPLL1(temp2, result))   // return DPLL(temp2,result);
        {
            //delete replica;
            return TRUE;
        }
        else {
            //delete replica;
            return FALSE;
        }
    }
   
}
status DPLL1(HeadNode* LIST, consequence* result) {//拉一点点
    //单子句规则
    //int choose_dpll = 0;
    //int Var = 0;
    HeadNode* Pfind = LIST;
    HeadNode* SingleClause = IsSingleClause(Pfind);
    while (SingleClause != nullptr) {
        SingleClause->right->data > 0 ? result[abs(SingleClause->right->data) - 1].value = TRUE : result[abs(SingleClause->right->data) - 1].value = FALSE;
        int temp = SingleClause->right->data;
        DeleteHeadNode(SingleClause, LIST);//删除单子句这一行
        DeleteDataNode(temp, LIST);//删除相等或相反数的节点
        if (!LIST) return TRUE;
        else if (IsEmptyClause(LIST)) return FALSE;
        Pfind = LIST;
        SingleClause = IsSingleClause(Pfind);//回到头节点继续进行检测是否有单子句
    }
    //分裂策略

   // if (choose_dpll == 1) {
      int Var = LIST->right->data;//选取变元
 //   }
   // else if (choose_dpll == 2) {
    //int Var = Choose_max(LIST);
    //  }
    HeadNode* replica = Duplication(LIST);//存放LIST的副本replica
    HeadNode* temp1 = ADDSingleClause(LIST, Var);//装载变元成为单子句
    if (DPLL1(temp1, result)) return TRUE;
    else {
        HeadNode* temp2 = ADDSingleClause(replica, -Var);
        if (DPLL1(temp2, result))   // return DPLL(temp2,result);
        {
            //delete replica;
            return TRUE;
        }
        else {
            //delete replica;
            return FALSE;
        }
    }
}