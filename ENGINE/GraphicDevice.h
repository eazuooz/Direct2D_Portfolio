#pragma once

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X32\\_BASED32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X32\\_BASER32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X64\\_BASED64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X64\\_BASER64.lib")
#endif
#endif

#include <Maths.h>

//윈도우 10부터는 윈도우 그 자체의 렌더링에도 다이렉트가 쓰이고 있기때문에
//윈도우 기반 c++에서는  stdlib수준으로 다 include 포함까지 되어있다.

#define D3D2

//#include <DirectXMath.h>
#include <d3dtypes.h>
#include <d3d11_4.h>

#include <d3dcompiler.h> //쉐이더를 컴파일러하는데 사용되는 헤더
#include <MyWindow.h>
#include <map>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "dxgi")



//그래픽 카듸의 기능을 사용하기 위한 라이브러리인 D3DX 의 기능을 모아둔 클래스

class Window;
class GraphicDevice : public ControlBlock
{
private:
	//static GraphicDevice* mainDevice;	
	static GraphicDevice* m_Inst;
	static bool pathInit;
	//static ID3D11Device* pMainDevice;

public:
	static GraphicDevice* Inst()
	{
		return m_Inst;
	}
	
	//My_Ptr<GraphicDevice> CreateDevice(const wchar_t* _WindowName);

/////////MEMBER
private:
	UINT				iAdapter;
	IDXGIFactory*		factory;	
	IDXGIAdapter*		pAdapter;
	IDXGIOutput*		pOutput;
	DXGI_ADAPTER_DESC	adapterDesc;
	DXGI_OUTPUT_DESC	outDesc;
	IDXGIDevice*		giDevice;

private:
	Window* targetWindow;
	UINT MSAA_LV;	//멀티 샘플링 레벨
	//그래픽카드를 다이렉트로 프로그래밍하는것에대한 모든것은 아래의 두가지 포인터를 통해서 한다.
	ID3D11Device*			device;	//그래픽카드에 대한 모든 자원에 대한 권한을 담당
	ID3D11DeviceContext*	context;	//그래픽카드의 모든 연산에 대한 권한을 담당한다.	
	IDXGISwapChain*			swapChain; //IDXGISwapChain의 인터페이스는 하나 이상의 구현 표면 출력에 보내기 전에 렌더링 된 데이터를 저장한다.
	ID3D11RenderTargetView* backBufferView;
	ID3D11DepthStencilView* depthStencilView;	//깊이 버퍼 렌더링 파이프라인에 관계한다.
	ID3D11Texture2D*		texture2D;	//2D 텍스처 인터페이스는 구조화 된 메모리 인 텍셀 데이터를 관리합니다.
		
	Vector4					backColor;
	D3D11_VIEWPORT			viewPortInfo;	//뷰포트 행렬용 정보
	
	UINT multisampleLevel;
	UINT multisampleQuality;
	
	bool baseInit;
	void BaseResInit();

	void DeviceStateInit();
	void MeshInfoInit();
	void ShaderInfoInit();

public:
	void MainReset();

	ID3D11Device* GetDXDevice()
	{
		return device;
	}
	ID3D11DeviceContext* GetDXContext()
	{
		return context;
	}

public:
	void Init(Window* _TargetWindow);

	void ClearTarget();
	void Present();

private:
	//다이렉트 x에서도 우리가 직접 만들필요가 없는 화면 갱신신스템을 지원해준다.
	bool CreateSwapChain();
	bool CreateDepthStencilView();
	bool CreateViewPort();

public:
	void RenderTargetSetting();
	void ViewPortSetting();

public:
	GraphicDevice();
	~GraphicDevice();
};

