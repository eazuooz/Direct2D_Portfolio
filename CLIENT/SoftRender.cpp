#include "SoftRender.h"

#include <MyWindow.h>
#include <Path.h>
#include <Maths.h>
#include <Input.h>
#include <MyTime.h>
#include <Mesh.h>

#include <GraphicDevice.h>

#include <VertexShader.h>
#include <PixelShader.h>
#include <ConstantBuffer.h>

My_Ptr<Mesh> mesh;
My_Ptr<ConstBuffer> CB;
My_Ptr<VtxShader> VTXSH;
My_Ptr<PxlShader> PIXSH;


HDC mainGetHDC;
Vector4 Arr[6][4];
Vector4 RenderArr[6][4];

Vector4 CamPos;
Vector4 CamRot;
Matrix VIEWMAT;
Matrix VIEWROT;

Matrix PROJMAT;
Matrix VIEWPORTMAT;

Vector4 Pos;
Matrix POSMAT;

Vector4 Scale;
Matrix SCALEMAT;

Vector4 Rot;
Matrix ROTMAT;
Matrix ROTX;
Matrix ROTY;
Matrix ROTZ;
Matrix MATW;

float scaleValue = 100.0f;
float moveSpeed  = 100.0f;
float rotSpeed = 360.0f;

void DebugRender();

void Init()
{
#pragma region SOFTRENDERING
	//mainGetHDC = Window::MainWindow()->GetHDC();

	//// 앞면
	//Arr[0][0] = Vector4(-0.5f,	0.5f, -0.5f);
	//Arr[0][1] = Vector4( 0.5f,  0.5f, -0.5f);
	//Arr[0][2] = Vector4( 0.5f, -0.5f, -0.5f);
	//Arr[0][3] = Vector4(-0.5f, -0.5f, -0.5f);

	//// 뒷면
	//Arr[1][0] = Vector4(-0.5f, -0.5f, 0.5f);
	//Arr[1][1] = Vector4(0.5f,  -0.5f, 0.5f);
	//Arr[1][2] = Vector4(0.5f,   0.5f, 0.5f);
	//Arr[1][3] = Vector4(-0.5f,  0.5f, 0.5f);

	//// 왼쪽
	//Arr[2][0] = Vector4(-0.5f,  0.5f,  0.5f);
	//Arr[2][1] = Vector4(-0.5f,  0.5f, -0.5f);
	//Arr[2][2] = Vector4(-0.5f, -0.5f, -0.5f);
	//Arr[2][3] = Vector4(-0.5f, -0.5f,  0.5f);

	//// 오른쪽
	//Arr[3][0] = Vector4(0.5f, 0.5f, -0.5f);
	//Arr[3][1] = Vector4(0.5f, 0.5f, 0.5f);
	//Arr[3][2] = Vector4(0.5f, -0.5f, 0.5f);
	//Arr[3][3] = Vector4(0.5f, -0.5f, -0.5f);

	//// 위
	//Arr[4][0] = Vector4(-0.5f, 0.5f, 0.5f);
	//Arr[4][1] = Vector4(0.5f, 0.5f,  0.5f);
	//Arr[4][2] = Vector4(0.5f, 0.5f, -0.5f);
	//Arr[4][3] = Vector4(-0.5f, 0.5f,-0.5f);

	//// 아래
	//Arr[5][0] = Vector4(-0.5f, -0.5f, -0.5f);
	//Arr[5][1] = Vector4(0.5f, -0.5f,  -0.5f);
	//Arr[5][2] = Vector4(0.5f, -0.5f,   0.5f);
	//Arr[5][3] = Vector4(-0.5f, -0.5f,  0.5f);

	//
	//Pos = Vector4(100.0f, 100.0f, 0.0f);
	//CamPos = Vector4(0, 0, -200.0f);
	//
	//Scale.SetValue(50.0f);

	Input::CreateKey(L"CamPosX+", VK_RIGHT);
	Input::CreateKey(L"CamPosY+", VK_UP);
	Input::CreateKey(L"CamPosZ+", '[');
	Input::CreateKey(L"CamPosX-", VK_LEFT);
	Input::CreateKey(L"CamPosY-", VK_DOWN);
	Input::CreateKey(L"CamPosZ-", ']');

	Input::CreateKey(L"CamRotX+", '1');
	Input::CreateKey(L"CamRotY+", '2');
	Input::CreateKey(L"CamRotZ+", '3');
	Input::CreateKey(L"CamRotX-", '4');
	Input::CreateKey(L"CamRotY-", '5');
	Input::CreateKey(L"CamRotZ-", '6');

	Input::CreateKey(L"ScaleX+", 'I');
	Input::CreateKey(L"ScaleY+", 'O');
	Input::CreateKey(L"ScaleZ+", 'P');
	Input::CreateKey(L"ScaleX-", 'J');
	Input::CreateKey(L"ScaleY-", 'K');
	Input::CreateKey(L"ScaleZ-", 'L');
	
	Input::CreateKey(L"MoveX+", 'D');
	Input::CreateKey(L"MoveY+", 'W');
	Input::CreateKey(L"MoveZ+", 'Q');
	Input::CreateKey(L"MoveX-", 'A');
	Input::CreateKey(L"MoveY-", 'S');
	Input::CreateKey(L"MoveZ-", 'E');

	Input::CreateKey(L"RotX+", 'T');
	Input::CreateKey(L"RotY+", 'Y');
	Input::CreateKey(L"RotZ+", 'U');
	Input::CreateKey(L"RotX-", 'F');
	Input::CreateKey(L"RotY-", 'G');
	Input::CreateKey(L"RotZ-", 'H');

	Input::CreateKey(L"Debug1", 'Z');
	Input::CreateKey(L"Debug2", 'X');
	Input::CreateKey(L"Debug3", 'C');
	Input::CreateKey(L"Debug4", 'V');
	Input::CreateKey(L"Debug5", 'B');
	Input::CreateKey(L"Debug6", 'N');
	Input::CreateKey(L"Debug7", 'M');
#pragma endregion
	//new int;
	//내프로그램 어디에서 실행되더라도
	//리소스나 데이터파일들을 항상 같은 경로로 처리할 수 있는
	//방법과 경로를 만들어 내야 한다

	Path::root.ReplaceToParentPath();
	Path::root.MoveDirectory(L"_BIN");

	Path::CreatePath(L"SHADER");


	Debug::Inst().ConsolePrintLine(Path::root.GetFullPath());
	{
		std::vector<Index::IDX32> ArrIdx;
		ArrIdx.push_back({ 0, 3, 2 });
		ArrIdx.push_back({ 0, 1, 3 });

		std::vector<Vertex::Vtx2D> ArrVtx;
		ArrVtx.resize(4);

		ArrVtx[0].pos = Vector4(-0.5f, 0.5f, 0.5f, 1.0f);
		ArrVtx[1].pos = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
		ArrVtx[2].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.0f);
		ArrVtx[3].pos = Vector4(0.5f, -0.5f, 0.5f, 1.0f);

		ArrVtx[0].uv = Vector2(0.0f, 0.0f);
		ArrVtx[1].uv = Vector2(1.0f, 0.0f);
		ArrVtx[2].uv = Vector2(0.0f, 1.0f);
		ArrVtx[3].uv = Vector2(1.0f, 1.0f);
		
		ArrVtx[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		ArrVtx[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		ArrVtx[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		ArrVtx[3].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

		mesh = new Mesh();
		mesh->CreateIB(ArrIdx, D3D11_USAGE_DYNAMIC);
		mesh->CreateVB(ArrVtx, D3D11_USAGE_DYNAMIC);
		mesh->DrawModeChange(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	{
		VTXSH = new VtxShader();

		VTXSH->Load(Path::FindPathToString(L"SHADER") + L"\\ColorRect.fx", 5, 0, "VS_COLORRECT");
		VTXSH->AddLayOut("POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
		VTXSH->AddLayOut("TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0);
		VTXSH->EndLayOut("COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
		PIXSH = new PxlShader();
		PIXSH->Load(Path::FindPathToString(L"SHADER") + L"\\ColorRect.fx", 5, 0, "
			");
	}

	{
		CB = new ConstBuffer();
		CB->Create(Shader::SHADERTYPE::SHTYPE_VS, sizeof(Matrix), 0);
	}

	CamPos = Vector4(0, 0, -500.0f);

	Scale.SetValue(100.0f);
}

void TestLoop()
{
#pragma region SOFTRENDERING
	Time::Update();
		Input::Update();
	
		memcpy_s(RenderArr, sizeof(Vector4) * 4 * 6, Arr, sizeof(Vector4) * 4 * 6);
	
	#pragma region CAMPOS
	
		if (true == Input::Press(L"CamPosX+"))
		{
			CamPos.x += scaleValue * Time::DeltaTime();
		}
	
		if (true == Input::Press(L"CamPosY+"))
		{
			CamPos.y += scaleValue * Time::DeltaTime();
		}
		if (true == Input::Press(L"CamPosZ+"))
		{
			CamPos.z += scaleValue * Time::DeltaTime();
		}
	
		if (true == Input::Press(L"CamPosX-"))
		{
			CamPos.x -= scaleValue * Time::DeltaTime();
		}
		if (true == Input::Press(L"CamPosY-"))
		{
			CamPos.y -= scaleValue * Time::DeltaTime();
		}
		if (true == Input::Press(L"CamPosZ-"))
		{
			CamPos.z -= scaleValue * Time::DeltaTime();
		}
	
	#pragma endregion
	
	#pragma region CAMPOS
		if (true == Input::Press(L"CamRotX+"))
		{
			CamRot.x += rotSpeed /10.0f * Time::DeltaTime();
		}
		if (true == Input::Press(L"CamRotY+"))
		{
			CamRot.y += rotSpeed / 10.0f* Time::DeltaTime();
		}
		if (true == Input::Press(L"CamRotZ+"))
		{
			CamRot.z += rotSpeed / 10.0f* Time::DeltaTime();
		}
	
		if (true == Input::Press(L"CamRotX-"))
		{
			CamRot.x -= rotSpeed / 10.0f* Time::DeltaTime();
		}
		if (true == Input::Press(L"CamRotY-"))
		{
			CamRot.y -= rotSpeed / 10.0f* Time::DeltaTime();
		}
		if (true == Input::Press(L"CamRotZ-"))
		{
			CamRot.z -= rotSpeed / 10.0f* Time::DeltaTime();
		}
	#pragma endregion
	
	#pragma region SCALE
		if (true == Input::Press(L"ScaleX+"))
		{
			Scale.x += scaleValue * Time::DeltaTime();
		}
		if (true == Input::Press(L"ScaleY+"))
		{
			Scale.y += scaleValue * Time::DeltaTime();
		}
		if (true == Input::Press(L"ScaleZ+"))
		{
			Scale.z += scaleValue * Time::DeltaTime();
		}
	
		if (true == Input::Press(L"ScaleX-"))
		{
			Scale.x -= scaleValue * Time::DeltaTime();
		}
		if (true == Input::Press(L"ScaleY-"))
		{
			Scale.y -= scaleValue * Time::DeltaTime();
		}
		if (true == Input::Press(L"ScaleZ-"))
		{
			Scale.z -= scaleValue * Time::DeltaTime();
		}
	#pragma endregion
	
	#pragma region MOVE
		if (true == Input::Press(L"MoveX+"))
		{
			Pos.x += moveSpeed * Time::DeltaTime();
		}
		if (true == Input::Press(L"MoveY+"))
		{
			Pos.y += moveSpeed * Time::DeltaTime();
		}
		if (true == Input::Press(L"MoveZ+"))
		{
			Pos.z += moveSpeed * Time::DeltaTime();
		}
	
		if (true == Input::Press(L"MoveX-"))
		{
			Pos.x -= moveSpeed * Time::DeltaTime();
		}
		if (true == Input::Press(L"MoveY-"))
		{
			Pos.y -= moveSpeed * Time::DeltaTime();
		}
		if (true == Input::Press(L"MoveZ-"))
		{
			Pos.z -= moveSpeed * Time::DeltaTime();
		}
	
	
		//회전
		if (true == Input::Press(L"RotX+"))
		{
			Rot.x += rotSpeed * Time::DeltaTime();
		}
		if (true == Input::Press(L"RotY+"))
		{
			Rot.y -= rotSpeed * Time::DeltaTime();
		}
		if (true == Input::Press(L"RotZ+"))
		{
			Rot.z += rotSpeed * Time::DeltaTime();
		}
	
		if (true == Input::Press(L"RotX-"))
		{
			Rot.x -= rotSpeed * Time::DeltaTime();
		}
		if (true == Input::Press(L"RotY-"))
		{
			Rot.y += rotSpeed * Time::DeltaTime();
		}
		if (true == Input::Press(L"RotZ-"))
		{
			Rot.z -= rotSpeed * Time::DeltaTime();
		}
	//
	//
	//	//
	//
	//	//BOOL InvalidateRect(HWND hWnd,		CONST RECT *lpRect,		BOOL bErase	);
	//	InvalidateRect(Window::MainWindow()->GetHWnd(), NULL, TRUE);
	//
	//
	//	// 단위행렬    크자이공부    뷰행렬         투영행렬        뷰포트공간
	//	// 로컬    ->  월드       -> 뷰스페이스  -> 투영스페이스 -> 2D뷰포트
	//
	//	VIEWROT.RRot(CamRot);
	//	VIEWMAT.VIEWTOLH(CamPos, VIEWROT.Foword(), VIEWROT.Up());
	//	
	//	
	//	PROJMAT.PROJTOLHANDDEG(90.0f, 800.0F, 600.0F, 1.0f, 1000.0F);
	//	VIEWPORTMAT.VIEWPORT(0.0f, 0.0f, 800.0f, 600.0F, 0.0f, 1.0f);
	//
	//	//이동행렬이 되었다.
	//	SCALEMAT.Scale(Scale);
	//
	//	ROTX.DRotX(Rot.x);
	//	ROTX.DRotY(Rot.y);
	//	ROTX.DRotZ(Rot.z);
	//
	//	ROTMAT = ROTX * ROTY * ROTZ;
	//
	//	POSMAT.Pos(Pos);
	//
	//	MATW = SCALEMAT * ROTMAT * POSMAT;
	//	MATW = MATW * VIEWMAT * PROJMAT;
	//
	//#pragma endregion
	//
	//	bool render[6] = { true, true, true, true, true, true };
	//	//크자이공부
	//	for (size_t i = 0; i < 6; i++)
	//	{
	//		for (size_t j = 0; j < 4; j++)
	//		{
	//			RenderArr[i][j] = MATW * RenderArr[i][j];
	//		}
	//	}
	//
	//	// w로 갑자기 다 나눈다.
	//	// 그래서 -1~1공간에 들어가게 된다.
	//	for (size_t i = 0; i < 6; i++)
	//	{
	//		for (size_t j = 0; j < 4; j++)
	//		{
	//			if (RenderArr[i][j].z < 0.0f)
	//			{
	//				continue;
	//			}
	//
	//			float ViewZ = RenderArr[i][j].w;
	//			RenderArr[i][j].x /= ViewZ;
	//			RenderArr[i][j].y /= ViewZ;
	//			RenderArr[i][j].z /= ViewZ;
	//			RenderArr[i][j].w = 1.0f;
	//		}
	//	}
	//
	//	for (size_t i = 0; i < 6; i++)
	//	{
	//
	//		for (size_t j = 0; j < 4; j++)
	//		{
	//			RenderArr[i][j] = VIEWPORTMAT * RenderArr[i][j];
	//		}
	//	}
	//
	//	Vector4 Arr11[6];
	//	for (size_t i = 0; i < 6; i++)
	//	{
	//		Arr11[i] = ((RenderArr[i][0] - RenderArr[i][2]) * 0.5f) + RenderArr[i][2];
	//	}
	//
	//	Vector4 CrossArr[6];
	//	bool render2[6] = { false, false, false, false, false, false };
	//	for (size_t i = 0; i < 6; i++)
	//	{
	//		CrossArr[i] = Vector4::CrossProduct(RenderArr[i][0] - Arr11[i], RenderArr[i][1] - Arr11[i]);
	//		if (CrossArr[i].z > 0.0f)
	//		{
	//			render2[i] = true;
	//		}
	//	}
	//
	//
	//	POINT Arr[6][4];
	//	for (size_t i = 0; i < 6; i++)
	//	{
	//		for (size_t j = 0; j < 4; j++)
	//		{
	//			Arr[i][j] = RenderArr[i][j].ConvertPoint();
	//		}
	//	}
	//
	//
	//	
	//	
	//	/*if ( )
	//	{
	//		continue;
	//	}*/
	//	
	//	for (size_t k = 0; k < 6; k++)
	//	{
	//		Vector4 value = Vector4::CrossProduct(RenderArr[k][0] - RenderArr[k][1], RenderArr[k][1] - RenderArr[k][2]);
	//
	//		int CNT = 0;
	//	}
	//	
	//
	//
	//
	//	for (size_t i = 0; i < 6; i++)
	//	{
	//		for (size_t k = 0; k < 6; k++)
	//		{
	//			Vector4 value = Vector4::CrossProduct(RenderArr[k][0] - RenderArr[k][1], RenderArr[k][1] - RenderArr[k][2]);
	//
	//			int CNT = 0;
	//
	//			if (value.x < 0.0f || value.y < 0.0f || value.z < 0.0f)
	//			{
	//				continue;
	//			}
	//
	//			if (true == render[i] &&
	//				true == render2[i])
	//			Polygon(mainGetHDC, Arr[i], 4);
	//		}
	//		
	//		DebugRender();
	//		
	//	}
	//
	//	int a = 0;
	//}
	//
	//bool Debug[6];
	//void DebugRender()
	//{
	//	if (true == Input::Down(L"Debug1"))
	//	{
	//		Debug[0] = true;
	//		Debug[1] = false;
	//		Debug[2] = false;
	//		Debug[3] = false;
	//		Debug[4] = false;
	//		Debug[5] = false;
	//	}
	//	if (true == Input::Down(L"Debug2"))
	//	{
	//		Debug[0] = false;
	//		Debug[1] = true;
	//		Debug[2] = false;
	//		Debug[3] = false;
	//		Debug[4] = false;
	//		Debug[5] = false;
	//	}
	//	if (true == Input::Down(L"Debug3"))
	//	{
	//		Debug[0] = false;
	//		Debug[1] = false;
	//		Debug[2] = true;
	//		Debug[3] = false;
	//		Debug[4] = false;
	//		Debug[5] = false;
	//	}
	//	if (true == Input::Down(L"Debug4"))
	//	{
	//		Debug[0] = false;
	//		Debug[1] = false;
	//		Debug[2] = false;
	//		Debug[3] = true;
	//		Debug[4] = false;
	//		Debug[5] = false;
	//	}
	//	if (true == Input::Down(L"Debug5"))
	//	{
	//		Debug[0] = false;
	//		Debug[1] = false;
	//		Debug[2] = false;
	//		Debug[3] = false;
	//		Debug[4] = true;
	//		Debug[5] = false;
	//	}
	//	if (true == Input::Down(L"Debug6"))
	//	{
	//		Debug[0] = false;
	//		Debug[1] = false;
	//		Debug[2] = false;
	//		Debug[3] = false;
	//		Debug[4] = false;
	//		Debug[5] = true;
	//	}
	//
	//	if (true == Input::Down(L"Debug7"))
	//	{
	//		Debug[0] = false;
	//		Debug[1] = false;
	//		Debug[2] = false;
	//		Debug[3] = false;
	//		Debug[4] = false;
	//		Debug[5] = false;
	//	}
	//
	//	wchar_t ARR[10] = { 0 };
	//	std::wstring Text;
	//	
	//	if (true == Debug[0])
	//	{
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			swprintf_s(ARR, L"%d", i + 1);
	//			Text = ARR;
	//			TextOut(Window::MainWindow()->GetHDC(), (int)RenderArr[0][i].x, (int)RenderArr[0][i].y, Text.c_str(), (int)Text.size());
	//		}
	//	}
	//	
	//	if (true == Debug[1])
	//	{
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			swprintf_s(ARR, L"%d", i + 1);
	//			Text = ARR;
	//			TextOut(Window::MainWindow()->GetHDC(), (int)RenderArr[1][i].x, (int)RenderArr[1][i].y, Text.c_str(), (int)Text.size());
	//		}
	//	}
	//
	//	if (true == Debug[2])
	//	{
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			swprintf_s(ARR, L"%d", i + 1);
	//			Text = ARR;
	//			TextOut(Window::MainWindow()->GetHDC(), (int)RenderArr[2][i].x, (int)RenderArr[2][i].y, Text.c_str(), (int)Text.size());
	//		}
	//	}
	//	
	//	if (true == Debug[3])
	//	{
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			swprintf_s(ARR, L"%d", i + 1);
	//			Text = ARR;
	//			TextOut(Window::MainWindow()->GetHDC(), (int)RenderArr[3][i].x, (int)RenderArr[3][i].y, Text.c_str(), (int)Text.size());
	//		}
	//	}
	//
	//	if (true == Debug[4])
	//	{
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			swprintf_s(ARR, L"%d", i + 1);
	//			Text = ARR;
	//			TextOut(Window::MainWindow()->GetHDC(), (int)RenderArr[4][i].x, (int)RenderArr[4][i].y, Text.c_str(), (int)Text.size());
	//		}
	//	}
	//
	//	if (true == Debug[5])
	//	{
	//		for (int i = 0; i < 4; ++i)
	//		{
	//			swprintf_s(ARR, L"%d", i + 1);
	//			Text = ARR;
	//			TextOut(Window::MainWindow()->GetHDC(), (int)RenderArr[5][i].x, (int)RenderArr[5][i].y, Text.c_str(), (int)Text.size());
	//		}
	//	}
#pragma endregion

GraphicDevice::Inst()->ClearTarget();

GraphicDevice::Inst()->RenderTargetSetting();

GraphicDevice::Inst()->ViewPortSetting();

VIEWMAT.SetViewMatrix(CamPos, VIEWROT.Foword(), VIEWROT.Up());
PROJMAT.SetPerspectiveMatrix(60.0f, 800.0f, 600.0f, 1.0f, 100000.0f);

SCALEMAT.Scaling(Scale);
ROTX.RotateX_Degree(Rot.x);
ROTY.RotateY_Degree(Rot.y);
ROTZ.RotateZ_Degree(Rot.z);
ROTMAT = ROTX * ROTY * ROTZ;

POSMAT.Translation(Pos);

MATW = SCALEMAT * ROTMAT * POSMAT;
MATW = MATW * VIEWMAT * PROJMAT;

MATW.TransPose();

CB->DataSetting(&MATW, sizeof(Matrix));
CB->Update();


VTXSH->Update();
PIXSH->Update();

mesh->Render(0, 0);

GraphicDevice::Inst()->Present();



}
