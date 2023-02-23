#include "globals.hlsli"

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    
    if (time < 0.5f)
    {
        color = lerp(float4(0.0f, 0.0f, 0.0f, 0.0f), defaultTexture.Sample(anisotropicSampler, In.UV), time * 2.0f);
    }
    else
    {
        color = lerp(defaultTexture.Sample(anisotropicSampler, In.UV), float4(0.0f, 0.0f, 0.0f, 0.0f), (time - 0.5) * 2.0);
    }
    
    return color;
}