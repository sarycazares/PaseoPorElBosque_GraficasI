////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "openglclass.h"
#include "cameraclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "Terreno.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "Water.h"
#include "Modelos.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass : public CameraClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(OpenGLClass*, HWND);
	void Shutdown();
	bool Frame();
	float angx, angy, angz, vel;

	float posicionCameraX;
	float posicionCameraY;
	float posicionCameraZ;

	bool tercerapersona;
	float bicicletaTercerX;
	float bicicletaTercerZ;
	float bicicletacontador;
	float bicicletacontadorControl;


private:
	bool Render(float);

private:
	OpenGLClass* m_OpenGL;
	CameraClass* m_Camera;
	LightClass* m_Light;
	int contador;
	int wateranimation;
	OpenGLClass* m_OpenGL01;

	Terreno* terreno;
	LightShaderClass* m_LightShader;
	Terreno* terreno02;
	LightShaderClass* m_LightShader02;
	Terreno* terreno03;
	LightShaderClass* m_LightShader03;
	Terreno* terreno04;
	LightShaderClass* m_LightShader04;

	SkyDome* sky;
	LightShaderClass* m_LightShaderSky;

	Terreno* water01;
	LightShaderClass* m_LightShaderWater01;
	Terreno* water02;
	LightShaderClass* m_LightShaderWater02;

	///////////////////////////////////////////////
	Modelos* nube01;
	LightShaderClass* m_nube01Shader;
	Modelos* nube02;
	LightShaderClass* m_nube02Shader;
	Modelos* nube03;
	LightShaderClass* m_nube03Shader;
	Modelos* nube04;
	LightShaderClass* m_nube04Shader;
	Modelos* nube05;
	LightShaderClass* m_nube05Shader;
	Modelos* nube06;
	LightShaderClass* m_nube06Shader;
	Modelos* nube07;
	LightShaderClass* m_nube07Shader;
	Modelos* nube08;
	LightShaderClass* m_nube08Shader;
	Modelos* nube09;
	LightShaderClass* m_nube09Shader;
	Modelos* nube10;
	LightShaderClass* m_nube10Shader;

	Modelos* casaJaponesa01;
	LightShaderClass* m_casaJaponesa01Shader;
	Modelos* casaJaponesa02;
	LightShaderClass* m_casaJaponesa02Shader;
	Modelos* casaJaponesa03;
	LightShaderClass* m_casaJaponesa03Shader;
	Modelos* casaJaponesa04;
	LightShaderClass* m_casaJaponesa04Shader;

	Modelos* banca01;
	LightShaderClass* m_banca01Shader;
	Modelos* banca02;
	LightShaderClass* m_banca02Shader;
	Modelos* banca03;
	LightShaderClass* m_banca03Shader;
	Modelos* banca04;
	LightShaderClass* m_banca04Shader;
	Modelos* banca05;
	LightShaderClass* m_banca05Shader;
	Modelos* banca06;
	LightShaderClass* m_banca06Shader;

	Modelos* puente01;
	LightShaderClass* m_puenteShader01;
	Modelos* puente02;
	LightShaderClass* m_puenteShader02;
	Modelos* puente03;
	LightShaderClass* m_puenteShader03;

	Modelos* campaña;
	LightShaderClass* m_campañaShader;

	Modelos* faro;
	LightShaderClass* m_faroShader;
	Modelos* faro2;
	LightShaderClass* m_faro2Shader;

	Modelos* bicicleta;
	LightShaderClass* m_bicicletaShader;

	Modelos* pez01;
	LightShaderClass* m_pez01Shader;

	Modelos* perro;
	LightShaderClass* m_PerroShader;

	Modelos* ASakura01;
	LightShaderClass* m_SakuraShader01;
	//Modelos* ASakura02;
	//LightShaderClass* m_SakuraShader02;
	Modelos* ASakura03;
	LightShaderClass* m_SakuraShader03;

	//Modelos* Arbusto;
	//LightShaderClass* m_ArbustoShader;

	////////////////////////////////////////////////

	Billboard* billArbol01;
	LightShaderClass* m_BillShaderArbol01;

	Billboard* billArbol02;
	LightShaderClass* m_BillShaderArbol02;

	Billboard* billArbol03;
	LightShaderClass* m_BillShaderArbol03;

	Billboard* billArbol04;
	LightShaderClass* m_BillShaderArbol04;

	Billboard* billArbol05;
	LightShaderClass* m_BillShaderArbol05;

	Billboard* billArbol06;
	LightShaderClass* m_BillShaderArbol06;

	Billboard* billArbol07;
	LightShaderClass* m_BillShaderArbol07;
};

#endif