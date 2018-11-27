attribute mediump vec3 aPosition;
attribute mediump vec2 aTexCoord;
attribute mediump vec3 aNormal;
uniform   mediump mat4 uMvpMatrix;
uniform   mediump vec3 uSize;

varying mediump vec2 vTexCoord;
void main()
{
  mediump vec4 vertexPosition = vec4(aPosition, 1.0);
  vertexPosition.xyz *= uSize;
  vTexCoord = aTexCoord;
  gl_Position = uMvpMatrix * vertexPosition;
}