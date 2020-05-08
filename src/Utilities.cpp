
#include <string>

#include <boost/program_options.hpp>


#include "Utilities.h"



void Utilities::ReadInputParameters(const std::string &p_paramFileName, const std::string &p_preParamFilename) // will probably change the output when actually doing the work
{
    //TODO WWWWWWWWWWWWWWWWWWWWTTTTTTTTTTTTTTTTTTTTTTTTFFFFFFFFFFFFFFFFFFFFFFFFFFF ???????????????????????????????????????????????? 
    //hahaha gonna have some job to do in this thing holy cow!
    // This gun be fun :D

/*
	FILE* ParamFile_dat, * PreParamFile_dat, *AdminFile_dat;
	double s, t, AgeSuscScale;
	int i, j, k, f, nc, na;
	char CountryNameBuf[128 * MAX_COUNTRIES], AdunitListNamesBuf[128 * MAX_ADUNITS];

	char* CountryNames[MAX_COUNTRIES];
	for (i = 0; i < MAX_COUNTRIES; i++) { CountryNames[i] = CountryNameBuf + 128 * i; CountryNames[i][0] = 0; }
	char* AdunitListNames[MAX_ADUNITS];
	for (i = 0; i < MAX_ADUNITS; i++) { AdunitListNames[i] = AdunitListNamesBuf + 128 * i; AdunitListNames[i][0] = 0; }
	if (!(ParamFile_dat = fopen(ParamFile, "rb"))) ERR_CRITICAL("Unable to open parameter file\n");
	PreParamFile_dat = fopen(PreParamFile, "rb");
	if (!(AdminFile_dat = fopen(AdunitFile, "rb"))) AdminFile_dat = ParamFile_dat;
	AgeSuscScale = 1.0;
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Update timestep", "%lf", (void*) & (P.TimeStep), 1, 1, 0);
	GetInputParameter(ParamFile_dat, PreParamFile_dat, "Sampling timestep", "%lf", (void*) & (P.SampleStep), 1, 1, 0);
	if (P.TimeStep > P.SampleStep) ERR_CRITICAL("Update step must be smaller than sampling step\n");
	t = ceil(P.SampleStep / P.TimeStep - 1e-6);
	P.UpdatesPerSample = (int)t;
	P.TimeStep = P.SampleStep / t;
	P.TimeStepsPerDay = ceil(1.0 / P.TimeStep - 1e-6);
	fprintf(stderr, "Update step = %lf\nSampling step = %lf\nUpdates per sample=%i\nTimeStepsPerDay=%lf\n", P.TimeStep, P.SampleStep, P.UpdatesPerSample, P.TimeStepsPerDay);
	GetInputParameter(ParamFile_dat, PreParamFile_dat, "Sampling time", "%lf", (void*) & (P.SampleTime), 1, 1, 0);
	P.NumSamples = 1 + (int)ceil(P.SampleTime / P.SampleStep);
	GetInputParameter(ParamFile_dat, AdminFile_dat, "Population size", "%i", (void*) & (P.PopSize), 1, 1, 0);
	GetInputParameter(ParamFile_dat, PreParamFile_dat, "Number of realisations", "%i", (void*) & (P.NumRealisations), 1, 1, 0);
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of non-extinct realisations", "%i", (void*) & (P.NumNonExtinctRealisations), 1, 1, 0)) P.NumNonExtinctRealisations = P.NumRealisations;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum number of cases defining small outbreak", "%i", (void*) & (P.SmallEpidemicCases), 1, 1, 0)) P.SmallEpidemicCases = -1;
	P.NC = -1;
	GetInputParameter(ParamFile_dat, PreParamFile_dat, "Number of micro-cells per spatial cell width", "%i", (void*) & (P.NMCL), 1, 1, 0);
	//added parameter to reset seeds after every run
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Reset seeds for every run", "%i", (void*) & (P.ResetSeeds), 1, 1, 0)) P.ResetSeeds = 0;
	if (P.ResetSeeds)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Keep same seeds for every run", "%i", (void*) & (P.KeepSameSeeds), 1, 1, 0)) P.KeepSameSeeds = 0; //added this to control which seeds are used: ggilani 27/11/19
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Reset seeds after intervention", "%i", (void*) & (P.ResetSeedsPostIntervention), 1, 1, 0)) P.ResetSeedsPostIntervention = 0;
	if (P.ResetSeedsPostIntervention)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Time to reset seeds after intervention", "%i", (void*) & (P.TimeToResetSeeds), 1, 1, 0)) P.TimeToResetSeeds = 1000000;
	}
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Include households", "%i", (void*) & (P.DoHouseholds), 1, 1, 0)) P.DoHouseholds = 1;

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputAge"				, "%i", (void*) & (P.OutputAge)					, 1, 1, 0)) P.OutputAge = 1;				//// ON  by default.
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputSeverityAdminUnit"	, "%i", (void*) & (P.OutputSeverityAdminUnit)	, 1, 1, 0)) P.OutputSeverityAdminUnit = 1;	//// ON  by default.
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputR0"					, "%i", (void*) & (P.OutputR0)					, 1, 1, 0)) P.OutputR0 = 0;				    //// OFF by default.
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputControls"			, "%i", (void*) & (P.OutputControls)			, 1, 1, 0)) P.OutputControls = 0;		    //// OFF by default.
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputCountry"			, "%i", (void*) & (P.OutputCountry)				, 1, 1, 0)) P.OutputCountry = 0;		    //// OFF by default.
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputAdUnitVar"			, "%i", (void*) & (P.OutputAdUnitVar)			, 1, 1, 0)) P.OutputAdUnitVar = 0;		    //// OFF by default.
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputHousehold"			, "%i", (void*) & (P.OutputHousehold)			, 1, 1, 0)) P.OutputHousehold = 0;		    //// OFF by default.
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputInfType"			, "%i", (void*) & (P.OutputInfType)				, 1, 1, 0)) P.OutputInfType = 0;		    //// OFF by default.
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputNonSeverity"		, "%i", (void*) & (P.OutputNonSeverity)			, 1, 1, 0)) P.OutputNonSeverity = 0;		//// OFF by default.
  	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "OutputNonSummaryResults"	, "%i", (void*) & (P.OutputNonSummaryResults)	, 1, 1, 0)) P.OutputNonSummaryResults = 0;	//// OFF by default.

	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Kernel resolution", "%i", (void*)&P.NKR, 1, 1, 0)) P.NKR = 4000000;
	if (P.NKR < 2000000)
	{
		ERR_CRITICAL_FMT("[Kernel resolution] needs to be at least 2000000 - not %d", P.NKR);
	}
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Kernel higher resolution factor", "%i", (void*)&P.NK_HR, 1, 1, 0)) P.NK_HR = P.NKR / 1600;
	if (P.NK_HR < 1 || P.NK_HR >= P.NKR)
	{
		ERR_CRITICAL_FMT("[Kernel higher resolution factor] needs to be in range [1, P.NKR = %d) - not %d", P.NKR, P.NK_HR);
	}

	if (P.DoHouseholds)
	{
		GetInputParameter(PreParamFile_dat, AdminFile_dat, "Household size distribution", "%lf", (void*)P.HouseholdSizeDistrib[0], MAX_HOUSEHOLD_SIZE, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Household attack rate", "%lf", (void*) & (P.HouseholdTrans), 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Household transmission denominator power", "%lf", (void*) & (P.HouseholdTransPow), 1, 1, 0);
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Correct age distribution after household allocation to exactly match specified demography", "%i", (void*)&(P.DoCorrectAgeDist), 1, 1, 0)) P.DoCorrectAgeDist = 0;
	}
	else
	{
		P.HouseholdTrans = 0.0;
		P.HouseholdTransPow = 1.0;
		P.HouseholdSizeDistrib[0][0] = 1.0;
		for (i = 1; i < MAX_HOUSEHOLD_SIZE; i++)
			P.HouseholdSizeDistrib[0][i] = 0;
	}
	for (i = 1; i < MAX_HOUSEHOLD_SIZE; i++)
		P.HouseholdSizeDistrib[0][i] = P.HouseholdSizeDistrib[0][i] + P.HouseholdSizeDistrib[0][i - 1];
	for (i = 0; i < MAX_HOUSEHOLD_SIZE; i++)
		P.HouseholdDenomLookup[i] = 1 / pow(((double)(i + 1)), P.HouseholdTransPow);
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Include administrative units within countries", "%i", (void*) & (P.DoAdUnits), 1, 1, 0)) P.DoAdUnits = 1;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Divisor for countries", "%i", (void*) & (P.CountryDivisor), 1, 1, 0)) P.CountryDivisor = 1;
	if (P.DoAdUnits)
	{
		char** AdunitNames, * AdunitNamesBuf;
		if (!(AdunitNames = (char**)malloc(3 * ADUNIT_LOOKUP_SIZE * sizeof(char*)))) ERR_CRITICAL("Unable to allocate temp storage\n");
		if (!(AdunitNamesBuf = (char*)malloc(3 * ADUNIT_LOOKUP_SIZE * 360 * sizeof(char)))) ERR_CRITICAL("Unable to allocate temp storage\n");

		for (i = 0; i < ADUNIT_LOOKUP_SIZE; i++)
		{
			P.AdunitLevel1Lookup[i] = -1;
			AdunitNames[3 * i] = AdunitNamesBuf + 3 * i * 360;
			AdunitNames[3 * i + 1] = AdunitNamesBuf + 3 * i * 360 + 60;
			AdunitNames[3 * i + 2] = AdunitNamesBuf + 3 * i * 360 + 160;
		}
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Divisor for level 1 administrative units", "%i", (void*)&(P.AdunitLevel1Divisor), 1, 1, 0)) P.AdunitLevel1Divisor = 1;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Mask for level 1 administrative units", "%i", (void*)&(P.AdunitLevel1Mask), 1, 1, 0)) P.AdunitLevel1Mask = 1000000000;
		na = (GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Codes and country/province names for admin units", "%s", (void*)AdunitNames, 3 * ADUNIT_LOOKUP_SIZE, 1, 0)) / 3;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Number of countries to include", "%i", (void*)&nc, 1, 1, 0)) nc = 0;
		if ((na > 0) && (nc>0))
		{
			P.DoAdunitBoundaries = (nc > 0);
			nc = abs(nc);
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "List of names of countries to include", "%s", (nc > 1) ? ((void*)CountryNames) : ((void*)CountryNames[0]), nc, 1, 0);
			P.NumAdunits = 0;
			for (i = 0; i < na; i++)
				for (j = 0; j < nc; j++)
					if ((AdunitNames[3 * i + 1][0]) && (!strcmp(AdunitNames[3 * i + 1], CountryNames[j])) && (atoi(AdunitNames[3 * i]) != 0))
					{
						AdUnits[P.NumAdunits].id = atoi(AdunitNames[3 * i]);
						P.AdunitLevel1Lookup[(AdUnits[P.NumAdunits].id % P.AdunitLevel1Mask) / P.AdunitLevel1Divisor] = P.NumAdunits;
						if (strlen(AdunitNames[3 * i + 1]) < 100) strcpy(AdUnits[P.NumAdunits].cnt_name, AdunitNames[3 * i + 1]);
						if (strlen(AdunitNames[3 * i + 2]) < 200) strcpy(AdUnits[P.NumAdunits].ad_name, AdunitNames[3 * i + 2]);
						//						fprintf(stderr,"%i %s %s ## ",AdUnits[P.NumAdunits].id,AdUnits[P.NumAdunits].cnt_name,AdUnits[P.NumAdunits].ad_name);
						P.NumAdunits++;
					}
		}
		else
		{
			if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Number of level 1 administrative units to include", "%i", (void*) & (P.NumAdunits), 1, 1, 0)) P.NumAdunits = 0;
			if (P.NumAdunits > 0)
			{
				P.DoAdunitBoundaries = 1;
				if (P.NumAdunits > MAX_ADUNITS) ERR_CRITICAL("MAX_ADUNITS too small.\n");
				GetInputParameter(PreParamFile_dat, AdminFile_dat, "List of level 1 administrative units to include", "%s", (P.NumAdunits > 1) ? ((void*)AdunitListNames) : ((void*)AdunitListNames[0]), P.NumAdunits, 1, 0);
				na = P.NumAdunits;
				for (i = 0; i < P.NumAdunits; i++)
				{
					f = 0;
					if (na > 0)
					{
						for (j = 0; (j < na) && (!f); j++) f = (!strcmp(AdunitNames[3 * j + 2], AdunitListNames[i]));
						if(f) k = atoi(AdunitNames[3 * (j-1)]);
					}
					if ((na == 0) || (!f)) k = atoi(AdunitListNames[i]);
					AdUnits[i].id = k;
					P.AdunitLevel1Lookup[(k % P.AdunitLevel1Mask) / P.AdunitLevel1Divisor] = i;
					for (j = 0; j < na; j++)
						if (atoi(AdunitNames[3 * j]) == k)
						{
							if (strlen(AdunitNames[3 * j + 1]) < 100) strcpy(AdUnits[i].cnt_name, AdunitNames[3 * j + 1]);
							if (strlen(AdunitNames[3 * j + 2]) < 200) strcpy(AdUnits[i].ad_name, AdunitNames[3 * j + 2]);
							j = na;
						}
				}
			}
			else
				P.DoAdunitBoundaries = 0;
		}
    free(AdunitNames);
    free(AdunitNamesBuf);

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output incidence by administrative unit", "%i", (void*) & (P.DoAdunitOutput), 1, 1, 0)) P.DoAdunitOutput = 0;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Draw administrative unit boundaries on maps", "%i", (void*) & (P.DoAdunitBoundaryOutput), 1, 1, 0)) P.DoAdunitBoundaryOutput = 0;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Correct administrative unit populations", "%i", (void*) & (P.DoCorrectAdunitPop), 1, 1, 0)) P.DoCorrectAdunitPop = 0;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Fix population size at specified value", "%i", (void*) & (P.DoSpecifyPop), 1, 1, 0)) P.DoSpecifyPop = 0;
		fprintf(stderr, "Using %i administrative units\n", P.NumAdunits);
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Divisor for administrative unit codes for boundary plotting on bitmaps", "%i", (void*) & (P.AdunitBitmapDivisor), 1, 1, 0)) P.AdunitBitmapDivisor = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Only output household to place distance distribution for one administrative unit", "%i", (void*) & (P.DoOutputPlaceDistForOneAdunit), 1, 1, 0)) P.DoOutputPlaceDistForOneAdunit = 0;
		if (P.DoOutputPlaceDistForOneAdunit)
		{
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Administrative unit for which household to place distance distribution to be output", "%i", (void*) & (P.OutputPlaceDistAdunit), 1, 1, 0)) P.DoOutputPlaceDistForOneAdunit = 0;
		}
	}
	else
	{
		P.DoAdunitBoundaries = P.DoAdunitBoundaryOutput = P.DoAdunitOutput = P.DoCorrectAdunitPop = P.DoSpecifyPop = 0;
		P.AdunitLevel1Divisor = 1; P.AdunitLevel1Mask = 1000000000;
		P.AdunitBitmapDivisor = P.AdunitLevel1Divisor;
	}

	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Include age", "%i", (void*) & (P.DoAge), 1, 1, 0)) P.DoAge = 1;
	if (!P.DoAge)
	{
		for (i = 0; i < NUM_AGE_GROUPS; i++)
			P.PropAgeGroup[0][i] = 1.0 / NUM_AGE_GROUPS;
		for (i = 0; i < NUM_AGE_GROUPS; i++)
		{
			P.InitialImmunity[i] = 0;
			P.AgeInfectiousness[i] = P.AgeSusceptibility[i] = 1;
			P.RelativeSpatialContact[i] = P.RelativeTravelRate[i] = 1.0;
		}
	}
	else
	{

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Initial immunity acts as partial immunity", "%i", (void*)&(P.DoPartialImmunity), 1, 1, 0)) P.DoPartialImmunity = 1;
		if ((P.DoHouseholds)&&(!P.DoPartialImmunity))
		{
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Initial immunity applied to all household members", "%i", (void*) & (P.DoWholeHouseholdImmunity), 1, 1, 0)) P.DoWholeHouseholdImmunity = 0;
		}
		else
			P.DoWholeHouseholdImmunity = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Initial immunity profile by age", "%lf", (void*)P.InitialImmunity, NUM_AGE_GROUPS, 1, 0))
			for (i = 0; i < NUM_AGE_GROUPS; i++)
				P.InitialImmunity[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rates by age", "%lf", (void*)P.RelativeSpatialContact, NUM_AGE_GROUPS, 1, 0))
			for (i = 0; i < NUM_AGE_GROUPS; i++)
				P.RelativeSpatialContact[i] = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Age-dependent infectiousness", "%lf", (void*)P.AgeInfectiousness, NUM_AGE_GROUPS, 1, 0))
			for (i = 0; i < NUM_AGE_GROUPS; i++)
				P.AgeInfectiousness[i] = 1.0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Age-dependent susceptibility", "%lf", (void*)P.AgeSusceptibility, NUM_AGE_GROUPS, 1, 0))
			for (i = 0; i < NUM_AGE_GROUPS; i++)
				P.AgeSusceptibility[i] = 1.0;
		GetInputParameter(PreParamFile_dat, AdminFile_dat, "Age distribution of population", "%lf", (void*)P.PropAgeGroup[0], NUM_AGE_GROUPS, 1, 0);
		t = 0;
		for (i = 0; i < NUM_AGE_GROUPS; i++)
			t += P.PropAgeGroup[0][i];
		for (i = 0; i < NUM_AGE_GROUPS; i++)
			P.PropAgeGroup[0][i] /= t;
		t = 0;
		for (i = 0; i < NUM_AGE_GROUPS; i++)
			if (P.AgeSusceptibility[i] > t) t = P.AgeSusceptibility[i];  //peak susc has to be 1
		for (i = 0; i < NUM_AGE_GROUPS; i++)
			P.AgeSusceptibility[i] /= t;
		AgeSuscScale = t;
		if (P.DoHouseholds) P.HouseholdTrans *= AgeSuscScale;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Relative travel rates by age", "%lf", (void*)P.RelativeTravelRate, NUM_AGE_GROUPS, 1, 0))
			for (i = 0; i < NUM_AGE_GROUPS; i++)
				P.RelativeTravelRate[i] = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "WAIFW matrix", "%lf", (void*)P.WAIFW_Matrix, NUM_AGE_GROUPS, NUM_AGE_GROUPS, 0))
		{
			for (i = 0; i < NUM_AGE_GROUPS; i++)
				for (j = 0; j < NUM_AGE_GROUPS; j++)
					P.WAIFW_Matrix[i][j] = 1.0;
		}
		else
		{
			/* WAIFW matrix needs to be scaled to have max value of 1.
			1st index of matrix specifies host being infected, second the infector.
			Overall age variation in infectiousness/contact rates/susceptibility should be factored
			out of WAIFW_matrix and put in Age dep infectiousness/susceptibility for efficiency. 
			t = 0;
			for (i = 0; i < NUM_AGE_GROUPS; i++)
				for (j = 0; j < NUM_AGE_GROUPS; j++)
					if (P.WAIFW_Matrix[i][j] > t) t = P.WAIFW_Matrix[i][j];
			if (t > 0)
			{
				for (i = 0; i < NUM_AGE_GROUPS; i++)
					for (j = 0; j < NUM_AGE_GROUPS; j++)
						P.WAIFW_Matrix[i][j] /= t;
			}
			else
			{
				for (i = 0; i < NUM_AGE_GROUPS; i++)
					for (j = 0; j < NUM_AGE_GROUPS; j++)
						P.WAIFW_Matrix[i][j] = 1.0;
			}
		}
		P.DoDeath = 0;
		t = 0;
		for (i = 0; i < NUM_AGE_GROUPS; i++)	t += P.AgeInfectiousness[i] * P.PropAgeGroup[0][i];
		for (i = 0; i < NUM_AGE_GROUPS; i++)	P.AgeInfectiousness[i] /= t;
	}
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Include spatial transmission", "%i", (void*) & (P.DoSpatial), 1, 1, 0)) P.DoSpatial = 1;
	GetInputParameter(PreParamFile_dat, AdminFile_dat, "Kernel type", "%i", (void*) & (P.MoveKernelType), 1, 1, 0);
	GetInputParameter(PreParamFile_dat, AdminFile_dat, "Kernel scale", "%lf", (void*) & (P.MoveKernelScale), 1, 1, 0);
	if (P.KernelOffsetScale != 1)
	{
		P.MoveKernelScale *= P.KernelOffsetScale;
	}
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Kernel 3rd param", "%lf", (void*) & (P.MoveKernelP3), 1, 1, 0)) P.MoveKernelP3 = 0;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Kernel 4th param", "%lf", (void*) & (P.MoveKernelP4), 1, 1, 0)) P.MoveKernelP4 = 0;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Kernel Shape", "%lf", (void*) & (P.MoveKernelShape), 1, 1, 0)) P.MoveKernelShape = 1.0;
	if (P.KernelPowerScale != 1)
	{
		P.MoveKernelShape *= P.KernelPowerScale;
	}
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Airport Kernel Type", "%i", (void*) & (P.AirportKernelType), 1, 1, 0)) P.AirportKernelType = P.MoveKernelType;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Airport Kernel Scale", "%lf", (void*) & (P.AirportKernelScale), 1, 1, 0)) P.AirportKernelScale = P.MoveKernelScale;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Airport Kernel Shape", "%lf", (void*) & (P.AirportKernelShape), 1, 1, 0)) P.AirportKernelShape = P.MoveKernelShape;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Airport Kernel 3rd param", "%lf", (void*) & (P.AirportKernelP3), 1, 1, 0)) P.AirportKernelP3 = P.MoveKernelP3;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Airport Kernel 4th param", "%lf", (void*) & (P.AirportKernelP4), 1, 1, 0)) P.AirportKernelP4 = P.MoveKernelP4;

	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Include places", "%i", (void*)&(P.DoPlaces), 1, 1, 0)) P.DoPlaces = 1;
	if (P.DoPlaces)
	{
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Number of types of places", "%i", (void*)&(P.PlaceTypeNum), 1, 1, 0)) P.PlaceTypeNum = 0;
		if (P.PlaceTypeNum == 0) P.DoPlaces = P.DoAirports = 0;
	}
	else
		P.PlaceTypeNum = P.DoAirports = 0;
	if (P.DoPlaces)
	{
		if (P.PlaceTypeNum > NUM_PLACE_TYPES) ERR_CRITICAL("Too many place types\n");
		GetInputParameter(PreParamFile_dat, AdminFile_dat, "Minimum age for age group 1 in place types", "%i", (void*)P.PlaceTypeAgeMin, P.PlaceTypeNum, 1, 0);
		GetInputParameter(PreParamFile_dat, AdminFile_dat, "Maximum age for age group 1 in place types", "%i", (void*)P.PlaceTypeAgeMax, P.PlaceTypeNum, 1, 0);
		GetInputParameter(PreParamFile_dat, AdminFile_dat, "Proportion of age group 1 in place types", "%lf", (void*) & (P.PlaceTypePropAgeGroup), P.PlaceTypeNum, 1, 0);
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Proportion of age group 2 in place types", "%lf", (void*) & (P.PlaceTypePropAgeGroup2), P.PlaceTypeNum, 1, 0))
		{
			for (i = 0; i < NUM_PLACE_TYPES; i++)
			{
				P.PlaceTypePropAgeGroup2[i] = 0;
				P.PlaceTypeAgeMin2[i] = 0;
				P.PlaceTypeAgeMax2[i] = 1000;
			}
		}
		else
		{
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Minimum age for age group 2 in place types", "%i", (void*)P.PlaceTypeAgeMin2, P.PlaceTypeNum, 1, 0);
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Maximum age for age group 2 in place types", "%i", (void*)P.PlaceTypeAgeMax2, P.PlaceTypeNum, 1, 0);
		}
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Proportion of age group 3 in place types", "%lf", (void*) & (P.PlaceTypePropAgeGroup3), P.PlaceTypeNum, 1, 0))
		{
			for (i = 0; i < NUM_PLACE_TYPES; i++)
			{
				P.PlaceTypePropAgeGroup3[i] = 0;
				P.PlaceTypeAgeMin3[i] = 0;
				P.PlaceTypeAgeMax3[i] = 1000;
			}
		}
		else
		{
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Minimum age for age group 3 in place types", "%i", (void*)P.PlaceTypeAgeMin3, P.PlaceTypeNum, 1, 0);
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Maximum age for age group 3 in place types", "%i", (void*)P.PlaceTypeAgeMax3, P.PlaceTypeNum, 1, 0);
		}
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Kernel shape params for place types", "%lf", (void*) & (P.PlaceTypeKernelShape), P.PlaceTypeNum, 1, 0))
		{
			for (i = 0; i < NUM_PLACE_TYPES; i++)
			{
				P.PlaceTypeKernelShape[i] = P.MoveKernelShape;
				P.PlaceTypeKernelScale[i] = P.MoveKernelScale;
			}
		}
		else
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Kernel scale params for place types", "%lf", (void*) & (P.PlaceTypeKernelScale), P.PlaceTypeNum, 1, 0);
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Kernel 3rd param for place types", "%lf", (void*) & (P.PlaceTypeKernelP3), P.PlaceTypeNum, 1, 0))
		{
			for (i = 0; i < NUM_PLACE_TYPES; i++)
			{
				P.PlaceTypeKernelP3[i] = P.MoveKernelP3;
				P.PlaceTypeKernelP4[i] = P.MoveKernelP4;
			}
		}
		else
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Kernel 4th param for place types", "%lf", (void*) & (P.PlaceTypeKernelP4), P.PlaceTypeNum, 1, 0);
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Number of closest places people pick from (0=all) for place types", "%i", (void*) & (P.PlaceTypeNearestNeighb), P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++)
				P.PlaceTypeNearestNeighb[i] = 0;
		if (P.DoAdUnits)
		{
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Degree to which crossing administrative unit boundaries to go to places is inhibited", "%lf", (void*) & (P.InhibitInterAdunitPlaceAssignment), P.PlaceTypeNum, 1, 0))
				for (i = 0; i < NUM_PLACE_TYPES; i++)
					P.InhibitInterAdunitPlaceAssignment[i] = 0;
		}

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Include air travel", "%i", (void*)&(P.DoAirports), 1, 1, 0)) P.DoAirports = 0;
		if (!P.DoAirports)
		{
			// Airports disabled => all places are not to do with airports, and we
			// have no hotels.
			P.PlaceTypeNoAirNum = P.PlaceTypeNum;
			P.HotelPlaceType = P.PlaceTypeNum;
		}
		else
		{
			// When airports are activated we must have at least one airport place
			// // and a hotel type.
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Number of non-airport places", "%i", (void*)&(P.PlaceTypeNoAirNum), 1, 1, 0);
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Hotel place type", "%i", (void*)&(P.HotelPlaceType), 1, 1, 0);
			if (P.PlaceTypeNoAirNum >= P.PlaceTypeNum) {
				ERR_CRITICAL_FMT("[Number of non-airport places] parameter (%d) is greater than number of places (%d).\n", P.PlaceTypeNoAirNum, P.PlaceTypeNum);
			}
			if (P.HotelPlaceType < P.PlaceTypeNoAirNum || P.HotelPlaceType >= P.PlaceTypeNum) {
				ERR_CRITICAL_FMT("[Hotel place type] parameter (%d) not in the range [%d, %d)\n", P.HotelPlaceType, P.PlaceTypeNoAirNum, P.PlaceTypeNum);
			}

			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Scaling factor for input file to convert to daily traffic", "%lf", (void*) & (P.AirportTrafficScale), 1, 1, 0)) P.AirportTrafficScale = 1.0;
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of hotel attendees who are local", "%lf", (void*) & (P.HotelPropLocal), 1, 1, 0)) P.HotelPropLocal = 0;
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Distribution of duration of air journeys", "%lf", (void*) & (P.JourneyDurationDistrib), MAX_TRAVEL_TIME, 1, 0))
			{
				P.JourneyDurationDistrib[0] = 1;
				for (i = 0; i < MAX_TRAVEL_TIME; i++)
					P.JourneyDurationDistrib[i] = 0;
			}
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Distribution of duration of local journeys", "%lf", (void*) & (P.LocalJourneyDurationDistrib), MAX_TRAVEL_TIME, 1, 0))
			{
				P.LocalJourneyDurationDistrib[0] = 1;
				for (i = 0; i < MAX_TRAVEL_TIME; i++)
					P.LocalJourneyDurationDistrib[i] = 0;
			}
			P.MeanJourneyTime = P.MeanLocalJourneyTime = 0;
			for (i = 0; i < MAX_TRAVEL_TIME; i++)
			{
				P.MeanJourneyTime += ((double)(i)) * P.JourneyDurationDistrib[i];
				P.MeanLocalJourneyTime += ((double)(i)) * P.LocalJourneyDurationDistrib[i];
			}
			fprintf(stderr, "Mean duration of local journeys = %lf days\n", P.MeanLocalJourneyTime);
			for (i = 1; i < MAX_TRAVEL_TIME; i++)
			{
				P.JourneyDurationDistrib[i] += P.JourneyDurationDistrib[i - 1];
				P.LocalJourneyDurationDistrib[i] += P.LocalJourneyDurationDistrib[i - 1];
			}
			for (i = j = 0; i <= 1024; i++)
			{
				s = ((double)i) / 1024;
				while (P.JourneyDurationDistrib[j] < s)j++;
				P.InvJourneyDurationDistrib[i] = j;
			}
			for (i = j = 0; i <= 1024; i++)
			{
				s = ((double)i) / 1024;
				while (P.LocalJourneyDurationDistrib[j] < s)j++;
				P.InvLocalJourneyDurationDistrib[i] = j;
			}
		}
		GetInputParameter(PreParamFile_dat, AdminFile_dat, "Mean size of place types", "%lf", (void*)P.PlaceTypeMeanSize, P.PlaceTypeNum, 1, 0);
		GetInputParameter(PreParamFile_dat, AdminFile_dat, "Param 1 of place group size distribution", "%lf", (void*)P.PlaceTypeGroupSizeParam1, P.PlaceTypeNum, 1, 0);
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Power of place size distribution", "%lf", (void*)P.PlaceTypeSizePower, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++)
				P.PlaceTypeSizePower[i] = 0;
		//added to enable lognormal distribution - ggilani 09/02/17
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Standard deviation of place size distribution", "%lf", (void*)P.PlaceTypeSizeSD, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++)
				P.PlaceTypeSizeSD[i] = 0;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Offset of place size distribution", "%lf", (void*)P.PlaceTypeSizeOffset, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++)
				P.PlaceTypeSizeOffset[i] = 0;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Maximum of place size distribution", "%lf", (void*)P.PlaceTypeSizeMax, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++)
				P.PlaceTypeSizeMax[i] = 1e20;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Kernel type for place types", "%i", (void*)P.PlaceTypeKernelType, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++)
				P.PlaceTypeKernelType[i] = P.MoveKernelType;
		GetInputParameter(PreParamFile_dat, AdminFile_dat, "Place overlap matrix", "%lf", (void*)P.PlaceExclusivityMatrix, P.PlaceTypeNum * P.PlaceTypeNum, 1, 0); //changed from P.PlaceTypeNum,P.PlaceTypeNum,0);
/* Note P.PlaceExclusivityMatrix not used at present - places assumed exclusive (each person belongs to 0 or 1 place) 

		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Proportion of between group place links", "%lf", (void*)P.PlaceTypePropBetweenGroupLinks, P.PlaceTypeNum, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Relative transmission rates for place types", "%lf", (void*)P.PlaceTypeTrans, P.PlaceTypeNum, 1, 0);
		for (i = 0; i < P.PlaceTypeNum; i++) P.PlaceTypeTrans[i] *= AgeSuscScale;
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Daily seasonality coefficients", "%lf", (void*)P.Seasonality, DAYS_PER_YEAR, 1, 0))
	{
		P.DoSeasonality = 0;
		for (i = 0; i < DAYS_PER_YEAR; i++)
			P.Seasonality[i] = 1;
	}
	else
	{
		P.DoSeasonality = 1;
		s = 0;
		for (i = 0; i < DAYS_PER_YEAR; i++)
			s += P.Seasonality[i];
		s += 1e-20;
		s /= DAYS_PER_YEAR;
		for (i = 0; i < DAYS_PER_YEAR; i++)
			P.Seasonality[i] /= s;
	}
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Number of seed locations", "%i", (void*) & (P.NumSeedLocations), 1, 1, 0)) P.NumSeedLocations = 1;
	if (P.NumSeedLocations > MAX_NUM_SEED_LOCATIONS)
	{
		fprintf(stderr, "Too many seed locations\n");
		P.NumSeedLocations = MAX_NUM_SEED_LOCATIONS;
	}
	GetInputParameter(PreParamFile_dat, AdminFile_dat, "Initial number of infecteds", "%i", (void*)P.NumInitialInfections, P.NumSeedLocations, 1, 0);
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Location of initial infecteds", "%lf", (void*)&(P.LocationInitialInfection[0][0]), P.NumSeedLocations * 2, 1, 0)) P.LocationInitialInfection[0][0] = P.LocationInitialInfection[0][1] = 0.0;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Minimum population in microcell of initial infection", "%i", (void*) & (P.MinPopDensForInitialInfection), 1, 1, 0)) P.MinPopDensForInitialInfection = 0;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Maximum population in microcell of initial infection", "%i", (void*)&(P.MaxPopDensForInitialInfection), 1, 1, 0)) P.MaxPopDensForInitialInfection = 10000000;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Randomise initial infection location", "%i", (void*) & (P.DoRandomInitialInfectionLoc), 1, 1, 0)) P.DoRandomInitialInfectionLoc=1;
	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "All initial infections located in same microcell", "%i", (void*) & (P.DoAllInitialInfectioninSameLoc), 1, 1, 0)) P.DoAllInitialInfectioninSameLoc=0;
	if (P.DoAdUnits)
	{
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Administrative unit to seed initial infection into", "%s", (P.NumSeedLocations > 1) ? ((void*)AdunitListNames) : ((void*)AdunitListNames[0]), P.NumSeedLocations, 1, 0))
			for (i = 0; i < P.NumSeedLocations; i++) P.InitialInfectionsAdminUnit[i] = 0;
		else
			for (i = 0; i < P.NumSeedLocations; i++)
			{
				f = 0;
				if (P.NumAdunits > 0)
				{
					for (j = 0; (j < P.NumAdunits) && (!f); j++) f = (!strcmp(AdUnits[j].ad_name, AdunitListNames[i]));
					if (f) k = AdUnits[j-1].id;
				}
				if (!f) k = atoi(AdunitListNames[i]);
				P.InitialInfectionsAdminUnit[i] = k;
				P.InitialInfectionsAdminUnitId[i]=P.AdunitLevel1Lookup[(k % P.AdunitLevel1Mask) / P.AdunitLevel1Divisor];
			}
		if(!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Administrative unit seeding weights", "%lf", (void*) & (P.InitialInfectionsAdminUnitWeight[0]), P.NumSeedLocations, 1, 0))
			for(i = 0; i < P.NumSeedLocations; i++) P.InitialInfectionsAdminUnitWeight[i] = 1.0;
		s=0;
		for(i = 0; i < P.NumSeedLocations; i++) s+=P.InitialInfectionsAdminUnitWeight[i];
		for(i = 0; i < P.NumSeedLocations; i++) P.InitialInfectionsAdminUnitWeight[i]/=s;
	//	for (i = 0; i < P.NumSeedLocations; i++) fprintf(stderr, "## %i %s %i %i %lf\n",i, AdUnits[P.InitialInfectionsAdminUnitId[i]].ad_name, P.InitialInfectionsAdminUnitId[i], P.InitialInfectionsAdminUnit[i], P.InitialInfectionsAdminUnitWeight[i]);
	}
	else
	{
		for (i = 0; i < P.NumSeedLocations; i++) P.InitialInfectionsAdminUnit[i] = 0;
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Initial rate of importation of infections", "%lf", (void*)&(P.InfectionImportRate1), 1, 1, 0)) P.InfectionImportRate1 = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Changed rate of importation of infections", "%lf", (void*)&(P.InfectionImportRate2), 1, 1, 0)) P.InfectionImportRate2 = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Time when infection rate changes", "%lf", (void*)&(P.InfectionImportChangeTime), 1, 1, 0)) P.InfectionImportChangeTime = 1e10;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Imports via air travel", "%i", (void*)&(P.DoImportsViaAirports), 1, 1, 0)) P.DoImportsViaAirports = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Length of importation time profile provided", "%i", (void*)&(P.DurImportTimeProfile), 1, 1, 0)) P.DurImportTimeProfile = 0;
	if (P.DurImportTimeProfile > 0)
	{
		if (P.DurImportTimeProfile >= MAX_DUR_IMPORT_PROFILE) ERR_CRITICAL("MAX_DUR_IMPORT_PROFILE too small\n");
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Daily importation time profile", "%lf", (void*)P.ImportInfectionTimeProfile, P.DurImportTimeProfile, 1, 0);
	}
	GetInputParameter(ParamFile_dat, PreParamFile_dat, "Reproduction number", "%lf", (void*) & (P.R0), 1, 1, 0);
	GetInputParameter(ParamFile_dat, PreParamFile_dat, "Infectious period", "%lf", (void*) & (P.InfectiousPeriod), 1, 1, 0);
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "SD of individual variation in infectiousness", "%lf", (void*) & (P.InfectiousnessSD), 1, 1, 0)) P.InfectiousnessSD = 0;
	if (GetInputParameter2(ParamFile_dat, PreParamFile_dat, "k of individual variation in infectiousness", "%lf", (void*)& s, 1, 1, 0)) P.InfectiousnessSD = 1.0 / sqrt(s);
	if (P.InfectiousnessSD > 0)
	{
		P.InfectiousnessGamA = P.InfectiousnessGamR = 1 / (P.InfectiousnessSD * P.InfectiousnessSD);
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Model time varying infectiousness", "%i", (void*) & (P.DoInfectiousnessProfile), 1, 1, 0)) P.DoInfectiousnessProfile = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Power of scaling of spatial R0 with density", "%lf", (void*) & (P.R0DensityScalePower), 1, 1, 0)) P.R0DensityScalePower = 0;
	if (P.DoInfectiousnessProfile)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Infectiousness profile", "%lf", (void*)P.infectious_prof, INFPROF_RES, 1, 0))
		{
			for (i = 0; i < INFPROF_RES; i++)
				P.infectious_prof[i] = 1;
		}
		k = (int)ceil(P.InfectiousPeriod / P.TimeStep);
		if (k >= MAX_INFECTIOUS_STEPS) ERR_CRITICAL("MAX_INFECTIOUS_STEPS not big enough\n");
		s = 0;
		P.infectious_prof[INFPROF_RES] = 0;
		for (i = 0; i < MAX_INFECTIOUS_STEPS; i++)	P.infectiousness[i] = 0;
		for (i = 0; i < k; i++)
		{
			t = (((double)i) * P.TimeStep / P.InfectiousPeriod * INFPROF_RES);
			j = (int)t;
			t -= (double)j;
			if (j < INFPROF_RES)
				s += (P.infectiousness[i] = P.infectious_prof[j] * (1 - t) + P.infectious_prof[j + 1] * t);
			else
				s += (P.infectiousness[i] = P.infectious_prof[INFPROF_RES]);
		}
		s /= ((double)k);
		for (i = 0; i <= k; i++) P.infectiousness[i] /= s;
		for (i = 0; i <= CDF_RES; i++) P.infectious_icdf[i] = exp(-1.0);
	}
	else
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Infectious period inverse CDF", "%lf", (void*)P.infectious_icdf, CDF_RES + 1, 1, 0))
		{
			P.infectious_icdf[CDF_RES] = 100;
			for (i = 0; i < CDF_RES; i++)
				P.infectious_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		k = (int)ceil(P.InfectiousPeriod * P.infectious_icdf[CDF_RES] / P.TimeStep);
		if (k >= MAX_INFECTIOUS_STEPS) ERR_CRITICAL("MAX_INFECTIOUS_STEPS not big enough\n");
		for (i = 0; i < k; i++) P.infectiousness[i] = 1.0;
		P.infectiousness[k] = 0;
		for (i = 0; i <= CDF_RES; i++) P.infectious_icdf[i] = exp(-P.infectious_icdf[i]);
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Include latent period", "%i", (void*) & (P.DoLatent), 1, 1, 0)) P.DoLatent = 0;
	if (P.DoLatent)
	{
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Latent period", "%lf", (void*) & (P.LatentPeriod), 1, 1, 0);
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Latent period inverse CDF", "%lf", (void*)P.latent_icdf, CDF_RES + 1, 1, 0))
		{
			P.latent_icdf[CDF_RES] = 1e10;
			for (i = 0; i < CDF_RES; i++)
				P.latent_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for (i = 0; i <= CDF_RES; i++)
			P.latent_icdf[i] = exp(-P.latent_icdf[i]);
	}

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Include symptoms", "%i", (void*) & (P.DoSymptoms), 1, 1, 0)) P.DoSymptoms = 0;
	if (!P.DoSymptoms)
	{
		for (i = 0; i < NUM_AGE_GROUPS; i++)
			P.ProportionSymptomatic[i] = 0;
		P.FalsePositiveRate = 0;
		P.SymptInfectiousness = 1.0;
		P.LatentToSymptDelay = 0;
	}
	else
	{
		if (P.DoAge)
			GetInputParameter(ParamFile_dat, PreParamFile_dat, "Proportion symptomatic by age group", "%lf", (void*)P.ProportionSymptomatic, NUM_AGE_GROUPS, 1, 0);
		else
		{
			GetInputParameter(ParamFile_dat, PreParamFile_dat, "Proportion symptomatic", "%lf", (void*)P.ProportionSymptomatic, 1, 1, 0);
			for (i = 1; i < NUM_AGE_GROUPS; i++)
				P.ProportionSymptomatic[i] = P.ProportionSymptomatic[0];
		}
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Delay from end of latent period to start of symptoms", "%lf", (void*) & (P.LatentToSymptDelay), 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Relative rate of random contacts if symptomatic", "%lf", (void*) & (P.SymptSpatialContactRate), 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Symptomatic infectiousness relative to asymptomatic", "%lf", (void*) & (P.SymptInfectiousness), 1, 1, 0);
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Model symptomatic withdrawal to home as true absenteeism", "%i", (void*)& P.DoRealSymptWithdrawal, 1, 1, 0)) P.DoRealSymptWithdrawal = 0;
		if (P.DoPlaces)
		{
			GetInputParameter(ParamFile_dat, PreParamFile_dat, "Relative level of place attendance if symptomatic", "%lf", (void*)P.SymptPlaceTypeContactRate, P.PlaceTypeNum, 1, 0);
			if (P.DoRealSymptWithdrawal)
			{
				for (j = 0; j < NUM_PLACE_TYPES; j++)
				{
					P.SymptPlaceTypeWithdrawalProp[j] = 1.0 - P.SymptPlaceTypeContactRate[j];
					P.SymptPlaceTypeContactRate[j] = 1.0;
				}
			}
			else
				for (j = 0; j < NUM_PLACE_TYPES; j++) P.SymptPlaceTypeWithdrawalProp[j] = 0.0;
		}
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum age of child at home for whom one adult also stays at home", "%i", (void*)& P.CaseAbsentChildAgeCutoff, 1, 1, 0)) P.CaseAbsentChildAgeCutoff = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of children at home for whom one adult also stays at home", "%lf", (void*)& P.CaseAbsentChildPropAdultCarers, 1, 1, 0)) P.CaseAbsentChildPropAdultCarers = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place close round household", "%i", (void*)&P.PlaceCloseRoundHousehold, 1, 1, 0)) P.PlaceCloseRoundHousehold = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Absenteeism place closure", "%i", (void*)&P.AbsenteeismPlaceClosure, 1, 1, 0)) P.AbsenteeismPlaceClosure = 0;
		if (P.AbsenteeismPlaceClosure)
		{
			P.CaseAbsenteeismDelay = 0;  // Set to zero for tracking absenteeism
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Max absent time", "%i", (void*)&P.MaxAbsentTime, 1, 1, 0)) P.MaxAbsentTime = MAX_ABSENT_TIME;
			if (P.MaxAbsentTime > MAX_ABSENT_TIME || P.MaxAbsentTime < 0)
			{
				ERR_CRITICAL_FMT("[Max absent time] out of range (%d), should be in range [0, %d]", P.MaxAbsentTime, MAX_ABSENT_TIME);
			}
		}
		else
		{
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay in starting place absenteeism for cases who withdraw", "%lf", (void*)& P.CaseAbsenteeismDelay, 1, 1, 0)) P.CaseAbsenteeismDelay = 0;
			P.MaxAbsentTime = 0; // Not used when !P.AbsenteeismPlaceClosure
		}
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of place absenteeism for cases who withdraw", "%lf", (void*)& P.CaseAbsenteeismDuration, 1, 1, 0)) P.CaseAbsenteeismDuration = 7;

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "False positive rate", "%lf", (void*) & (P.FalsePositiveRate), 1, 1, 0)) P.FalsePositiveRate = 0.0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "False positive per capita incidence", "%lf", (void*) & (P.FalsePositivePerCapitaIncidence), 1, 1, 0)) P.FalsePositivePerCapitaIncidence = 0.0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "False positive relative incidence by age", "%lf", (void*)P.FalsePositiveAgeRate, NUM_AGE_GROUPS, 1, 0))
			for (j = 0; j < NUM_AGE_GROUPS; j++) P.FalsePositiveAgeRate[j] = 1.0;
	}

	if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Do Severity Analysis", "%i", (void*) & (P.DoSeverity), 1, 1, 0)) P.DoSeverity = 0;
	if(P.DoSeverity == 1)
	{
		//// Means for icdf's.
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_MildToRecovery"		, "%lf", (void*) & (P.Mean_MildToRecovery)		, 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_ILIToRecovery"			, "%lf", (void*) & (P.Mean_ILIToRecovery)		, 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_SARIToRecovery"		, "%lf", (void*) & (P.Mean_SARIToRecovery)		, 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_CriticalToCritRecov"	, "%lf", (void*) & (P.Mean_CriticalToCritRecov)	, 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_CritRecovToRecov"		, "%lf", (void*) & (P.Mean_CritRecovToRecov)	, 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_ILIToSARI"				, "%lf", (void*) & (P.Mean_ILIToSARI)			, 1, 1, 0);
		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Mean_ILIToDeath"			, "%lf", (void*) & (P.Mean_ILIToDeath)			, 1, 1, 0)) P.Mean_ILIToDeath=7.0;
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_SARIToCritical"		, "%lf", (void*) & (P.Mean_SARIToCritical)		, 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_SARIToDeath"			, "%lf", (void*) & (P.Mean_SARIToDeath)			, 1, 1, 0);
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Mean_CriticalToDeath"		, "%lf", (void*) & (P.Mean_CriticalToDeath)		, 1, 1, 0);
		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "MeanTimeToTest", "%lf", (void*)&(P.Mean_TimeToTest), 1, 1, 0)) P.Mean_TimeToTest=0.0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "MeanTimeToTestOffset", "%lf", (void*)&(P.Mean_TimeToTestOffset), 1, 1, 0)) P.Mean_TimeToTestOffset = 1.0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "MeanTimeToTestCriticalOffset", "%lf", (void*)&(P.Mean_TimeToTestCriticalOffset), 1, 1, 0)) P.Mean_TimeToTestCriticalOffset = 1.0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "MeanTimeToTestCritRecovOffset", "%lf", (void*)&(P.Mean_TimeToTestCritRecovOffset), 1, 1, 0)) P.Mean_TimeToTestCritRecovOffset = 1.0;

		//// Get ICDFs
		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "MildToRecovery_icdf", "%lf", (void*)P.MildToRecovery_icdf, CDF_RES + 1, 1, 0))
		{
			P.MildToRecovery_icdf[CDF_RES] = 100;
			for(i = 0; i < CDF_RES; i++)
				P.MildToRecovery_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for(i = 0; i <= CDF_RES; i++) P.MildToRecovery_icdf[i] = exp(-P.MildToRecovery_icdf[i]);

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "ILIToRecovery_icdf", "%lf", (void*)P.ILIToRecovery_icdf, CDF_RES + 1, 1, 0))
		{
			P.ILIToRecovery_icdf[CDF_RES] = 100;
			for(i = 0; i < CDF_RES; i++)
				P.ILIToRecovery_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for(i = 0; i <= CDF_RES; i++) P.ILIToRecovery_icdf[i] = exp(-P.ILIToRecovery_icdf[i]);

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "ILIToDeath_icdf", "%lf", (void*)P.ILIToDeath_icdf, CDF_RES + 1, 1, 0))
		{
			P.ILIToDeath_icdf[CDF_RES] = 100;
			for (i = 0; i < CDF_RES; i++)
				P.ILIToDeath_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for (i = 0; i <= CDF_RES; i++) P.ILIToDeath_icdf[i] = exp(-P.ILIToDeath_icdf[i]);

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "SARIToRecovery_icdf", "%lf", (void*)P.SARIToRecovery_icdf, CDF_RES + 1, 1, 0))
		{
			P.SARIToRecovery_icdf[CDF_RES] = 100;
			for(i = 0; i < CDF_RES; i++)
				P.SARIToRecovery_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for(i = 0; i <= CDF_RES; i++) P.SARIToRecovery_icdf[i] = exp(-P.SARIToRecovery_icdf[i]);

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "CriticalToCritRecov_icdf", "%lf", (void*)P.CriticalToCritRecov_icdf, CDF_RES + 1, 1, 0))
		{
			P.CriticalToCritRecov_icdf[CDF_RES] = 100;
			for(i = 0; i < CDF_RES; i++)
				P.CriticalToCritRecov_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for(i = 0; i <= CDF_RES; i++) P.CriticalToCritRecov_icdf[i] = exp(-P.CriticalToCritRecov_icdf[i]);

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "CritRecovToRecov_icdf", "%lf", (void*)P.CritRecovToRecov_icdf, CDF_RES + 1, 1, 0))
		{
			P.CritRecovToRecov_icdf[CDF_RES] = 100;
			for(i = 0; i < CDF_RES; i++)
				P.CritRecovToRecov_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for(i = 0; i <= CDF_RES; i++) P.CritRecovToRecov_icdf[i] = exp(-P.CritRecovToRecov_icdf[i]);

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "ILIToSARI_icdf", "%lf", (void*)P.ILIToSARI_icdf, CDF_RES + 1, 1, 0))
		{
			P.ILIToSARI_icdf[CDF_RES] = 100;
			for(i = 0; i < CDF_RES; i++)
				P.ILIToSARI_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for(i = 0; i <= CDF_RES; i++) P.ILIToSARI_icdf[i] = exp(-P.ILIToSARI_icdf[i]);

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "SARIToCritical_icdf", "%lf", (void*)P.SARIToCritical_icdf, CDF_RES + 1, 1, 0))
		{
			P.SARIToCritical_icdf[CDF_RES] = 100;
			for(i = 0; i < CDF_RES; i++)
				P.SARIToCritical_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for(i = 0; i <= CDF_RES; i++) P.SARIToCritical_icdf[i] = exp(-P.SARIToCritical_icdf[i]);

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "SARIToDeath_icdf"		, "%lf", (void*)P.SARIToDeath_icdf, CDF_RES + 1, 1, 0))
		{
			P.SARIToDeath_icdf[CDF_RES] = 100;
			for (i = 0; i < CDF_RES; i++)
				P.SARIToDeath_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for (i = 0; i <= CDF_RES; i++) P.SARIToDeath_icdf[i] = exp(-P.SARIToDeath_icdf[i]);

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "CriticalToDeath_icdf", "%lf", (void*)P.CriticalToDeath_icdf, CDF_RES + 1, 1, 0))
		{
			P.CriticalToDeath_icdf[CDF_RES] = 100;
			for(i = 0; i < CDF_RES; i++)
				P.CriticalToDeath_icdf[i] = -log(1 - ((double)i) / CDF_RES);
		}
		for(i = 0; i <= CDF_RES; i++) P.CriticalToDeath_icdf[i] = exp(-P.CriticalToDeath_icdf[i]);

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Prop_Mild_ByAge", "%lf", (void*)P.Prop_Mild_ByAge, NUM_AGE_GROUPS, 1, 0))
			for(i = 0; i < NUM_AGE_GROUPS; i++)
				P.Prop_Mild_ByAge[i] = 0.5;

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Prop_ILI_ByAge", "%lf", (void*)P.Prop_ILI_ByAge, NUM_AGE_GROUPS, 1, 0))
			for(i = 0; i < NUM_AGE_GROUPS; i++)
				P.Prop_ILI_ByAge[i] = 0.3;

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Prop_SARI_ByAge", "%lf", (void*)P.Prop_SARI_ByAge, NUM_AGE_GROUPS, 1, 0))
			for(i = 0; i < NUM_AGE_GROUPS; i++)
				P.Prop_SARI_ByAge[i] = 0.15;

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Prop_Critical_ByAge", "%lf", (void*)P.Prop_Critical_ByAge, NUM_AGE_GROUPS, 1, 0))
			for(i = 0; i < NUM_AGE_GROUPS; i++)
				P.Prop_Critical_ByAge[i] = 0.05;

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "CFR_SARI_ByAge", "%lf", (void*)P.CFR_SARI_ByAge, NUM_AGE_GROUPS, 1, 0))
			for(i = 0; i < NUM_AGE_GROUPS; i++)
				P.CFR_SARI_ByAge[i] = 0.50;

		if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "CFR_Critical_ByAge", "%lf", (void*)P.CFR_Critical_ByAge, NUM_AGE_GROUPS, 1, 0))
			for(i = 0; i < NUM_AGE_GROUPS; i++)
				P.CFR_Critical_ByAge[i] = 0.50;

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "CFR_ILI_ByAge", "%lf", (void*)P.CFR_ILI_ByAge, NUM_AGE_GROUPS, 1, 0))
			for (i = 0; i < NUM_AGE_GROUPS; i++)
				P.CFR_ILI_ByAge[i] = 0.00;
	}

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Bounding box for bitmap", "%lf", (void*) & (P.BoundingBox[0]), 4, 1, 0))
	{
		P.BoundingBox[0] = P.BoundingBox[1] = 0.0;
		P.BoundingBox[2] = P.BoundingBox[3] = 1.0;
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Spatial domain for simulation", "%lf", (void*) & (P.SpatialBoundingBox[0]), 4, 1, 0))
	{
		P.SpatialBoundingBox[0] = P.SpatialBoundingBox[1] = 0.0;
		P.SpatialBoundingBox[2] = P.SpatialBoundingBox[3] = 1.0;
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Grid size", "%lf", (void*) & (P.cwidth), 1, 1, 0)) P.cwidth = 1.0 / 120.0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Use long/lat coord system", "%i", (void*) & (P.DoUTM_coords), 1, 1, 0)) P.DoUTM_coords = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Bitmap scale", "%lf", (void*) & (P.BitmapScale), 1, 1, 0)) P.BitmapScale = 1.0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Bitmap y:x aspect scaling", "%lf", (void*) & (P.BitmapAspectScale), 1, 1, 0)) P.BitmapAspectScale = 1.0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Bitmap movie frame interval", "%i", (void*) & (P.BitmapMovieFrame), 1, 1, 0)) P.BitmapMovieFrame = 250;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output bitmap", "%i", (void*) & (P.OutputBitmap), 1, 1, 0)) P.OutputBitmap = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output bitmap detected", "%i", (void*) & (P.OutputBitmapDetected), 1, 1, 0)) P.OutputBitmapDetected = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output immunity on bitmap", "%i", (void*) & (P.DoImmuneBitmap), 1, 1, 0)) P.DoImmuneBitmap = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output infection tree", "%i", (void*) & (P.DoInfectionTree), 1, 1, 0)) P.DoInfectionTree = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Do one generation", "%i", (void*) & (P.DoOneGen), 1, 1, 0)) P.DoOneGen = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output every realisation", "%i", (void*) & (P.OutputEveryRealisation), 1, 1, 0)) P.OutputEveryRealisation = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum number to sample for correlations", "%i", (void*) & (P.MaxCorrSample), 1, 1, 0)) P.MaxCorrSample = 1000000000;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Assume SI model", "%i", (void*) & (P.DoSI), 1, 1, 0)) P.DoSI = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Assume periodic boundary conditions", "%i", (void*) & (P.DoPeriodicBoundaries), 1, 1, 0)) P.DoPeriodicBoundaries = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Only output non-extinct realisations", "%i", (void*) & (P.OutputOnlyNonExtinct), 1, 1, 0)) P.OutputOnlyNonExtinct = 0;

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Use cases per thousand threshold for area controls", "%i", (void*) & (P.DoPerCapitaTriggers), 1, 1, 0)) P.DoPerCapitaTriggers = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Use global triggers for interventions", "%i", (void*) & (P.DoGlobalTriggers), 1, 1, 0)) P.DoGlobalTriggers = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Use admin unit triggers for interventions", "%i", (void*) & (P.DoAdminTriggers), 1, 1, 0)) P.DoAdminTriggers = 0;
	if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Use ICU case triggers for interventions", "%i", (void*) & (P.DoICUTriggers), 1, 1, 0)) P.DoICUTriggers = 0;
	if (P.DoGlobalTriggers)  P.DoAdminTriggers = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Divisor for per-capita area threshold (default 1000)", "%i", (void*) & (P.IncThreshPop), 1, 1, 0)) P.IncThreshPop = 1000;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Divisor for per-capita global threshold (default 1000)", "%i", (void*) & (P.GlobalIncThreshPop), 1, 1, 0)) P.GlobalIncThreshPop = 1000;


	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of sampling intervals over which cumulative incidence measured for global trigger", "%i", (void*) & (P.TriggersSamplingInterval), 1, 1, 0)) P.TriggersSamplingInterval = 10000000;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of cases detected for treatment", "%lf", (void*) & (P.PostAlertControlPropCasesId), 1, 1, 0)) P.PostAlertControlPropCasesId = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of cases detected before outbreak alert", "%lf", (void*) & (P.PreAlertControlPropCasesId), 1, 1, 0)) P.PreAlertControlPropCasesId = 1.0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger alert on deaths", "%i", (void*)&(P.PreControlClusterIdUseDeaths), 1, 1, 0)) P.PreControlClusterIdUseDeaths = 0;
	if (P.PreControlClusterIdUseDeaths)
	{
		if (P.PreControlClusterIdCaseThreshold == 0)
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of deaths accummulated before alert", "%i", (void*)&(P.PreControlClusterIdCaseThreshold), 1, 1, 0)) P.PreControlClusterIdCaseThreshold = 0;
	}
	else if (P.PreControlClusterIdCaseThreshold == 0)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of detected cases needed before outbreak alert triggered", "%i", (void*) & (P.PreControlClusterIdCaseThreshold), 1, 1, 0)) P.PreControlClusterIdCaseThreshold = 0;
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Alert trigger starts after interventions", "%i", (void*)&(P.DoAlertTriggerAfterInterv), 1, 1, 0)) P.DoAlertTriggerAfterInterv = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Day of year trigger is reached", "%lf", (void*)&(P.PreControlClusterIdCalTime), 1, 1, 0)) P.PreControlClusterIdCalTime = -1;
	if (P.DoAlertTriggerAfterInterv)
	{
		GetInputParameter(ParamFile_dat, PreParamFile_dat, "Day of year interventions start", "%lf", (void*)&(P.PreIntervIdCalTime), 1, 1, 0);
		if (P.PreControlClusterIdCalTime <= P.PreIntervIdCalTime)
			P.DoAlertTriggerAfterInterv = 0;
		else
		{
			P.AlertTriggerAfterIntervThreshold = P.PreControlClusterIdCaseThreshold;
			P.PreControlClusterIdCaseThreshold = 1000;
		}
	}
	else
		P.PreIntervIdCalTime = P.PreControlClusterIdCalTime;
	P.StopCalibration = P.ModelCalibIteration = 0;
	P.SeedingScaling = 1.0;
	P.PreControlClusterIdTime = 0;
	//if (P.DoAlertTriggerAfterInterv) P.ResetSeeds =P.KeepSameSeeds = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of days to accummulate cases/deaths before alert", "%i", (void*)&(P.PreControlClusterIdDuration), 1, 1, 0)) P.PreControlClusterIdDuration = 1000;

	P.PreControlClusterIdHolOffset = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Only use confirmed cases to trigger alert", "%i", (void*) & (P.DoEarlyCaseDiagnosis), 1, 1, 0)) P.DoEarlyCaseDiagnosis = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Only treat mixing groups within places", "%i", (void*) & (P.DoPlaceGroupTreat), 1, 1, 0)) P.DoPlaceGroupTreat = 0;

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Treatment trigger incidence per cell"				, "%lf", (void*) & (P.TreatCellIncThresh)			, 1, 1, 0)) P.TreatCellIncThresh			= 1000000000;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Case isolation trigger incidence per cell"		, "%lf", (void*) & (P.CaseIsolation_CellIncThresh)	, 1, 1, 0)) P.CaseIsolation_CellIncThresh	= P.TreatCellIncThresh; //// changed default to be P.TreatCellIncThresh
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Household quarantine trigger incidence per cell"	, "%lf", (void*) & (P.HHQuar_CellIncThresh)			, 1, 1, 0)) P.HHQuar_CellIncThresh			= P.TreatCellIncThresh; //// changed default to be P.TreatCellIncThresh

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative susceptibility of treated individual", "%lf", (void*) & (P.TreatSuscDrop), 1, 1, 0)) P.TreatSuscDrop = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative infectiousness of treated individual", "%lf", (void*) & (P.TreatInfDrop), 1, 1, 0)) P.TreatInfDrop = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of symptomatic cases resulting in death prevented by treatment", "%lf", (void*) & (P.TreatDeathDrop), 1, 1, 0)) P.TreatDeathDrop = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of symptomatic cases prevented by treatment", "%lf", (void*) & (P.TreatSympDrop), 1, 1, 0)) P.TreatSympDrop = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to treat cell", "%lf", (void*) & (P.TreatDelayMean), 1, 1, 0)) P.TreatDelayMean = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of course of treatment", "%lf", (void*) & (P.TreatCaseCourseLength), 1, 1, 0)) P.TreatCaseCourseLength = 5;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of course of prophylaxis", "%lf", (void*) & (P.TreatProphCourseLength), 1, 1, 0)) P.TreatProphCourseLength = 10;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of detected cases treated", "%lf", (void*) & (P.TreatPropCases), 1, 1, 0)) P.TreatPropCases = 1;
	if (P.DoHouseholds)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of households of cases treated", "%lf", (void*) & (P.TreatPropCaseHouseholds), 1, 1, 0)) P.TreatPropCaseHouseholds = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of household prophylaxis policy", "%lf", (void*) & (P.TreatHouseholdsDuration), 1, 1, 0)) P.TreatHouseholdsDuration = USHRT_MAX / P.TimeStepsPerDay;
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion treated", "%lf", (void*) & (P.TreatPropRadial), 1, 1, 0)) P.TreatPropRadial = 1.0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion treated in radial prophylaxis", "%lf", (void*) & (P.TreatPropRadial), 1, 1, 0)) P.TreatPropRadial = 1.0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Treatment radius", "%lf", (void*) & (P.TreatRadius), 1, 1, 0)) P.TreatRadius = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of place/geographic prophylaxis policy", "%lf", (void*) & (P.TreatPlaceGeogDuration), 1, 1, 0)) P.TreatPlaceGeogDuration = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Treatment start time", "%lf", (void*) & (P.TreatTimeStartBase), 1, 1, 0)) P.TreatTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
	if (P.DoPlaces)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of places treated after case detected", "%lf", (void*)P.TreatPlaceProbCaseId, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.TreatPlaceProbCaseId[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of people treated in targeted places", "%lf", (void*)P.TreatPlaceTotalProp, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.TreatPlaceTotalProp[i] = 0;
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum number of doses available", "%lf", (void*) & (P.TreatMaxCoursesBase), 1, 1, 0)) P.TreatMaxCoursesBase = 1e20;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Start time of additional treatment production", "%lf", (void*) & (P.TreatNewCoursesStartTime), 1, 1, 0)) P.TreatNewCoursesStartTime = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Rate of additional treatment production (courses per day)", "%lf", (void*) & (P.TreatNewCoursesRate), 1, 1, 0)) P.TreatNewCoursesRate = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum number of people targeted with radial prophylaxis per case", "%i", (void*) & (P.TreatMaxCoursesPerCase), 1, 1, 0)) P.TreatMaxCoursesPerCase = 1000000000;


	if (P.DoAdUnits)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Treat administrative units rather than rings", "%i", (void*) & (P.TreatByAdminUnit), 1, 1, 0)) P.TreatByAdminUnit = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Administrative unit divisor for treatment", "%i", (void*) & (P.TreatAdminUnitDivisor), 1, 1, 0)) P.TreatAdminUnitDivisor = 1;
		if ((P.TreatAdminUnitDivisor == 0) || (P.TreatByAdminUnit == 0)) { P.TreatByAdminUnit = 0; P.TreatAdminUnitDivisor = 1; }
	}
	else
	{
		P.TreatAdminUnitDivisor = 1; P.TreatByAdminUnit = 0;
	}

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Vaccination trigger incidence per cell", "%lf", (void*) & (P.VaccCellIncThresh), 1, 1, 0)) P.VaccCellIncThresh = 1000000000;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative susceptibility of vaccinated individual", "%lf", (void*) & (P.VaccSuscDrop), 1, 1, 0)) P.VaccSuscDrop = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative susceptibility of individual vaccinated after switch time", "%lf", (void*) & (P.VaccSuscDrop2), 1, 1, 0)) P.VaccSuscDrop2 = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Switch time at which vaccine efficacy increases", "%lf", (void*) & (P.VaccTimeEfficacySwitch), 1, 1, 0)) P.VaccTimeEfficacySwitch = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Decay rate of vaccine efficacy (per year)", "%lf", (void*) & (P.VaccEfficacyDecay), 1, 1, 0)) P.VaccEfficacyDecay = 0;
	P.VaccEfficacyDecay /= DAYS_PER_YEAR;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative infectiousness of vaccinated individual", "%lf", (void*) & (P.VaccInfDrop), 1, 1, 0)) P.VaccInfDrop = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of symptomatic cases resulting in death prevented by vaccination", "%lf", (void*) & (P.VaccMortDrop), 1, 1, 0)) P.VaccMortDrop = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of symptomatic cases prevented by vaccination", "%lf", (void*) & (P.VaccSympDrop), 1, 1, 0)) P.VaccSympDrop = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to vaccinate", "%lf", (void*) & (P.VaccDelayMean), 1, 1, 0)) P.VaccDelayMean = 0;

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay from vaccination to full protection", "%lf", (void*) & (P.VaccTimeToEfficacy), 1, 1, 0)) P.VaccTimeToEfficacy = 0;

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Years between rounds of vaccination", "%lf", (void*) & (P.VaccCampaignInterval), 1, 1, 0)) P.VaccCampaignInterval = 1e10;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Max vaccine doses per day", "%i", (void*) & (P.VaccDosePerDay), 1, 1, 0)) P.VaccDosePerDay = -1;
	P.VaccCampaignInterval *= DAYS_PER_YEAR;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum number of rounds of vaccination", "%i", (void*) & (P.VaccMaxRounds), 1, 1, 0)) P.VaccMaxRounds = 1;
	if (P.DoHouseholds)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of households of cases vaccinated", "%lf", (void*) & (P.VaccPropCaseHouseholds), 1, 1, 0)) P.VaccPropCaseHouseholds = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of household vaccination policy", "%lf", (void*) & (P.VaccHouseholdsDuration), 1, 1, 0)) P.VaccHouseholdsDuration = USHRT_MAX / P.TimeStepsPerDay;
	}

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Vaccination start time", "%lf", (void*) & (P.VaccTimeStartBase), 1, 1, 0)) P.VaccTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of population vaccinated", "%lf", (void*) & (P.VaccProp), 1, 1, 0)) P.VaccProp = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Time taken to reach max vaccination coverage (in years)", "%lf", (void*) & (P.VaccCoverageIncreasePeriod), 1, 1, 0)) P.VaccCoverageIncreasePeriod = 0;
	P.VaccCoverageIncreasePeriod *= DAYS_PER_YEAR;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Time to start geographic vaccination", "%lf", (void*) & (P.VaccTimeStartGeo), 1, 1, 0)) P.VaccTimeStartGeo = 1e10;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Vaccination radius", "%lf", (void*) & (P.VaccRadius), 1, 1, 0)) P.VaccRadius = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Minimum radius from case to vaccinate", "%lf", (void*) & (P.VaccMinRadius), 1, 1, 0)) P.VaccMinRadius = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum number of vaccine courses available", "%lf", (void*) & (P.VaccMaxCoursesBase), 1, 1, 0)) P.VaccMaxCoursesBase = 1e20;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Start time of additional vaccine production", "%lf", (void*) & (P.VaccNewCoursesStartTime), 1, 1, 0)) P.VaccNewCoursesStartTime = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "End time of additional vaccine production", "%lf", (void*) & (P.VaccNewCoursesEndTime), 1, 1, 0)) P.VaccNewCoursesEndTime = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Rate of additional vaccine production (courses per day)", "%lf", (void*) & (P.VaccNewCoursesRate), 1, 1, 0)) P.VaccNewCoursesRate = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Apply mass rather than reactive vaccination", "%i", (void*) & (P.DoMassVacc), 1, 1, 0)) P.DoMassVacc = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Priority age range for mass vaccination", "%i", (void*)P.VaccPriorityGroupAge, 2, 1, 0)) { P.VaccPriorityGroupAge[0] = 1; P.VaccPriorityGroupAge[1] = 0; }
	if (P.DoAdUnits)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Vaccinate administrative units rather than rings", "%i", (void*) & (P.VaccByAdminUnit), 1, 1, 0)) P.VaccByAdminUnit = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Administrative unit divisor for vaccination", "%i", (void*) & (P.VaccAdminUnitDivisor), 1, 1, 0)) P.VaccAdminUnitDivisor = 1;
		if ((P.VaccAdminUnitDivisor == 0) || (P.VaccByAdminUnit == 0)) P.VaccAdminUnitDivisor = 1;
	}
	else
	{
		P.VaccAdminUnitDivisor = 1; P.VaccByAdminUnit = 0;
	}

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Movement restrictions trigger incidence per cell", "%i", (void*) & (P.MoveRestrCellIncThresh), 1, 1, 0)) P.MoveRestrCellIncThresh = 1000000000;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to start movement restrictions", "%lf", (void*) & (P.MoveDelayMean), 1, 1, 0)) P.MoveDelayMean = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of movement restrictions", "%lf", (void*) & (P.MoveRestrDuration), 1, 1, 0)) P.MoveRestrDuration = 7;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual movements after restrictions", "%lf", (void*) & (P.MoveRestrEffect), 1, 1, 0)) P.MoveRestrEffect = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Minimum radius of movement restrictions", "%lf", (void*) & (P.MoveRestrRadius), 1, 1, 0)) P.MoveRestrRadius = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Movement restrictions start time", "%lf", (void*) & (P.MoveRestrTimeStartBase), 1, 1, 0)) P.MoveRestrTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Impose blanket movement restrictions", "%i", (void*) & (P.DoBlanketMoveRestr), 1, 1, 0)) P.DoBlanketMoveRestr = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Movement restrictions only once", "%i", (void*) & (P.DoMoveRestrOnceOnly), 1, 1, 0)) P.DoMoveRestrOnceOnly = 0;
	if (P.DoMoveRestrOnceOnly) P.DoMoveRestrOnceOnly = 4;
	if (P.DoAdUnits)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Movement restrictions in administrative units rather than rings", "%i", (void*) & (P.MoveRestrByAdminUnit), 1, 1, 0)) P.MoveRestrByAdminUnit = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Administrative unit divisor for movement restrictions", "%i", (void*) & (P.MoveRestrAdminUnitDivisor), 1, 1, 0)) P.MoveRestrAdminUnitDivisor = 1;
		if ((P.MoveRestrAdminUnitDivisor == 0) || (P.MoveRestrByAdminUnit == 0)) P.MoveRestrAdminUnitDivisor = 1;
	}
	else
	{
		P.MoveRestrAdminUnitDivisor = 1; P.MoveRestrByAdminUnit = 0;
	}

	//Intervention delays and durations by admin unit: ggilani 16/03/20
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Include intervention delays by admin unit", "%i", (void*) & (P.DoInterventionDelaysByAdUnit), 1, 1, 0)) P.DoInterventionDelaysByAdUnit = 0;
	if (P.DoInterventionDelaysByAdUnit)
	{
		//Set up arrays to temporarily store parameters per admin unit
		double AdunitDelayToSocialDistance	[MAX_ADUNITS];
		double AdunitDelayToHQuarantine		[MAX_ADUNITS];
		double AdunitDelayToCaseIsolation	[MAX_ADUNITS];
		double AdunitDelayToPlaceClose		[MAX_ADUNITS];
		double AdunitDurationSocialDistance	[MAX_ADUNITS];
		double AdunitDurationHQuarantine	[MAX_ADUNITS];
		double AdunitDurationCaseIsolation	[MAX_ADUNITS];
		double AdunitDurationPlaceClose		[MAX_ADUNITS];

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to social distancing by admin unit"			, "%lf", (void*)AdunitDelayToSocialDistance	, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDelayToSocialDistance	[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to household quarantine by admin unit"		, "%lf", (void*)AdunitDelayToHQuarantine	, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDelayToHQuarantine		[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to case isolation by admin unit"			, "%lf", (void*)AdunitDelayToCaseIsolation	, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDelayToCaseIsolation	[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to place closure by admin unit"				, "%lf", (void*)AdunitDelayToPlaceClose		, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDelayToPlaceClose		[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of social distancing by admin unit"		, "%lf", (void*)AdunitDurationSocialDistance, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDurationSocialDistance	[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of household quarantine by admin unit"	, "%lf", (void*)AdunitDurationHQuarantine	, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDurationHQuarantine		[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of case isolation by admin unit"			, "%lf", (void*)AdunitDurationCaseIsolation	, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDurationCaseIsolation	[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of place closure by admin unit"			, "%lf", (void*)AdunitDurationPlaceClose	, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDurationPlaceClose		[i] = 0;

		for (i = 0; i < P.NumAdunits; i++)
		{
			AdUnits[i].SocialDistanceDelay			= AdunitDelayToSocialDistance	[i];
			AdUnits[i].SocialDistanceDuration		= AdunitDurationSocialDistance	[i];
			AdUnits[i].HQuarantineDelay				= AdunitDelayToHQuarantine		[i];
			AdUnits[i].HQuarantineDuration			= AdunitDurationHQuarantine		[i];
			AdUnits[i].CaseIsolationDelay			= AdunitDelayToCaseIsolation	[i];
			AdUnits[i].CaseIsolationPolicyDuration	= AdunitDurationCaseIsolation	[i];
			AdUnits[i].PlaceCloseDelay				= AdunitDelayToPlaceClose		[i];
			AdUnits[i].PlaceCloseDuration			= AdunitDurationPlaceClose		[i];
		}
	}

	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****
	///// **** DIGITAL CONTACT TRACING
	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****

	//New code for digital contact tracing - ggilani: 09/03/20
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Include digital contact tracing", "%i", (void*) & (P.DoDigitalContactTracing), 1, 1, 0)) P.DoDigitalContactTracing = 0;
	if (P.DoDigitalContactTracing)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Digital contact tracing trigger incidence per cell", "%lf", (void*) & (P.DigitalContactTracing_CellIncThresh), 1, 1, 0)) P.DigitalContactTracing_CellIncThresh = 1000000000;

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of population or households covered by digital contact tracing", "%lf", (void*) & (P.PropPopUsingDigitalContactTracing), 1, 1, 0)) P.PropPopUsingDigitalContactTracing = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of smartphone users by age", "%lf", (void*)P.ProportionSmartphoneUsersByAge, NUM_AGE_GROUPS, 1, 0))
		{
			for (i = 0; i < NUM_AGE_GROUPS; i++)
			{
				P.ProportionSmartphoneUsersByAge[i] = 1;
			}
		}
		if (P.DoPlaces)
		{
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Cluster digital app clusters by household", "%i", (void*) & (P.ClusterDigitalContactUsers), 1, 1, 0)) P.ClusterDigitalContactUsers = 0; // by default, don't cluster by location
		}
		else
		{
			P.ClusterDigitalContactUsers = 0;
		}
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of digital contacts who self-isolate", "%lf", (void*) & (P.ProportionDigitalContactsIsolate), 1, 1, 0)) P.ProportionDigitalContactsIsolate = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum number of contacts to trace per index case", "%i", (void*)&(P.MaxDigitalContactsToTrace), 1, 1, 0)) P.MaxDigitalContactsToTrace = MAX_CONTACTS;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay between isolation of index case and contacts", "%lf", (void*) & (P.DigitalContactTracingDelay), 1, 1, 0)) P.DigitalContactTracingDelay = P.TimeStep;
		//we really need one timestep between to make sure contact is not processed before index
		if (P.DigitalContactTracingDelay == 0) P.DigitalContactTracingDelay = P.TimeStep;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Length of self-isolation for digital contacts", "%lf", (void*) & (P.LengthDigitalContactIsolation), 1, 1, 0)) P.LengthDigitalContactIsolation = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Spatial scaling factor - digital contact tracing", "%lf", (void*) & (P.ScalingFactorSpatialDigitalContacts), 1, 1, 0)) P.ScalingFactorSpatialDigitalContacts = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place scaling factor - digital contact tracing", "%lf", (void*)&(P.ScalingFactorPlaceDigitalContacts), 1, 1, 0)) P.ScalingFactorPlaceDigitalContacts = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Digital contact tracing start time", "%lf", (void*) & (P.DigitalContactTracingTimeStartBase), 1, 1, 0)) P.DigitalContactTracingTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of digital contact tracing policy", "%lf", (void*) & (P.DigitalContactTracingPolicyDuration), 1, 1, 0)) P.DigitalContactTracingPolicyDuration = 7;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output digital contact tracing", "%i", (void*) & (P.OutputDigitalContactTracing), 1, 1, 0)) P.OutputDigitalContactTracing = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output digital contact distribution", "%i", (void*)&(P.OutputDigitalContactDist), 1, 1, 0)) P.OutputDigitalContactDist = 0;

		//if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Include household contacts in digital contact tracing", "%i", (void*) & (P.IncludeHouseholdDigitalContactTracing), 1, 1, 0)) P.IncludeHouseholdDigitalContactTracing = 1;
		//if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Include place group contacts in digital contact tracing", "%i", (void*) & (P.IncludePlaceGroupDigitalContactTracing), 1, 1, 0)) P.IncludePlaceGroupDigitalContactTracing = 1;

		//added admin unit specific delays by admin unit
		if (P.DoInterventionDelaysByAdUnit)
		{
			double AdunitDelayToDCT[MAX_ADUNITS];
			double AdunitDurationDCT[MAX_ADUNITS];

			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to digital contact tracing by admin unit", "%lf", (void*)AdunitDelayToDCT, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDelayToDCT[i] = 0;
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of digital contact tracing by admin unit", "%lf", (void*)AdunitDurationDCT, P.NumAdunits, 1, 0)) for (i = 0; i < P.NumAdunits; i++) AdunitDurationDCT[i] = 0;
			for (i = 0; i < P.NumAdunits; i++)
			{
				AdUnits[i].DCTDelay = AdunitDelayToDCT[i];
				AdUnits[i].DCTDuration = AdunitDurationDCT[i];
			}
		}
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Isolate index cases in digital contact tracing", "%i", (void*)&(P.DCTIsolateIndexCases), 1, 1, 0)) P.DCTIsolateIndexCases = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual contacts after digital contact tracing isolation", "%lf", (void*)&(P.DCTCaseIsolationEffectiveness), 1, 1, 0)) P.DCTCaseIsolationEffectiveness = P.CaseIsolationEffectiveness;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual household contacts after digital contact tracing isolation", "%lf", (void*)&(P.DCTCaseIsolationHouseEffectiveness), 1, 1, 0)) P.DCTCaseIsolationHouseEffectiveness = P.CaseIsolationHouseEffectiveness;
		//initialise total number of users to 0
		P.NDigitalContactUsers = 0;
		P.NDigitalHouseholdUsers = 0;

		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay between symptom onset and isolation for index case", "%lf", (void*)&(P.DelayFromIndexCaseDetectionToDCTIsolation), 1, 1, 0)) P.DelayFromIndexCaseDetectionToDCTIsolation = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Test index cases and contacts", "%i", (void*)&(P.DoDCTTest), 1, 1, 0)) P.DoDCTTest = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to test index case", "%lf", (void*)&(P.DelayToTestIndexCase), 1, 1, 0)) P.DelayToTestIndexCase = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to test DCT contacts", "%lf", (void*)&(P.DelayToTestDCTContacts), 1, 1, 0)) P.DelayToTestDCTContacts = 7;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Testing specificity - DCT", "%lf", (void*)&(P.SpecificityDCT), 1, 1, 0)) P.SpecificityDCT = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Testing sensitivity - DCT", "%lf", (void*)&(P.SensitivityDCT), 1, 1, 0)) P.SensitivityDCT = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Find contacts of digital contacts", "%i", (void*)&(P.FindContactsOfDCTContacts), 1, 1, 0)) P.FindContactsOfDCTContacts = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Remove contacts of a negative index case", "%i", (void*)&(P.RemoveContactsOfNegativeIndexCase), 1, 1, 0)) P.RemoveContactsOfNegativeIndexCase = 0;
	}
	else
	{
		//Set these to 1 so it doesn't interfere with code if we aren't using digital contact tracing.

		P.ScalingFactorSpatialDigitalContacts = 1;
		P.ScalingFactorPlaceDigitalContacts = 1;
	}

	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****
	///// **** PLACE CLOSURE
	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****


	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger incidence per cell for place closure", "%i", (void*) & (P.PlaceCloseCellIncThresh1), 1, 1, 0)) P.PlaceCloseCellIncThresh1 = 1000000000;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger incidence per cell for second place closure", "%i", (void*)&(P.PlaceCloseCellIncThresh2), 1, 1, 0)) P.PlaceCloseCellIncThresh2 = 1000000000;
	if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger incidence per cell for end of place closure", "%i", (void*) & (P.PlaceCloseCellIncStopThresh), 1, 1, 0)) P.PlaceCloseCellIncStopThresh = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to start place closure", "%lf", (void*) & (P.PlaceCloseDelayMean), 1, 1, 0)) P.PlaceCloseDelayMean = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of place closure", "%lf", (void*) & (P.PlaceCloseDurationBase), 1, 1, 0)) P.PlaceCloseDurationBase = 7;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of second place closure", "%lf", (void*) & (P.PlaceCloseDuration2), 1, 1, 0)) P.PlaceCloseDuration2 = 7;
	if (P.DoPlaces)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of places remaining open after closure by place type", "%lf", (void*)P.PlaceCloseEffect, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.PlaceCloseEffect[i] = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportional attendance after closure by place type", "%lf", (void*)P.PlaceClosePropAttending, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.PlaceClosePropAttending[i] = 0;
	}
	if (P.DoHouseholds)
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rate after closure", "%lf", (void*)& P.PlaceCloseHouseholdRelContact, 1, 1, 0)) P.PlaceCloseHouseholdRelContact = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rate after closure", "%lf", (void*)& P.PlaceCloseSpatialRelContact, 1, 1, 0)) P.PlaceCloseSpatialRelContact = 1;

	if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Include holidays", "%i", (void*) & (P.DoHolidays), 1, 1, 0)) P.DoHolidays = 0;
	if (P.DoHolidays)
	{
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Proportion of places remaining open during holidays by place type", "%lf", (void*)P.HolidayEffect, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.HolidayEffect[i] = 1;
		if (!GetInputParameter2(PreParamFile_dat, AdminFile_dat, "Number of holidays", "%i", (void*) & (P.NumHolidays), 1, 1, 0)) P.NumHolidays = 0;
		if (P.NumHolidays > DAYS_PER_YEAR) P.NumHolidays = DAYS_PER_YEAR;
		if (P.NumHolidays > 0)
		{
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Holiday start times", "%lf", (void*)P.HolidayStartTime, P.NumHolidays, 1, 0);
			GetInputParameter(PreParamFile_dat, AdminFile_dat, "Holiday durations", "%lf", (void*)P.HolidayDuration, P.NumHolidays, 1, 0);
		}
	}
	else
		P.NumHolidays = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Minimum radius for place closure", "%lf", (void*) & (P.PlaceCloseRadius), 1, 1, 0)) P.PlaceCloseRadius = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place closure start time", "%lf", (void*) & (P.PlaceCloseTimeStartBase), 1, 1, 0)) P.PlaceCloseTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place closure second start time", "%lf", (void*) & (P.PlaceCloseTimeStartBase2), 1, 1, 0)) P.PlaceCloseTimeStartBase2 = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Places close only once", "%i", (void*) & (P.DoPlaceCloseOnceOnly), 1, 1, 0)) P.DoPlaceCloseOnceOnly = 0;
	if (P.DoPlaceCloseOnceOnly) P.DoPlaceCloseOnceOnly = 4;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place closure incidence threshold", "%i", (void*) & (P.PlaceCloseIncTrig1), 1, 1, 0)) P.PlaceCloseIncTrig1 = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place closure second incidence threshold", "%i", (void*)&(P.PlaceCloseIncTrig2), 1, 1, 0)) P.PlaceCloseIncTrig2 = P.PlaceCloseIncTrig1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place closure fractional incidence threshold", "%lf", (void*) & (P.PlaceCloseFracIncTrig), 1, 1, 0)) P.PlaceCloseFracIncTrig = 0;
	if ((P.DoAdUnits) && (P.DoPlaces))
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place closure in administrative units rather than rings", "%i", (void*) & (P.PlaceCloseByAdminUnit), 1, 1, 0)) P.PlaceCloseByAdminUnit = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Administrative unit divisor for place closure", "%i", (void*) & (P.PlaceCloseAdminUnitDivisor), 1, 1, 0)) P.PlaceCloseAdminUnitDivisor = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place types to close for admin unit closure (0/1 array)", "%i", (void*) & (P.PlaceCloseAdunitPlaceTypes), P.PlaceTypeNum, 1, 0))
			for (i = 0; i < P.PlaceTypeNum; i++) P.PlaceCloseAdunitPlaceTypes[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Cumulative proportion of place members needing to become sick for admin unit closure", "%lf", (void*) & (P.PlaceCloseCasePropThresh), 1, 1, 0)) P.PlaceCloseCasePropThresh = 2;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of places in admin unit needing to pass threshold for place closure", "%lf", (void*) & (P.PlaceCloseAdunitPropThresh), 1, 1, 0)) P.PlaceCloseAdunitPropThresh = 2;
		if ((P.PlaceCloseAdminUnitDivisor < 1) || (P.PlaceCloseByAdminUnit == 0)) P.PlaceCloseAdminUnitDivisor = 1;
	}
	else
	{
		P.PlaceCloseAdminUnitDivisor = 1; P.PlaceCloseByAdminUnit = 0;
	}

	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****
	///// **** SOCIAL DISTANCING
	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger incidence per cell for social distancing", "%i", (void*) & (P.SocDistCellIncThresh), 1, 1, 0)) P.SocDistCellIncThresh = 1000000000;
	if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger incidence per cell for end of social distancing", "%i", (void*) & (P.SocDistCellIncStopThresh), 1, 1, 0)) P.SocDistCellIncStopThresh = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of social distancing", "%lf", (void*) & (P.SocDistDuration), 1, 1, 0)) P.SocDistDuration = 7;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of social distancing after change", "%lf", (void*) & (P.SocDistDuration2), 1, 1, 0)) P.SocDistDuration2 = 7;
	if (P.DoPlaces)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative place contact rate given social distancing by place type", "%lf", (void*)P.SocDistPlaceEffect, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.SocDistPlaceEffect[i] = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative place contact rate given enhanced social distancing by place type", "%lf", (void*)P.EnhancedSocDistPlaceEffect, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.EnhancedSocDistPlaceEffect[i] = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative place contact rate given social distancing by place type after change", "%lf", (void*)P.SocDistPlaceEffect2, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.SocDistPlaceEffect2[i] = P.SocDistPlaceEffect[i];
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative place contact rate given enhanced social distancing by place type after change", "%lf", (void*)P.EnhancedSocDistPlaceEffect2, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.EnhancedSocDistPlaceEffect2[i] = P.EnhancedSocDistPlaceEffect[i];
	}
	if (P.DoHouseholds)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rate given social distancing", "%lf", (void*)&P.SocDistHouseholdEffect, 1, 1, 0)) P.SocDistHouseholdEffect = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rate given enhanced social distancing", "%lf", (void*)&P.EnhancedSocDistHouseholdEffect, 1, 1, 0)) P.EnhancedSocDistHouseholdEffect = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rate given social distancing  after change", "%lf", (void*)&P.SocDistHouseholdEffect2, 1, 1, 0)) P.SocDistHouseholdEffect2 = P.SocDistHouseholdEffect;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rate given enhanced social distancing after change", "%lf", (void*)&P.EnhancedSocDistHouseholdEffect2, 1, 1, 0)) P.EnhancedSocDistHouseholdEffect2 = P.EnhancedSocDistHouseholdEffect;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Cluster compliance with enhanced social distancing by household", "%i", (void*)&P.EnhancedSocDistClusterByHousehold, 1, 1, 0)) P.EnhancedSocDistClusterByHousehold = 0;
	}
	else
		P.EnhancedSocDistClusterByHousehold = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rate given social distancing", "%lf", (void*)& P.SocDistSpatialEffect, 1, 1, 0)) P.SocDistSpatialEffect = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rate given social distancing after change", "%lf", (void*)&P.SocDistSpatialEffect2, 1, 1, 0)) P.SocDistSpatialEffect2 = P.SocDistSpatialEffect;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Minimum radius for social distancing", "%lf", (void*) & (P.SocDistRadius), 1, 1, 0)) P.SocDistRadius = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Social distancing start time", "%lf", (void*) & (P.SocDistTimeStartBase), 1, 1, 0)) P.SocDistTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay for change in effectiveness of social distancing", "%lf", (void*)&(P.SocDistChangeDelay), 1, 1, 0)) P.SocDistChangeDelay = USHRT_MAX / P.TimeStepsPerDay;
	if(!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion compliant with enhanced social distancing by age group", "%lf", (void*)P.EnhancedSocDistProportionCompliant, NUM_AGE_GROUPS, 1, 0))
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion compliant with enhanced social distancing", "%lf", (void*)&t, 1, 1, 0)) t = 0;
		for (i = 0; i < NUM_AGE_GROUPS; i++)
			P.EnhancedSocDistProportionCompliant[i] = t;
	}
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rate given enhanced social distancing", "%lf", (void*)& P.EnhancedSocDistSpatialEffect, 1, 1, 0)) P.EnhancedSocDistSpatialEffect = 1;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rate given enhanced social distancing after change", "%lf", (void*)&P.EnhancedSocDistSpatialEffect2, 1, 1, 0)) P.EnhancedSocDistSpatialEffect2 = P.EnhancedSocDistSpatialEffect;

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Social distancing only once", "%i", (void*) & (P.DoSocDistOnceOnly), 1, 1, 0)) P.DoSocDistOnceOnly = 0;
	if (P.DoSocDistOnceOnly) P.DoSocDistOnceOnly = 4;

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Airport closure effectiveness", "%lf", (void*) & (P.AirportCloseEffectiveness), 1, 1, 0)) P.AirportCloseEffectiveness = 0;
	P.AirportCloseEffectiveness = 1.0 - P.AirportCloseEffectiveness;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Airport closure start time", "%lf", (void*) & (P.AirportCloseTimeStartBase), 1, 1, 0)) P.AirportCloseTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Airport closure duration", "%lf", (void*) & (P.AirportCloseDuration), 1, 1, 0)) P.AirportCloseDuration = USHRT_MAX / P.TimeStepsPerDay;

	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****
	///// **** HOUSEHOLD QUARANTINE
	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****

	if (P.DoHouseholds)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Retrigger household quarantine with each new case in quarantine window", "%i", (void*) & (P.DoHQretrigger), 1, 1, 0)) P.DoHQretrigger =0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Household quarantine start time", "%lf", (void*) & (P.HQuarantineTimeStartBase), 1, 1, 0)) P.HQuarantineTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to start household quarantine", "%lf", (void*) & (P.HQuarantineDelay), 1, 1, 0)) P.HQuarantineDelay = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Length of time households are quarantined", "%lf", (void*) & (P.HQuarantineHouseDuration), 1, 1, 0)) P.HQuarantineHouseDuration = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of household quarantine policy", "%lf", (void*) & (P.HQuarantinePolicyDuration), 1, 1, 0)) P.HQuarantinePolicyDuration = USHRT_MAX / P.TimeStepsPerDay;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rate after quarantine", "%lf", (void*) & (P.HQuarantineHouseEffect), 1, 1, 0)) P.HQuarantineHouseEffect = 1;
		if (P.DoPlaces)
		{
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual place contacts after household quarantine by place type", "%lf", (void*)P.HQuarantinePlaceEffect, P.PlaceTypeNum, 1, 0))
				for (i = 0; i < NUM_PLACE_TYPES; i++) P.HQuarantinePlaceEffect[i] = 1;
		}
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual spatial contacts after household quarantine", "%lf", (void*) & (P.HQuarantineSpatialEffect), 1, 1, 0)) P.HQuarantineSpatialEffect = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Household level compliance with quarantine", "%lf", (void*) & (P.HQuarantinePropHouseCompliant), 1, 1, 0)) P.HQuarantinePropHouseCompliant = 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Individual level compliance with quarantine", "%lf", (void*) & (P.HQuarantinePropIndivCompliant), 1, 1, 0)) P.HQuarantinePropIndivCompliant = 1;
	}
	else
		P.HQuarantineTimeStartBase = 1e10;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Case isolation start time", "%lf", (void*) & (P.CaseIsolationTimeStartBase), 1, 1, 0)) P.CaseIsolationTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of detected cases isolated", "%lf", (void*) & (P.CaseIsolationProp), 1, 1, 0)) P.CaseIsolationProp = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Delay to start case isolation", "%lf", (void*) & (P.CaseIsolationDelay), 1, 1, 0)) P.CaseIsolationDelay = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of case isolation", "%lf", (void*) & (P.CaseIsolationDuration), 1, 1, 0)) P.CaseIsolationDuration = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of case isolation policy", "%lf", (void*) & (P.CaseIsolationPolicyDuration), 1, 1, 0)) P.CaseIsolationPolicyDuration = 1e10;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual contacts after case isolation", "%lf", (void*) & (P.CaseIsolationEffectiveness), 1, 1, 0)) P.CaseIsolationEffectiveness = 1;
	if (P.DoHouseholds)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual household contacts after case isolation", "%lf", (void*) & (P.CaseIsolationHouseEffectiveness), 1, 1, 0))
			P.CaseIsolationHouseEffectiveness = P.CaseIsolationEffectiveness;
	}

	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****
	///// **** VARIABLE EFFICACIES OVER TIME
	///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// **** ///// ****

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Vary efficacies over time", "%i", (void*) & (P.VaryEfficaciesOverTime), 1, 1, 0)) P.VaryEfficaciesOverTime = 0;
	//// **** number of change times
	if (!P.VaryEfficaciesOverTime)
	{
		P.Num_SD_ChangeTimes = 1;
		P.Num_CI_ChangeTimes = 1;
		P.Num_HQ_ChangeTimes = 1;
		P.Num_PC_ChangeTimes = 1;
		P.Num_DCT_ChangeTimes = 1;
	}
	else
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of change times for levels of social distancing"		, "%i", (void*) & (P.Num_SD_ChangeTimes)	, 1, 1, 0)) P.Num_SD_ChangeTimes	= 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of change times for levels of case isolation"			, "%i", (void*) & (P.Num_CI_ChangeTimes)	, 1, 1, 0)) P.Num_CI_ChangeTimes	= 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of change times for levels of household quarantine"	, "%i", (void*) & (P.Num_HQ_ChangeTimes)	, 1, 1, 0)) P.Num_HQ_ChangeTimes	= 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of change times for levels of place closure"			, "%i", (void*) & (P.Num_PC_ChangeTimes)	, 1, 1, 0)) P.Num_PC_ChangeTimes	= 1;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of change times for levels of digital contact tracing"	, "%i", (void*) & (P.Num_DCT_ChangeTimes)	, 1, 1, 0)) P.Num_DCT_ChangeTimes	= 1;
	}

	//// **** change times:
	//// By default, initialize first change time to zero and all subsequent change times to occur after simulation time, i.e. single value of efficacy for social distancing.
	P.SD_ChangeTimes	[0] = 0;
	P.CI_ChangeTimes	[0] = 0;
	P.HQ_ChangeTimes	[0] = 0;
	P.PC_ChangeTimes	[0] = 0;
	P.DCT_ChangeTimes	[0] = 0;
	for (int ChangeTime = 1; ChangeTime < MAX_NUM_INTERVENTION_CHANGE_TIMES; ChangeTime++)
	{
		P.SD_ChangeTimes	[ChangeTime] = 1e10;
		P.CI_ChangeTimes	[ChangeTime] = 1e10;
		P.HQ_ChangeTimes	[ChangeTime] = 1e10;
		P.PC_ChangeTimes	[ChangeTime] = 1e10;
		P.DCT_ChangeTimes	[ChangeTime] = 1e10;
	}
	//// Get real values from (pre)param file
	GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Change times for levels of social distancing"		, "%lf", (void*)P.SD_ChangeTimes	, P.Num_SD_ChangeTimes	, 1, 0);
	GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Change times for levels of case isolation"			, "%lf", (void*)P.CI_ChangeTimes	, P.Num_CI_ChangeTimes	, 1, 0);
	GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Change times for levels of household quarantine"	, "%lf", (void*)P.HQ_ChangeTimes	, P.Num_HQ_ChangeTimes	, 1, 0);
	GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Change times for levels of place closure"			, "%lf", (void*)P.PC_ChangeTimes	, P.Num_PC_ChangeTimes	, 1, 0);
	GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Change times for levels of digital contact tracing", "%lf", (void*)P.DCT_ChangeTimes, P.Num_DCT_ChangeTimes	, 1, 0);

	// initialize to zero (regardless of whether doing places or households).
	for (int ChangeTime = 0; ChangeTime < MAX_NUM_INTERVENTION_CHANGE_TIMES; ChangeTime++)
	{
		//// **** "efficacies"
		//// spatial
		P.SD_SpatialEffects_OverTime				[ChangeTime] = 0;
		P.Enhanced_SD_SpatialEffects_OverTime		[ChangeTime] = 0;
		P.CI_SpatialAndPlaceEffects_OverTime		[ChangeTime] = 0;
		P.HQ_SpatialEffects_OverTime				[ChangeTime] = 0;
		P.PC_SpatialEffects_OverTime				[ChangeTime] = 0;
		P.DCT_SpatialAndPlaceEffects_OverTime		[ChangeTime] = 0;

		//// Household
		P.SD_HouseholdEffects_OverTime			[ChangeTime] = 0;
		P.Enhanced_SD_HouseholdEffects_OverTime	[ChangeTime] = 0;
		P.CI_HouseholdEffects_OverTime			[ChangeTime] = 0;
		P.HQ_HouseholdEffects_OverTime			[ChangeTime] = 0;
		P.PC_HouseholdEffects_OverTime			[ChangeTime] = 0;
		P.DCT_HouseholdEffects_OverTime			[ChangeTime] = 0;

		//// place
		for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
		{
			P.SD_PlaceEffects_OverTime			[ChangeTime][PlaceType] = 0;
			P.Enhanced_SD_PlaceEffects_OverTime	[ChangeTime][PlaceType] = 0;
			P.HQ_PlaceEffects_OverTime			[ChangeTime][PlaceType] = 0;
			P.PC_PlaceEffects_OverTime			[ChangeTime][PlaceType] = 0;
		}
		P.PC_Durs_OverTime[ChangeTime] = 0;

		//// **** compliance
		P.CI_Prop_OverTime					[ChangeTime] = 0;
		P.HQ_Individual_PropComply_OverTime	[ChangeTime] = 0;
		P.HQ_Household_PropComply_OverTime	[ChangeTime] = 0;
		P.DCT_Prop_OverTime					[ChangeTime] = 0;
	}


	//// **** "efficacies": by default, initialize to values read in previously.
	///// spatial contact rates rates over time (and place too for CI and DCT)
	//// soc dist
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rates over time given social distancing"			, "%lf", (void*)P.SD_SpatialEffects_OverTime, P.Num_SD_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_SD_ChangeTimes; ChangeTime++) P.SD_SpatialEffects_OverTime[ChangeTime] = P.SocDistSpatialEffect; //// by default, initialize to Relative spatial contact rate given social distancing
	//// enhanced soc dist
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rates over time given enhanced social distancing"	, "%lf", (void*)P.Enhanced_SD_SpatialEffects_OverTime, P.Num_SD_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_SD_ChangeTimes; ChangeTime++) P.Enhanced_SD_SpatialEffects_OverTime[ChangeTime] = P.EnhancedSocDistSpatialEffect; //// by default, initialize to Relative spatial contact rate given enhanced social distancing
	//// case isolation
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual contacts after case isolation over time"							, "%lf", (void*)P.CI_SpatialAndPlaceEffects_OverTime, P.Num_CI_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_CI_ChangeTimes; ChangeTime++) P.CI_SpatialAndPlaceEffects_OverTime[ChangeTime] = P.CaseIsolationEffectiveness;
	//// household quarantine
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual spatial contacts over time after household quarantine"				, "%lf", (void*)P.HQ_SpatialEffects_OverTime, P.Num_HQ_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_HQ_ChangeTimes; ChangeTime++) P.HQ_SpatialEffects_OverTime[ChangeTime] = P.HQuarantineSpatialEffect;
	//// place closure
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative spatial contact rates over time after place closure"				, "%lf", (void*)P.PC_SpatialEffects_OverTime, P.Num_PC_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_PC_ChangeTimes; ChangeTime++) P.PC_SpatialEffects_OverTime[ChangeTime] = P.PlaceCloseSpatialRelContact;
	//// digital contact tracing
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual contacts after digital contact tracing isolation over time"			, "%lf", (void*)P.DCT_SpatialAndPlaceEffects_OverTime, P.Num_DCT_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_DCT_ChangeTimes; ChangeTime++) P.DCT_SpatialAndPlaceEffects_OverTime[ChangeTime] = P.DCTCaseIsolationEffectiveness;

	///// Household contact rates over time
	if (P.DoHouseholds)
	{
		//// soc dist
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rates over time given social distancing"			, "%lf", (void*)P.SD_HouseholdEffects_OverTime, P.Num_SD_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_SD_ChangeTimes; ChangeTime++) P.SD_HouseholdEffects_OverTime[ChangeTime] = P.SocDistHouseholdEffect;
		//// enhanced soc dist
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rates over time given enhanced social distancing"	, "%lf", (void*)P.Enhanced_SD_HouseholdEffects_OverTime, P.Num_SD_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_SD_ChangeTimes; ChangeTime++) P.Enhanced_SD_HouseholdEffects_OverTime[ChangeTime] = P.EnhancedSocDistHouseholdEffect;
		//// case isolation
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual household contacts after case isolation over time"					, "%lf", (void*)P.CI_HouseholdEffects_OverTime, P.Num_CI_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_CI_ChangeTimes; ChangeTime++) P.CI_HouseholdEffects_OverTime[ChangeTime] = P.CaseIsolationHouseEffectiveness;
		//// household quarantine
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rates over time after quarantine"					, "%lf", (void*)P.HQ_HouseholdEffects_OverTime, P.Num_HQ_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_HQ_ChangeTimes; ChangeTime++) P.HQ_HouseholdEffects_OverTime[ChangeTime] = P.HQuarantineHouseEffect;
		//// place closure
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative household contact rates over time after place closure"				, "%lf", (void*)P.PC_HouseholdEffects_OverTime, P.Num_PC_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_PC_ChangeTimes; ChangeTime++) P.PC_HouseholdEffects_OverTime[ChangeTime] = P.PlaceCloseHouseholdRelContact;
		//// digital contact tracing
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual household contacts after digital contact tracing isolation over time", "%lf", (void*)P.DCT_HouseholdEffects_OverTime, P.Num_DCT_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_DCT_ChangeTimes; ChangeTime++) P.DCT_HouseholdEffects_OverTime[ChangeTime] = P.DCTCaseIsolationHouseEffectiveness;
	}

	///// place contact rates over time
	if (P.DoPlaces)
	{
		//// soc dist
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative place contact rates over time given social distancing by place type", "%lf", (void*) &P.SD_PlaceEffects_OverTime[0][0], P.Num_SD_ChangeTimes * P.PlaceTypeNum, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_SD_ChangeTimes; ChangeTime++) //// by default populate to values of P.SocDistPlaceEffect
				for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
					P.SD_PlaceEffects_OverTime[ChangeTime][PlaceType] = P.SocDistPlaceEffect[PlaceType];

		//// enhanced soc dist
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Relative place contact rates over time given enhanced social distancing by place type", "%lf", (void*) &P.Enhanced_SD_PlaceEffects_OverTime[0][0], P.Num_SD_ChangeTimes * P.PlaceTypeNum, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_SD_ChangeTimes; ChangeTime++) //// by default populate to values of P.EnhancedSocDistPlaceEffect
				for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
					P.Enhanced_SD_PlaceEffects_OverTime[ChangeTime][PlaceType] = P.EnhancedSocDistPlaceEffect[PlaceType];

		//// household quarantine
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Residual place contacts over time after household quarantine by place type", "%lf", (void*) &P.HQ_PlaceEffects_OverTime[0][0], P.Num_HQ_ChangeTimes * P.PlaceTypeNum, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_HQ_ChangeTimes; ChangeTime++) //// by default populate to values of P.HQuarantinePlaceEffect
				for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
					P.HQ_PlaceEffects_OverTime[ChangeTime][PlaceType] = P.HQuarantinePlaceEffect[PlaceType];

		//// place closure
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of places remaining open after closure by place type over time", "%lf", (void*) &P.PC_PlaceEffects_OverTime[0][0], P.Num_PC_ChangeTimes * P.PlaceTypeNum, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_PC_ChangeTimes; ChangeTime++) //// by default populate to values of P.PlaceCloseEffect
				for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
					P.PC_PlaceEffects_OverTime[ChangeTime][PlaceType] = P.PlaceCloseEffect[PlaceType];

		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportional attendance after closure by place type over time", "%lf", (void*) &P.PC_PropAttending_OverTime[0][0], P.Num_PC_ChangeTimes * P.PlaceTypeNum, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_PC_ChangeTimes; ChangeTime++) //// by default populate to values of P.PlaceClosePropAttending
				for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
					P.PC_PropAttending_OverTime[ChangeTime][PlaceType] = P.PlaceClosePropAttending[PlaceType];
	}


	//// ****  compliance
	//// case isolation
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of detected cases isolated over time", "%lf", (void*)P.CI_Prop_OverTime, P.Num_CI_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_CI_ChangeTimes; ChangeTime++) P.CI_Prop_OverTime[ChangeTime] = P.CaseIsolationProp;
	//// household quarantine (individual level)
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Individual level compliance with quarantine over time"	, "%lf", (void*)P.HQ_Individual_PropComply_OverTime, P.Num_HQ_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_HQ_ChangeTimes; ChangeTime++) P.HQ_Individual_PropComply_OverTime[ChangeTime] = P.HQuarantinePropIndivCompliant;
	//// household quarantine (Household level)
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Household level compliance with quarantine over time"	, "%lf", (void*)P.HQ_Household_PropComply_OverTime, P.Num_HQ_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_HQ_ChangeTimes; ChangeTime++) P.HQ_Household_PropComply_OverTime[ChangeTime] = P.HQuarantinePropHouseCompliant;
	//// digital contact tracing
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of digital contacts who self-isolate over time", "%lf", (void*)P.DCT_Prop_OverTime, P.Num_DCT_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_DCT_ChangeTimes; ChangeTime++) P.DCT_Prop_OverTime[ChangeTime] = P.ProportionDigitalContactsIsolate;
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Maximum number of contacts to trace per index case over time", "%i", (void*)P.DCT_MaxToTrace_OverTime, P.Num_DCT_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_DCT_ChangeTimes; ChangeTime++) P.DCT_MaxToTrace_OverTime[ChangeTime] = P.MaxDigitalContactsToTrace;
	if (P.DoPlaces)
	{
		//// ****  thresholds
		//// place closure (global threshold)
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place closure incidence threshold over time", "%lf", (void*)P.PC_IncThresh_OverTime, P.Num_PC_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_PC_ChangeTimes; ChangeTime++) P.PC_IncThresh_OverTime[ChangeTime] = P.PlaceCloseIncTrig1;
		//// place closure (fractional global threshold)
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Place closure fractional incidence threshold over time", "%lf", (void*)P.PC_FracIncThresh_OverTime, P.Num_PC_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_PC_ChangeTimes; ChangeTime++) P.PC_FracIncThresh_OverTime[ChangeTime] = P.PlaceCloseFracIncTrig;
		//// place closure (cell incidence threshold)
		if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger incidence per cell for place closure over time", "%i", (void*)P.PC_CellIncThresh_OverTime, P.Num_PC_ChangeTimes, 1, 0))
			for (int ChangeTime = 0; ChangeTime < P.Num_PC_ChangeTimes; ChangeTime++) P.PC_CellIncThresh_OverTime[ChangeTime] = P.PlaceCloseCellIncThresh1;
	}
	//// household quarantine
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Household quarantine trigger incidence per cell over time", "%lf", (void*)P.HQ_CellIncThresh_OverTime, P.Num_HQ_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_HQ_ChangeTimes; ChangeTime++) P.HQ_CellIncThresh_OverTime[ChangeTime] = P.HHQuar_CellIncThresh;
	//// case isolation
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Case isolation trigger incidence per cell over time", "%lf", (void*)P.CI_CellIncThresh_OverTime, P.Num_CI_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_CI_ChangeTimes; ChangeTime++) P.CI_CellIncThresh_OverTime[ChangeTime] = P.CaseIsolation_CellIncThresh;
	//// soc dists
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger incidence per cell for social distancing over time", "%i", (void*)P.SD_CellIncThresh_OverTime, P.Num_SD_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_SD_ChangeTimes; ChangeTime++) P.SD_CellIncThresh_OverTime[ChangeTime] = P.SocDistCellIncThresh;

	//// **** Durations (later add Case isolation and Household quarantine)
	// place closure
	if (!P.VaryEfficaciesOverTime || !GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of place closure over time", "%lf", (void*)P.PC_Durs_OverTime, P.Num_PC_ChangeTimes, 1, 0))
		for (int ChangeTime = 0; ChangeTime < P.Num_PC_ChangeTimes; ChangeTime++) P.PC_Durs_OverTime[ChangeTime] = P.PlaceCloseDurationBase;

	//// Guards: make unused change values in array equal to final used value
	if (P.VaryEfficaciesOverTime)
	{
		//// soc dist
		for (int SD_ChangeTime = P.Num_SD_ChangeTimes; SD_ChangeTime < MAX_NUM_INTERVENTION_CHANGE_TIMES - 1; SD_ChangeTime++)
		{
			//// non-enhanced
			P.SD_SpatialEffects_OverTime	[SD_ChangeTime] = P.SD_SpatialEffects_OverTime		[P.Num_SD_ChangeTimes - 1];
			P.SD_HouseholdEffects_OverTime	[SD_ChangeTime] = P.SD_HouseholdEffects_OverTime	[P.Num_SD_ChangeTimes - 1];
			for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
				P.SD_PlaceEffects_OverTime[SD_ChangeTime][PlaceType] = P.SD_PlaceEffects_OverTime[P.Num_SD_ChangeTimes - 1][PlaceType];
			//// enhanced
			P.Enhanced_SD_SpatialEffects_OverTime	[SD_ChangeTime] = P.Enhanced_SD_SpatialEffects_OverTime		[P.Num_SD_ChangeTimes - 1];
			P.Enhanced_SD_HouseholdEffects_OverTime	[SD_ChangeTime] = P.Enhanced_SD_HouseholdEffects_OverTime	[P.Num_SD_ChangeTimes - 1];
			for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
				P.Enhanced_SD_PlaceEffects_OverTime[SD_ChangeTime][PlaceType] = P.Enhanced_SD_PlaceEffects_OverTime[P.Num_SD_ChangeTimes - 1][PlaceType];

			P.SD_CellIncThresh_OverTime				[SD_ChangeTime] = P.SD_CellIncThresh_OverTime				[P.Num_SD_ChangeTimes - 1];
		}

		//// case isolation
		for (int CI_ChangeTime = P.Num_CI_ChangeTimes; CI_ChangeTime < MAX_NUM_INTERVENTION_CHANGE_TIMES - 1; CI_ChangeTime++)
		{
			P.CI_SpatialAndPlaceEffects_OverTime[CI_ChangeTime] = P.CI_SpatialAndPlaceEffects_OverTime	[P.Num_CI_ChangeTimes - 1];
			P.CI_HouseholdEffects_OverTime		[CI_ChangeTime] = P.CI_HouseholdEffects_OverTime		[P.Num_CI_ChangeTimes - 1];
			P.CI_Prop_OverTime					[CI_ChangeTime] = P.CI_Prop_OverTime					[P.Num_CI_ChangeTimes - 1];
			P.CI_CellIncThresh_OverTime			[CI_ChangeTime] = P.CI_CellIncThresh_OverTime			[P.Num_CI_ChangeTimes - 1];
		}

		//// household quarantine
		for (int HQ_ChangeTime = P.Num_HQ_ChangeTimes; HQ_ChangeTime < MAX_NUM_INTERVENTION_CHANGE_TIMES - 1; HQ_ChangeTime++)
		{
			P.HQ_SpatialEffects_OverTime	[HQ_ChangeTime] = P.HQ_SpatialEffects_OverTime	[P.Num_HQ_ChangeTimes - 1];
			P.HQ_HouseholdEffects_OverTime	[HQ_ChangeTime] = P.HQ_HouseholdEffects_OverTime[P.Num_HQ_ChangeTimes - 1];
			for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
				P.HQ_PlaceEffects_OverTime[HQ_ChangeTime][PlaceType] = P.HQ_PlaceEffects_OverTime[P.Num_HQ_ChangeTimes - 1][PlaceType];

			P.HQ_Individual_PropComply_OverTime	[HQ_ChangeTime] = P.HQ_Individual_PropComply_OverTime	[P.Num_HQ_ChangeTimes - 1];
			P.HQ_Household_PropComply_OverTime	[HQ_ChangeTime] = P.HQ_Household_PropComply_OverTime	[P.Num_HQ_ChangeTimes - 1];

			P.HQ_CellIncThresh_OverTime			[HQ_ChangeTime] = P.HQ_CellIncThresh_OverTime			[P.Num_HQ_ChangeTimes - 1];
		}

		//// place closure
		for (int PC_ChangeTime = P.Num_PC_ChangeTimes; PC_ChangeTime < MAX_NUM_INTERVENTION_CHANGE_TIMES - 1; PC_ChangeTime++)
		{
			P.PC_SpatialEffects_OverTime	[PC_ChangeTime] = P.PC_SpatialEffects_OverTime	[P.Num_PC_ChangeTimes - 1];
			P.PC_HouseholdEffects_OverTime	[PC_ChangeTime] = P.PC_HouseholdEffects_OverTime[P.Num_PC_ChangeTimes - 1];
			for (int PlaceType = 0; PlaceType < P.PlaceTypeNum; PlaceType++)
			{
				P.PC_PlaceEffects_OverTime[PC_ChangeTime][PlaceType] = P.PC_PlaceEffects_OverTime[P.Num_PC_ChangeTimes - 1][PlaceType];
				P.PC_PropAttending_OverTime[PC_ChangeTime][PlaceType] = P.PC_PropAttending_OverTime[P.Num_PC_ChangeTimes - 1][PlaceType];
			}

			P.PC_IncThresh_OverTime			[PC_ChangeTime]	= P.PC_IncThresh_OverTime		[P.Num_PC_ChangeTimes - 1];
			P.PC_FracIncThresh_OverTime		[PC_ChangeTime]	= P.PC_FracIncThresh_OverTime	[P.Num_PC_ChangeTimes - 1];
			P.PC_CellIncThresh_OverTime		[PC_ChangeTime]	= P.PC_CellIncThresh_OverTime	[P.Num_PC_ChangeTimes - 1];
		}

		//// digital contact tracing
		for (int DCT_ChangeTime = P.Num_DCT_ChangeTimes; DCT_ChangeTime < MAX_NUM_INTERVENTION_CHANGE_TIMES - 1; DCT_ChangeTime++)
		{
			P.DCT_SpatialAndPlaceEffects_OverTime	[DCT_ChangeTime] = P.DCT_SpatialAndPlaceEffects_OverTime[P.Num_DCT_ChangeTimes - 1];
			P.DCT_HouseholdEffects_OverTime			[DCT_ChangeTime] = P.DCT_HouseholdEffects_OverTime		[P.Num_DCT_ChangeTimes - 1];
			P.DCT_Prop_OverTime						[DCT_ChangeTime] = P.DCT_Prop_OverTime					[P.Num_DCT_ChangeTimes - 1];
			P.DCT_MaxToTrace_OverTime				[DCT_ChangeTime] = P.DCT_MaxToTrace_OverTime			[P.Num_DCT_ChangeTimes - 1];
		}
	}

	if (P.DoPlaces)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of key workers randomly distributed in the population", "%i", (void*) & (P.KeyWorkerPopNum), 1, 1, 0)) P.KeyWorkerPopNum = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Number of key workers in different places by place type", "%i", (void*)P.KeyWorkerPlaceNum, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.KeyWorkerPlaceNum[i] = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of staff who are key workers per chosen place by place type", "%lf", (void*)P.KeyWorkerPropInKeyPlaces, P.PlaceTypeNum, 1, 0))
			for (i = 0; i < NUM_PLACE_TYPES; i++) P.KeyWorkerPropInKeyPlaces[i] = 1.0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Trigger incidence per cell for key worker prophylaxis", "%i", (void*) & (P.KeyWorkerProphCellIncThresh), 1, 1, 0)) P.KeyWorkerProphCellIncThresh = 1000000000;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Key worker prophylaxis start time", "%lf", (void*) & (P.KeyWorkerProphTimeStartBase), 1, 1, 0)) P.KeyWorkerProphTimeStartBase = USHRT_MAX / P.TimeStepsPerDay;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Duration of key worker prophylaxis", "%lf", (void*) & (P.KeyWorkerProphDuration), 1, 1, 0)) P.KeyWorkerProphDuration = 0;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Time interval from start of key worker prophylaxis before policy restarted", "%lf", (void*) & (P.KeyWorkerProphRenewalDuration), 1, 1, 0)) P.KeyWorkerProphRenewalDuration = P.KeyWorkerProphDuration;
		if (P.DoHouseholds)
		{
			if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Proportion of key workers whose households are also treated as key workers", "%lf", (void*) & (P.KeyWorkerHouseProp), 1, 1, 0)) P.KeyWorkerHouseProp = 0;
		}
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Minimum radius for key worker prophylaxis", "%lf", (void*) & (P.KeyWorkerProphRadius), 1, 1, 0)) P.KeyWorkerProphRadius = 0;
	}
	else
	{
		P.KeyWorkerPopNum = 0;
		P.KeyWorkerProphTimeStartBase = 1e10;
	}

	//Added this to parameter list so that recording infection events (and the number to record) can easily be turned off and on: ggilani - 10/10/2014
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Record infection events", "%i", (void*) & (P.DoRecordInfEvents), 1, 1, 0)) P.DoRecordInfEvents = 0;
	if (P.DoRecordInfEvents)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Max number of infection events to record", "%i", (void*) & (P.MaxInfEvents), 1, 1, 0)) P.MaxInfEvents = 1000;
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Record infection events per run", "%i", (void*) & (P.RecordInfEventsPerRun), 1, 1, 0)) P.RecordInfEventsPerRun = 0;
	}
	else
	{
		P.MaxInfEvents = 0;
	}
	//Include a limit to the number of infections to simulate, if this happens before time runs out
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Limit number of infections", "%i", (void*) & (P.LimitNumInfections), 1, 1, 0)) P.LimitNumInfections = 0;
	if (P.LimitNumInfections)
	{
		if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Max number of infections", "%i", (void*) & (P.MaxNumInfections), 1, 1, 0)) P.MaxNumInfections = 60000;
	}
	//Add origin-destination matrix parameter
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Output origin destination matrix", "%i", (void*) & (P.DoOriginDestinationMatrix), 1, 1, 0)) P.DoOriginDestinationMatrix = 0;

	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Mean child age gap", "%i", (void*) & (P.MeanChildAgeGap), 1, 1, 0)) P.MeanChildAgeGap=2;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Min adult age", "%i", (void*)&(P.MinAdultAge), 1, 1, 0)) P.MinAdultAge = 19;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Max MF partner age gap", "%i", (void*) & (P.MaxMFPartnerAgeGap), 1, 1, 0)) P.MaxMFPartnerAgeGap = 5;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Max FM partner age gap", "%i", (void*) & (P.MaxFMPartnerAgeGap), 1, 1, 0)) P.MaxFMPartnerAgeGap = 5;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Min parent age gap", "%i", (void*) & (P.MinParentAgeGap), 1, 1, 0)) P.MinParentAgeGap = 19;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Max parent age gap", "%i", (void*) & (P.MaxParentAgeGap), 1, 1, 0)) P.MaxParentAgeGap = 44;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Max child age", "%i", (void*) & (P.MaxChildAge), 1, 1, 0)) P.MaxChildAge = 20;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "One Child Two Pers Prob", "%lf", (void*) & (P.OneChildTwoPersProb), 1, 1, 0)) P.OneChildTwoPersProb = 0.08;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Two Child Three Pers Prob", "%lf", (void*) & (P.TwoChildThreePersProb), 1, 1, 0)) P.TwoChildThreePersProb = 0.11;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "One Pers House Prob Old", "%lf", (void*) & (P.OnePersHouseProbOld), 1, 1, 0)) P.OnePersHouseProbOld = 0.5;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Two Pers House Prob Old", "%lf", (void*) & (P.TwoPersHouseProbOld), 1, 1, 0)) P.TwoPersHouseProbOld = 0.5;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "One Pers House Prob Young", "%lf", (void*) & (P.OnePersHouseProbYoung), 1, 1, 0)) P.OnePersHouseProbYoung = 0.23;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Two Pers House Prob Young", "%lf", (void*) & (P.TwoPersHouseProbYoung), 1, 1, 0)) P.TwoPersHouseProbYoung = 0.23;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "One Child Prob Youngest Child Under Five", "%lf", (void*) & (P.OneChildProbYoungestChildUnderFive), 1, 1, 0)) P.OneChildProbYoungestChildUnderFive = 0.5;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Two Children Prob Youngest Under Five", "%lf", (void*) & (P.TwoChildrenProbYoungestUnderFive), 1, 1, 0)) P.TwoChildrenProbYoungestUnderFive = 0.0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Prob Youngest Child Under Five", "%lf", (void*) & (P.ProbYoungestChildUnderFive), 1, 1, 0)) P.ProbYoungestChildUnderFive = 0;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Zero Child Three Pers Prob", "%lf", (void*) & (P.ZeroChildThreePersProb), 1, 1, 0)) P.ZeroChildThreePersProb = 0.25;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "One Child Four Pers Prob", "%lf", (void*) & (P.OneChildFourPersProb), 1, 1, 0)) P.OneChildFourPersProb = 0.2;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Young And Single Slope", "%lf", (void*) & (P.YoungAndSingleSlope), 1, 1, 0)) P.YoungAndSingleSlope = 0.7;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Young And Single", "%i", (void*) & (P.YoungAndSingle), 1, 1, 0)) P.YoungAndSingle = 36;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "No Child Pers Age", "%i", (void*) & (P.NoChildPersAge), 1, 1, 0)) P.NoChildPersAge = 44;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Old Pers Age", "%i", (void*) & (P.OldPersAge), 1, 1, 0)) P.OldPersAge = 60;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Three Child Five Pers Prob", "%lf", (void*) & (P.ThreeChildFivePersProb), 1, 1, 0)) P.ThreeChildFivePersProb = 0.5;
	if (!GetInputParameter2(ParamFile_dat, PreParamFile_dat, "Older Gen Gap", "%i", (void*) & (P.OlderGenGap), 1, 1, 0)) P.OlderGenGap = 19;

	// Close input files.
	fclose(ParamFile_dat);
	if (PreParamFile_dat != NULL) fclose(PreParamFile_dat);
	if (ParamFile_dat != AdminFile_dat && AdminFile_dat != NULL) fclose(AdminFile_dat);

	if (P.DoOneGen != 0) P.DoOneGen = 1;
	P.ColourPeriod = 2000;
	P.MoveRestrRadius2 = P.MoveRestrRadius * P.MoveRestrRadius;
	P.SocDistRadius2 = P.SocDistRadius * P.SocDistRadius;
	P.VaccRadius2 = P.VaccRadius * P.VaccRadius;
	P.VaccMinRadius2 = P.VaccMinRadius * P.VaccMinRadius;
	P.TreatRadius2 = P.TreatRadius * P.TreatRadius;
	P.PlaceCloseRadius2 = P.PlaceCloseRadius * P.PlaceCloseRadius;
	P.KeyWorkerProphRadius2 = P.KeyWorkerProphRadius * P.KeyWorkerProphRadius;
	if (P.TreatRadius2 == 0) P.TreatRadius2 = -1;
	if (P.VaccRadius2 == 0) P.VaccRadius2 = -1;
	if (P.PlaceCloseRadius2 == 0) P.PlaceCloseRadius2 = -1;
	if (P.MoveRestrRadius2 == 0) P.MoveRestrRadius2 = -1;
	if (P.SocDistRadius2 == 0) P.SocDistRadius2 = -1;
	if (P.KeyWorkerProphRadius2 == 0) P.KeyWorkerProphRadius2 = -1;
	if (P.TreatCellIncThresh < 1) P.TreatCellIncThresh = 1;
	if (P.CaseIsolation_CellIncThresh < 1) P.CaseIsolation_CellIncThresh = 1;
	if (P.DigitalContactTracing_CellIncThresh < 1) P.DigitalContactTracing_CellIncThresh = 1;
	if (P.HHQuar_CellIncThresh < 1) P.HHQuar_CellIncThresh = 1;
	if (P.MoveRestrCellIncThresh < 1) P.MoveRestrCellIncThresh = 1;
	if (P.PlaceCloseCellIncThresh < 1) P.PlaceCloseCellIncThresh = 1;
	if (P.KeyWorkerProphCellIncThresh < 1) P.KeyWorkerProphCellIncThresh = 1;


	//// Make unsigned short versions of various intervention variables. And scaled them by number of timesteps per day
	P.usHQuarantineHouseDuration = ((unsigned short int) (P.HQuarantineHouseDuration * P.TimeStepsPerDay));
	P.usVaccTimeToEfficacy = ((unsigned short int) (P.VaccTimeToEfficacy * P.TimeStepsPerDay));
	P.usVaccTimeEfficacySwitch = ((unsigned short int) (P.VaccTimeEfficacySwitch * P.TimeStepsPerDay));
	P.usCaseIsolationDelay = ((unsigned short int) (P.CaseIsolationDelay * P.TimeStepsPerDay));
	P.usCaseIsolationDuration = ((unsigned short int) (P.CaseIsolationDuration * P.TimeStepsPerDay));
	P.usCaseAbsenteeismDuration = ((unsigned short int) (P.CaseAbsenteeismDuration * P.TimeStepsPerDay));
	P.usCaseAbsenteeismDelay = ((unsigned short int) (P.CaseAbsenteeismDelay * P.TimeStepsPerDay));
	if (P.DoUTM_coords)
	{
		for (i = 0; i <= 1000; i++)
		{
			asin2sqx[i] = asin(sqrt(((double)(i)) / 1000));
			asin2sqx[i] = asin2sqx[i] * asin2sqx[i];
		}
		for (t = 0; t <= 360; t++)
		{
			sinx[(int)t] = sin(PI * t / 180);
			cosx[(int)t] = cos(PI * t / 180);
		}
	}
	fprintf(stderr, "Parameters read\n");
    */
}
