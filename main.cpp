#include<bits/stdc++.h>
#include"C:\\Users\\jizho\\AppData\\Local\\Programs\\Python\\Python310\\include\\Python.h"

using namespace std;
typedef long double ld;
vector<ld> XArray;
vector<ld> YArray;
ld end_b,end_w;
ld learning_rate = 0.0001;
ld initial_b = 0;
ld initial_w = 0;
int num_iterations=5000;

//处理csv文件得到数据点集
void getData(){
    ifstream inFile("data.csv", ios::in); //ifstream对象打开文件进行读操作,ios::in打开文件用于读取
    string lineStr;
    vector<vector<string>> strArray;
    while(getline(inFile,lineStr)){ //getline(文件流,保存到该字符串,终结符（可不加）)
        stringstream ss(lineStr);   //stringstream流的输入和输出操作
        string str;
        while(getline(ss,str,',')){
            XArray.push_back(stod(str)); //push_back在 vector 容器尾部添加一个元素
            getline(ss,str,',');
            YArray.push_back(stod(str));
        }
     }
    // for(int i=0;i<XArray.size();i++){
    //     cout<<XArray[i]<<" "<<YArray[i]<<endl;
    // }
}
//衡量精确度的方法：loss函数
ld compute_error_for_line_given_points(ld b,ld w){
    ld totalError = 0;
    for(int i=0;i<XArray.size();i++){
        ld x =XArray[i];
        ld y =YArray[i];
        totalError += (y - (w * x + b))*(y - (w * x + b));
    }
    return totalError / ld(XArray.size());
}
//每次下降的具体做法：求导变化
vector<ld> step_gradient(ld b_current,ld w_current,ld learningRate){
    ld b_gradient = 0;
    ld w_gradient = 0;
    vector<ld> temp;
    int NumOfData = XArray.size();
    for(int i=0;i<NumOfData;i++){
        ld x = XArray[i];
        ld y = YArray[i];
        b_gradient += -(2.0/NumOfData) * (y - ((w_current * x) + b_current));
        w_gradient += -(2.0/NumOfData) * x * (y - ((w_current * x) + b_current));
    }
    temp.push_back(b_current - (learningRate * b_gradient));
    temp.push_back(w_current - (learningRate * w_gradient));
    return temp;
}
    
//梯度下降法，迭代次数num_iterations
void gradient_descent_runner(ld b,ld w,int lr,int num_iterations){
    ld t_b = b;
    ld t_w = w;
    for(int i=0;i<num_iterations;i++){
        vector<ld> v = step_gradient(t_b, t_w,learning_rate);
        t_b = v[0];
        t_w = v[1];
    }
    end_b=t_b;
    end_w=t_w;
}
int main(){
    getData();
    cout<<"Starting gradient descent at b = "<<initial_b
        <<" , w = "<<initial_w<<" , error = "
        <<compute_error_for_line_given_points(initial_b, initial_w)<<endl;
    cout<<"Running..."<<endl;
    gradient_descent_runner(initial_b, initial_w, learning_rate, num_iterations);
    cout<<"After "<<num_iterations<<" iterations b = "<<end_b
        <<" , w = "<<end_w<<" , error = "
        <<compute_error_for_line_given_points(end_b, end_w)<<endl;
    
    //迭代器遍历vector
    // cout<< "XArray"<<endl;
    // for (std::vector<ld>::const_iterator i = XArray.begin(); i != XArray.end(); ++i) {
    //     std::cout << *i << ' ';
    // }
    // cout<< "\n" << "YArray"<<endl;
    // for (std::vector<ld>::const_iterator i = YArray.begin(); i != YArray.end(); ++i) {
    //     std::cout << *i << ' ';
    // }
    // cout<<endl;

    // 设置Python的Home路径
    Py_SetPythonHome(L"C:\\Users\\jizho\\AppData\\Local\\Programs\\Python\\Python310");
    Py_Initialize(); /*初始化python解释器,告诉编译器要用的python编译器*/
    // 检查初始化是否成功  
    if ( !Py_IsInitialized() ) {  
        return -1;  
    }  

    PyObject *pModule, *pDict, *pArgs1, *pArgs2, *pArgs3, *pArgs4, *pFunc;
    pModule = PyImport_ImportModule("function"); //使用PyObject* pModule来存储导入的.py文件模块
    if (!pModule) {
        printf("Cant open python file!/n");
        return -1;
    }
    pDict = PyModule_GetDict(pModule); //使用PyObject* pDict来存储导入模块中的方法字典
    if (!pDict) {
        printf("Cant find dictionary./n");
        return -1;
    }
    // 演示函数调用
    pFunc = PyDict_GetItemString(pDict, "pydraw"); //PyDict_GetItemString(dict, methodName)获取方法, 调用dict的methodName方法
    pArgs1 = PyList_New(XArray.size());//新建列表，括号内所创建列表的长度
    pArgs2 = PyList_New(YArray.size());
    
    double arrx[XArray.size()];
    for(int i=0;i<XArray.size();++i)
    {
         arrx[i] = XArray[i];
    }
    //arrx
    for(int i =0; i <XArray.size(); i++)
    {
        //cout << arrx[i] << " ";
        PyList_SetItem(pArgs1,i,Py_BuildValue("d", arrx[i])); 
        //Py_BuildValue(格式化字符串,剩余的参数)
    }

    double arry[YArray.size()];
    for(int i=0;i<YArray.size();++i)
    {
         arry[i] = YArray[i];
    }
    //arry
    for(int i =0; i <YArray.size(); i++)
    {
        //cout << arry[i] << " ";
        PyList_SetItem(pArgs2,i,Py_BuildValue("d", arry[i])); 
        //PyList_SetItem(要添加项的列表,所添加项的位置索引,所添加项的值)
    }

    // pArgs3 = PyTuple_New(1);//新建列表，括号内所创建列表的长度
    // pArgs4 = PyTuple_New(1);
    //w
    double pyend_w = static_cast<double>(end_w);
    //cout << "\n" << end_w << endl;
    pArgs3=Py_BuildValue("d", pyend_w); 
    //b
    double pyend_b = static_cast<double>(end_b);
    //cout << "\n" << end_b << endl;
    pArgs4=Py_BuildValue("d", pyend_b); 
    PyObject_CallFunctionObjArgs(pFunc, pArgs1, pArgs2, pArgs3, pArgs4, NULL);
    //PyObject_CallFunctionObjArgs(PyObject *callable, …, NULL)
    //返回执行结果的一个新引用，失败返回NULL。调用对象callable，
    //参数是若干个PyObject对象，以NULL结尾。



    Py_Finalize(); /*结束python解释器，释放资源*/

    return 0;
}
