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
    
    color = defaultTexture.Sample(anisotropicSampler, In.UV);
    
    if (color.a == 0.0f)
    {
        discard;
    }
    
    return color;
}