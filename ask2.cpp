//this program takes the number of the participants at a race
//for each of them it takes their current speed, the distace the have allready taveled, and their acceleration
//finally it takes the tottal lengh of the truck 
//all the variables are taken at runtime
//it uses a function to calculate sort and frint the racers from most to list liklly to win with their according number
//this function grates two vecton one for the times needed two finish and one for the according number of each racer
//then it usees three other function for the caclulation of the time, to short the arrays and to print the results


//#include "std_lib_facilities.h"


#include <iostream>
#include <vector>
#include<cmath>
using namespace std;


// error() simply disguises throws:
inline void error(const string& s)
{
    throw runtime_error(s);
}

// prints the shorted vectors (takes the num of racers and the vectors time, number by reference to again save tive and memmory)
void print_time_num( int racers, vector<double> &time, vector<int> &numbers){
    int i;
    cout << "\n\nThe drivers from most likely to list likely to win are:\n";
    for (i = 0; i < racers; i++){ //print message for each racer with theri number 
        cout << "Divers number " << numbers[i] + 1 << " with a time of " << time[i] << " sec" << endl;
    }                              // the + 1 is is so it starts from one and not zero 
}

// sorts the two vectors(takes num of racers and by reference the two vectors time, numbers)
void babblesort( int racers, vector<double> &time, vector<int> &numbers){
    int i,j;
    for ( i = 0 ; i < racers - 1; i++ ){ //useing babblesort
        for ( j = 0; j < racers - i - 1; j++){
            if ( time[j] > time[j+1] ){// sort with ascending order the time vector
                swap( time[j], time[j+1]);
                swap( numbers[j], numbers[j+1]);//follow with number vector to keep them linked
            }
        }
    } 
}


// calculates the time needed to finish the race (takes speed, acceraration, dist traveled, lengh og truck) 
double calc_time (double u, double a, double x, double l){ //takes arguments by value
    double d; //discriminant
    if (a == 0) return (l - x)/u; //if acceleration == 0 the racers is doing "eok"
    d = (u * u) + ( (2 * a) * ( l - x) ); //if not accelerating eok
    return ( -u + sqrt(d) ) / a ;
}


//this function calculates, sorts and prints the predictions using tree other functions
void calc_sort_print_predictions(int racers, vector<double> &speed, vector<double> &dinstance, vector<double> &accelaration, double lenght){
    //the vectors pass by reference to save time and memmory
    vector<double> time;
    vector<int> numbers;  //we create two vectors time and numbers that will store the time and the number of each racer
    int i;
    for ( i = 0; i < racers; i++){ //for evry racer we calclulate the time needed to finish
        time.push_back( calc_time(speed[i], accelaration[i], dinstance[i], lenght) );// by using the function calc_time
        numbers.push_back(i); // initialize the numbers vector with the according number
    }
    babblesort( racers, time, numbers);//call the fuction to sort the time vector and move the number vector item accordinly
    print_time_num( racers, time, numbers);//print the sorted recults
}


//main collects the veriables and calles the first fanction
int main(){
    int racers, i;
    double lenght, temp;
    vector<double> speed, distance, acceleration;
   try{//exception for char as racers or non possitive number
        cout << "How many racers are taking part at the race?\n>";
        cin >> racers;
        if (cin.fail() || !(racers > 0) ) throw racers; //if not valid throw the non valid variable
   }
   catch(int racers){//get the problematic value print error mesage and end programm
       cerr << "invalid inpute. Input must be an integer greater than zero\nYou gave " << racers << endl;
       error("invalid inpute (number or racers)\n");
   }
   for (i = 0; i < racers; i++){//get the info for each triver(for every driver)
       try{//exception for char as speed or negative number (dont accept racers stoped on truck)
            cout << "What is the current speed of driver number " << i + 1 << endl << '>';
            cin.clear(); //clearing cin
            cin.ignore(100, '\n'); //ignoring previous imputes
            cin >> temp;
            if (cin.fail() || !(temp > 0)) throw temp;
            speed.push_back(temp);
       }
       catch(double speed){// catch and hanle error
            cerr << "invalid inpute. Input must be an double greater than zero\nYou gave " << speed << endl;
            error("invalid inpute (current speed of driver)\n");
       }
       try{//exception for char as distance or negative number
           cout << "What the distance the diver number " << i + 1 << " has already traveled?\n>";
           cin.clear();
           cin.ignore(100, '\n');
           cin >> temp;
            if (cin.fail() || !(temp >= 0)) throw temp;
            distance.push_back(temp);
       }
       catch(double distance){//catch and handle error
           cerr << "invalid inpute. Input must be an double greater than zero\nYou gave " << distance << endl;
           error("invalid inpute (distance traveled)\n");
       }
       try{//exception for char as accelration or negative number
           cout << "What the acceleration of the driver number " << i + 1 << "\n>";
           cin.clear();
           cin.ignore(100, '\n');
           cin >> temp;
           if (cin.fail() || !(temp >= 0)) throw temp;
           acceleration.push_back(temp);
       }//catch and hanle error
       catch(double acceleration){
           cerr << "invalid inpute. Input must be an double greater than zero You gave " << acceleration << endl;
           error("invalid input (acceleration)");
       }
   }
   try{//exception for char as truck lenght or non positive number
       cout << "Finally plese give the tottal lenght of the truck\n>";
       cin.clear();
       cin.ignore(100, '\n');
       cin >> lenght;
       if (cin.fail() || !(lenght > 0)) throw lenght;
   }
   catch(double lenght){//catch and hanle error
       cerr << "invalid inpute. Input must be an double greater than zero\nYou gave " << lenght << endl;
       error("invalid input (tottal lenght)");
   }
   try{//exception to check if a distance taveled is biger than the tottal lenght (that mean he has alrady finished)
        for (i = 0; i < racers; i++ ){
            if (distance[i] >= lenght) throw distance[i];
        }
   }
   catch(double distance){//catch and handle error 
       cerr << "The dinstance allready traveled can not be equal or greater than the tottal lenght of the truck and you gave the dinstance (" << distance << ") which is not valid with the givern lenght\n";
       error("distance teveled biger/equal to total lenght");
   }
   calc_sort_print_predictions(racers, speed, distance, acceleration, lenght);//call the fanction whith the arguments (discription on top of function)
    
    //system("pause");
    return 0;
}
