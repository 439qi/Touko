#include"class.h"
#include"main.h"
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9math.h>
static GameState_Menu gsm;
D3DXVECTOR3 pos = { 0,0,0 };
GameState::GameState()
{
	m_currentstate =&gsm;
	m_buttons.push_back(new Button(4,0,0,0));
	stranger = new Player(0,400,300);
}
GameState* GameState::instance()
{
	static GameState gs;
	return &gs;
}



void GameState_Menu::Execute()
{
	GS->stranger->Update();
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	if (!d3ddev)	MessageBox(NULL, "d3ddev not existed", "Error", MB_OK);
	if (d3ddev->BeginScene())
	{
		d3ddev->StretchRect(surface, NULL, backbuffer, NULL, D3DTEXF_NONE);
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
		spriteobj->Draw(texture[GS->m_buttons[0]->m_imageindex], &GS->m_buttons[0]->m_rect, NULL, &GS->m_buttons[0]->m_pos, Color_White);
		spriteobj->Draw(texture[GS->stranger->m_imageindex], &GS->stranger->m_framerect, NULL, &GS->stranger->m_pos, Color_White);
		printtext(text, 0, 0, 0);
		spriteobj->End();
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
	
	if (Key_Down(DIK_ESCAPE))  Over = true;
}



Button::Button(int imageindex,int id,int x,int y)
{
	LoadXml(); m_imageindex = imageindex;
	m_pos.x = x; m_pos.y = y; m_pos.z = 0;
}
void Button::LoadXml()
{
	tinyxml2::XMLDocument* doc=new tinyxml2::XMLDocument(); if (doc==NULL) MessageBox(NULL, "Error Load Xm", "Error", MB_OK); 
	int res = doc->LoadFile("./xml/blueSheet.xml");
	if (res) MessageBox(NULL, "Error Load Xml", inttostring(res).c_str(), MB_OK);
	XMLElement* root = doc->RootElement();
	if (root==NULL) MessageBox(NULL, "Error Get root", "Error", MB_OK);
	XMLElement* node = root->FirstChildElement("SubTexture");
	if (node == NULL)   (NULL, "Error Load node", "Error", MB_OK);
	m_rect.left = node->Int64Attribute("x"); m_rect.top = node->Int64Attribute("y"); 
	m_rect.right = m_rect.left + node->Int64Attribute("width"); m_rect.bottom = m_rect.top + node->Int64Attribute("height");
	delete doc;
}

void OriSprite::LoadXml()
{	
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument(); if (doc == NULL) MessageBox(NULL, "Error Load Xm", "Error", MB_OK);
	int res = doc->LoadFile("./xml/XMLFile1.xml");
	if (res) MessageBox(NULL, "Error Load Xml", inttostring(res).c_str(), MB_OK);
	XMLElement* sprite = doc->RootElement();
	if (sprite == NULL) MessageBox(NULL, "Error Get root", "Error", MB_OK);
	XMLElement* cursor = sprite->FirstChildElement("Player");
	if (cursor == NULL)   (NULL, "Error Load cursor", "Error", MB_OK);
	m_imageindex = cursor->Int64Attribute("imageindex");
	m_framew = cursor->Int64Attribute("framew"); m_frameh = cursor->Int64Attribute("frameh"); m_framep = cursor->Int64Attribute("framep");
	m_startframe = cursor->Int64Attribute("startframe"); m_endframe = cursor->Int64Attribute("endframe");
	delete doc;
}
OriSprite::OriSprite(int id,int posx, int posy)
{	
	LoadXml();
	m_pos.x = posx; m_pos.y = posy; m_pos.z = 0;

}
OriSprite::~OriSprite(){}

Player::Player(int id,int posx,int posy)
{	
	OriSprite::LoadXml(); m_pos.x = posx; m_pos.y = posy; m_pos.z = 0;
	
	m_starttime=(int)GetTickCount();
	m_frame = m_startframe; m_delay = 150;
}
void Player::Update()
{	
	if ((int)GetTickCount() > m_starttime + m_delay)
	{
		m_starttime = (int)GetTickCount();
		m_frame += 1;
		if (m_frame > m_endframe)	m_frame = m_startframe;
		if (m_frame < m_startframe)	m_frame = m_endframe;
	}
	m_framerect.left = long((m_frame%m_framep)*m_framew);
	m_framerect.top = long((m_frame / m_framep)*m_frameh);
	m_framerect.right = long((m_framerect.left + m_framew));
	m_framerect.bottom = long((m_framerect.top + m_frameh));
}
/*void MySprite::Animate()
{	
	if ((int)GetTickCount() > m_starttime + m_delay)
	{
		m_starttime = (int)GetTickCount();
		m_frame += 1;
		if (m_frame > m_endframe)	m_frame = m_startframe;
		if (m_frame < m_startframe)	m_frame = m_endframe;
	}
} 
void MySprite::MouseUpdate()
{
	m_v = { 0,0,0 }; Animate();
	m_prepos = m_pos;
	m_pos.x = mousepos.x; m_pos.y = mousepos.y;
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
*/
