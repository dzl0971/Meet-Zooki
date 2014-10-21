#define SOUND_H
#ifdef SOUND_H
class sounds{
private:
public:
	float time_till_end;
	sf::SoundBuffer jump_buffer;
	sf::SoundBuffer coin_buffer;
	sf::SoundBuffer walk_buffer;
	sf::SoundBuffer hit_buffer;
	sf::SoundBuffer death_buffer;

	sf::Sound jump;
	sf::Sound coin;
	sf::Sound walk;
	sf::Sound hit;
	sf::Sound death;

	void loadSounds();

	void insertSounds();

	void playSound(const char* sound);

	void stopSound(const char* sound);
};
void sounds::loadSounds(){
	if(jump_buffer.loadFromFile("Data/Sounds/Jump.wav")==true)
		cout<<"Jump.wav loaded"<<endl;
	if(coin_buffer.loadFromFile("Data/Sounds/Pickup_Coin.wav")==true)
		cout<<"Pickup_Coin.wav loaded"<<endl;
	if(walk_buffer.loadFromFile("Data/Sounds/Walk.wav")==true)
		cout<<"Walk.wav loaded"<<endl;
	if(hit_buffer.loadFromFile("Data/Sounds/Hit_Hurt.wav")==true)
		cout<<"Hit_Hurt.wav loaded"<<endl;

	if(death_buffer.loadFromFile("Data/Sounds/Death.wav")==true)
		cout<<"Death.wav loaded"<<endl;

	time_till_end=0;
}
void sounds::insertSounds(){
	jump.setBuffer(jump_buffer);

	coin.setBuffer(coin_buffer);

	walk.setBuffer(walk_buffer);

	hit.setBuffer(hit_buffer);

	death.setBuffer(death_buffer);
}

void sounds::playSound(const char* sound){
	  if(sound=="jump")
      jump.play();

	  if(sound=="coin")
	  coin.play();
	   if(sound=="walk")
	   {
		 cout<<time_till_end<<endl;
		 if(time_till_end==0){
	       walk.play();
         }
		  time_till_end+=0.1;
		  if(time_till_end>2)
			  time_till_end=0;
	   }

	   if(sound=="hit")
	      hit.play();

	   if(sound=="death")
		  death.play();

}
void sounds::stopSound(const char* sound){
	  if(sound=="jump")
	  {
        jump.stop();
	  }
	  if(sound=="coin")
	  {
	    coin.stop();
	  }
	  if(sound=="walk")
	  {
        walk.stop();
	  }

	  if(sound=="hit")
	  {
	     hit.stop();
	  }
	  if(sound=="death")
	  {
	     death.stop();
	  }


}
#endif