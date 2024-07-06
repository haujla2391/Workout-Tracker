//
//  exercise.cpp
//  Workout Grader
//
//  Created by Harman  Aujla on 7/4/24.
//

#include "exercise.h"

Exercises::Exercises(){
    name = "";
    setsAndReps = vector<pair<int,int> >();
}

Exercises::Exercises(string Aname, vector<pair<int,int> > AsetsAndReps){
    name = Aname;
    setsAndReps = AsetsAndReps;
}

void Exercises::setName(string aName){
    name = aName;
}

void Exercises::setSetsAndReps(vector<pair<int,int> > aSetsAndReps){
    setsAndReps = aSetsAndReps;
}
