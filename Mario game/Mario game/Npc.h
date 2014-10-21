#define NPC_H
#ifdef NPC_H
 class monster_1
 {
 private:
		int move_animation;
		int AI;
		bool continue_game;
		bool delete_monster;
 public:
	   sf::Texture monster_texture1;
	   sf::Texture monster_texture2;
	   sf::Texture monster_texture3;
	   sf::RectangleShape monster_mesh;
	    int delete_monster_cooldown;
	 void setTexture();

	 void setMesh();

	 void setPosition(int x,int y);

	 void setMovementAnimation();

	 void movementAnimation();

	 void movement(sf::RectangleShape,sf::RectangleShape);
	 
	 int collisionPlayer();
 };

 void monster_1::setTexture(){

	 if(monster_texture1.loadFromFile("Data/NPC/fog_r.png")==true)
	    cout<<"Monster_1_r loaded"<<endl;

     if(monster_texture2.loadFromFile("Data/NPC/fog_l.png")==true)
	    cout<<"Monster_1_l loaded"<<endl;
      
      if(monster_texture3.loadFromFile("Data/NPC/bear_death.png")==true)
	    cout<<"Monster_1_dead loaded"<<endl; 
	 
 }

 void monster_1::setMesh(){

	 monster_mesh.setSize(sf::Vector2f(30,30));
	 monster_mesh.setTexture(&monster_texture1);
 }
 void monster_1::setPosition(int x,int y){
	 monster_mesh.setPosition(x,y);
 }
 void monster_1::setMovementAnimation()
 {
	 move_animation=0;
	 AI=1;
	 delete_monster=false;
	 delete_monster_cooldown=0;
 }
 void monster_1::movementAnimation(){
	 move_animation=move_animation+1;
	 if(move_animation==1)
		   monster_mesh.setTexture(&monster_texture1);
     if(move_animation==2)
		   monster_mesh.setTexture(&monster_texture2);
	 if(move_animation>2)
        move_animation=0;
 }
 void monster_1::movement(sf::RectangleShape item,sf::RectangleShape item2){
	 if(delete_monster==false){
	  if((monster_mesh.getGlobalBounds().intersects(item.getGlobalBounds())==true)||(monster_mesh.getGlobalBounds().intersects(item2.getGlobalBounds())==true))
	  {
		 AI=AI*(-1);
	  }

	 if(AI==1){

	      monster_mesh.move(2,0);

	 }

	 if(AI==(-1)){

	      monster_mesh.move(-2,0);

	 }
	 
 }
 }

int monster_1::collisionPlayer()
 {  
	if(delete_monster==false){
	 if(monster_mesh.getGlobalBounds().intersects(player.getGlobalBounds())==true)
	 {
		 if(player.getGlobalBounds().intersects(terrain.getGlobalBounds())==true)
		 {
			 player.setPosition(player.getPosition().x,400);
			 return 0;
		 }
		 if(player.getGlobalBounds().intersects(terrain.getGlobalBounds())==false) 
		 {
			 delete_monster=true;
			 return 1;
		 }
	 }
	 else{
		 return 1;
	 }
	}
	 if(delete_monster==true){
		 if(delete_monster_cooldown<100)
		 delete_monster_cooldown+=1;
		  monster_mesh.setTexture(&monster_texture3);
		 return 1;
	 }
}
#endif