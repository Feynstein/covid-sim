#pragma once
//
//  Utilities.h
//
//  Created by Feynstein on 05/08/2020
//
//


#include <thread> // only for std::thread::hardware_concurrency()


/*!
 * \class	Utilities
 *
 * \brief	Class of static utilities functions
 */

class Utilities
{
    public:
        static void ReadInputParameters(const std::string &p_paramFileName, const std::string &p_preParamFilename);
};