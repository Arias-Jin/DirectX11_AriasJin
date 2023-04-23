#include "globals.hlsli"

struct VSIn
{
    float4 Pos : POSITIONT;
    uint iInstance : SV_InstanceID;
};

struct VSOut
{
    float4 Pos : SV_Position;
};

float4 main(VSOut In) : SV_Target
{
    float4 outColor = (float4) 0.0f;
    
    outColor = float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    return outColor;
}