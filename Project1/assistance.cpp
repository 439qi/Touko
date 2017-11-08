#include"main.h"
#include<sstream>
int flashtime = 0, flashdelay =10;
string inttostring(const int &a)
{	std::stringstream ss;
	std::string str;
	ss<<a;ss>>str;
	return str;
}
void All_Run()
{
	
	sp.KeyUpdate();				cursor.MouseUpdate();										aientity.Animate();
	sp.DrawFrame();				cursor.DrawFrame();				cinfo.DrawFrame();			aientity.DrawFrame();
	dm.SpriteReigster(sp);		dm.SpriteReigster(cursor);		dm.SpriteReigster(cinfo);	dm.SpriteReigster(aientity);
		if (Key_Down(DIK_ESCAPE))  Over = true;	
	
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
RECT GetCursorRect()
{
	RECT cursorrect = {mousepos.x,mousepos.y,mousepos.x+cursor.m_width,mousepos.y+ cursor.m_height};
	return cursorrect;
}
