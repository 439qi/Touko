#include<d3d9.h>
#include<d3dx9.h>
#include<vector>
#include<string>
using namespace std;
#ifndef classes
#define classes
class Button
{
public:int m_imageindex;
	   D3DXVECTOR3 m_pos;
	   RECT m_rect;
	   Button(int imageindex, int id, int x, int y);
	   void LoadXml();
};
class State
{
public:virtual void Execute() = 0;
};
class GameState
{
public:vector<Button*> m_buttons;
	   GameState();
	   State* m_currentstate;
	   static GameState gs;
	   static GameState* instance();
};
class GameState_Menu :public State
{
public:void Execute();
	   static GameState_Menu gsm;
	   static GameState_Menu* instance();

};

class OriSprite 
{public:
		int m_imageindex, m_framew, m_frameh,m_framep,m_startframe,m_endframe;
		D3DXVECTOR3 m_pos,m_sale,m_centre,m_rotation;
		RECT m_framerect;
public:	OriSprite(int id, int posx, int posy);
		void LoadXml(OriSprite &os);
		virtual ~OriSprite();
		virtual void Update()=0;
};

class MySprite:public OriSprite
{public://���ݳ�Ա 
		D3DXVECTOR3 m_pos; D3DXVECTOR3 m_prepos;
		D3DXVECTOR3 m_v; int m_controller;
		int m_score;
		int m_width,m_height;
		int m_frame,m_startframe,m_endframe,m_framep,m_starttime,m_direction,m_delay;
		//��Ա���� 
		void Animate();
		void MouseUpdate();
		void KeyUpdate();
		void SelfUpdate();
};


#endif 