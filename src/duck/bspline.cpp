//
// Created by jakub on 5/30/16.
//

#include "bspline.h"

using namespace std;
using namespace glm;

BSpline::BSpline(std::vector<glm::vec3> controlPoints):
        controlPoints(controlPoints){
    buildCurve();
}

BSpline::~BSpline() {

}

void BSpline::buildCurve() {
    int n = controlPoints.size();

    int knotCount = n + DEGREE +1 ;

    for(int i = 0; i < knotCount; i++){
        knotVector.push_back(i);
    }

    t_max = getKnotMax();
    t_min = getKnotMin();

    t = t_min;
}

glm::vec3 BSpline::computeBSpline(float dt) {
    t += dt;

    float x,y,z;
    x = y = z = 0;
    for(unsigned int i = 0; i < controlPoints.size(); i++){
        float bsplineBasisValue = bsplineRecurvise(t, DEGREE, i);

        const vec3& pos = controlPoints[i];
        x += pos.x * bsplineBasisValue;
        y += pos.y * bsplineBasisValue;
        z += pos.z * bsplineBasisValue;
    }
    return vec3(x,y,z);
}

float BSpline::bsplineRecurvise(float t, int n, int i) {
    if(t == knotVector[0] && i == 0) return 1.0f;
    if(t == knotVector[knotVector.size()-1]
       && i == knotVector.size() - n - 2) return 1.0f;

    if (n == 0){
        if(t >= knotVector[i] && t < knotVector[i+1])
            return 1;
        else
            return 0;
    }
    float leftRecursion = (t - knotVector[i]);
    float leftDenominator = (knotVector[i+n] - knotVector[i]);
    if(leftRecursion == 0 || leftDenominator == 0)
        leftRecursion = 0;
    else
        leftRecursion /= leftDenominator;

    float rightRecursion = knotVector[i+1+n] - t;
    float rightDenominator = (knotVector[i+1+n] - knotVector[i+1]);
    if(rightRecursion == 0 || rightDenominator == 0)
        rightRecursion = 0;
    else
        rightRecursion /= rightDenominator;

    leftRecursion *= bsplineRecurvise(t, n-1, i);
    rightRecursion *= bsplineRecurvise(t, n-1, i+1);

    return leftRecursion + rightRecursion;
}

float BSpline::getKnotMax(){
    int size = knotVector.size();
    int index = controlPoints.size();
    if(index >= size){
        return -1;
    }
    //return knotVector[index];
    return knotVector[size - 1];
}

float BSpline::getKnotMin(){
    int size = knotVector.size();
    int index = DEGREE;
    if(index >= size){
        return -1;
    }
    //return knotVector[index];
    return knotVector[0];
}