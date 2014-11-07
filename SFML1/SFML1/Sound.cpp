#include "Sound.h"
#include<iostream>
using namespace std;
Sound::Sound()
{

}

void Sound::loadSounds()
{
	if(jump_buffer.loadFromFile("Data/Sounds/Jump.wav")==true)
		cout<<"Jump.wav loaded"<<endl;
	jumpSound.setBuffer(jump_buffer);

	if(igloo_buffer.loadFromFile("Data/Sounds/Pickup_Coin.wav")==true)
		cout<<"Pickup_Coin.wav loaded"<<endl;
	iglooSound.setBuffer(igloo_buffer);

	if(walk_buffer.loadFromFile("Data/Sounds/Walk.wav")==true)
		cout<<"Walk.wav loaded"<<endl;
	walkSound.setBuffer(walk_buffer);

	if(hit_buffer.loadFromFile("Data/Sounds/Hit_Hurt.wav")==true)
		cout<<"Hit_Hurt.wav loaded"<<endl;
	hitSound.setBuffer(hit_buffer);

	if(death_buffer.loadFromFile("Data/Sounds/Death.wav")==true)
		cout<<"Death.wav loaded"<<endl;
	deathSound.setBuffer(death_buffer);
	time_till_end=0;
}

void Sound::playSound(const char* sound){
	  if(sound=="jump")
      jumpSound.play();

	  if(sound=="igloo")
	  iglooSound.play();
	   if(sound=="walk")
	   {
		 cout<<time_till_end<<endl;
		 if(time_till_end==0){
	       walkSound.play();
         }
		  time_till_end+=0.1;
		  if(time_till_end>2)
			  time_till_end=0;
	   }

	   if(sound=="hit")
	      hitSound.play();

	   if(sound=="death")
		  deathSound.play();

}

void Sound::stopSound(const char* sound){
	  if(sound=="jump")
	  {
        jumpSound.stop();
	  }
	  if(sound=="igloo")
	  {
	    iglooSound.stop();
	  }
	  if(sound=="walk")
	  {
        walkSound.stop();
	  }

	  if(sound=="hit")
	  {
	     hitSound.stop();
	  }
	  if(sound=="death")
	  {
	     deathSound.stop();
	  }


}

Sound::~Sound()
{

}