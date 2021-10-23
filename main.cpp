#include<bits/stdc++.h>
using namespace std ;
#define endl "\n"
// #define int long long
void clearScreen() {
    cout<<"\033[2J\033[1;1H";
}

void start();
void initialize(int n1, string arr1[], int n2, string arr2[], int n3, string arr3[], map<string, vector<string>> &adj, map<string,int> &color);
map<int, vector<string>> schedule(map<string, vector<string>> &adj, map<string, int> &color, int &max_days);
void display(int days, map<int, vector<string>> &hash, string name, int semester);


int32_t main()
{   
    bool choice = false;
    do {
        start();
        cout<<"\n\n\t\tDo You wish to continue Again.. Press (1 for Yes) & (2 for No): ";
        string inp; cin>>inp;
        if(inp=="1") choice = true; 
        else choice = false;
        clearScreen();
    } while(choice);
	return 0;
}

void start() {
    cout<<"\n\n\n\t\t----------------------------Welcome To Exam Time Table Scheduler------------------------\n\n\n\n";
    cout<<"\t\t\tEnter the Name of Your College: ";
    string name; getline(cin,name);
    cout<<"\n\t\t\tEnter Odd(1) or Even(2) Semester: ";
    int semester;  cin>>semester;
    
    // Clearing Screen
    clearScreen();
    cout<<"\n\n\t\t-----------------Currently Supporting upto 3 Semesters-------------------";
    
    cout<<"\n\n\t\t\tEnter no. of Semester "<<semester<<" subjects: ";
    int n1; cin>>n1;
    cout<<"\n\t\t\tEnter subject codes: ";
    string arr1[n1];
    for(int i=0;i<n1;i++) cin>>arr1[i];

    // Clearing Screen
    clearScreen();
    
    cout<<"\n\n\t\t\tEnter no. of Semester "<<(semester==1?"3":"4")<<" subjects including the previous semester overload subjects:  ";
    int n2; cin>>n2;
    cout<<"\n\t\t\tEnter subject codes: ";
    string arr2[n2];
    for(int i=0;i<n2;i++)cin>>arr2[i];
    
    // Clearing Screen
    clearScreen();

    cout<<"\n\t\t\tEnter no. of Semester "<<(semester==1?"5":"7")<<" subjects including the previous semster overloads: ";
    int n3; cin>>n3;
    string arr3[n3];
    cout<<"\n\t\t\tEnter subject codes: ";
    for(int i=0;i<n3;i++)cin>>arr3[i];

    // Clearing Screen
    clearScreen();
    
    // Initializing Graph 
    map<string, vector<string>> adj;
    map<string, int> color; 
    initialize(n1,arr1,n2,arr2,n3,arr3, adj, color);
    
    // Scheduling the Slots
    int max_days=-1;
    map<int, vector<string>> exam_schedule = schedule(adj,color, max_days);
    
    // Displaying the Results 
    display(max_days, exam_schedule, name, semester);
    
}

void initialize(int n1, string arr1[], int n2, string arr2[], int n3, string arr3[], map<string, vector<string>> &adj, map<string, int> &color) {
    
    for(int i=0;i<n1; i++) {
        for(int j=0;j<n1; j++) {
            if(i!=j)
            adj[arr1[i]].push_back(arr1[j]);
        }
    }
    for(int i=0;i<n2; i++) {
        for(int j=0;j<n2; j++) {
            if(i!=j)
            adj[arr2[i]].push_back(arr2[j]);
        }
    }
    for(int i=0;i<n3; i++) {
        for(int j=0;j<n3; j++) {
            if(i!=j)
            adj[arr3[i]].push_back(arr3[j]);
        }
    }
    
    //Initialize the color of each node to -1
    for(auto x: adj) {
        color[x.first]=-1;
    }

    color[adj.begin()->first]=1;
    vector<bool> alreadyAssigned(n1+n2+n3);

    auto it= adj.begin();
    it++;
    map<string, vector<string>>::iterator i;
    for(i=it; i!=adj.end(); i++) {
        fill(alreadyAssigned.begin(), alreadyAssigned.end(), false);

        for (auto av : adj[i->first])
            if (color[av] != -1)
                alreadyAssigned[color[av]] = true;

        int c;
        for (c = 1; c <= n1+n2+n3 ; c++)
            if (alreadyAssigned[c] == false)
                break;

        color[i->first] = c;
    }
}


map<int, vector<string>> schedule(map<string, vector<string>> &adj, map<string, int> &color, int &max_days) {
    map<int, vector<string>> hash;
    for (auto ele: adj) {
        // cout << "Vertex  " << ele.first << " ---> Color " << color[ele.first] << endl;
        hash[color[ele.first]].push_back(ele.first);
    }

    int mx=INT_MIN;
    for(auto ele: color)
    {
        mx= max(mx, ele.second);
    }

    //cout << "\nNumber of colors required: " << mx << endl;
    
    max_days=mx;
    
    return hash;
}

void display(int days, map<int, vector<string>> &hash, string name, int semester) {
    
    cout<<"\n\t\t\tNumber of Days to take Examinations would be: "<<days<<"\n";
    
    cout<<"\n\t\t\tHow many Maximum number of Slots per Day you Want? ";
    int slots; cin>>slots;
    
    // Clearing Screen
    clearScreen();
    
    cout<<"\n\n\t\t----------------------------- Examination Schedule ------------------------------";
    cout<<"\n\n\t\t\t\t\tCollege: "<<name<<"\tSemester: "<<((semester==1?"ODD":"EVEN"));

    int day_cnt=1, slot_cnt=1; 
    cout<<"\n\n\t\t\t-----------------------Day "<<day_cnt<<"-----------------------\n\n";
    for(auto it: hash) {
        cout<<"\t\t\t\tSlot "<<slot_cnt<<" -> ";
        for(auto k: it.second) cout<<k<<" , ";
        cout<<"\n";
        slot_cnt++;
        if(slot_cnt>slots) {
            day_cnt++;
            slot_cnt=1;
            cout<<"\n\t\t\t-----------------------Day "<<day_cnt<<"-----------------------\n\n";
        }
    }
}

// Some Sample Cases to try -
// 5
// phy102 ma101 cy101 cso101 me104
// 7
// cso211 ma102 me102 cso204 phy101 ma101 me104
// 5
// ma301 cso301 ma302 ma101 ma102