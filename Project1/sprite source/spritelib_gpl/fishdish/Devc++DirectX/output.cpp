#include"main.h"
RECT rect={0,0,100,200};
D3DXVECTOR3 drawpos={100,100,0};
int starttime=0;
int frame=0;
void Run()
{	if(!d3ddev) return;
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	if (d3ddev->BeginScene())
	{
		spriteobj->Begin(D3DXSPRITE_ALPHABLEND);
		spriteobj->Draw(texture,NULL, NULL, &drawpos, D3DCOLOR_XRGB(255, 255, 255));
		spriteobj->End();
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}
