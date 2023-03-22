#include "globals.hlsli"

struct VSOut
{
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

float4 main(VSOut In) : SV_Target
{
    float4 color = (float) 0.0f;
    
    // 2D
    if (animationType == 1)
    {
        float2 diff = (atlasSize - spriteSize) / 2.0f;
        float2 UV = (leftTop - diff - offset) + (atlasSize * In.UV);
        
        if (
            UV.x < leftTop.x ||
            UV.y < leftTop.y ||
            UV.x > leftTop.x + spriteSize.x ||
            UV.y > leftTop.y + spriteSize.y
            )
        {
            discard;
        }
        
        color = atlasTexture.Sample(anisotropicSampler, UV);
    }
    else
    {
        color = defaultTexture.Sample(anisotropicSampler, In.UV);
    }
    
    LightColor lightColor = (LightColor) 0.0f;
    
    for (int i = 0; i < numberOfLight; i++)
    {
        CalculateLight(lightColor, In.WorldPos.xyz, i);
    }
    
    color *= lightColor.diffuse;
    
    if (color.a == 0.0f)
    {
        discard;
    }
    
    return color;
}