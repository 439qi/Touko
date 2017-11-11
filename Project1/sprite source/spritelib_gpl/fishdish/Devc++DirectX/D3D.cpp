#include"main.h"

//D3D初始化
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev=NULL;
//表面、纹理及精灵
LPDIRECT3DSURFACE9 surface=NULL;
LPDIRECT3DSURFACE9 backbuffer=NULL;
LPD3DXSPRITE spriteobj=NULL;
LPDIRECT3DTEXTURE9 texture = NULL;
//输入
void LoadTexture(string filename)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
	result = D3DXCreateTextureFromFileEx(d3ddev,
		filename.c_str(),
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 255, 255),
		&info,
		NULL,
		&texture);
}
bool D3D_Init(HWND hwnd)
{	d3d=Direct3DCreate9(D3D_SDK_VERSION);
	if(d3d==NULL)
	{	MessageBox(hwnd,"Error create D3D","Error",MB_OK);return false;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed=true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount=1;
	d3dpp.BackBufferWidth=Swidth;
	d3dpp.BackBufferHeight=Sheight;	
	d3dpp.hDeviceWindow = hwnd;
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	if(d3ddev==NULL)
	{	MessageBox(hwnd,"Error Create D3DDev","Error",MB_OK);return false;
	}	
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	D3DXCreateSprite(d3ddev,&spriteobj);
	LoadTexture("2333.bmp");
	if(texture==NULL)
	{	MessageBox(hwnd,"Error load texture","Error",MB_OK);
		return false;
	}
	return true;
}
void D3D_End()
{	spriteobj->Release();
	d3ddev->Release();
	d3d->Release();
 } 

