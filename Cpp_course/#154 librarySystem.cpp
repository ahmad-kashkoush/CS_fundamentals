/*

1-book
    1)methods
        -add book[id, name, quantity]
        -Searching for book[by prefix]
        -listing books by name, by id
    2) data members
        -
2-users
        - listing users who borrowed a specific book
        -add user
        -list of books users have borrowed
        -borrow a book
        -return a book


3-library_system
        - menu methods
*/
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
const int max_book=10;
const int max_users=10;
// order by name

// order by id

struct book{
    int id, quantity, total_borrowed;
     string name;
    book(){
        quantity=0;
        total_borrowed=0;
    }
    void read(){
         cout<<"Enter book info: id & name & total quantity: ";
         cin>>id>>name>> quantity;
    }
    bool has_prefix(string pre){
        for(int i=0;i<pre.size();i++){
           if(name[i]!=pre[i])
            return false;
        }
        return true;

    }
    void print(){
        cout<<"id = "<<id<<" name = "<<name
            <<" total_quantity = "<<quantity<<" total_borrowed = "<<total_borrowed<<"\n";
    }
    void make_a_borrow(){
        total_borrowed++;
        quantity--;
    }
    void return_book(){
        total_borrowed--;
        quantity++;
    }

};












struct user{
    book borrowed_books[100];
    string name; int id, total_borrowed;
    user(){
        total_borrowed=0;
        id=0;
    }
    read(){
        cout<<"Enter name & national id : ";
        cin>>name>>id;
    }
    void print(){
        cout<<"user name: "<< name
            <<" User Id  : "<<id
            <<" borrowed books Ids: ";
        for(int i=0;i<total_borrowed;i++)
            cout<<borrowed_books[i].id<<" ";

    }
    void add_book(book &b){
        borrowed_books[total_borrowed++]=b;
        b.make_a_borrow();
    }
    void shift_left(int i){
        for(int x=i;x<total_borrowed-1;x++){
            borrowed_books[x]=borrowed_books[x+1];
        }
    }
    void return_book(book &b){
        for(int i=0;i<total_borrowed;i++){
            if(  b.name==borrowed_books[i].name && i!=total_borrowed-1 ){
                    shift_left(i);
                    break;
                }
        }
        total_borrowed--;
        b.return_book();
    }
    bool has_book(string name){
        for(int i=0;i<total_borrowed;i++){
            if(borrowed_books[i].name==name)
                return true;
        }
        return false;

    }
};


bool cmp_name(book a, book b){
    return a.name<b.name;
}
bool cmp_id(book a, book b){
    return a.id<b.id;
}
struct library_system{
     int total_books;
     book books[max_book];
     int total_users;
     user  users[max_users];
     library_system(){
        total_books=0, total_users=0;
    }
    // some adding------------------------
    add_book(){
       books[total_books++].read();
    }
    add_user(){
        users[total_users++].read();
    }
    // search function
    search_books_by_prefix(){
        cout<<"Enter your book name prefix: ";
        string prefix;cin>>prefix;
        bool flag=false;
        for(int i=0;i<total_books;i++){
                if(books[i].has_prefix(prefix))
                    flag=true,cout<<books[i].name<<"\n";
        }
        if(!flag)
            cout<<"No books with this prefix\n";
    }
    // check if book is here or not
    bool valid_book_name(string name){
        for(int i=0;i<total_books;i++)
            if(books[i].name==name)
                return true;
        return false;
    }//some printing----------------------------------
    void print_books(){
        for(int i=0;i<total_books;i++)
            books[i].print();
    }
    void print_library_by_name(){
        sort(books, books+total_books, cmp_name);
        print_books();
    }
    void print_library_by_id(){
        sort(books, books+total_books, cmp_id);
        print_books();
    }
    void  print_who_borrowed_book_by_name(){
        cout<<"Enter book name: ";
        string name;cin>>name;
        if(valid_book_name(name)){
            for(int i=0;i<total_users;i++){
                if(users[i].has_book(name))
                    cout<<users[i].name<<"\n";
            }
        }else
            cout<<"Not a valid book name\n";
    }
    void print_users(){
        for(int i=0;i<total_users;i++)
            users[i].print();
    }
    //-----------------------
    // I'll assume that they exist
    user get_user_by_name(string name){
        for(int i=0;i<total_users;i++){
            if(users[i].name==name)
                return users[i];
        }
    }
    book get_book_by_name(string name){
        for(int i=0;i<total_books;i++){
            if(books[i].name==name)
                return books[i];
        }
    }
    void user_borrow_book(){
            cout<<"Enter user name && Book name : ";
            string user_name, book_name;
            cin>>user_name>>book_name;
            book bk=get_book_by_name(book_name);
            user usr=get_user_by_name(user_name);
            usr.add_book(bk);
    }
    void user_return_book(){
         cout<<"Enter user name && Book name : ";
         string user_name, book_name;
         cin>>user_name>>book_name;
         book bk=get_book_by_name(book_name);
         user usr=get_user_by_name(user_name);
         usr.return_book(bk);

    }

    void display_options(){
        cout<<"---------\nLibrary Menu:\n";
        cout<<"1) add_book\n";
        cout<<"2) search_books_by_prefix\n";
        cout<<"3) print_who_borrowed_book_by_name\n";
        cout<<"4) print_library_by_id\n";
        cout<<"5) print_library_by_name\n";
        cout<<"6) add_user\n";
        cout<<"7) user_borrow_book\n";
        cout<<"8) user_return_book\n";
        cout<<"9) print_users\n";
        cout<<"10) Exit\n\n";
    }
    int menu(){
        int choice=-1;
        while(choice==-1){
        cout<<"Enter your menu choice[1-10]: ";
            cin>>choice;
            if(!(choice>=1&&choice<=10)){
                cout<<"Enter valid choice";
                choice=-1;
            }
        }
        return choice;
    }

    void run(){
        display_options();
        while(true){
            int choice=menu();
            if(choice==1)
                add_book();
            else if(choice==2)
                search_books_by_prefix();
            else if(choice==3)
                print_who_borrowed_book_by_name();
            else if(choice==4)
                print_library_by_name();
            else if(choice==5)
                print_library_by_id();
            else if(choice==6)
                add_user();
            else if(choice==7)
                user_borrow_book();
            else if(choice==8)
                user_return_book();
            else if(choice==9)
                print_users();
            else
                break;
        }
    }
};

int main(){
    library_system admin1=library_system();
    admin1.run();
}
































