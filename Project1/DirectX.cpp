#include"main.h"
const int texnum = 5;
string texturetoload[texnum] = { "./pics/id_314.png","./pics/cursor.png" ,"./pics/charinfo.png","./pics/jl.png","./pics/blueSheet.png" };
string surfacetoload = "./pics/background.jpg";
//D3D初始化
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev=NULL;
//图像输出 
LPDIRECT3DSURFACE9 backbuffer=NULL;
LPDIRECT3DTEXTURE9 texture[10];
LPDIRECT3DSURFACE9 surface=NULL;
LPD3DXSPRITE spriteobj=NULL;
//文本输出 
LPD3DXFONT font=NULL;

//控制
POINT mousepos;
char keys[256];
char prekeys[256];
DIMOUSESTATE mousexy;
LPDIRECTINPUT8 dinput=NULL;
LPDIRECTINPUTDEVICE8 keyboard=NULL;
LPDIRECTINPUTDEVICE8 mouse=NULL;
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
	surface=LoadSurface(surfacetoload);
	if(surface==NULL)	MessageBox(NULL,"Error load surface","Error",MB_OK);
	 //字体加载
	font=LoadFont(17);
	if(font==NULL)	MessageBox(NULL,"Error Load font","Error",MB_OK);
	//纹理加载
	for (int i = 0; i < texnum; i++)
	{
		texture[i]=LoadTexture(texturetoload[i]);
	}
	if(texture[0]==NULL)	MessageBox(NULL,"Error Load texture","Error",MB_OK);
	//键盘鼠标控制获取 
	DInput_Init(hwnd);

}
LPDIRECT3DTEXTURE9 LoadTexture(string filename)
{	
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 ls;
		HRESULT result = D3DXGetImageInfoFromFile(filename.c_str(), &info);
		if (result != D3D_OK) MessageBox(hwnd,"Error get image info","Error",MB_OKCANCEL);
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
			D3DCOLOR_XRGB(255,255,255),
			&info,
			0,
			&ls);
		if (result != D3D_OK) return NULL;
		return ls;
}
LPDIRECT3DSURFACE9 LoadSurface(string filename)
{	

	LPDIRECT3DSURFACE9 surface = NULL; D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(filename.c_str(), &info);
	d3ddev->CreateOffscreenPlainSurface(info.Width,info.Height,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT,&surface,NULL);
	D3DXLoadSurfaceFromFile(surface,NULL,NULL,filename.c_str(),NULL,D3DX_DEFAULT,0,NULL);
	return surface;
}
LPD3DXFONT LoadFont(int height)
{	LPD3DXFONT font=NULL;
	D3DXFONT_DESC desc={height,0,0,0,false,DEFAULT_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_PITCH,"aRIAL"};	
	D3DXCreateFontIndirect(d3ddev,&desc,&font);
	return font;
}
void printtext(string text,int r,int g,int b)
{
	font->DrawText(NULL,text.c_str(),text.length(),&textrect,DT_CALCRECT,Color_White);
	font->DrawText(spriteobj,text.c_str(),text.length(),&textrect,DT_LEFT,D3DCOLOR_XRGB(r,g,b));
}
void printtext(int a, int r, int g, int b)
{
	string text = inttostring(a);
	font->DrawText(NULL, text.c_str(), text.length(), &textrect, DT_CALCRECT, Color_White);
	font->DrawText(spriteobj, text.c_str(), text.length(), &textrect, DT_LEFT, D3DCOLOR_XRGB(r, g, b));
}
bool DInput_Init(HWND hwnd)
{
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL);
	dinput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (keyboard == NULL) { MessageBox(NULL, "Error create keyboard", "Error", MB_OKCANCEL); return false; }
	keyboard->SetDataFormat(&c_dfDIKeyboard); keyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	keyboard->Acquire();
	dinput->CreateDevice(GUID_SysMouse,&mouse,NULL);
	if(mouse==NULL) { MessageBox(NULL, "Error create mouse", "Error", MB_OKCANCEL); return false; }
	mouse->SetDataFormat(&c_dfDIMouse); mouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE |DISCL_BACKGROUND);
	mouse->Acquire();
	return true;
}
void Dinput_Update()
{	
	GetCursorPos(&mousepos); ScreenToClient(FindWindow("WindowClass","Transistor"), &mousepos);
	memcpy(prekeys, keys, sizeof(keys));
	keyboard->GetDeviceState(sizeof(keys),(LPVOID)&keys);
	mouse->GetDeviceState(sizeof(mousexy), (LPVOID)&mousexy);
}
void D3D_End()
{	

	dinput->Release();
	keyboard->Unacquire();
	keyboard->Release();
	font->Release(); 
	spriteobj->Release();
	d3ddev->Release();
	d3d->Release();
 } 
