#include"main.h"
//D3D初始化
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev=NULL;
LPDIRECT3DSURFACE9 backbuffer=NULL;
LPDIRECT3DTEXTURE9 stickman=NULL;
LPDIRECT3DSURFACE9 surface=NULL;
LPD3DXSPRITE spriteobj=NULL;
LPD3DXFONT font=NULL;
void D3D_Init(HWND hwnd)
{	//D3D初始化 
	d3d=Direct3DCreate9(D3D_SDK_VERSION);
	if(d3d==NULL)	MessageBox(NULL,"Error create D3D","Error",MB_OK);
	//D3D设备初始化 
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
	if(d3ddev==NULL)	MessageBox(NULL,"Error Create D3DDev","Error",MB_OK);	
	//后台缓存区获取 
	d3ddev->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&backbuffer);
	//精灵创建
	D3DXCreateSprite(d3ddev,&spriteobj); 
	//表面加载
	surface=LoadSurface("2333.bmp");
	if(surface==NULL)	MessageBox(NULL,"Error load surface","Error",MB_OK);
	 //字体加载
	font=LoadFont(17);
	if(font==NULL)	MessageBox(NULL,"Error Load font","Error",MB_OK);
	//纹理加载
	stickman=LoadTexture("stickman.bmp"); 
	if(stickman==NULL)	MessageBox(NULL,"Error Load texture","Error",MB_OK);
}
LPDIRECT3DTEXTURE9 LoadTexture(string filename)
{	
	LPDIRECT3DTEXTURE9 texture=NULL;
	D3DXIMAGE_INFO info;
	HRESULT result=D3DXGetImageInfoFromFile(filename.c_str(),&info);
	if(result!=D3D_OK) return NULL;
	result=D3DXCreateTextureFromFileEx(d3ddev,
	filename.c_str(),
	info.Width,
	info.Height,
	1,
	D3DPOOL_DEFAULT,
	D3DFMT_UNKNOWN,
	D3DPOOL_DEFAULT,
	D3DX_DEFAULT,
	D3DX_DEFAULT,
	D3DCOLOR_XRGB(0,0,0),
	&info,
	0,
	&texture);
	if(result!=D3D_OK) return NULL;
	return texture;
}
LPDIRECT3DSURFACE9 LoadSurface(string filename)
{	

	LPDIRECT3DSURFACE9 surface=NULL;
	d3ddev->CreateOffscreenPlainSurface(400,400,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&surface,NULL);
	D3DXLoadSurfaceFromFile(surface,NULL,NULL,filename.c_str(),NULL,D3DX_DEFAULT,0,NULL);
	return surface;
}
void D3D_End()
{	spriteobj->Release();
	d3ddev->Release();
	d3d->Release();
 } 

