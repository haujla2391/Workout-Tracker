//
//  main.cpp
//  Workout Grader
//
//  Created by Harman  Aujla on 5/17/24.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include "exercise.h"
using namespace std;

void AddExercise(vector<Exercises> &data, string &name, vector<pair<int, int> > &setsreps){
    Exercises newExercise(name, setsreps);
    data.push_back(newExercise);
}

void display(vector<Exercises> &data){
    for(int i = 0; i < data.size(); ++i){
        Exercises currExercise = data[i];
        cout << "Exercise: " << currExercise.getName() << endl;
        for(int j = 0; j < currExercise.getSetsReps().size(); ++j){
            pair<int, int> curr_set = currExercise.getSetsReps()[j];
            cout << "Set " << curr_set.first << ": " << curr_set.second << " reps" << endl;
        }
        cout << endl;
    }
}

bool search(vector<Exercises> &data, string &name, Exercises &found){
    for(int i = 0; i < data.size(); ++i){
        Exercises curr = data[i];
        if(curr.getName() == name){
            found = curr;
            return true;
        }
    }
    return false;
}

void Save_Data(vector<Exercises> &data, string &outputfile){
    ofstream outFile(outputfile);
    for(int i = 0; i < data.size(); ++i){
        Exercises currExercise = data[i];
        outFile << "Exercise: " << currExercise.getName() << endl;
        for(int j = 0; j < currExercise.getSetsReps().size(); ++j){
            pair<int, int> curr_set = currExercise.getSetsReps()[j];
            outFile << "Set " << curr_set.first << ": " << curr_set.second << " reps" << endl;
        }
        outFile << endl;
    }
    outFile.close();
}

vector<Exercises> Load_Data(string& inputfile){
    vector<Exercises> loaded_data;
    ifstream inputFile(inputfile);
    string line, name;
    vector<pair<int, int> > setsreps;
    while(getline(inputFile, line)){
        if(line.find("Exercise:") != string::npos){
            if (!name.empty()) {
                loaded_data.push_back(Exercises(name, setsreps));
                setsreps.clear();
            }
            name = line.substr(10);
        } else if(line.find("Set") != string::npos){
            istringstream iss(line);
            string temp;
            int set, reps;
            if (iss >> temp >> set >> temp >> reps >> temp) {
                setsreps.push_back(make_pair(set, reps));
            }
        }
    }
    if (!name.empty()) {
        loaded_data.push_back(Exercises(name, setsreps));
    }
    inputFile.close();
    return loaded_data;
}

int main(int argc, char* argv[]) {
    
    string datafile = argv[1];
    
    vector<Exercises> data = Load_Data(datafile);
    bool cont = true;
    while(cont){
        int choice;
        cout << "1. Add Exercise\n2. Display All Exercises\n3. Display Exercise Data\n4. Save and Exit\nEnter Choice: ";
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number.\n";
            continue;
        }
        
        switch(choice) {
            case 1: {
                string name;
                vector<pair<int, int> > exerciseData;
                cout << "Enter exercise name: ";
                cin.ignore();
                getline(cin, name);
                int i = 1, reps;
                while(true){
                    cout << "Enter reps for set " << i << " (enter 0 to stop): ";
                    cin >> reps;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a number.\n";
                        continue;
                    }
                    if(reps == 0){break;}
                    exerciseData.push_back(make_pair(i,reps));
                    ++i;
                }
                AddExercise(data, name, exerciseData);
                break;
            }
            case 2: {
                display(data);
                break;
            }
            case 3: {
                string name;
                cout << "Enter exercise name: ";
                cin.ignore();
                getline(cin, name);
                Exercises found;
                if(search(data, name, found)){
                    cout << "Exercise: " << found.getName() << endl;
                    for(int j = 0; j < found.getSetsReps().size(); ++j){
                        pair<int, int> curr_set = found.getSetsReps()[j];
                        cout << "Set " << curr_set.first << ": " << curr_set.second << " reps" << endl;
                    }
                } else{
                    cout << "Exercise not found\n";
                }
                break;
            }
            case 4: {
                Save_Data(data, datafile);
                cont = false;
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}
/*
 This will take entries from users to build their workout plan and add exercises with sets and reps to help them track their lifts. Output the lift sets and reps on a output file.
 */
