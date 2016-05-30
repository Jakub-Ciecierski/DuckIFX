//
// Created by jakub on 5/30/16.
//

#ifndef DUCK_BSPLINE_H
#define DUCK_BSPLINE_H

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class BSpline {
private:
    std::vector<float> knotVector;
    std::vector<glm::vec3> controlPoints;

    const int DEGREE = 3;

    void buildCurve();

    float bsplineRecurvise(float t, int n, int i);

    float getKnotMax();
    float getKnotMin();
public:
    float t;
    float t_max;
    float t_min;

    BSpline(std::vector<glm::vec3> controlPoints);

    ~BSpline();

    glm::vec3 computeBSpline(float t);
};


#endif //DUCK_BSPLINE_H
