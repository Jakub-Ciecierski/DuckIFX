//
// Created by jakub on 5/30/16.
//

#ifndef DUCK_DUCK_LOADER_H
#define DUCK_DUCK_LOADER_H


#include <mesh/model.h>

/*
 * Class only focuses on loading the duck model for GK2 Project
 */
class DuckLoader {
private:
    std::vector<std::string> splitString(std::string s,
                                         std::string delimiter);
public:

    DuckLoader();

    ~DuckLoader();

    Model loadDuckModel();

};


#endif //DUCK_DUCK_LOADER_H
