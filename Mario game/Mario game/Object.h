#define OBJECT_H
#ifdef OBJECT_H


//BLOCK 1


 class block_1
 {
 public:
	 bool ok;

	 sf::Texture block_texture;
	 sf::RectangleShape block;

	  void setTexture();

	  void setMesh();

	  void setPosition(int block_x,int block_y);

	  void collision_x_r();
	  void collision_x_l();
	  void collision_y_u();
	  void collision_y_d();
	  int jump();
	 
 };

void block_1::setTexture(){
	if(block_texture.loadFromFile("Data/Block.png")==false){
		cout<<"Texture failed to initialize"<<endl;
	}
}



void block_1::setMesh(){
	block.setSize(sf::Vector2f(30,30));
	block.setTexture(&block_texture);
}

 void block_1::setPosition(int block_x,int block_y){
	 block.setPosition(block_x,block_y);
 }

 void block_1::collision_x_r(){
	 if(player.getGlobalBounds().intersects(block.getGlobalBounds())==true)
	 {
		 if(player.getPosition().x<block.getPosition().x)
		      player.move(-4,0);

	 }
	
 }

 void block_1::collision_x_l(){
	 if(player.getGlobalBounds().intersects(block.getGlobalBounds())==true)
	 {
		 if(player.getPosition().x>block.getPosition().x)
		      player.move(4,0);


	 }
	 
 }

 void block_1::collision_y_u(){
	 if(player.getGlobalBounds().intersects(block.getGlobalBounds())==true)
	 {
		 if(player.getPosition().y<block.getPosition().y)
		 {
			  ok=true;
			 player.move(0,-10);
		 }
		 
	 }

	 else
		 ok=false;
 }
 
 int block_1::jump(){
		if(ok==true) 
	      return 0;
		if(ok==false)
		  return 10;
 }
 void block_1::collision_y_d()
 {
	  if(player.getGlobalBounds().intersects(block.getGlobalBounds())==true)
	 {
		 if(player.getPosition().y>block.getPosition().y)
		 {
	        player.move(0,20);
		 }
     }
 }
 //coin 1

 class coin {
 private:
	 int coin_animation;
 public:
	 sf::Texture coin_texture1;
	 sf::Texture coin_texture2;
	 sf::Texture coin_texture3;
	 sf::Texture coin_texture4;
	 sf::RectangleShape coin_mesh;

	 int collision_player;

	 int score;

	 void setVariables();

	 void setTexture();

	 void setMesh();

	 void setPosition(int x,int y);

	 void setAnimation();

	 void collision();

 };
 void coin::setVariables(){
	 coin_animation=0;
	 collision_player=0;
	score=0;
 }
 void coin::setTexture(){
	    if(coin_texture1.loadFromFile("Data/Objects/cone.png")==true)
		  cout<<"coin_p1 loaded"<<endl;
	    if(coin_texture2.loadFromFile("Data/Objects/cone.png")==true)
		  cout<<"coin_p2 loaded"<<endl;
	    if(coin_texture3.loadFromFile("Data/Objects/cone.png")==true)
		  cout<<"coin_p3 loaded"<<endl;
	    if(coin_texture4.loadFromFile("Data/Objects/cone.png")==true)
		  cout<<"coin_p4 loaded"<<endl;
 }
 void coin::setMesh(){
		 coin_mesh.setSize(sf::Vector2f(30,30));
 }
 void coin::setAnimation(){
	 coin_animation++;
		 if (coin_animation==1)
	       coin_mesh.setTexture(&coin_texture1);
		 if (coin_animation==2)
            coin_mesh.setTexture(&coin_texture2);
		 if (coin_animation==3)
            coin_mesh.setTexture(&coin_texture3);
		 if (coin_animation==4)
			 coin_mesh.setTexture(&coin_texture4);
          if (coin_animation>4)
			 coin_animation=0;
 }
 void coin::setPosition(int x,int y){
	 coin_mesh.setPosition(x,y);
 }

 void coin::collision(){
	 if(player.getGlobalBounds().intersects(coin_mesh.getGlobalBounds())==true)
	 {
				score=score+10;
				
	            collision_player=1;
	 }
 }

#endif