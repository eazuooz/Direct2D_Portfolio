#pragma once
#include "Renderer.h"
#include "Font.h"

class FontRenderer : public Renderer
{
private:
	Font* font;

	class TextInfo
	{
	public:
		std::wstring fontName;
		std::wstring text;

		float size;
		Vector4 color;
	};
	TextInfo text;

	Vector4 addPos;

public:
	void SetText(std::wstring _Text, float _Size, Vector4 _Color)
	{
		text.text = _Text;
		text.size = _Size;
		text.color = _Color;
	}

	void SetPos(Vector4 _Pos)
	{
		addPos = _Pos;
	}


public:
	void Init() override;
	void Render(const My_Ptr<Camera>& _CAM) override;
	void Update() override;


	void SetFont(std::wstring _FontName);
	void SetColorAlpha(float _Value);
	void SetColorAlphaMul(float _Value);

public:
	FontRenderer();
	~FontRenderer();
};

