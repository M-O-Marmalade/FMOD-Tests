

#include <Windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "fmod.hpp"
#include "fmod_studio.hpp"


using namespace std;

int main()
{
	
	FMOD_RESULT result;
	FMOD::Studio::System* system = NULL;

	result = FMOD::Studio::System::create(&system); // Create the Studio System object.

	result = system->initialize(256, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);


	FMOD::Studio::Bank* masterBank = NULL;
	system->loadBankFile("media/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);

	FMOD::Studio::Bank* stringsBank = NULL;
	system->loadBankFile("media/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
	   
	FMOD::Studio::Bank* bankA = NULL;
	result = system->loadBankFile("media/Bank A.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &bankA);

	FMOD::Studio::EventDescription* testADescription = NULL;
	system->getEvent("event:/TestA", &testADescription);

	FMOD::Studio::EventInstance* testAInstance = NULL;
	testADescription->createInstance(&testAInstance);

	testAInstance->start();

	system->update(); //begin FMOD sound generation/song playback	
	

	


	/*
	FMOD_STUDIO_PARAMETER_DESCRIPTION paramDesc;

	testADescription->getParameterDescriptionByName("Cutoff", &paramDesc);
	
	FMOD_STUDIO_PARAMETER_ID cutoffID = paramDesc.id;

	float cutoffParameterValue = 0.1f;

	testAInstance->setParameterByID(cutoffID, cutoffParameterValue);

	system->update();

	*/

	this_thread::sleep_for(2000ms);

	testAInstance->setParameterByName("Cutoff", 7000.0f);

	//testAInstance->setPitch(0.5f);

	system->update();

	this_thread::sleep_for(10s);

	testAInstance->setParameterByName("Res", 5.0f);
	system->update();

	this_thread::sleep_for(20s);

}
