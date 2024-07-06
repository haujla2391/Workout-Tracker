//
//  exercise.h
//  Workout Grader
//
//  Created by Harman  Aujla on 7/4/24.
//

#ifndef exercise_h
#define exercise_h

#include <vector>
using namespace std;

class Exercises{
public:
    Exercises();
    Exercises(string Aname, vector<pair<int,int> > AsetsAndReps);
    
    string getName() const {return name;}
    vector<pair<int,int> > getSetsReps() const {return setsAndReps;}
    
    void setName(string aName);
    void setSetsAndReps(vector<pair<int,int> > aSetsAndReps);
    
private:
    string name;
    vector<pair<int,int> > setsAndReps;
};

#endif /* exercise_h */
