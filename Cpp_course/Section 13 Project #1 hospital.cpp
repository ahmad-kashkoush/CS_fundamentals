#include<iostream>
#include<string>
using namespace std;
struct hospital_queue{
    string patients[21];
    int status[21];
    int len=0;
    int spec=0

    hospital_queue(){
        len=0;
        spec=-1;

    }
    hospital_queue(int spec_){
        len=0;
        spec=spec_;
    }
    bool add_end(string pat, int st){
        if(len==5)
            return false;
        patients[len+1]=pat;
        status[len+1]=st;
        len++;
        return true;
    }
    void remove_front(){
        if(len==0){
            cout<<"no patients go have some rest doc\n";
            return;
        }
        cout<<patients[0]<<", Go with the doctor\n";
        for(int i=0;i<len-1;i++){
            patients[i]=patients[sp][i+1];
            status[i]=status[sp][i+1];
        }
        len--;

    }
    void print(){
        if(len!=0){
            cout<<"There'are "<<len<<"patients:\n";
            for(int i=0;i<len;i++){
                cout<<patients[i]<<" ";
                cout<<(status[i]?"Urgent\n":"regular\n");
            }
            cout<<"\n";
        }

    }


};

int added[21];
void print_section(int sp){
    if(added[sp]==0)
        cout<<"no patients go have some rest doc\n";
    else{
        for(int i=0;i<added[sp];i++)
            cout<<patients[sp][i]<<" "<<status[sp][i]<<"\n";

    }
}
void print(){
    for(int i=1;i<=21;i++){
        if(added[i]!=0)
            print_section(i);
    }
}
void shift_left(int sp){



}
void get_next(){
    cout<<"Enter Specilization : ";
    int sp; cin>>sp;
    if(added[sp]==0)
        return ;

    shift_left(sp);
}
void shift_right(int sp){
    for(int i=added[sp];i>=1;i--){
        patients[sp][i]=patients[sp][i-1];
        status[sp][i]=status[sp][i-1];
    }
}
void add(){
    cout<<"Enter specilization, name, and status: ";
    string name; int sp, st;
    cin>>sp>>name>>st;
    if(added[sp]>=5){
        cout<<"Sorry no place\n";
    }
    else{
        if(st==0){// not urgent push_back
            patients[sp][added[sp]]=name;
            status[sp][added[sp]]="regular";
        }else{
            shift_right(sp);
            patients[sp][0]=name;
            status[sp][0]="urgent";
        }
        added[sp]++;
    }
}
void display_choices(){
    cout<<"Enter Choice\n";
    cout<<" 1) Add \n";
    cout<<" 2) Print \n";
    cout<<" 3) get next \n" ;
    cout<<" 4) Exit     \n";

}
void choice(){
    int c=-1;
    while(c!=4){
        display_choices();
        cin>>c;
        if(c==1)          add();
        else  if(c==2)    print();
        else  if(c==3)    get_next();
        else  if(c==4)    break;
    }
}
int main(){
    choice();
    return 0;
}
