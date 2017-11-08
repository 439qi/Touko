#include"main.h"
RECT framerect;
string text="User: Touko";
RECT textrect = { Swidth-100,Sheight-20,Swidth,Sheight };
DrawManager dm;
void Draw()
{	
	d3ddev->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,255,255),1.0f,0);
	if(!d3ddev)	MessageBox(NULL,"d3ddev not existed","Error",MB_OK);
	if(d3ddev->BeginScene())
	{	d3ddev->StretchRect(surface,NULL,backbuffer,NULL,D3DTEXF_NONE);
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
		dm.qdraw();
		printtext(text,0,0,0);
		spriteobj->End();
		d3ddev->EndScene();	
		d3ddev->Present(NULL,NULL,NULL,NULL);
	}
} 