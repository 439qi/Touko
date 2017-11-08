#include"class.h"
#include"main.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9math.h>
MySprite sp(3, 0, 0,96,96, 10, 36, 10, 1, 30);
MySprite cursor(1,0,0,48,48,0,2,10,1,100);
MySprite cinfo(2,900-78, 0,  78, 107, 0, 0, 1, 0, 0);
MySprite aientity(3, rand() % 900, rand() % Sheight, 96, 96, 0, 9, 10, 1, 33);
OriSprite::~OriSprite(){}
MySprite::MySprite(int index, float posx, float posy, int framew, int frameh,int startframe, int endframe, int framep, int direction, int delay):
	m_startframe(startframe),m_endframe(endframe),m_framep(framep),m_direction(direction),m_delay(delay),m_width(framew),m_height(frameh)
	{	
		m_score = 0;m_index=index;
		m_pos.x=posx;m_pos.y=posy;m_pos.z=0;
		m_v.x = 5; m_v.y = 5; m_frame = startframe;
	}
void MySprite::Animate()
{	
	if ((int)GetTickCount() > m_starttime + m_delay)
	{
		m_starttime = (int)GetTickCount();
		m_frame += m_direction;
		if (m_frame > m_endframe)	m_frame = m_startframe;
		if (m_frame < m_startframe)	m_frame = m_endframe;
	}
} 
void MySprite::MouseUpdate()
{
	m_v = { 0,0,0 }; Animate();
	m_prepos = m_pos;
	m_pos.x = mousepos.x; m_pos.y = mousepos.y;
	if (WindowLimit(sp)) m_pos = m_prepos;
}
void MySprite::KeyUpdate()
{
	m_v = { 0,0,0 }; m_prepos = m_pos;
	if (Key_Down(DIK_RIGHT))			m_v.x += 1;
	if (Key_Down(DIK_LEFT))				m_v.x += -1;
	if (Key_Down(DIK_UP))				m_v.y += -1;
	if (Key_Down(DIK_DOWN))				m_v.y += 1;
	if (Key_Down(DIK_W))				{ m_pos.x = mousepos.x; m_pos.y = mousepos.y; }
	if (Key_Down(DIK_Q))				Animate();
	m_pos.x += m_v.x; m_pos.y += m_v.y;  
	if (WindowLimit(sp)) m_pos = m_prepos; 
}
void MySprite::DrawFrame()
{
	m_framerect.left = long((m_frame%m_framep)*m_width);
	m_framerect.top = long((m_frame / m_framep)*m_height);
	m_framerect.right = long((m_framerect.left + m_width));
	m_framerect.bottom = long((m_framerect.top + m_height));
}
void MySprite::SelfUpdate()
{ 
		m_pos.x += m_v.x; m_pos.y += m_v.y;
		if (m_pos.x<0 || m_pos.x + m_width>900) m_v.x = -m_v.x;
		if (m_pos.y<0||m_pos.y + m_height>Sheight)	m_v.y = -m_v.y;

	
}
void DrawManager::SpriteReigster(MySprite &spritetodraw)
{
	OriSprite ls;
	ls.m_framerect = spritetodraw.m_framerect; ls.m_pos = spritetodraw.m_pos, ls.m_index = spritetodraw.m_index;
	m_todraw.push_back(ls);
}
void DrawManager::qdraw()
{
	for (int i = 0; i <m_todraw.size();++i)
	{
		spriteobj->Draw(texture[m_todraw[i].m_index],&m_todraw[i].m_framerect,NULL,&m_todraw[i].m_pos,D3DCOLOR_XRGB(255,255,255));
	}
	m_todraw.clear();
}