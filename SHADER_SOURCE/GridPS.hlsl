#include "globals.hlsli"

struct VSOut
{
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    float2 WorldPos : POSITION;
};

float4 main(VSOut In) : SV_Target
{
    float4 Out = float4(0.5f, 0.5f, 0.5f, 1.0f);
    
    const int width = 100;
    const int height = 100;
    
    float worldX = (float)In.WorldPos.x;
    float worldY = (float)In.WorldPos.y;
    
    // ¼± µÎ²²
    const float thickness = 1.0f;
    
    if (abs(worldX) % width <= thickness || abs(worldY) % height <= thickness)
    {
        if (abs(worldX) <= 1.0f)
        {
            return float4(0.0f, 1.0f, 0.0f, 1.0f);
        }
        
        if (abs(worldY) <= 1.0f)
        {
            return float4(1.0f, 0.0f, 0.0f, 1.0f);
        }
        
        return Out;
    }
    
    discard;
    
    return Out;
}

