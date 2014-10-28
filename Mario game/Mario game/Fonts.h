#define FONT_H
#ifdef FONT_H
#include<sstream>
sf::Font font;
void load_font(){
if(font.loadFromFile("Data/Fonts/arial.ttf")==true)
	cout<<"arial.tff was loaded"<<endl;
}
sf::Text score;
void write_font(){
	score.setFont(font);
	score.setCharacterSize(20);
	score.setString("Score:0");
	score.setPosition(0,0);
}

class font_class{
public:
	sf::Text menu;

	void setFont(const char* write);

	void setCharacherSize(int size);

	void setPosition(int x,int y);
};
   
void font_class::setFont(const char* write)
{
	menu.setFont(font);
	menu.setString(write);
	menu.setColor(sf::Color::Red);
}
void font_class::setCharacherSize(int size)
{
	menu.setCharacterSize(size);
}
void font_class::setPosition(int x,int y)
{
	menu.setPosition(x,y);
}

#endif