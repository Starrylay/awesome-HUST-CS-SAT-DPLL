#include "Global.h"



int main() {
    Start();
    int choice = 0;
    int value = 0;
    double T1 = 0.0;
    double T2 = 0.0;
    char judge_continue;
    cin>>choice;
    while (choice){
        if(choice == 1) {
        string filename = createSudokuToFile();
        sudoku_easyx();
        cout <<filename<< " has been successfully created!" << endl;
        int VARNUM;
        HeadNode* LIST = CreateClause(VARNUM,filename);
        conse * SudoResult= new conse [VARNUM]; //conse SudoResult[VARNUM];//记录最终的真假值*****************添加new
        clock_t StartTime,EndTime;
        StartTime = clock();
        int value = SudoDPLL(LIST,SudoResult,VARNUM);
        EndTime = clock();
        cout << "********************************show the time********************************" << endl;
        cout<<"The time is "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";
        if (value == 1)
        {
            cout << "******************************finish the soduku******************************" << endl;
            SudokuShow(SudoResult, VARNUM);
            delete[] SudoResult;//*****************************************添加delete
            cout << "Do you want to continue? Y/N" << endl;
            cin >> judge_continue;
            if (judge_continue == 'Y') {
                Start();
                cin >> choice;
                continue;
            }
           // else exit(0);
        }
        else {
            cout << "there is no anwser.";
            cout << "Do you want to continue? Y/N" << endl;
            cin >> judge_continue;
            if (judge_continue == 'Y') {
                Start();
                cin >> choice;
                continue;
            }
           // else exit(0);
        }
            choice = 0;
            exit(0);
        }
        
        else if (choice == 2) {//SAT
            int VARNUM;
            string filename;// = "sat-20.cnf";
            cout << "Please input the file name" << endl;
            HeadNode* LIST = nullptr;
            do {
                cin >> filename;
                filename = filename + ".cnf";
                LIST = CreateClause(VARNUM, filename);
                if (LIST == nullptr)cout << "please input the existed filename!" << endl;
            } while (LIST==nullptr);
           
            consequence* result=new consequence[VARNUM];//consequence result[VARNUM];//记录最终的真假值**********添加new
            clock_t StartTime,EndTime;
          
            //cout<<"Result: \n";
            //StartTime = clock();
            //int value = DPLL(LIST,result);
            //EndTime = clock();
            //if(value) {
            //    cout << "S " << TRUE << endl;
            //    show(result, VARNUM);//输出解
            //}
            //else {
            //    cout << "S " << NoAnwser << endl;
            //    cout<<"V "<<endl;
            //}
            //cout<<"T "<<(double)(EndTime-StartTime)/CLOCKS_PER_SEC*1000.0<<" ms\n";

             //写到文件
             string suffix = ".res";
             string name = "solution";
             string Outputfile = name + suffix;
             ofstream fos(Outputfile);
             if(!fos.is_open()) {
                 cout<<"Can not open a new file.\n";
                 exit;
             }
             
            //StartTime = clock();
            int choose_dpll =0;//决策下行函数
            cout << "Whether to optimize?Y(For 1)/N(For 2)" << endl;
            cin >> choose_dpll;
            while (choose_dpll != 1 && choose_dpll != 2) {
                cout << "input the correct number!" << endl;
                cin >> choose_dpll;
            }
            if (choose_dpll == 1) {//优化
                
                 StartTime = clock();
                value = DPLL1(LIST, result);//
                  EndTime = clock();//计算dpll1时间
                T1 = (double)(EndTime - StartTime); 
               
                HeadNode* LIST = CreateClause(VARNUM, filename);
             
              //  cout << EndTime<<StartTime<<T1 << endl;
                 StartTime = clock();//////////////////////////
                 DPLL2(LIST, result);/////////////////////
                 EndTime = clock();//计算dpll2时间//////////////////////
                T2 = (double)(EndTime - StartTime);/////////////
               // cout << EndTime << StartTime << T2 << endl;
               // fos << "T2 " << T2 / CLOCKS_PER_SEC * 1000.0 << " ms\n";//
               // fos << "T1 " << T1 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                cout << "Congratulations!" << endl;
            }
                
            else if(choose_dpll==2) {
                StartTime = clock();
                value = DPLL1(LIST, result);
                EndTime = clock();
                cout << "Congratulations!" << endl;
                T2= (double)(EndTime - StartTime);

               // cout << EndTime << StartTime << T2 << endl;
                
            }
               

            //结果
            if(value) {
                fos << "S " << TRUE << endl;
                fos<<"V ";
                for(int i = 0; i < VARNUM; i++) {
                    if (result[i].value == TRUE)
                        fos<<i+1<<" ";
                    else if(result[i].value == FALSE)
                        fos<<-(i+1)<<" ";
                    else
                        fos<<(i+1)<<" ";//剩下一堆可true可false，就索性输出true
                }

                fos<<endl;
            }
            else {
                fos << "S " << NoAnwser << endl;
                fos<<"V ";
                fos<<endl;
            }
            //时间
            if (choose_dpll == 1) {
               if (T1 > T2) {
                    fos << "T1 " << T1 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                    fos << "T2 " << T2 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                   
                    if(T1&&T2)
                    fos << "Improve by " << (T1 - T2) / T1 * 100.0<<"%";
               }
                else {
                    fos << "T1 " << T2 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                    fos << "T2 " << T1 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
                    if (T1 && T2)
                    fos << "Improve by " << (T2 - T1) / T2 * 100.0<<"%";
                }
            }
            else {
                fos << "T " << T2 / CLOCKS_PER_SEC * 1000.0 << " ms\n";
            }
           
            fos.close();
            cout << "Do you want to continue? Y/N" << endl;
            cin >> judge_continue;
            if (judge_continue == 'Y') {
                Start();
                cin >> choice;
                continue;
            }
            delete[] result;//*******************************************添加delete
            choice = 0;
            exit(0);
            
        }
        else { //其他值不理睬
            cout<<"Please input the right num! "<<endl;
            cin >> choice;
            cout << endl;
           // exit;
        }
        
    }
}