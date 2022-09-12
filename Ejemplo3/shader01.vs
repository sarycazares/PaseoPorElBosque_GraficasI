////////////////////////////////////////////////////////////////////////////////
// Filename: shader01.vs
////////////////////////////////////////////////////////////////////////////////
#version 400


in vec3 inputPosition;
in vec3 inputNormal;
in vec2 inputTexCoord;
in vec3 inputTangent;
in vec3 inputBinormal;

out vec2 texCoord;
out vec3 normal;
out mat3 TBN;
out vec3 light;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightDirection;	

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader - Multitextura - Ambient Light - Difuse Light - Especular Light
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	gl_Position = worldMatrix * vec4(inputPosition, 1.0f);
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;


	texCoord = inputTexCoord;
	

	vec3 normal = vec3(worldMatrix * vec4(inputNormal, 1.0));
	vec3 tangente = vec3(worldMatrix * vec4(inputTangent, 1.0));
	vec3 binormal = normalize(cross(normal, tangente));


	normal = normalize(normal);
	tangente = normalize(tangente);
	binormal = normalize(binormal);
	light = normalize(lightDirection);
	//incluir la tang la binormal y la normal
	TBN = mat3(tangente, binormal, normal);
	
}