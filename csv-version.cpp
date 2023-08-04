#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class flight
{
public:
    int id;
    flight(int x){                                          //constructor
        id = x;
    }

    int check_pref(char *from_d, char *to_d, char *day){              //internal function to check if the user preferences match with the flight properties
        vector<string> flight_props;
        string flight_line;
        flight_props.clear();

        ifstream properties("flight_objects_prop.csv");
        if(properties.is_open()){
            int current_line = 0;
            while(getline(properties, flight_line)){         //navigate to the line of the flight object
                current_line++;
                if(current_line - 1 == id){
                    break;
                }
            }
            stringstream ss(flight_line);                    //used to help split the line string into words
            string prop_word;
            while(getline(ss, prop_word, ',')){              //to store each column data of the row
                flight_props.push_back(prop_word);
            }

            if((flight_props[1] == from_d) && (flight_props[2] == to_d)){       //checking if the user preferences match with the flight properties
                for(int i = 4; i <= 10; i++){
                    if(flight_props[i] == day){
                        cout << "\nFlight " << flight_props[0] << " has been identified. Press " << id << " to select it.\n";
                        properties.close();
                        return 1;
                    }
                }
            }
            return 0;
        }
        else {
            cout << "Could not open CSV file.";
            return -1;
        }
    }

    void book_ticket(char *name, char *day){
        ifstream passengers_read("passengers.csv");             //file opened for reading
        string pass_names;
        vector<string> passengers;
        if(passengers_read.is_open()){
            while(getline(passengers_read, pass_names)){
                passengers.push_back(pass_names);                   //storing each line from csv file in a string vector
            }

            passengers_read.close();
        }
        else {
            cout << "\nCould not access passenger list.";
        }

        ofstream passengers_write("passengers.csv");             //file opened for writing

        if(passengers_write.is_open()){
            int name_line_number = id + (id - 1);
            int day_line_number = id + (id - 1) + 1;
            for(int i = 0; i < passengers.size(); i++){
                if(i == name_line_number - 1){
                    stringstream ss(passengers[i]);
                    string temp;
                    vector<string> temp_vector;
                    while(getline(ss, temp, ',')){
                        temp_vector.push_back(temp);
                    }
                    for(int i = 0; i < temp_vector.size(); i++){
                        if(temp_vector[i] == "0"){
                            temp_vector[i] = name;                      //replace zero with the passenger name
                            break;
                        }
                    }
                    string temp2;
                    for(int i = 0; i < temp_vector.size(); i++){
                        temp2 = temp2 + temp_vector[i] + ",";                 //combine all strings from the temp vector into a single string temp2
                    }

                    passengers_write << temp2 << "\n";                  //write the combined string temp2 to the csv file
                }
                else if(i == day_line_number - 1){
                    stringstream ss(passengers[i]);
                    string temp3;
                    vector<string> temp_vector3;
                    while(getline(ss, temp3, ',')){
                        temp_vector3.push_back(temp3);
                    }
                    for(int i = 0; i < temp_vector3.size(); i++){
                        if(temp_vector3[i] == "0"){
                            temp_vector3[i] = day;                      //replace zero with the day given by the passenger
                            break;
                        }
                    }
                    string temp4;
                    for(int i = 0; i < temp_vector3.size(); i++){
                        temp4 = temp4 + temp_vector3[i] + ",";                //combine all strings into one
                    }

                    passengers_write << temp4 << "\n";
                }
                else {
                    passengers_write << passengers[i] << "\n";            //skipping all other lines
                }                                                         //these lines are written back to the file as they were
            }
            passengers_write.close();
        }
        else{
            cout << "\nCould not access passenger list.";
        }
    }

    void generate_ticket(char *name, char *day){
        ifstream ticket("flight_objects_prop.csv");
        vector<string> details_lines;
        string line_string;
        if(ticket.is_open()){
            while(getline(ticket, line_string)){
                details_lines.push_back(line_string);                //obtaining the lines from csv file
            }
        }
        else{
            cout << "\nCould not open file.";
        }

        vector<string> details_main;
        string main_string;

        int current_line = 0;
        for(int i = 0; i < details_lines.size(); i++){
            current_line++;
            if(current_line - 1 == id){
                stringstream ss(details_lines[i]);
                while(getline(ss, main_string, ',')){
                    details_main.push_back(main_string);             //obtaining the line containing the required data
                }
            }
        }

        char *day_full;
        if(day == "mo"){
            day_full = "Monday";
        }
        else if(day == "tu"){
            day_full = "Tuesday";
        }
        else if(day == "we"){
            day_full = "Wednesday";               //obtaining the text to be displayed from user selected day
        }
        else if(day == "th"){
            day_full = "Thursday";
        }
        else if(day == "fr"){
            day_full = "Friday";
        }
        else if(day == "sa"){
            day_full = "Saturday";
        }
        else if(day == "su"){
            day_full = "Sunday";
        }

           //printing ticket after retrieving data from the CSV file
        cout << "---------------------------\n\n";
        cout << "Name: " << name << endl;
        cout << "\nFrom: " << details_main[1] << "\tTo: " << details_main[2];
        cout << "\nFlight name: " << details_main[0];
        cout << "\nDay: " << day_full;
        cout << "\nTime: " << details_main[3];
        cout << "\n\n\tThank you for choosing to fly with us!";
    }
};

int main(){
    char name[15], *from, *to, *day;
    int from_num, to_num, day_num;

    flight A1(1), A2(2), A3(3), A4(4);                                      //flight objects declared

    cout << "\tWelcome to Random Airlines\n";
    cout << "---------------------------\n";

    cout << "Please enter your name: ";
    cin >> name;

    label1:
    cout << "\nPlease select departure city:\n";
    cout << "1 for Mumbai\n2 for New York\n3 for Dubai\n4 for Berlin\n";
    cin >> from_num;
    switch(from_num)
    {
    case 1:
        from = "Mumbai"; break;
    case 2:
        from = "New York"; break;
    case 3:
        from = "Dubai"; break;
    case 4:
        from = "Berlin"; break;
    default:
        cout << "Invalid input";
        goto label1;
    }

    label2:
    cout << "Please select city for arrival:\n";
    cout << "1 for Dubai\n2 for London\n3 for Mumbai\n4 for New York\n";
    cin >> to_num;
    switch(to_num)
    {
    case 1:
        to = "Dubai"; break;
    case 2:
        to = "London"; break;
    case 3:
        to = "Mumbai"; break;
    case 4:
        to = "New York"; break;
    default:
        cout << "Invalid input";
        goto label2;
    }

    label3:
    cout << "Please select the day of departure:\n";
    cout << "1 for Monday\n2 for Tuesday\n3 for Wednesday\n4 for Thursday\n5 for Friday\n6 for Saturday\n7 for Sunday\n";
    cin >> day_num;
    switch(day_num)
    {
    case 1:
        day = "mo"; break;
    case 2:
        day = "tu"; break;
    case 3:
        day = "we"; break;
    case 4:
        day = "th"; break;
    case 5:
        day = "fr"; break;
    case 6:
        day = "sa"; break;
    case 7:
        day = "su"; break;
    default:
        cout << "Invalid input, please enter again.";
        goto label3;
    }

    flight flights[4] = {A1, A2, A3, A4};                                 //array of flight objects

    int flag = 0;                                                         //flag variable indicating whether one or more flights have been matched
    cout << "Here are some matches:\n";
    int flag_arr[4] = {0,0,0,0};
    for(int i = 0; i < 4; i++){
        int flag2 = flights[i].check_pref(from, to, day);
        if(flag2 == 1){
            flag_arr[i] = flights[i].id;
            flag = 1;
        }
    }
    if(flag == 0){                                                         //if no flights set the flag variable true
        cout << "\nNo flights were found matching your preferences. Please make a different selection.\n";
        goto label1;
    }

    label4:
    int choice = 0;
    cout << "Please enter your choice:";
    cin >> choice;
    flag = 0;
    for(int i = 0; i < 4; i++){
        if(choice == flag_arr[i]){
            flag = 1;
            break;
        }
    }
    if(flag == 0){
        cout << "\nInvalid selection. Please select again.\n";
        goto label4;
    }
    flights[choice - 1].book_ticket(name, day);

    flights[choice - 1].generate_ticket(name, day);
    }
