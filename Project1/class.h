#include<d3d9.h>
#include<d3dx9.h>
#include<vector>
#include<string>
using namespace std;
#ifndef classes
#define classes
class OriSprite 
{public:D3DXVECTOR3 m_pos;
		int m_index;
		RECT m_framerect;
		virtual ~OriSprite();
};
class MySprite:public OriSprite
{public://数据成员 
		D3DXVECTOR3 m_pos; D3DXVECTOR3 m_prepos;
		D3DXVECTOR3 m_v; int m_controller;
		int m_score;
		int m_width,m_height;
		int m_frame,m_startframe,m_endframe,m_framep,m_starttime,m_direction,m_delay;
		//成员函数 
		MySprite(int index,float posx,float posy, int framew, int frameh,int startframe,int endframe,int framep,int direction,int delay);
		void Animate();
		void MouseUpdate();
		void KeyUpdate();
		void SelfUpdate();
		void DrawFrame();
};
class DrawManager
{
public:vector<OriSprite> m_todraw;
	   void SpriteReigster(MySprite &spritetodraw);
	   void qdraw();
};
#endif 