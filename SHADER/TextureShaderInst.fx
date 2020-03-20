
struct VTX_IN
{
    float4 vPos      : POSITION;
    float2 vUv       : TEXCOORD;
    float4 vColor    : COLOR;

    row_major matrix    MATWVP : WVP;         // row_major 요 표현을 쓰면 중간 메모리 구분을 없애고 한번에 세트로 받을수 있게 된다.
    float4              vSpriteUv : SPRITEUV;
};

struct VTX_OUT
{
    float4 vPos      : SV_POSITION;
    float2 vUv       : TEXCOORD;
    float4 vColor    : COLOR;
};

VTX_OUT VS_TEX(VTX_IN _In)
{
    VTX_OUT Out = (VTX_OUT) 0.0f;
    Out.vColor = _In.vColor;

    //              1               0.5             0.25
    Out.vUv.x = (_In.vUv.x * _In.vSpriteUv.z) + _In.vSpriteUv.x;
    Out.vUv.y = (_In.vUv.y * _In.vSpriteUv.w) + _In.vSpriteUv.y;

    Out.vPos = mul(_In.vPos, _In.MATWVP);

    return Out;
}