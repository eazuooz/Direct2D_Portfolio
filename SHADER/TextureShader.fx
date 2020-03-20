////////// VTX
struct VTX_IN
{
    float4 vPos : POSITION;
    float2 vUv : TEXCOORD; // 텍스처 좌표
    float4 vCol : COLOR; // 색깔
};

struct VTX_OUT
{
    float4 vPos : SV_POSITION;
    float2 vUv : TEXCOORD; // 텍스처 좌표
    float4 vCol : COLOR; // 색깔
};

struct TEST
{
    float4 vColor;
};

// 행렬
cbuffer MATDATA : register(b0)
{
    matrix WVP;
}

// 텍스처중 일부분만 렌더링 하기 위한 FLOAT4가 필요.
cbuffer CUTDATA : register(b1)
{
    float4 CutUv;
    // x y는 시작점의 정보.
    // z w에는 크기를 넣어줄 것이다.
    // 시작점은?
    // 0.25 0.25 시작점
    // 0.5 0.5 크기
}

cbuffer COLDATA : register(b2)
{
    float4 COL;
}

cbuffer HPDATA : register(b3)
{
    float HP;
}

VTX_OUT VS_TEX(VTX_IN _in)
{
    // 일부분만 랜더링 한다는 이야기는
    // 

    // 0 0 | 1 0
    // 0 1 | 1 1

    //   0.25 0.25   | 0.75    0.25 
    //   0.25 0.75F   | 0.75  0.75

    VTX_OUT Out = (VTX_OUT) 0.0f;
    Out.vCol = _in.vCol;
    

    //           1           0.5        0.25
    Out.vUv.x = (_in.vUv.x * CutUv.z) + CutUv.x;
    //           0           0.5        0.25
    Out.vUv.y = (_in.vUv.y * CutUv.w) + CutUv.y;

    // Out.vUv = _in.vUv;

    Out.vPos = mul(_in.vPos, WVP);





    return Out;
}


///// PIX



struct PIX_OUT
{
    float4 vOutColor : SV_Target;
};

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);

PIX_OUT PS_TEX(VTX_OUT _in)
{
    PIX_OUT Out = (PIX_OUT) 0.0f;
    Out.vOutColor = Tex.Sample(Smp, _in.vUv); // 이부분
    
    
    Out.vOutColor.a *= COL.a; //0.55f;

    if (0.0f == Out.vOutColor.a)
    {
        clip(-1); //이픽셀을 무시해라
    }

    // 0.9를 넣으면 0.9~ 1.0까지 클립
    //if (Uv.x > 0.7f)
    if (_in.vUv.x > HP.x)
    {
        clip(-1);
    }

    //_in.vUv.x = HP;

    
    
    //if (HP)
    //{
    //    clip(-1);
    //}



    //TEST colorTest = {0.0f, 0.0f, 0.0f, 1.0f };
    //Out.vOutColor.r = COL.r;     
    
    
    //float4 black = { 0.0f, 0.0f, 0.0f, 1.0f};
    //if (0.0f == Out.vOutColor.r && 0.0f == Out.vOutColor.g && 0.0f == Out.vOutColor.b)
    //{
    //    clip(-1); //이픽셀을 무시해라
    //}

    
    //if (0.0f == Out.vOutColor.rgb )
    //{
    //    clip(-1); //이픽셀을 무시해라
    //}

    //int r = Out.vOutColor.r * 256;
    //int g = Out.vOutColor.r * 256;
    //int b = Out.vOutColor.r * 256;

    ////Out.vOutColor.x *= 10.0f;
    ////Out.vOutColor.y *= 10.0f;
    ////Out.vOutColor.z *= 10.0f;
    
    //if(15 < r && 17 > r )
    //{
    //    Out.vOutColor.x *= 20.0f;
    //    Out.vOutColor.y *= 20.0f;
    //    Out.vOutColor.z *= 20.0f;
    //    Out.vOutColor.a = 0.5f;
    //}
    



    return Out;
}