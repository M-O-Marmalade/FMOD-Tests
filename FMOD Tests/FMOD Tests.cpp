

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
	   
	FMOD::Studio::Bank* musicandFX = NULL;
	result = system->loadBankFile("media/MusicandFX.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &musicandFX);

	FMOD::Studio::EventDescription* splashJingleDescription = NULL;
	system->getEvent("event:/SplashJingle", &splashJingleDescription);

	FMOD::Studio::EventInstance* splashJingleInstance = NULL;
	splashJingleDescription->createInstance(&splashJingleInstance);

	splashJingleInstance->start();

	system->update(); //begin FMOD sound generation/song playback	
	

	this_thread::sleep_for(3000ms);
}
