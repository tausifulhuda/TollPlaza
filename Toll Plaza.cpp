#include<bits/stdc++.h>
using namespace std;

class Operator{
    char pass[50][5];
    int total=0;

    public:
        char username[100][5];
        int CheckUsername(char y[]){
            int i;
            for(i=0;i<total;i++)
                if(strcmp(username[i],y)==0)
                    return i;
            return -1;
        }

        int CheckPassword(char y[]){
            int i;
            for(i=0;i<total;i++)
                if(strcmp(pass[i],y)==0)
                    return i;
            return -1;
        }

        void addOperator(){
            char x[100], y[50]; char reconfirm_pass[50];
            int i;
            cout<<"Enter new username: ";
            cin>>x;
            i=CheckUsername(x);
            if(i==-1){
                strcpy(username[total], x);
                cout<<"Set Password: ";
                cin>>y;
                cout<<"Reconfirm Password: ";
                cin>>reconfirm_pass;

                if(strcmp(reconfirm_pass, y)==0){
                    cout<<"\nNew operator added successfully\n\n";
                    strcpy(pass[total], y);
                    total++;
                }
                else
                    cout<<"\nPassword doesn't match\n\n";
            }
            else
                cout<<"\nOperator already exists\n\n";
        }

        int login(){
            char x[100], y[50];
            int i,j;;
            cout<<"Enter username: ";
            cin>>x;
            i=CheckUsername(x);
            if(i!=-1){
                cout<<"Enter Password: ";
                cin>>y;
                j=CheckPassword(y);
                if(j!=-1){
                    cout<<"\nLogged in successfully\n\n";
                    return 1;
                }
                else
                    cout<<"\nWrong Password\n\n";
            }
            else
                cout<<"\nUsername invalid\n\n";

            return -1;
        }
};

class Vehicle: public Operator{
    public:
    string reg_no;
    string d, t;
    void regi_no(){
        cout<<"Enter Registration Number: ";
        cin>>reg_no;
    }
    void date(){
        cout<<"Enter date (dd/mm/yyyy): ";
        cin>>d;
        if(d<"01/01/2010"||d>"31/12/2030"){
            cout<<"Invalid date\n";
            exit(0);
            }
    }
    void time(){
        cout<<"Enter time (hh:mm): ";
        cin>>t;
        if(t<"00:00"||t>"23:59"){
            cout<<"Invalid time\n";
            exit(0);
        }
    }
    void user_id(){
        cout<<"Operator User ID is: ";
        cin>>username[0];

    }
};

class Toll{
    public:
    int given_toll;
    void get_input(){
        cout<<"Enter the given amount: ";
        cin>>given_toll;
    }
    virtual void toll_calculate()=0;
    virtual void toll_change()=0;
    virtual void search_by_reg()=0;
    virtual void search_by_operator()=0;
    virtual void search_by_date_range()=0;
};

class Bus: public Vehicle, public Toll{
    int s;

    struct TollRecord{
        string date;
        string time;
        string amount;
        string operatorName;
        string reg_no;
    };

    map<string, vector<TollRecord>>busRecords, opRecords;

    bool is_within_date_range(const string& start_date, const string& end_date, const string& record_date) {
        return (start_date <= record_date && record_date <= end_date);
    }

    public:

    int num_bus=0, bus_toll=0, toll=500;

    void seats(){
        cout<<"Number of seats in the bus: ";
        cin>>s;
        cout<<"\n";
    }

    void toll_calculate(){
        if(given_toll<toll)
            cout<<"Insufficient Balance\n\n";
        else{
            TollRecord busrecord={d, t, to_string(toll), username[0], reg_no};
            busRecords[reg_no].push_back(busrecord);

            TollRecord oprecord={d, t, to_string(toll), username[0], reg_no};
            opRecords[username[0]].push_back(oprecord);

            cout<<"Return Amount: "<<given_toll-toll<<"\n";
            cout<<"Toll collection is successful.\n\n";

            num_bus++;
            bus_toll=bus_toll+toll;
        }
    }
    void toll_change(){
        cout<<"Change the toll amount for bus: ";
        cin>>toll;
    }
    void search_by_reg(){
        string searchreg;
        cout<<"Enter the registration number of the bus: ";
        cin>>searchreg;

        if(busRecords.find(searchreg)!=busRecords.end()){
            cout<<"\nDate\t\tTime\tAmount\tOperator\n";
            for(const auto &busrecord: busRecords[searchreg]){
                cout<<busrecord.date<<"\t"<<busrecord.time<<"\t"<<busrecord.amount<<"\t"<<busrecord.operatorName<<"\n";
            }
            cout<<"\n";
        }
        else
            cout<<"Registration number not found.\n\n";
    }
    void search_by_operator(){
        string searchop;
        cout<<"Enter the username of the operator: ";
        cin>>searchop;

        if(opRecords.find(searchop)!=opRecords.end()){
            cout<<"\nDate\t\tTime\tAmount\tRegistration No.\n";
            for(const auto &oprecord: opRecords[searchop]){
                cout<<oprecord.date<<"\t"<<oprecord.time<<"\t"<<oprecord.amount<<"\t"<<oprecord.reg_no<<"\n";
            }
            cout<<"\n";
        }
        else
            cout<<"Username not found.\n\n";
    }

    void search_by_date_range(){
        string start_date, end_date;

        cout<<"Enter start date (dd/mm/yyyy): ";
        cin>>start_date;

        cout<<"Enter end date (dd/mm/yyyy): ";
        cin>>end_date;

        cout<<"\nDate\t\tTime\tAmount\tReg. No.\tOperator\n";

        for (const auto& entry : busRecords) {
            const auto& reg_no = entry.first;
            const auto& records = entry.second;
            for (const auto& record : records) {
                if(is_within_date_range(start_date, end_date, record.date)) {
                    cout << record.date << "\t" << record.time << "\t" << record.amount << "\t" << record.reg_no << "\t" << record.operatorName << "\n";
                }
            }
        }
        cout <<"\n";
    }
};

class Truck: public Vehicle, public Toll{
    int w, h;

    struct TollRecord{
        string date;
        string time;
        string amount;
        string operatorName;
        string reg_no;
    };

    map<string, vector<TollRecord>>truckRecords, opRecords;

    bool is_within_date_range(const string& start_date, const string& end_date, const string& record_date) {
        return (start_date <= record_date && record_date <= end_date);
    }

    public:

    int num_truck=0, truck_toll=0, toll=400;

    void weight(){
        cout<<"Weight of the truck in kg: ";
        cin>>w;
        if(w>2000){
            cout<<"Maximum weight exceeded\n";
            exit(0);
        }
    }
    void height(){
        cout<<"Height of the truck in feet: ";
        cin>>h;
        if(h>15){
            cout<<"Maximum height exceeded\n";
            exit(0);
        }
    }
    void toll_calculate(){
        if(given_toll<toll)
            cout<<"Insufficient Balance\n\n";
        else{
            TollRecord truckrecord={d, t, to_string(toll), username[0], reg_no};
            truckRecords[reg_no].push_back(truckrecord);

            TollRecord oprecord={d, t, to_string(toll), username[0], reg_no};
            opRecords[username[0]].push_back(oprecord);

            cout<<"Return Amount: "<<given_toll-toll<<"\n";
            cout<<"Toll collection is successful.\n\n";

            num_truck++;
            truck_toll=truck_toll+toll;
        }
    }
    void toll_change(){
        cout<<"Change the toll amount for truck: ";
        cin>>toll;
    }

    void search_by_reg(){
        string searchreg;
        cout<<"Enter the registration number of the truck: ";
        cin>>searchreg;

        if(truckRecords.find(searchreg)!=truckRecords.end()){
            cout<<"\nDate\t\tTime\tAmount\tOperator\n";
            for(const auto &truckrecord: truckRecords[searchreg]){
                cout<<truckrecord.date<<"\t"<<truckrecord.time<<"\t"<<truckrecord.amount<<"\t"<<truckrecord.operatorName<<"\n";
            }
            cout<<"\n";
        }
        else
            cout<<"Registration number not found.\n\n";
    }

    void search_by_operator(){
        string searchop;
        cout<<"Enter the username of the operator: ";
        cin>>searchop;

        if(opRecords.find(searchop)!=opRecords.end()){
            cout<<"\nDate\t\tTime\tAmount\tRegistration No.\n";
            for(const auto &oprecord: opRecords[searchop]){
                cout<<oprecord.date<<"\t"<<oprecord.time<<"\t"<<oprecord.amount<<"\t"<<oprecord.reg_no<<"\n";
            }
            cout<<"\n";
        }
        else
            cout<<"Username not found.\n\n";
    }
    void search_by_date_range(){
        string start_date, end_date;

        cout<<"Enter start date (dd/mm/yyyy): ";
        cin>>start_date;

        cout<<"Enter end date (dd/mm/yyyy): ";
        cin>>end_date;

        cout<<"\nDate\t\tTime\tAmount\tReg. No.\tOperator\n";

        for (const auto& entry : truckRecords) {
            const auto& reg_no = entry.first;
            const auto& records = entry.second;
            for (const auto& record : records) {
                if(is_within_date_range(start_date, end_date, record.date)) {
                    cout << record.date << "\t" << record.time << "\t" << record.amount << "\t" << record.reg_no << "\t" << record.operatorName << "\n";
                }
            }
        }
        cout <<"\n";
    }
};

class Car: public Vehicle, public Toll{
    string name;

    struct TollRecord{
        string date;
        string time;
        string amount;
        string operatorName;
        string reg_no;
    };

    map<string, vector<TollRecord>>carRecords, opRecords;

    bool is_within_date_range(const string& start_date, const string& end_date, const string& record_date) {
        return (start_date <= record_date && record_date <= end_date);
    }

    public:

    int num_car=0, car_toll=0, toll=150;;

    void owner(){
        cout<<"Name of the owner: ";
        cin>>name;
        cout<<"\n";
    }
    void toll_calculate(){
        if(given_toll<toll)
            cout<<"Insufficient Balance\n\n";
        else{
            TollRecord carrecord={d, t, to_string(toll), username[0], reg_no};
            carRecords[reg_no].push_back(carrecord);

            TollRecord oprecord={d, t, to_string(toll), username[0], reg_no};
            opRecords[username[0]].push_back(oprecord);

            cout<<"Return Amount: "<<given_toll-toll<<"\n";
            cout<<"Toll collection is successful.\n\n";

            num_car++;
            car_toll=car_toll+toll;
        }
    }
    void toll_change(){
        cout<<"Change the toll amount for car: ";
        cin>>toll;
    }
    void search_by_reg(){
        string searchreg;
        cout<<"Enter the registration number of the car: ";
        cin>>searchreg;

        if(carRecords.find(searchreg)!=carRecords.end()){
            cout<<"\nDate\t\tTime\tAmount\tOperator\n";
            for(const auto &carrecord: carRecords[searchreg]){
                cout<<carrecord.date<<"\t"<<carrecord.time<<"\t"<<carrecord.amount<<"\t"<<carrecord.operatorName<<"\n";
            }
            cout<<"\n";
        }
        else
            cout<<"Registration number not found.\n\n";
    }

    void search_by_operator(){
        string searchop;
        cout<<"Enter the username of the operator: ";
        cin>>searchop;

        if(opRecords.find(searchop)!=opRecords.end()){
            cout<<"\nDate\t\tTime\tAmount\tRegistration No.\n";
            for(const auto &oprecord: opRecords[searchop]){
                cout<<oprecord.date<<"\t"<<oprecord.time<<"\t"<<oprecord.amount<<"\t"<<oprecord.reg_no<<"\n";
            }
            cout<<"\n";
        }
        else
            cout<<"Username not found.\n\n";
    }

    void search_by_date_range(){
        string start_date, end_date;

        cout<<"Enter start date (dd/mm/yyyy): ";
        cin>>start_date;

        cout<<"Enter end date (dd/mm/yyyy): ";
        cin>>end_date;

        cout<<"\nDate\t\tTime\tAmount\tReg. No.\tOperator\n";

        for (const auto& entry : carRecords) {
            const auto& reg_no = entry.first;
            const auto& records = entry.second;
            for (const auto& record : records) {
                if(is_within_date_range(start_date, end_date, record.date)) {
                    cout << record.date << "\t" << record.time << "\t" << record.amount << "\t" << record.reg_no << "\t" << record.operatorName << "\n";
                }
            }
        }
        cout <<"\n";
    }
};

int main(){

    ofstream fout;
    string filename;
    cout<<"Enter File Name to save Statistics (Please use one word): ";
    cin>>filename;
    cout<<"\n";
    fout.open(filename+".txt");

    int option;
    Operator o;
    Bus b;
    Truck t;
    Car c;

    for(;;){
        cout<<"*Toll Plaza: Operator*\n\n";
        cout<<"1. Login\n";
        cout<<"2. Register\n";
        cout<<"3. Exit\n";
        cout<<"\nEnter your option: ";
        cin>>option;
        cout<<endl;
        if(option==3)break;
        switch(option){
        case 1:
        if(o.login()==1){
            for(;;){
                cout<<"*****Toll Plaza Menu*****\n\n";
                cout<<"1. Bus\n";
                cout<<"2. Truck\n";
                cout<<"3. Car\n";
                cout<<"4. Search\n";
                cout<<"5. Statistics\n";
                cout<<"6. Toll Settings\n";
                cout<<"7. Save and Logout\n";
                cout<<"\nEnter your option: ";
                cin>>option;
                cout<<endl;
                if(option==7)break;
                switch(option){
                case 1:
                    b.regi_no();
                    b.date();
                    b.time();
                    b.user_id();
                    b.seats();
                    b.get_input();
                    b.toll_calculate();
                    break;
                 case 2:
                    t.regi_no();
                    t.date();
                    t.time();
                    t.user_id();
                    t.weight();
                    t.height();
                    t.get_input();
                    t.toll_calculate();
                    break;
                case 3:
                    c.regi_no();
                    c.date();
                    c.time();
                    c.user_id();
                    c.owner();
                    c.get_input();
                    c.toll_calculate();
                    break;
                case 4:
                    for(;;){
                        cout<<"*****Toll Plaza: Search*****\n\n";
                        cout<<"1. Vehicle\n";
                        cout<<"2. Date to date\n";
                        cout<<"3. Operator\n";
                        cout<<"4. Back\n";
                        cout<<"\nEnter your option: ";
                        cin>>option;
                        cout<<endl;
                        if(option==4)break;
                        switch(option){
                        case 1:
                            for(;;){
                                cout<<"*****Toll Plaza: Search: Vehicle*****\n\n";
                                cout<<"1. Bus\n";
                                cout<<"2. Truck\n";
                                cout<<"3. Car\n";
                                cout<<"4. Back\n";
                                cout<<"\nEnter your option: ";
                                cin>>option;
                                cout<<endl;
                                if(option==4)break;
                                switch(option){
                                    case 1: b.search_by_reg();break;
                                    case 2: t.search_by_reg();break;
                                    case 3: c.search_by_reg();break;
                                }
                            }
                            break;
                        case 2:
                             for(;;){
                                cout<<"*****Toll Plaza: Search: Date to Date*****\n\n";
                                cout<<"1. Bus\n";
                                cout<<"2. Truck\n";
                                cout<<"3. Car\n";
                                cout<<"4. Back\n";
                                cout<<"\nEnter your option: ";
                                cin>>option;
                                cout<<endl;
                                if(option==4)break;
                                switch(option){
                                    case 1: b.search_by_date_range();break;
                                    case 2: t.search_by_date_range();break;
                                    case 3: c.search_by_date_range();break;
                                }
                            }
                            break;
                        case 3:
                            for(;;){
                                cout<<"*****Toll Plaza: Search: Operator*****\n\n";
                                cout<<"1. Bus\n";
                                cout<<"2. Truck\n";
                                cout<<"3. Car\n";
                                cout<<"4. Back\n";
                                cout<<"\nEnter your option: ";
                                cin>>option;
                                cout<<endl;
                                if(option==4)break;
                                switch(option){
                                    case 1: b.search_by_operator();break;
                                    case 2: t.search_by_operator();break;
                                    case 3: c.search_by_operator();break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                case 5:
                    cout<<"Vehicle\t\Number\tAmount\n";
                    cout<<"Bus\t"<<b.num_bus<<"\t"<<b.bus_toll<<"\n";
                    cout<<"Truck\t"<<t.num_truck<<"\t"<<t.truck_toll<<"\n";
                    cout<<"Car\t"<<c.num_car<<"\t"<<c.car_toll<<"\n\n";
                    cout<<"Total Amount: "<<(b.bus_toll)+(t.truck_toll)+(c.car_toll)<<"\n\n";

                    fout<<"Vehicle\t\Number\tAmount\n";
                    fout<<"Bus\t"<<b.num_bus<<"\t"<<b.bus_toll<<"\n";
                    fout<<"Truck\t"<<t.num_truck<<"\t"<<t.truck_toll<<"\n";
                    fout<<"Car\t"<<c.num_car<<"\t"<<c.car_toll<<"\n\n";
                    fout<<"Total Amount: "<<(b.bus_toll)+(t.truck_toll)+(c.car_toll)<<"\n\n";

                    fout.close();

                    break;
                case 6:
                    if(o.login()==1){
                        b.toll_change();
                        t.toll_change();
                        c.toll_change();
                    }
                    cout<<"\n";
                    break;
                }
            }
        }
        break;
        case 2:o.addOperator();break;
        }
    }
    return 0;
}
