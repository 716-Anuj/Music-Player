#include <cstddef>
#include <cstdio>
#include<iostream>
#include<string.h>
#include<fstream>
#include <string>

using namespace std;

class node{
    public:
    char song[100];
    struct node* next;
    struct node* prev;
}*top, *temp, *top1;

void tofile(char a[]){
    fstream f1;
    f1.open("playlist.txt", ios::out | ios::app);
    f1<<a<<endl;
    f1.close();
}

void add_node(struct node* first){
    char a[100];
    while(first->next != NULL){
        first = first->next;
    }
    struct node* new_node = new node();
    first->next = new_node;
    new_node->prev = first;
    cout<<"\n\a\a\a\aEnter Song Name : ";
    cin>>a;
    strcpy(new_node->song, a);
    tofile(a);
    new_node->next = NULL;
}

void add_node_file(struct node* first, string a){
    while(first->next != NULL){
        first = first->next;
    }
    struct node* new_node = new node();
    first->next = new_node;
    new_node->prev = first;
    strcpy(new_node->song, a.c_str());
    new_node->next = NULL;
}

void printlist(struct node* first){
    cout<<"\nPlaylist name : ";
    while(first != NULL){
        cout<<first->song<<endl;
        first = first->next;
    }
}

void count_nodes(struct node* first){
    int i = 0;
    while(first != NULL){
        first = first->next;
        i++;
    }
    cout<<"\nTotal Songs : "<<i-1<<endl;
}

void search1(struct node* first){
    char song[100];
    cout<<"\n\a\a\a\aEnter song to be searched : ";
    cin>>song;
    int flag = 0;

    while(first != NULL){
        if(strcmp(first->song, song) == 0){
            cout<<"\n\a\a\a\a#Song found"<<endl;
            flag++;
            break;
        }
        else{
            first = first->next;
        }
    }
    if(flag == 0){
        cout<<"\n\a\a\a\a#Song not found"<<endl;
    }
}

void create(){
    top = NULL;
}

void push(char data[]){
    if(top == NULL){
        top = new node();
        top->next = NULL;
        strcpy(top->song, data);
    } else if(strcmp(top->song, data) != 0){
        temp = new node();
        temp->next = top;
        strcpy(temp->song, data);
        top = temp;
    }
}

void display(){
    top1 = top;
    if(top1 == NULL){
        cout<<"\n\a\a\a\a=>No recently played track.\n";
        return;
    }
    cout<<"\n\a\a\a\a#Recently played track : \n";
    while(top1 != NULL){
        cout<<top1->song<<endl;
        top1 = top1->next;
    }
}

void play(struct node* first){
    char song[100];
    printlist(first);
    cout<<"\n\a\a\a\aChoose a song you wish to play : ";
    cin>>song;
    int flag = 0;

    while(first != NULL){
        if(strcmp(first->song, song) == 0){
            cout<<"\n\a\a\a\a=>Now playing......."<<song<<endl;
            flag++;
            push(song);
            break;
        } else{
            first = first->next;
        }
    }
    if(flag == 0){
        cout<<"\n\a\a\a\a#Song not found"<<endl;
    }
}

void recent(){
    display();
}

void topelement(){
    top1 = top;
    if(top1 == NULL){
        cout<<"\n\a\a\a\a#No last played track.\n";
        return;
    }
    cout<<"\n=>Last played song : "<<top->song<<endl;
}

void sort(node*& pointer){
    if(!pointer) return;
    node* sorted = NULL;
    node* current = pointer;

    while(current != NULL){
        node* next = current->next;
        if(!sorted || strcmp(sorted->song, current->song) >= 0){
            current->next = sorted;
            sorted = current;
        } else{
            node* temp = sorted;
            while(temp->next != NULL && strcmp(temp->next->song, current->song) < 0){
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    pointer = sorted;
}

void delete_file(char a[]){
    fstream f1, f2;
    string line;
    int x = 0;
    f1.open("playlist.txt", ios::in);
    f2.open("temp.txt", ios::out);
    while(getline(f1, line)){
        if(strcmp(a, line.c_str()) != 0)
            f2<<line<<endl;
        else
            x = 1;
    }
    f1.close();
    f2.close();
    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");
    if(x == 0){
        cout<<"There is no song with this name you entered."<<endl;
    } else{
        cout<<"Song has been deleted."<<endl;
    }
}

struct node *del_pos(struct node *pointer, int pos){
     if (pos < 0 || pointer == NULL) {
        cout << "\nInvalid position.\n";
        return pointer;
    }

    struct node* temp = pointer;

    if (pos == 0) {
        pointer = pointer->next;
        if (pointer != NULL)
            pointer->prev = NULL;
        delete_file(temp->song);
        delete temp;
        cout << "\nThe list is updated\nUse the display function to check\n";
        return pointer;
    }

    for (int i = 0; temp != NULL && i < pos - 1; i++)
        temp = temp->next;

    if (temp == NULL || temp->next == NULL) {
        cout << "\nInvalid position.\n";
        return pointer;
    }

    struct node* next = temp->next->next;
    delete_file(temp->next->song);
    delete temp->next;
    temp->next = next;
    if (next != NULL)
        next->prev = temp;

    cout << "\nThe list is updated\nUse the display function to check\n";
    return pointer;
}

void addplaylist(struct node* start){
    fstream f1;
    string line;
    f1.open("playlist.txt", ios::in);
    while(getline(f1, line)){
        add_node_file(start, line);
    }
    cout<<"Playlist Added"<<endl;
    f1.close();
}

void del_search(struct node* start){
    char song[100];
    printlist(start);
    cout<<"\n\a\a\a\aChoose song you wish to delete : ";
    cin>>song;
    int flag = 0;
    while(start != NULL){
        if(strcmp(start->song, song) == 0){
            cout<<"\n\a\a\a\a#Song Found"<<endl;
            delete_file(start->song);
            if(start->prev != NULL){
                start->prev->next = start->next;
            }
            if(start->next != NULL){
                start->next->prev = start->prev;
            }
            delete start;
            flag++;
            break;
        } else{
            start = start->next;
        }
    }
    if(flag == 0){
        cout<<"\n\a\a\a\a#Song not found"<<endl;
    }
}

void deletemenu(struct node* start){
    int c;
    cout<<"Enter type of delete do you want?\n1. By Search\n2. By Position"<<endl;
    cin>>c;

    switch(c){
        case 1: del_search(start);
            break;
        case 2: int pos;
            cout<<endl<<"Enter the pos of the song: ";
            cin>>pos;
            start = del_pos(start, pos-1);
            break;
    }
}

int main(){
    int choice, loc;
    char song[100];
    struct node* start, * hold;
    
    start = new node();

    cout<<"\t\t\t\a\a\a\a**WELCOME**"<<endl;
    cout<<"\n**please use '_' for space."<<endl;
    cout<<"\n\n\a\a\a\aEnter your playlist name : ";
    cin.getline(start->song, 100);
    start->next = NULL;
    hold = start;

    create();

    do{
        cout << "\n1.Add New Song\n2.Delete Song\n3.Display Entered Playlist\n4.Total Songs\n5.Search Song\n6.Play Song\n7.Recently Played List\n8.Last Played\n9.Sorted playlist\n10.Add From File\n11.Exit" << endl;
        cout<<"\n\a\a\a\aEnter your choice : "<<endl;
        cin>>choice;

        switch(choice){
            case 1: add_node(start);
                break;
            case 2: deletemenu(start);
                break;
            case 3: printlist(start);
                break;
            case 4: count_nodes(hold);
                break;
            case 5: search1(start);
                break;
            case 6: play(start);
                break;
            case 7: recent();
                break;
            case 8: topelement();
                break;
            case 9: sort(start);
                printlist(start);
                break;
            case 10: addplaylist(start);
                break;
            case 11: exit(0);
        } 
    }while(choice != 11);
    return 0;
}