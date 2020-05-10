#pragma once
//
//  ParametersReader.h
//
//  Created by ybelanger on 05/10/2020
//
//



#include "Defines.h"

//Forward declaration... mostly a habit of mine
class Parameters;


/*!
 * \class	Parameters Reader
 *
 * \brief	Class of static? file reading functions... we'll see if we need to implement states in it
 */

class ParametersReader
{
    public:
        static void ReadInputParameters(const sP<Parameters> &p_params);
};