#include "CoinBox.h"

#include "ENUM.h"


int CoinBox::money = 200;
CoinBox::CoinBox() 
{
}


CoinBox::~CoinBox()
{
}


void CoinBox::Init()
{
	collider = GetActor()->GetComponent<BoundingBox>();

	collider->RegisterEnterFunction(&CoinBox::Enter, this);
	collider->RegisterStayFunction(&CoinBox::Stay, this);
	collider->RegisterExitFunction(&CoinBox::Exit, this);

	font = GetActor()->AddComponent< FontRenderer>(RG_UI);
	font->SetFont(L"Silkscreen");
	//std::wstring text = 100;


	//std::to_wstring();
	//Thank you all for watching";


	font->SetText(L"&100", 13.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });

	font->SetLocalPosition({0.0f, 0.37f, 10.0f});
}

void CoinBox::Update()
{
	std::wstring temp = L"$";
	temp += std::to_wstring(money);
	font->SetText(temp, 13.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });
	//폰트 실시간으로 출력해줘야한다.

}



void CoinBox::Enter(Collider* _This, Collider* _Other)
{
	int a = 0;

	Actor* coinActor = _Other->GetActor();
	CoinMove*  coinInfo = coinActor->GetComponent<CoinMove>();
	coinActor->Die();


	int coinLevel = coinInfo->GetCoinLevel();

	switch (coinLevel) //코인종류에 맞게 돈이 오르면된다.
	{
	case 1:
	{
		money += 20;
	}
	break;
	case 2:
	{
		money += 40;
	}
	break;
	case 3:
	{
		money += 60;
	}
	break;
	case 4:
	{
		money += 80;
	}
	break;
	case 5:
	{
		money += 100;
	}
	break;
	case 6:
	{
		money += 300;
	}
	break;
	}
}
void CoinBox::Stay(Collider* _This, Collider* _Other)
{

}
void CoinBox::Exit(Collider* _This, Collider* _Other)
{

}
