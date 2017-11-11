#include"main.h"
#include<sstream>
using namespace tinyxml2;
int flashtime = 0, flashdelay =10;
string inttostring(const int &a)
{	std::stringstream ss;
	std::string str;
	ss<<a;ss>>str;
	return str;
}
int stringtoint(const string &a)
{
	std::istringstream s(a);
	int i; s >> i;
	return i;
}
int Key_Down(int key)
{
	return (keys[key] & 0x80);
}
bool MoveLimit(const MySprite &spi, RECT &limit)
{
	RECT what;
	RECT entity = { spi.m_pos.x,spi.m_pos.y,spi.m_pos.x + spi.m_width,spi.m_pos.y + spi.m_height };
	return (IntersectRect(&what, &limit, &entity));
}
bool WindowLimit(const MySprite &spi)
{
	return	(spi.m_pos.x<0|| spi.m_pos.x+spi.m_width>Swidth|| spi.m_pos.y<0|| spi.m_pos.y+spi.m_height>Sheight);
}
