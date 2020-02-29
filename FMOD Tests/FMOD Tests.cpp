#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "fmod.hpp"
#include "fmod_studio.hpp"


using namespace std;

int main()
{

	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	FMOD_RESULT result;
	FMOD::Studio::System* system = NULL;

	result = FMOD::Studio::System::create(&system);

	result = system->initialize(200, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);

	FMOD::Studio::Bank* masterBank = NULL;
	result = system->loadBankFile("media/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);

	FMOD::Studio::Bank* stringsBank = NULL;
	result = system->loadBankFile("media/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);

	FMOD::Studio::Bank* bankA = NULL;
	result = system->loadBankFile("media/Bank A.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &bankA);

	
	int bankAEventCount;
	result = bankA->getEventCount(&bankAEventCount);
	cout << bankAEventCount << " events found!\n";


	int bankAEventsLoadedCount;
	vector<FMOD::Studio::EventDescription*> bankAEventList;
	bankAEventList.resize(bankAEventCount);	
	result = bankA->getEventList(bankAEventList.data(), bankAEventCount, &bankAEventsLoadedCount);
	cout << bankAEventsLoadedCount << " event loaded!\n";


	vector<FMOD::Studio::EventInstance*> bankAEvents;
	bankAEvents.resize(bankAEventsLoadedCount);
	for (int x = 0; x < bankAEventsLoadedCount; x++) {
		result = bankAEventList[x]->createInstance(&bankAEvents[x]);
	}	

	
	bankAEvents[0]->start();
	bankAEvents[0]->triggerCue();
	result = system->update();

	cout << "Press G Key to lengthen timestretch\npress H Key to shorten timestretch\npress X Key to quit\n";

	bool zKey = false;
	bool xKey = false;
	bool gKey = false;
	bool hKey = false;
	bool holdZKey = false;
	bool holdGKey = false;
	bool holdHKey = false;
	bool counter = false;
	float timeStretchValue = 1.0f;
	while (!counter) {

		zKey = ((0x8000 & GetAsyncKeyState((unsigned char)("Z"[0]))) != 0);
		xKey = ((0x8000 & GetAsyncKeyState((unsigned char)("X"[0]))) != 0);
		gKey = ((0x8000 & GetAsyncKeyState((unsigned char)("G"[0]))) != 0);
		hKey = ((0x8000 & GetAsyncKeyState((unsigned char)("H"[0]))) != 0);

		if (zKey && !holdZKey) {		
			bankAEvents[0]->triggerCue();			
			holdZKey = true;
		}
		else if (!zKey && holdZKey) {
			holdZKey = false;
		}

		if (gKey && !holdGKey) {
			timeStretchValue -= 0.05f;
			bankAEvents[0]->setParameterByName("TimeStretch", timeStretchValue);
			holdGKey = true;
			cout << "Current timestretch: " << timeStretchValue << endl;
		}
		else if (!gKey && holdGKey) {
			holdGKey = false;
		}

		if (hKey && !holdHKey) {
			timeStretchValue += 0.05f;
			bankAEvents[0]->setParameterByName("TimeStretch", timeStretchValue);
			holdHKey = true;
			cout << "Current timestretch: " << timeStretchValue << endl;
		}
		else if (!hKey && holdHKey) {
			holdHKey = false;
		}

		if (xKey) {
			counter = true;
		}		

		result = system->update();
	}
	
	result = system->release();
	CoUninitialize();

	return 0;
	/*FMOD_RESULT result;
	FMOD::System* system = NULL;

	result = FMOD::System_Create(&system);      // Create the main system object.
	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.

	FMOD::Sound* rdts;
	FMOD::Channel* channel = 0;

	system->createSound("media/rollingdownthestreet.xm", FMOD_ACCURATETIME, 0, &rdts);

	result = system->playSound(rdts, 0, false, &channel);

	result = system->update();

	this_thread::sleep_for(4s);
	
	channel->setPitch(2.0f);
	rdts->setMusicSpeed(0.5f);
	
	this_thread::sleep_for(4s);

	channel->setPitch(0.5f);
	rdts->setMusicSpeed(2.0f);

	this_thread::sleep_for(14s);

	channel->setPitch(4.0f);
	rdts->setMusicSpeed(0.25f);

	this_thread::sleep_for(50s);

	channel->setPitch(0.5f);
	rdts->setMusicSpeed(2.0f);

	this_thread::sleep_for(200s);

	result = rdts->release();
	result = system->close();
	result = system->release();
	*/
	
	/*FMOD_RESULT result;
	FMOD::Studio::System* system = NULL;

	result = FMOD::Studio::System::create(&system); // Create the Studio System object.

	result = system->initialize(64, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);


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
	/*

	this_thread::sleep_for(2s);

	testAInstance->setParameterByName("Cutoff", 7000.0f);

	//testAInstance->setPitch(0.5f);
	
	system->update();

	this_thread::sleep_for(4s);

	testAInstance->setParameterByName("Res", 5.0f);

	system->update();

	this_thread::sleep_for(5s);

	float x = 7000.0f;

	

	while (x < 22001.0f) {

		testAInstance->setParameterByName("Cutoff", x++);		
		system->update();
		this_thread::sleep_for(1ms);

	}

	testAInstance->setParameterByName("Res", 0.0f);
	system->update();
	testAInstance->setPitch(0.5f);
	system->update();
	this_thread::sleep_for(1min);
	*/



}
