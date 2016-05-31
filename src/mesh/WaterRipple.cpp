//
// Created by anna on 30.05.2016.
//

#include "WaterRipple.h"

WaterRipple::WaterRipple() {

}

WaterRipple::WaterRipple(int vertexX, int vertexY, int waterX, int waterY)
        : vertexX(vertexX), vertexY(vertexY), waterX(waterX), waterY(waterY){
    //initialize d, ripple, prev_ripple, norlams matrixes : RIPPLE_SIZE x RIPPLE_SIZE
    float l;
    for (int i = 0; i < RIPPLE_SIZE; i++)
        for (int j = 0; j < RIPPLE_SIZE; j++) {
            //TODO: check correctness of value of l
            float distX = j/(RIPPLE_SIZE-1.0f)*2.0f;
            float distY = i/(RIPPLE_SIZE-1.0f)*2.0f;
            distX = (distX <= 1)? distX : 1-distX;
            distY = (distY <= 1)? distY : 1-distY;
            l = glm::min(distX, distY);
            d[i][j] = 0.95f * glm::min(1.0f, l / 0.2f);

            rippleHeights[i][j] = 0;
            prev_rippleHeights[i][j]=0;
        }
    //heigh distortion
    rippleHeights[(RIPPLE_SIZE)/2][(RIPPLE_SIZE)/2] = 0.025f;
    A = (c*c*dt*dt)/(h*h);
    B = 2 - (4*A);
}

void WaterRipple::UpdateRipple() {
    //here update A and B if dt/c/h will be changed during program execution

    float middleValues = 0;
    //float a1, a2, a3, a4;
    for (int i = 1; i < RIPPLE_SIZE-1; i++) {
        for (int j = 1; j < RIPPLE_SIZE-1; j++) {
//            a1 = (i == (RIPPLE_SIZE) - 1) ? 0 : rippleHeights[i + 1][j];
//            a2 = (i == 0) ? 0 : rippleHeights[i - 1][j];
//            a3 = (j == (RIPPLE_SIZE) - 1) ? 0 : rippleHeights[i][j + 1];
//            a4 = (j == 0) ? 0 : rippleHeights[i][j - 1];
//            middleValues = a1 + a2 + a3 + a4;
            middleValues = rippleHeights[i + 1][j] + rippleHeights[i - 1][j] + rippleHeights[i][j + 1] + rippleHeights[i][j - 1];
            tmp_rippleHeights[i][j] = d[i][j] * ((A * middleValues) + (B * rippleHeights[i][j]) - prev_rippleHeights[i][j]);
            //std::cout << tmp_rippleHeights[i][j] << " ";
        }
        //std::cout << std::endl;
    }
    //change arrays
    memcpy(&prev_rippleHeights, &rippleHeights, RIPPLE_SIZE * RIPPLE_SIZE * sizeof(float));
    memcpy(&rippleHeights, &tmp_rippleHeights, RIPPLE_SIZE * RIPPLE_SIZE * sizeof(float));
    /*for (int i = 0; i < RIPPLE_SIZE; i++)
        for (int j = 0; j < RIPPLE_SIZE; j++) {
            prev_rippleHeights[i][j] = rippleHeights[i][j];
            rippleHeights[i][j] = tmp_rippleHeights[i][j];
        }*/
}








