#include"main.h"
RECT textrect={0,10,10,20};
LPD3DXFONT LoadFont(int height)
{	LPD3DXFONT font=NULL;
	D3DXFONT_DESC desc={
	height,0,0,0,false,DEFAULT_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_PITCH,"aRIAL"};	
	D3DXCreateFontIndirect(d3ddev,&desc,&font);
	return font;
}
void printtext(string text)
{	
	font->DrawText(NULL,text.c_str(),text.length(),&textrect,DT_CALCRECT,D3DCOLOR_XRGB(255,255,255));
	font->DrawText(spriteobj,text.c_str(),text.length(),&textrect,DT_LEFT,D3DCOLOR_XRGB(255,0,0));
}
