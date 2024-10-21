   #include<iostream>
    #include<thread>
    using namespace std;
    void add(int a, int b, int &c, int &ready){
        c=a+b;
        ready =1;
    }

    int main(){

        int x, y, z;
        int ready=0;    
        cout<<"Nhap x: ";cin>>x;
        cout<<"Nhap y: ";cin>>y;

        thread tong(add,x,y, ref(z), ref(ready));

        while(ready==0){
            continue;
        }
        cout<<"x + y = "<<z<<endl;
        tong.join();

        return 0;
    }