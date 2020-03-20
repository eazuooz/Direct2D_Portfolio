#include "GraphicDevice.h"
#include <MyWindow.h>


#pragma region MGR

//std::map<std::wstring, My_Ptr<GraphicDevice>> GraphicDevice::g_DeviceMap;
GraphicDevice* GraphicDevice::m_Inst = nullptr;
bool GraphicDevice::pathInit = false;


//My_Ptr<GraphicDevice> GraphicDevice::CreateDevice(const wchar_t* _WindowName)
//{
//	My_Ptr<Window> findWindow = Window::FindMyWindow(_WindowName);
//
//	if (nullptr == findWindow)
//	{
//		BOOM;
//	}
//
//	My_Ptr<GraphicDevice> newDevice = new GraphicDevice();
//
//	newDevice->Init(findWindow);
//
//	if (0 == g_DeviceMap.size())
//	{
//		m_Inst = newDevice;
//	}
//	newDevice->BaseResInit();
//	newDevice->baseInit = true;
//
//
//	g_DeviceMap.insert(std::map<std::wstring, My_Ptr<GraphicDevice>>::value_type(_WindowName, newDevice));
//
//	//return nullptr;
//	return newDevice;
//}


#pragma endregion


#pragma region MEMBER

GraphicDevice::GraphicDevice(): device(nullptr), context(nullptr), swapChain(nullptr), 
								depthStencilView(nullptr), texture2D(nullptr), backBufferView(nullptr), baseInit(false)
{

}


GraphicDevice::~GraphicDevice()
{
	targetWindow = nullptr;

	if (nullptr != texture2D)			{ texture2D			->Release();	texture2D			= nullptr; };
	if (nullptr != depthStencilView)	{ depthStencilView	->Release();	depthStencilView	= nullptr; };
	if (nullptr != backBufferView)		{ backBufferView	->Release();	backBufferView		= nullptr; };
	if (nullptr != swapChain)			{ swapChain			->Release();	swapChain			= nullptr; };
	if (nullptr != context)				{ context			->Release();	context				= nullptr; };
	if (nullptr != device)				{ device			->Release();	device				= nullptr; };
}

void GraphicDevice::MainReset()
{
	context->VSSetShader(nullptr, nullptr, 0);
	context->HSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->CSSetShader(nullptr, nullptr, 0);
	context->DSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->OMSetDepthStencilState(nullptr, 0);
}

void GraphicDevice::Init(Window* _TargetWindow)
{
	int flag = 0;

#ifdef  _DEBUG
	flag = D3D11_CREATE_DEVICE_DEBUG;
#endif //  _DEBUG
	targetWindow = _TargetWindow;

	D3D_FEATURE_LEVEL eLv = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;


	backColor = { 4.0f/ 255.0f, 104.0f / 255.0f, 216.0f / 255.0f, 1.0f }; 

	
	//QueryInterface(__uuidof(IDXGIDevice), (void**)&giDevice);
	//giDevice->GetAdapter(&pAdapter);
	
	iAdapter = 0;
	if (S_OK != CreateDXGIFactory1(__uuidof(IDXGIFactory), (void**)&factory))
	{		
		return;
	}

	//IDXGIDevice::GetAdapter(&pAdapter);
	if (S_OK != factory->EnumAdapters(iAdapter, &pAdapter))
	{		
		return;
	}
	pAdapter->GetDesc(&adapterDesc);
	pAdapter->EnumOutputs(iAdapter, &pOutput);
	pOutput	->GetDesc(&outDesc);
	
	
	HRESULT check;

	check = D3D11CreateDevice
	(
		nullptr,	//디바이스 만들때 부가정보가 있나요? nullptr
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,	//그래픽카드가 어떤 기반에 의한것인가 -> 하드웨어
		nullptr,
		flag,
		nullptr,
		0,
		D3D11_SDK_VERSION, //SDK버전
		&device,
		&eLv,
		&context
	);

	//check = D3D11CreateDevice
	//(
	//	pAdapter,	//디바이스 만들때 부가정보가 있나요? nullptr
	//	D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,	//그래픽카드가 어떤 기반에 의한것인가 -> 하드웨어
	//	nullptr,
	//	flag,
	//	nullptr,
	//	0,
	//	D3D11_SDK_VERSION, //SDK버전
	//	&device,
	//	&eLv,
	//	&context
	//);

	if (S_OK != check) { BOOM; return; }

	//이걸 색갈 기반으로 처리하는 것이기 때문에 가장 기준이 되는 색상을
	//DXGI_FORMAT_R8G8B8A8_UNORM
	//device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MSAA_LV);

	////스왑체인을 만든다.......
	//check = device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &MSAA_LV);
	//if (S_OK != check) { BOOM; return; }


	multisampleLevel	= 4;
	multisampleQuality	= 0;

	D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT;
	check = device->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, multisampleLevel, &multisampleQuality);
	if (S_OK != check)
	{
		multisampleLevel = 1;
		multisampleQuality = 0;
		check = device->CheckMultisampleQualityLevels(DXGI_FORMAT_B8G8R8A8_UNORM, multisampleLevel, &multisampleQuality);
		return;
	}
	multisampleLevel = 1;
	multisampleQuality = 0;

	// 스왑체인을 만든다.
	// 내일 나머지 
	if (false == CreateSwapChain())
	{
		BOOM;
	}

	if (false == CreateDepthStencilView())
	{
		BOOM;
	}

	if (false == CreateViewPort())
	{
		BOOM;
	}

	if (nullptr == m_Inst)
	{
		m_Inst = this;
		device = this->GetDXDevice();
		context = this->GetDXContext();
	}

	BaseResInit();
}

////PUBLIC
void GraphicDevice::ClearTarget()
{
	if (nullptr != context)
	{
		context->ClearRenderTargetView(backBufferView, backColor.Arr);
		context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}
void GraphicDevice::Present()
{
	if (nullptr != swapChain)
	{
		swapChain->Present(0, 0);
	}
}

////PRIVATE
bool GraphicDevice::CreateSwapChain()
{
	

	//DESC 단어 나오면 디스크립션 정보
	DXGI_SWAP_CHAIN_DESC SCInfo;

	SCInfo.BufferDesc.Width		= targetWindow->GetWindowSize().UINT_X();
	SCInfo.BufferDesc.Height	= targetWindow->GetWindowSize().UINT_Y();

	//모니터의 최대해상도를 얻어올수 있다.
	//모니터의 헤르츠(주사율)을 얻어올수 있다.

	//분자 분모
	SCInfo.BufferDesc.RefreshRate.Numerator		= 144;
	SCInfo.BufferDesc.RefreshRate.Denominator	= 1;

	SCInfo.BufferDesc.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;
	SCInfo.BufferDesc.ScanlineOrdering	= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SCInfo.BufferDesc.Scaling			= DXGI_MODE_SCALING_UNSPECIFIED;

	//백버퍼의 용도
	//화면에 출력하는 용도로 쓰인다
	SCInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	//백버퍼의 갯수
	//멀티샘플링 퀄리티
	//0 알아서
	//SCInfo.SampleDesc.Count = m_ML;
	SCInfo.SampleDesc.Count = multisampleLevel;
	SCInfo.SampleDesc.Quality = multisampleQuality;

	// 더블버퍼링과 비슷한데.
// 2개의 이미지로 
	SCInfo.OutputWindow = targetWindow->GetHWnd();
	// 버퍼개수 1 ~ 
	SCInfo.BufferCount = 2;

	//0  -> 화면에 나오고 있다.
	//1 -> 그려지고 있다. -> 다 그려졌다.
	//기존 정보를 다지운다
	//2개의 그림을 그리기 시작할때 지우고 새로그린다. -> 다 그려지면 -> 기존걸
	SCInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	//swap chain 이펙트

	//풀스크린 인가요
	SCInfo.Windowed =! targetWindow->IsFull();
	SCInfo.Flags = 0;
	DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED;

	//정보만 세팅된거고
	//이제 만드는 것을 해야한다.
	//그런데 다이렉트는 스왑체인을 만들기 위해서 좀 복잡한 과정을 거쳐야한다.

	// 다이렉트 11부터는 난이도가 높아졌다는 이유가
	//com객체방식이라는 것을 사용해서 처리하게 만들어졋다

	//m_pDevice->createsw
	//이녀석들을 단순히 힙에 할당하고 관리되는 녀석이 아니고
	//마소에서 만든 메모리 관리방식에 의해 따로 관리되고 있다.
	// 그래픽카드에 뭔가를 요청하거나 메모리를 할당하는 방식에 대한 인터페이스는
	// new Texture();
	// 이녀석들을 통해서만 그래픽카드에 요청해라.
	// ID3D11Device* m_pDevice

	IDXGIDevice*	pidxDevice	= nullptr;
	IDXGIAdapter*	pIdxAdapter = nullptr;
	IDXGIFactory*	pIdxFactory = nullptr;
	// 이걸 통하지 않고서는 
	// 못만들게 해놨다.
	// 그래픽 카드와의 통로

	device->QueryInterface(__uuidof(IDXGIDevice), (void**)&pidxDevice);
	if (nullptr == pidxDevice)
	{
		BOOM;
		return false;
	}

	//GUID를 통해서 얻어오게 만들어 놨다.
	pidxDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pIdxAdapter);
	if (nullptr == pIdxAdapter)
	{
		BOOM;
		return false;
	}

	pIdxAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pIdxFactory);
	if (nullptr == pIdxFactory)
	{
		BOOM;
		return false;
	}

	if (S_OK != pIdxFactory->CreateSwapChain(device, &SCInfo, &swapChain))
	{
		BOOM;
		return false;
	}

	pIdxFactory	->Release();
	pIdxAdapter	->Release();
	pidxDevice	->Release();

	return true;
}

bool GraphicDevice::CreateDepthStencilView()
{
	ID3D11Texture2D* backBufferTex = nullptr;

	//자동으로 텍스쳐 하나가 만들어져있기 때문에 이걸 얻어올수 있다.
	if (S_OK != swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferTex))
	{
		BOOM;
		return false;
	}

	//다이렉트의 view라고 표현된 객체들은
	//텍스쳐에 대한 정보와 처리관한을 사용할수 있는 인터페이스이다.
	//백버퍼의 깊이에 관여하거나 명령내릴수 있는 권한 객체를 만들어줘
	//나중에 백버퍼에 어떠한 명령을 내릴때 이녀석을 통해서 내린다
	
	if (S_OK != device->CreateRenderTargetView(backBufferTex, 0, &backBufferView))
	{
		BOOM;
		return false;
	}

	if (nullptr != backBufferTex)
	{
		backBufferTex->Release();
		backBufferTex = nullptr;
	}

	D3D11_TEXTURE2D_DESC textureDesc = {};

	textureDesc.ArraySize = 1;
	textureDesc.Width = targetWindow->GetWindowSize().UINT_X();
	textureDesc.Height = targetWindow->GetWindowSize().UINT_Y();

	//거울 만들거나
	//눈만 불타게 하고싶다거나
	//화면의 모든 픽셀중 스텐실 값이 4인녀석만 뭘할게요
	//3바이트만 깊이 값으로 사용하고 뒤에 8비트는 0~255 스텐실 값으로 사용한다.

	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.MipLevels = 1; // 꼭 설명해야 한다.
	// 메모리 관리 옵션
	// D3D11_USAGE_DEFAULT면 그래픽카드에서 관리해라.
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	// 텍스처의 용도가 뭐냐?
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	device->CreateTexture2D(&textureDesc, 0, &texture2D);

	if (nullptr == texture2D)
	{
		BOOM;
		return false;
	}

	device->CreateDepthStencilView(texture2D, 0, &depthStencilView);

	if (nullptr == depthStencilView)
	{
		BOOM;
		return false;
	}

	// D3D11_DEPTH_STENCIL_DESC TD;
	// m_pContext->OMSetDepthStencilState(TD, 1);

	return true;



}

bool GraphicDevice::CreateViewPort()
{
	viewPortInfo.TopLeftX = 0;
	viewPortInfo.TopLeftY = 0;

	viewPortInfo.Width = targetWindow->GetWindowSize().x;
	viewPortInfo.Height = targetWindow->GetWindowSize().y;
	viewPortInfo.MinDepth = 0.0f;
	viewPortInfo.MaxDepth = 1.0f;

	context->RSSetViewports(1, &viewPortInfo);

	return true;
}

#pragma endregion


void GraphicDevice::RenderTargetSetting()
{
	if (nullptr != context && nullptr != depthStencilView)
	{
		//깊이 버퍼는 그런다 자체만 놓고보면 없어도 상관이 없다.
		//내가 이 렌더타겟과 이 깊이버퍼를 사용해서
		//그려지는 놈들의 색깔과 정보를 세팅하겠습니다.

		context->OMSetRenderTargets(1, &backBufferView, depthStencilView);
	}
}

void GraphicDevice::ViewPortSetting()
{
	if (nullptr != context)
	{
		context->RSSetViewports(1, &viewPortInfo);
	}
}



