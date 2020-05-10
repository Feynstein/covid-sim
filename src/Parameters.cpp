//
//  Parameters.cpp
//
//  Created by Feynstein on 05/09/2020
//
//

#include <exception>
#include <iostream>
#include <cassert>

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
    m_dataMap["R0Scale"] = (double) 1.0;
    m_dataMap["KernelOffsetScale"] = (double) 1.0; //added this so that kernel parameters are only changed if input from the command line: ggilani - 15/10/2014
    m_dataMap["KernelPowerScale"] = (double) 1.0;
    m_dataMap["DoSaveSnapshot"] = (int) 0;
    m_dataMap["DoLoadSnapshot"] = (int) 0;

    //This is where the keys should be loaded from txt or xml in order to verify when setting and getting
}

const std::any Parameters::GetValue(const std::string &p_key)
{
  //Will have to implement protection, doing it like that now
  assert(m_dataMap.count(p_key) == 1);
  //This is where the keys will be verified; do something like std::count(m_availableKeys.begin(), m_availableKeys.end(), p_key) == 1;
  return m_dataMap[p_key]; 
}

void Parameters::SetValue(const std::string &p_key, const std::any &p_value)
{
  //Verify that its in the keys vector
  assert(m_dataMap.count(p_key) == 0);

  m_dataMap[p_key] = p_value;
}

std::vector<std::string> Parameters::GetKeys()
{
  std::vector<std::string> outputVector;
  for(auto pair : m_dataMap)
  {
    outputVector.push_back(pair.first); //There should be a better way since we don't like push-backs they make stuff slower... to see
  }

  return outputVector;
}

void Parameters::ModifyValue(const std::string &p_key, const std::any &p_value)
{
  assert(m_dataMap.count(p_key) == 1);

  m_dataMap[p_key] = p_value;

  assert(m_dataMap.count(p_key) == 1); // Just because I don't use unordered_map that often lol sorry
}