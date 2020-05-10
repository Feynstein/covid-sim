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
    // Need to check if anys can be instanciated this way without being cast in their final state ... so yeah make sure we dont get casting errors down the road
    m_dataMap["PlaceCloseIndepThresh"] = (int)0;
    m_dataMap["LoadSaveNetwork"] = (int)0;
    m_dataMap["DoHeteroDensity"] = (int)0;
    m_dataMap["DoPeriodicBoundaries"] = (int)0;
    m_dataMap["DoSchoolFile"] = (int)0;
    m_dataMap["DoAdunitDemog"] = (int)0;
    m_dataMap["OutputDensFile"] = (int)0;
    m_dataMap["OutputDensFile"] = (int)0;
    m_dataMap["MaxNumThreads"] = (int)0; // Doesnt seem right ... 
    m_dataMap["DoInterventionFile"] = (int)0;
    m_dataMap["PreControlClusterIdCaseThreshold"] = (int)0;
    m_dataMap["R0scale"] = (double) 1.0;


    P.PlaceCloseIndepThresh = P.LoadSaveNetwork = P.DoHeteroDensity = P.DoPeriodicBoundaries = P.DoSchoolFile = P.DoAdunitDemog = P.OutputDensFile = P.MaxNumThreads = P.DoInterventionFile = 0;
		P.PreControlClusterIdCaseThreshold = 0;
		P.R0scale = 1.0;
		P.KernelOffsetScale = P.KernelPowerScale = 1.0; //added this so that kernel parameters are only changed if input from the command line: ggilani - 15/10/2014
		P.DoSaveSnapshot = P.DoLoadSnapshot  = 0;
}