#include <iostream>
#include <string>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

class Donate{
    private:
        string number;
        string date;
        string current_date;
        int quantity;
        string name;
        string b_g;
        int age;
        int a_stock = 0, b_stock = 0, ab_stock = 0, o_stock = 0;

    public:
        
        int login(){
            cout << "Enter number: ";
            cin >> number;
            cout <<endl<< "Enter your date of birth: ";
            cin >> date;
            cout <<endl <<"Enter quantity: ";
            cin >> quantity;
            cout << endl<<"Enter name: ";
            cin >> name;
            cout << endl<<"Enter blood group: ";
            cin >> b_g;
            for (auto &c : b_g) c = toupper(c);
            return 1;
        }

        int checking(){
            if(number.length() < 10){
                cout << "Number should have at least 10 digits" << endl;
            }
            if(quantity < 50){
                cout << "Increase the quantity to at least 50 ml." << endl;
            }
            if(number.length()>=10){
                cout<<"YOUR DONATION ID IS ---> "<<name<<number.substr(7,9);
            }
        }

        void set_current_date() {
            time_t now = time(0);
            tm *ltm = localtime(&now);
            char buf[11];
            strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
            current_date = buf;
        }
        int age_cal(){
            int dob_year=stoi(date.substr(0,4));
            int curr_year=stoi(current_date.substr(0,4));
            age=curr_year-dob_year;
            if(age>=18 && age<=50){
                cout<<endl<<"You can donate";
            }
            else{
                cout<<endl<<"You are not eligible for donation";
            }
        }
        void load_stock() {
            std::ifstream fin("stock.csv");
            char comma;
            if (fin) {
                fin >> a_stock >> comma >> b_stock >> comma >> ab_stock >> comma >> o_stock;
            }
            fin.close();
        }
        void save_stock() {
            std::ofstream fout("stock.csv");
            fout << a_stock << "," << b_stock << "," << ab_stock << "," << o_stock;
            fout.close();
        }
        void stock(){
            bool eligible = true;
            if (age < 18) {
                cout << endl << "Stock not updated: Age less than 18." << endl;
                eligible = false;
            }
            if(quantity < 50){
                cout << endl << "Insufficient quantity.";
                eligible = false;
            }
             if(number.length() < 10){
                eligible=false;
            }
            string bg_upper = b_g;
            for (auto &c : bg_upper) c = toupper(c);
            if (bg_upper != "A" && bg_upper != "B" && bg_upper != "AB" && bg_upper != "O") {
                cout << endl << "Invalid blood group." << endl;
                eligible = false;
            }
            if (!eligible) return;
            if (bg_upper == "A") {
                a_stock += quantity;
            } else if (bg_upper == "B") {
                b_stock += quantity;
            } else if (bg_upper == "AB") {
                ab_stock += quantity;
            } else if (bg_upper == "O") {
                o_stock += quantity;
            }
            save_stock();
            cout << endl << "A STOCK --> " << a_stock << " ml" << endl;
            cout << "B STOCK --> " << b_stock << " ml" << endl;
            cout << "AB STOCK --> " << ab_stock << " ml" << endl;
            cout << "O STOCK --> " << o_stock << " ml" << endl;
        }
        void add_hos(){
            string name, contact, address;
            cout << "Enter hospital name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter hospital contact: ";
            getline(cin, contact);
            cout << "Enter hospital address: ";
            getline(cin, address);
            std::ofstream fout("Hospital.csv", std::ios::app);
            fout << name << "," << contact << "," << address << "\n";
            fout.close();
            cout << "Hospital data saved successfully!" << endl;
        }
        void hospital(){
            std::ifstream fin("Hospital.csv");
            string line;
            cout << "Hospital Records:\n";
            while (getline(fin, line)) {
                cout << line << endl;
            }
            fin.close();
        }
        void request_blood(){
            string group;
            cout << "Enter blood group to request (A, B, AB, O): ";
            cin >> group;
            for (auto &c : group) c = toupper(c);
            int how_much;
            cout << "Enter quantity to request: ";
            cin >> how_much;
            bool available = false;
            if (group == "A" && a_stock >= how_much) {
                available = true;
                a_stock -= how_much;
            } else if (group == "B" && b_stock >= how_much) {
                available = true;
                b_stock -= how_much;
            } else if (group == "AB" && ab_stock >= how_much) {
                available = true;
                ab_stock -= how_much;
            } else if (group == "O" && o_stock >= how_much) {
                available = true;
                o_stock -= how_much;
            }
            if (available) {
                save_stock();
                cout << "Request successful! " << how_much << " ml of " << group << " blood provided." << endl;
            } else {
                cout << "Insufficient stock for " << group << ". Request cannot be fulfilled." << endl;
            }
        }
        void view_stock() {
            cout << endl << "A STOCK --> " << a_stock << " ml" << endl;
            cout << "B STOCK --> " << b_stock << " ml" << endl;
            cout << "AB STOCK --> " << ab_stock << " ml" << endl;
            cout << "O STOCK --> " << o_stock << " ml" << endl;
        }

};

int main(){
    Donate d1;
    d1.load_stock();
    int choice;
    do {
        cout << "\n========= BLOOD BANK MENU =========" << endl;
        cout << "1. Donate Blood" << endl;
        cout << "2. View Stock" << endl;
        cout << "3. Add Hospital" << endl;
        cout << "4. View Hospital" << endl;
        cout << "5. Request Blood" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        cin.ignore();
        switch(choice) {
            case 1:
                d1.login();
                d1.set_current_date();
                d1.checking();
                d1.age_cal();
                d1.stock();
                break;
            case 2:
                d1.view_stock();
                break;
            case 3:
                d1.add_hos();
                break;
            case 4:
                d1.hospital();
                break;
            case 5:
                d1.request_blood();
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while(choice != 6);
    return 0;
}
