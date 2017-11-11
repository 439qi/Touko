#include"main.h"
RECT framerect;
int starttime=0;
int frame=0;
D3DXVECTOR3 pos;
int fx=1,fy=1;
int score=0;
void AniSprite(int startframe,int endframe,int direction,int delay)
{	
	if((int)GetTickCount()>starttime+delay)
	{	starttime=GetTickCount();
		frame+=direction;
		//移动 
		pos.x+=direction*15*fx;
		pos.y+=direction*10*fy;
		if(pos.x>Swidth)	{fx=-1;score++;}
		if(pos.x<0)			{fx=1;score++;}
		if(pos.y>Sheight)	{fy=-1;score++;}
		if(pos.y<0)			{fy=1;score++;}
		if(frame>endframe)	frame=startframe;
		if(frame<startframe)	frame=endframe;
	}
}
void DrawFrame(int frame,int framew,int frameh,int framecolumn)
{	framerect.left=long((frame%framecolumn)*framew);
	framerect.top=long((frame/framecolumn)*frameh);
	framerect.right=long((framerect.left+framew));
	framerect.bottom=long((framerect.top+frameh));
}
void Draw()
{	
	pos.z=0;
	d3ddev->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,255,255),1.0f,0);
	AniSprite(0,4,1,75);
	DrawFrame(frame,32,32,5);
	if(!d3ddev)	MessageBox(NULL,"d3ddev not existed","Error",MB_OK);
	if(d3ddev->BeginScene())
	{	d3ddev->StretchRect(surface,NULL,backbuffer,NULL,D3DTEXF_NONE);
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
		spriteobj->Draw(stickman,&framerect,NULL,&pos,D3DCOLOR_XRGB(255,255,255));
		printtext("Score: 不会打印");
		spriteobj->End();
		d3ddev->EndScene();	
		d3ddev->Present(NULL,NULL,NULL,NULL);
	}
}
