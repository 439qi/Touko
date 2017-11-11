#include<windows.h>
#include<string>
#include<iostream>
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9math.h>
using namespace std;
//常量 
extern const int Swidth;
extern const int Sheight;
extern int score;
extern RECT framerect;
extern RECT textrect;
//Direct3D
//D3D初始化
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;
extern LPDIRECT3DTEXTURE9 stickman;
extern LPDIRECT3DSURFACE9 surface;
extern LPD3DXSPRITE spriteobj;
extern LPD3DXFONT font;
//函数
void Draw();
LPD3DXFONT LoadFont(int height);
void printtext(string text);
void DrawFrame(int frame,int framew,int frameh,int framecolumn);
void AniSprite(int startframe,int endframe,int direction,int delay);
void D3D_Init(HWND hwnd); 
void D3D_End();
LPDIRECT3DTEXTURE9 LoadTexture(string filename);
LPDIRECT3DSURFACE9 LoadSurface(string filename);
