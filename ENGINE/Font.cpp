#include "Font.h"



Font::Font() : fontFactory(nullptr), fontWrapper(nullptr)
{
}


Font::~Font()
{
	if (nullptr != fontFactory)
	{
		fontFactory->Release();
		fontFactory = nullptr;
	}

	if (nullptr != fontWrapper)
	{
		fontWrapper->Release();
		fontWrapper = nullptr;
	}
}


//다이렉트에서 폰트를 만드는건 폰트 캐싱 글자조합에 따른 쉐어더 처리를 해줘야한다.
bool Font::Create(const wchar_t* _FontName)
{
	if (S_OK != FW1CreateFactory(FW1_VERSION, &fontFactory))
	{
		BOOM;
		return false;
	}

	if (S_OK != fontFactory->CreateFontWrapper(GraphicDevice::Inst()->GetDXDevice(), _FontName, &fontWrapper))
	{
		BOOM;
		return false;
	}

	return true;
}

bool Font::DrawWorld(const wchar_t* _Name, float _FontSize, Vector4 _Position, Vector4 _Color, FW1_TEXT_FLAG _Flag)
{
	return true;
}

void Font::DrawUI(const wchar_t* _Name, float _FontSize, Vector4 _Position, Vector4 _Color, FW1_TEXT_FLAG _Flag)
{
	if (nullptr == fontWrapper)
	{
		BOOM;
		return;
	}

	fontWrapper->DrawString(GraphicDevice::Inst()->GetDXContext(), _Name, _FontSize, _Position.x, _Position.y, _Color.ConvertUINTtoColorRGB(), _Flag);
}
