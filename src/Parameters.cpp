//
//  Parameters.cpp
//
//  Created by Feynstein on 05/09/2020
//
//

#include "Parameters.h"









// Ctor needed to setup all the default variables
Parameters::Parameters()
{

    m_dataMap["PlaceCloseIndepThresh"] = 0;
    m_dataMap["LoadSaveNetwork"] = 0;
    m_dataMap["DoHeteroDensity"] = 0;

    P.PlaceCloseIndepThresh = P.LoadSaveNetwork = P.DoHeteroDensity = P.DoPeriodicBoundaries = P.DoSchoolFile = P.DoAdunitDemog = P.OutputDensFile = P.MaxNumThreads = P.DoInterventionFile = 0;
		P.PreControlClusterIdCaseThreshold = 0;
		P.R0scale = 1.0;
		P.KernelOffsetScale = P.KernelPowerScale = 1.0; //added this so that kernel parameters are only changed if input from the command line: ggilani - 15/10/2014
		P.DoSaveSnapshot = P.DoLoadSnapshot  = 0;
}