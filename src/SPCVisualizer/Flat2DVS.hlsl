struct VertexInputType
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInputType main(VertexInputType input)
{
    PixelInputType output;
    output.color = input.color;
    output.position = input.position;
    return output;
}