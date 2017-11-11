#include<d3d9.h>
#include<d3dx9.h>
#include<windows.h>
#include<string>
#include<cstring>
#include<iostream>
#include"class.h"
#include<dinput.h>
#include"resource.h"
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <imm.h>  
#include"tinyxml2.h"
#pragma comment (lib ,"imm32.lib") 
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
using namespace std;
using namespace tinyxml2;
#define Color_White D3DCOLOR_XRGB(255,255,255)
#define Color_Black D3DCOLOR_XRGB(0,0,0)
#define GS GameState::instance()

//���� 
extern bool Over;
extern bool showcursor;
extern bool limitcursor;
extern string Title;
string texturetoload[];
extern RECT window;
extern POINT mousepos;
extern char keys[256];
extern char prekeys[256];
enum keypress { press, hold, loose };
enum controller{mousecol,keycol,nothing};
extern int  Swidth;
extern int Sheight;
extern RECT framerect;
extern RECT textrect;
extern string text;


//Direct3D
//D3D��ʼ��
extern HWND hwnd;
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
//���漰������� 
extern LPDIRECT3DTEXTURE9 texture[10];
extern LPDIRECT3DSURFACE9 surface;
extern LPD3DXSPRITE spriteobj;
extern LPD3DXFONT font;
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 keyboard;
extern LPDIRECTINPUTDEVICE8 mouse; 
extern DIMOUSESTATE mousexy;
//����


void Settings();
void All_Run();
string inttostring(const int &a);
int stringtoint(const string &a);
void Draw();
LPD3DXFONT LoadFont(int height);
void printtext(string text,int r,int g,int b);
void D3D_Init(HWND hwnd); 
bool DInput_Init(HWND hwnd);
void Dinput_Update();
int Key_Down(int key );
bool MoveLimit(const MySprite &spi, RECT &limit);
bool WindowLimit(const MySprite &spi);
RECT GetCursorRect();
void D3D_End();
LPDIRECT3DTEXTURE9 LoadTexture(string filename);
LPDIRECT3DSURFACE9 LoadSurface(string filename);

//��(��ṹ��) 
class myvector
{public:float x, y;
		myvector(float a,float b):x(a),y(b){
		}
};


