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
extern "C"
{
#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>
}
#pragma comment (lib ,"imm32.lib") 
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"lua5.1.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
using namespace std;
#define Color_White D3DCOLOR_XRGB(255,255,255)
#define Color_Black D3DCOLOR_XRGB(0,0,0)

//常量 
extern RECT window;
extern POINT mousepos;
extern bool Over;
extern char keys[256];
extern char prekeys[256];
enum keypress { press, hold, loose };
enum controller{mousecol,keycol,nothing};
extern  int Swidth;
extern const int Sheight;
extern RECT framerect;
extern RECT textrect;
extern string text;


//Direct3D
//D3D初始化
extern HWND hwnd;
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
//表面及纹理相关 
extern LPDIRECT3DTEXTURE9 texture[10];
extern LPDIRECT3DSURFACE9 surface;
extern LPD3DXSPRITE spriteobj;
extern LPD3DXFONT font;
extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 keyboard;
extern LPDIRECTINPUTDEVICE8 mouse; 
extern DIMOUSESTATE mousexy;
//函数
//Lua
bool Lua_Init();
int Lua_GetInt(lua_State* pl, const string &zname);

void All_Run();
string inttostring(const int &a);
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

//类(或结构体) 
class myvector
{public:float x, y;
		myvector(float a,float b):x(a),y(b){
		}
};
extern MySprite sp;
extern MySprite cursor;
extern MySprite cinfo;
extern MySprite aientity;
extern DrawManager dm;

