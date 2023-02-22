#include "globals.hlsli"

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    
    float2 WorldPos : POSITION;
};

float4 main(VSOut In) : SV_Target
{
    float4 Out = float4(0.5f, 0.5f, 0.5f, 0.5f);
    
    const int width = 100;
    const int height = 100;
    
    int worldX = (int) In.WorldPos.x;
    int worldY = (int) In.WorldPos.y;
    
    // ¼± µÎ²²
    const float thickness = 1.0f;
    
    if (abs(worldX) % width <= thickness)
    {
        return Out;
    }
    
    if (abs(worldY) % height <= thickness)
    {
        return Out;
    }
    
    discard;
    
    return Out;
}