#include<bits/stdc++.h>
#include"data.h"
using namespace std;
//typedef long double ld;
vector<ld> XArray;
vector<ld> YArray;
ld end_b,end_w;
ld learning_rate = 0.0001;
ld initial_b = 0;
ld initial_w = 0;
int num_iterations=5000;

//处理.h文件得到数据点集
void getData(){
    //迭代器遍历vector
    cout<< "XArray"<<endl;
    for (std::vector<ld>::const_iterator i = xArray.begin(); i != xArray.end(); ++i) {
        XArray.push_back(*i);
        std::cout << *i << ' ';
    }
    cout<< "\n" << "YArray"<<endl;
    for (std::vector<ld>::const_iterator i = yArray.begin(); i != yArray.end(); ++i) {
        YArray.push_back(*i);
        std::cout << *i << ' ';
    }
    cout<<endl;
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

int main()
{
    getData();
    cout<<"Starting gradient descent at b = "<<initial_b
        <<" , w = "<<initial_w<<" , error = "
        <<compute_error_for_line_given_points(initial_b, initial_w)<<endl;
    cout<<"Running..."<<endl;
    gradient_descent_runner(initial_b, initial_w, learning_rate, num_iterations);
    cout<<"After "<<num_iterations<<" iterations b = "<<end_b
        <<" , w = "<<end_w<<" , error = "
        <<compute_error_for_line_given_points(end_b, end_w)<<endl;

    return 0;
}
