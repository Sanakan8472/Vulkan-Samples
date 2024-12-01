
RWTexture2DArray<half4> OutputTexture : register(u0, space0);

[numthreads(8, 8, 1)]
void main(uint3 groupID : SV_GroupID, uint3 groupThreadID : SV_GroupThreadID)
{
  const uint faceIndex = groupID.z;
  const uint2 pixelIndex = uint2(groupID.x * 8 + groupThreadID.x, groupID.y * 8 + groupThreadID.y);

  uint width, height, mipCount;
  OutputTexture.GetDimensions(width, height, mipCount);

  //if (width != 8)
  //  return;

  // Check for out of bounds threads
  if (pixelIndex.x >= width || pixelIndex.y >= height)
    return;

  // Compute tex coord using centroid sampling.
  const float2 texCoord = float2(((float)pixelIndex.x + 0.5) / width, ((float)pixelIndex.y + 0.5) / height );
  
  float4 color = float4(texCoord.xy, 0, 1);

  if (pixelIndex.x == width - 1 || pixelIndex.y == height - 1 || pixelIndex.x == 0 || pixelIndex.y == 0)
    color = float4(0,0,1,0);
  OutputTexture[uint3(pixelIndex, faceIndex)] = color;
}
