////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "cameraclass.h"
#include "Water.h"

#define DEG_TO_RAD 0.0174532925f

GraphicsClass::GraphicsClass()
{
	m_OpenGL = 0;
	m_Camera = 0;
	m_LightShader = 0;
	m_LightShaderSky = 0;
	m_BillShaderArbol01 = 0;
	m_Light = 0;
	angx = angy = angz = 0;
	contador = 0;
	wateranimation = 500;
	tercerapersona = false;
	bicicletaTercerX = 0;
	bicicletaTercerZ = 6;
	bicicletacontador = 0;
	bicicletacontadorControl = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(OpenGLClass* OpenGL, HWND hwnd)
{
	bool result;

	//////////////////////////// CAMARA
	{
		// Store a pointer to the OpenGL class object.
		m_OpenGL = OpenGL;
		// Create the camera object.
		m_Camera = new CameraClass;
		if (!m_Camera)
		{
			return false;
		}
		// Set the initial position of the camera.
		m_Camera->SetPosition(76.0f, 50.0f, -9.0f);
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// TERRENO01
	{
		terreno = new Terreno(hwnd, m_OpenGL, L"Imagenes/terreno_01.bmp", L"Imagenes/hierba-cesped-textura-jardin.jpg", L"Imagenes/ZacatitoNorm.jpg",
			(float)400, (float)400, 0, 1);

		// Create the light shader object.
		m_LightShader = new LightShaderClass((char*)"light.vs", (char*)"light.ps");
		if (!m_LightShader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// TERRENO 02
	{
		//L"Imagenes//terreno_02.bmp", L"Imagenes//PebblesBeach003_DISP_1K.jpg", L"Imagenes//PebblesBeach003_NRM_1K.jpg"
		terreno02 = new Terreno(hwnd, m_OpenGL, L"Imagenes/terreno_11.bmp", L"Imagenes/PebblesBeach003_DISP_1K.jpg", L"Imagenes/PebblesBeach003_NRM_1K.jpg",
			(float)400, (float)400, 2, 3);

		// Create the light shader object.
		m_LightShader02 = new LightShaderClass((char*)"light.vs", (char*)"light.ps");
		if (!m_LightShader02)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShader02->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// TERRENO 03
	{
	//	//L"Imagenes//terreno_02.bmp", L"Imagenes//PebblesBeach003_DISP_1K.jpg", L"Imagenes//PebblesBeach003_NRM_1K.jpg"
	//	terreno03 = new Terreno(hwnd, m_OpenGL, L"Imagenes/terreno_13.bmp", L"Imagenes/hierba-cesped-textura-jardin.jpg", L"Imagenes/ZacatitoNorm.jpg",
	//		(float)1000, (float)1000, 8, 9);

	

	terreno03 = new Terreno(hwnd, m_OpenGL, L"Imagenes/terreno_13.bmp", L"Imagenes/hierba-cesped-textura-jardin.jpg", L"Imagenes/ZacatitoNorm.jpg",
		L"Imagenes/test1.jpg", L"Imagenes/ZacatitoNorm.jpg", L"Imagenes/blending_map.png", (float)1000, (float)1000, 150, 151,152,153,154);

		// Create the light shader object.
		m_LightShader03 = new LightShaderClass((char*)"shader01.vs", (char*)"shader01.ps");
		if (!m_LightShader03)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShader03->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}



	//////////////////////////// TERRENO 04
	{
		//L"Imagenes//terreno_02.bmp", L"Imagenes//PebblesBeach003_DISP_1K.jpg", L"Imagenes//PebblesBeach003_NRM_1K.jpg"
		terreno04 = new Terreno(hwnd, m_OpenGL, L"Imagenes/terreno_12.bmp", L"Imagenes/PebblesBeach003_DISP_1K.jpg", L"Imagenes/PebblesBeach003_NRM_1K.jpg",
			(float)1000, (float)1000, 6, 7);

		// Create the light shader object.
		m_LightShader04 = new LightShaderClass((char*)"light.vs", (char*)"light.ps");
		if (!m_LightShader04)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShader04->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// AGUA01
	{
		water01 = new Terreno(hwnd, m_OpenGL, L"Imagenes/water04.bmp", L"Imagenes/water.bmp", L"Imagenes/agua_01.bmp",
			(float)600, (float)600, 4, 5);

		// Create the light shader object.
		m_LightShaderWater01 = new LightShaderClass((char*)"Water.vs", (char*)"Water.ps");
		if (!m_LightShaderWater01)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShaderWater01->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the water shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// AGUA02
	{
		water02 = new Terreno(hwnd, m_OpenGL, L"Imagenes/water02.bmp", L"Imagenes/water.bmp", L"Imagenes/agua_01.bmp",
			(float)600, (float)600, 6, 7);

		// Create the light shader object.
		m_LightShaderWater02 = new LightShaderClass((char*)"Water.vs", (char*)"Water.ps");
		if (!m_LightShaderWater02)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShaderWater02->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the water shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-1.0f, 0.5f, -1.0f);


	//////////////////////////// SKYDOME
	{

		sky = new SkyDome(hwnd, m_OpenGL, 32, 32, 300, L"Imagenes/sky_reverse.jpg");
		// Create the light shader object.
		m_LightShaderSky = new LightShaderClass((char*)"Sky.vs", (char*)"Sky.ps");
		if (!m_LightShaderSky)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_LightShaderSky->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// NUBE01
	{
		//nube01 = new Modelos(hwnd, m_OpenGL,(char*)"Modelos/Clouds/cloud.obj", L"Modelos/Clouds/cloud.png", 0.25, 0, 0);

		nube01 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 20, 21, 0.50, 0, 0);

		m_nube01Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube01Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube01Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE02
	{
		//nube02 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/cloud.obj", L"Modelos/Clouds/cloud.png", 0.25, 0, 0);
		nube02 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 22, 23, 0.50, 0, 0);

		m_nube02Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube02Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube02Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE03
	{
		
		nube03 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 24, 25, 0.50, 0, 0);

		m_nube03Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube03Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube03Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE04
	{
		
		nube04 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 26, 27, 0.50, 0, 0);

		m_nube04Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube04Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube04Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE05
	{
		
		nube05 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 28, 29, 0.50, 0, 0);

		m_nube05Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube05Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube05Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE06
	{
		
		nube06 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 30, 31, 0.50, 0, 0);

		m_nube06Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube06Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube06Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE07
	{
		
		nube07 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 32, 33, 0.50, 0, 0);

		m_nube07Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube07Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube07Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE08
	{

		nube08 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 34, 35, 0.50, 0, 0);

		m_nube08Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube08Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube08Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE09
	{

		nube09 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 36, 37, 0.50, 0, 0);

		m_nube09Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube09Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube09Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// NUBE10
	{

		nube10 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Clouds/nube_esponjosa.obj", L"Modelos/Clouds/cloud_colored01.png", L"Modelos/Clouds/cloud_ddn.png", 38, 39, 0.50, 0, 0);

		m_nube10Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_nube10Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_nube10Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// CASAJAPONESA01
	{

		casaJaponesa01 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/House_japanese/japanese_house.obj", L"Modelos/House_japanese/Texture1.jpg", L"Modelos/House_japanese/Texture_Norm.jpg", 40, 41, 0.25, 0, 0);

		m_casaJaponesa01Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_casaJaponesa01Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_casaJaponesa01Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// CASAJAPONESA02
	{

		casaJaponesa02 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/House_japanese/japanese_house.obj", L"Modelos/House_japanese/Texture1.jpg", L"Modelos/House_japanese/Texture_Norm.jpg", 54, 55, 0.25, 0, 0);

		m_casaJaponesa02Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_casaJaponesa02Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_casaJaponesa02Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// CASAJAPONESA03
	{

		casaJaponesa03 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/House_japanese/japanese_house.obj", L"Modelos/House_japanese/Texture1.jpg", L"Modelos/House_japanese/Texture_Norm.jpg", 56, 57, 0.25, 0, 0);

		m_casaJaponesa03Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_casaJaponesa03Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_casaJaponesa03Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// CASAJAPONESA04
	{

		casaJaponesa04 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/House_japanese/japanese_house.obj", L"Modelos/House_japanese/Texture1.jpg", L"Modelos/House_japanese/Texture_Norm.jpg", 58, 59, 0.25, 0, 0);

		m_casaJaponesa04Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_casaJaponesa04Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_casaJaponesa04Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// BANCA01
	{

		banca01 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/banca/Banca.obj", L"Modelos/banca/TextuBanca.jpg", L"Modelos/banca/TextuBancaNorm.jpg", 42, 43, 0.25, 0, 0);

		m_banca01Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_banca01Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_banca01Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// BANCA02
	{

		banca02 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/banca/Banca.obj", L"Modelos/banca/TextuBanca.jpg", L"Modelos/banca/TextuBancaNorm.jpg", 44, 45, 0.25, 0, 0);

		m_banca02Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_banca02Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_banca02Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// BANCA03
	{

		banca03 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/banca/Banca.obj", L"Modelos/banca/TextuBanca.jpg", L"Modelos/banca/TextuBancaNorm.jpg", 46, 47, 0.25, 0, 0);

		m_banca03Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_banca03Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_banca03Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// BANCA04
	{

		banca04 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/banca/Banca.obj", L"Modelos/banca/TextuBanca.jpg", L"Modelos/banca/TextuBancaNorm.jpg", 48, 49, 0.25, 0, 0);

		m_banca04Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_banca04Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_banca04Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// BANCA05
	{

		banca05 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/banca/Banca.obj", L"Modelos/banca/TextuBanca.jpg", L"Modelos/banca/TextuBancaNorm.jpg", 50, 51, 0.25, 0, 0);

		m_banca05Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_banca05Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_banca05Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// BANCA06
	{

		banca06 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/banca/Banca.obj", L"Modelos/banca/TextuBanca.jpg", L"Modelos/banca/TextuBancaNorm.jpg", 52, 53, 0.25, 0, 0);

		m_banca06Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_banca06Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_banca06Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// PUENTE01
	{

		puente01 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/puente/Puente.obj", L"Modelos/puente/Puente.jpg", L"Modelos/puente/Puente.jpg", 60, 61, 0.25, 0, 0);

		m_puenteShader01 = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_puenteShader01)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_puenteShader01->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// PUENTE02
	{

		puente02 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/puente/Puente.obj", L"Modelos/puente/Puente.jpg", L"Modelos/puente/Puente.jpg", 62, 63, 0.25, 0, 0);

		m_puenteShader02 = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_puenteShader02)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_puenteShader02->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}
	//////////////////////////// PUENTE03
	{

		puente03 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/puente/Puente.obj", L"Modelos/puente/Puente.jpg", L"Modelos/puente/Puente.jpg", 64, 65, 0.25, 0, 0);

		m_puenteShader03 = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_puenteShader03)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_puenteShader03->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// CAMPAÑA
	{

		campaña = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/campaña/campaña.obj", L"Modelos/campaña/lambert3SG_Base_Color.png", L"Modelos/campaña/lambert3SG_Normal.png", 66, 67, 0.25, 0, 0);

		m_campañaShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_campañaShader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_campañaShader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// FARO
	{

		faro = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/faro/faro.obj", L"Modelos/faro/faro_04.png", L"Modelos/faro/faro_lambert6SG_Normal_OpenGL.png", 68, 69, 0.25, 0, 0);

		m_faroShader = new LightShaderClass((char*)"shader02.vs", (char*)"shader02.ps");
		if (!m_faroShader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_faroShader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// FARO2  shader3
	{

		faro2 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/faro/faro.obj", L"Modelos/faro/faro_04.png", L"Modelos/faro/faro_lambert6SG_Normal_OpenGL.png", 110, 111, 0.25, 0, 0);

		m_faro2Shader = new LightShaderClass((char*)"shader03.vs", (char*)"shader03.ps");
		if (!m_faro2Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_faro2Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// BICICLETA
	{

		bicicleta = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Bicicleta/BiciP.obj", L"Modelos/Bicicleta/bike.png", L"Modelos/Bicicleta/bike.png", 70, 71, 0.25, 0, 0);

		m_bicicletaShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_bicicletaShader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_bicicletaShader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// PEZ01
	{

		pez01 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/pez_01/TropicalFish01.obj", L"Modelos/pez_01/TropicalFish01.bmp", L"Modelos/pez_01/TropicalFish01.bmp", 72, 73, 0.010, 0, 0);

		m_pez01Shader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_pez01Shader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_pez01Shader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	////////////////////////////// PERRITO
	{

		perro = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/perro/Perrito.obj", L"Modelos/perro/ShibaD.bmp", L"Modelos/perro/ShibaN.bmp", 81, 82, 0.13, 0, 0);

		m_PerroShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_PerroShader)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_PerroShader->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	////////////////////////////// Grupo Arbol Sakura1
	{

		ASakura01 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Sakura/AGrupo3.obj", L"Modelos/Sakura/BASE2.bmp", L"Modelos/Sakura/BASE2N.bmp", 83, 84, 4, 0, 0);

		m_SakuraShader01 = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_SakuraShader01)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_SakuraShader01->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////////// Grupo Arbol Sakura1 GRUPO_2
	//{

	//	ASakura02 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Sakura/AGrupo3.obj", L"Modelos/Sakura/BASE2.bmp", L"Modelos/Sakura/BASE2N.bmp", 85, 86, 4, 0, 0);

	//	m_SakuraShader02 = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_SakuraShader02)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_SakuraShader02->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}

	////////////////////////////// Grupo Arbol Sakura1 GRUPO_3
	{

		ASakura03 = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/Sakura/AGrupo3.obj", L"Modelos/Sakura/BASE2.bmp", L"Modelos/Sakura/BASE2N.bmp", 87, 88, 4, 0, 0);

		m_SakuraShader03 = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
		if (!m_SakuraShader03)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_SakuraShader03->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////////// abusto#1
	//{

	//	Arbusto = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/arbusto/Arbusto.obj", L"Modelos/arbusto/Texttura.bmp", L"Modelos/arbusto/Text2N.bmp", 89, 90, 2, 0, 0);

	//	m_ArbustoShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_ArbustoShader)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_ArbustoShader->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}
	//////////////////////////////// abusto #2
	//{

	//	Arbusto = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/arbusto/Arbusto.obj", L"Modelos/arbusto/Texttura.bmp", L"Modelos/arbusto/Text2N.bmp", 91, 92, 2, 0, 0);

	//	m_ArbustoShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_ArbustoShader)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_ArbustoShader->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}
	//////////////////////////////// abusto #3
	//{

	//	Arbusto = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/arbusto/Arbusto.obj", L"Modelos/arbusto/Texttura.bmp", L"Modelos/arbusto/Text2N.bmp", 93, 94, 2, 0, 0);

	//	m_ArbustoShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_ArbustoShader)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_ArbustoShader->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}
	//////////////////////////////// abusto #4
	//{

	//	Arbusto = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/arbusto/Arbusto.obj", L"Modelos/arbusto/Texttura.bmp", L"Modelos/arbusto/Text2N.bmp", 95, 96, 2, 0, 0);

	//	m_ArbustoShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_ArbustoShader)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_ArbustoShader->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}
	//////////////////////////////// abusto #5
	//{

	//	Arbusto = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/arbusto/Arbusto.obj", L"Modelos/arbusto/Texttura.bmp", L"Modelos/arbusto/Text2N.bmp", 97, 98, 2, 0, 0);

	//	m_ArbustoShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_ArbustoShader)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_ArbustoShader->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}
	//////////////////////////////// abusto #6
	//{

	//	Arbusto = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/arbusto/Arbusto.obj", L"Modelos/arbusto/Texttura.bmp", L"Modelos/arbusto/Text2N.bmp", 99, 100, 2, 0, 0);

	//	m_ArbustoShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_ArbustoShader)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_ArbustoShader->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}
	//////////////////////////////// abusto #7
	//{

	//	Arbusto = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/arbusto/Arbusto.obj", L"Modelos/arbusto/Texttura.bmp", L"Modelos/arbusto/Text2N.bmp", 101, 102, 2, 0, 0);

	//	m_ArbustoShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_ArbustoShader)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_ArbustoShader->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}
	//////////////////////////////// abusto #8
	//{

	//	Arbusto = new Modelos(hwnd, m_OpenGL, (char*)"Modelos/arbusto/Arbusto.obj", L"Modelos/arbusto/Texttura.bmp", L"Modelos/arbusto/Text2N.bmp", 103, 104, 2, 0, 0);

	//	m_ArbustoShader = new LightShaderClass((char*)"Modelo.vs", (char*)"Modelo.ps");
	//	if (!m_ArbustoShader)
	//	{
	//		return false;
	//	}

	//	// Initialize the light shader object.
	//	result = m_ArbustoShader->Initialize(m_OpenGL, hwnd);
	//	if (!result)
	//	{
	//		MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
	//		return false;
	//	}
	//}

	//////////////////////////// BILLBOARD ARBOL 01
	{
		billArbol01 = new Billboard(hwnd, m_OpenGL, L"Billboards/arbol05_reverse01.png", 40.0f, 74, 91, 117);
		// Create the light shader object.
		m_BillShaderArbol01 = new LightShaderClass((char*)"Billboard.vs", (char*)"Billboard.ps");
		//m_BillShader = new LightShaderClass((char*)"shaders01.vs", (char*)"shaders01.ps");
		if (!m_BillShaderArbol01)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillShaderArbol01->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// BILLBOARD ARBOL 02
	{
		billArbol02 = new Billboard(hwnd, m_OpenGL, L"Billboards/arbol05_reverse01.png", 40.0f, 75, -142, 169);
		// Create the light shader object.
		m_BillShaderArbol02 = new LightShaderClass((char*)"Billboard.vs", (char*)"Billboard.ps");
		if (!m_BillShaderArbol02)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillShaderArbol02->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// BILLBOARD ARBOL 03
	{
		billArbol03 = new Billboard(hwnd, m_OpenGL, L"Billboards/arbol05_reverse01.png", 40.0f, 76, -182, 49);
		// Create the light shader object.
		m_BillShaderArbol03 = new LightShaderClass((char*)"Billboard.vs", (char*)"Billboard.ps");
		if (!m_BillShaderArbol03)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillShaderArbol03->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// BILLBOARD ARBOL 04
	{
		billArbol04 = new Billboard(hwnd, m_OpenGL, L"Billboards/arbol05_reverse01.png", 40.0f, 77, -192, 107);
		// Create the light shader object.
		m_BillShaderArbol04 = new LightShaderClass((char*)"Billboard.vs", (char*)"Billboard.ps");
		if (!m_BillShaderArbol04)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillShaderArbol04->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// BILLBOARD ARBOL 05
	{
		billArbol05 = new Billboard(hwnd, m_OpenGL, L"Billboards/arbol05_reverse01.png", 40.0f, 78, -49, -183);
		// Create the light shader object.
		m_BillShaderArbol05 = new LightShaderClass((char*)"Billboard.vs", (char*)"Billboard.ps");
		if (!m_BillShaderArbol05)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillShaderArbol05->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// BILLBOARD ARBOL 06
	{
		billArbol06 = new Billboard(hwnd, m_OpenGL, L"Billboards/arbol05_reverse01.png", 40.0f, 79, 123, -188);
		// Create the light shader object.
		m_BillShaderArbol06 = new LightShaderClass((char*)"Billboard.vs", (char*)"Billboard.ps");
		if (!m_BillShaderArbol06)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillShaderArbol06->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	//////////////////////////// BILLBOARD ARBOL 07
	{
		billArbol07 = new Billboard(hwnd, m_OpenGL, L"Billboards/arbol05_reverse01.png", 40.0f, 80, 182, 23);
		// Create the light shader object.
		m_BillShaderArbol07 = new LightShaderClass((char*)"Billboard.vs", (char*)"Billboard.ps");
		if (!m_BillShaderArbol07)
		{
			return false;
		}

		// Initialize the light shader object.
		result = m_BillShaderArbol07->Initialize(m_OpenGL, hwnd);
		if (!result)
		{
			MessageBox(hwnd, (LPCSTR)"Could not initialize the light shader object.", (LPCSTR)"Error", MB_OK);
			return false;
		}
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown(m_OpenGL);
		delete m_LightShader;
		m_LightShader = 0;
	}

	if (m_LightShader02)
	{
		m_LightShader02->Shutdown(m_OpenGL);
		delete m_LightShader02;
		m_LightShader02 = 0;
	}

	// Release the light shader object.
	if (m_LightShaderSky)
	{
		m_LightShaderSky->Shutdown(m_OpenGL);
		delete m_LightShaderSky;
		m_LightShaderSky = 0;
	}

	///////////////////////////////////////////////// NUBES
	// Release the light shader object.
	if (m_nube01Shader)
	{
		m_nube01Shader->Shutdown(m_OpenGL);
		delete m_nube01Shader;
		m_nube01Shader = 0;
	}
	if (m_nube02Shader)
	{
		m_nube02Shader->Shutdown(m_OpenGL);
		delete m_nube02Shader;
		m_nube02Shader = 0;
	}
	if (m_nube03Shader)
	{
		m_nube03Shader->Shutdown(m_OpenGL);
		delete m_nube03Shader;
		m_nube03Shader = 0;
	}
	if (m_nube04Shader)
	{
		m_nube04Shader->Shutdown(m_OpenGL);
		delete m_nube04Shader;
		m_nube04Shader = 0;
	}
	if (m_nube05Shader)
	{
		m_nube05Shader->Shutdown(m_OpenGL);
		delete m_nube05Shader;
		m_nube05Shader = 0;
	}
	if (m_nube06Shader)
	{
		m_nube06Shader->Shutdown(m_OpenGL);
		delete m_nube06Shader;
		m_nube06Shader = 0;
	}
	if (m_nube07Shader)
	{
		m_nube07Shader->Shutdown(m_OpenGL);
		delete m_nube07Shader;
		m_nube07Shader = 0;
	}
	if (m_nube08Shader)
	{
		m_nube08Shader->Shutdown(m_OpenGL);
		delete m_nube08Shader;
		m_nube08Shader = 0;
	}
	if (m_nube09Shader)
	{
		m_nube09Shader->Shutdown(m_OpenGL);
		delete m_nube09Shader;
		m_nube09Shader = 0;
	}
	if (m_nube10Shader)
	{
		m_nube10Shader->Shutdown(m_OpenGL);
		delete m_nube10Shader;
		m_nube10Shader = 0;
	}
	
	if (m_casaJaponesa01Shader)
	{
		m_casaJaponesa01Shader->Shutdown(m_OpenGL);
		delete m_casaJaponesa01Shader;
		m_casaJaponesa01Shader = 0;
	}
	if (m_casaJaponesa02Shader)
	{
		m_casaJaponesa02Shader->Shutdown(m_OpenGL);
		delete m_casaJaponesa02Shader;
		m_casaJaponesa02Shader = 0;
	}
	if (m_casaJaponesa03Shader)
	{
		m_casaJaponesa03Shader->Shutdown(m_OpenGL);
		delete m_casaJaponesa03Shader;
		m_casaJaponesa03Shader = 0;
	}
	if (m_casaJaponesa04Shader)
	{
		m_casaJaponesa04Shader->Shutdown(m_OpenGL);
		delete m_casaJaponesa04Shader;
		m_casaJaponesa04Shader = 0;
	}

	if (m_banca01Shader)
	{
		m_banca01Shader->Shutdown(m_OpenGL);
		delete m_banca01Shader;
		m_banca01Shader = 0;
	}
	if (m_banca02Shader)
	{
		m_banca02Shader->Shutdown(m_OpenGL);
		delete m_banca02Shader;
		m_banca02Shader = 0;
	}
	if (m_banca03Shader)
	{
		m_banca03Shader->Shutdown(m_OpenGL);
		delete m_banca03Shader;
		m_banca03Shader = 0;
	}
	if (m_banca04Shader)
	{
		m_banca04Shader->Shutdown(m_OpenGL);
		delete m_banca04Shader;
		m_banca04Shader = 0;
	}
	if (m_banca05Shader)
	{
		m_banca05Shader->Shutdown(m_OpenGL);
		delete m_banca05Shader;
		m_banca05Shader = 0;
	}
	if (m_banca06Shader)
	{
		m_banca06Shader->Shutdown(m_OpenGL);
		delete m_banca06Shader;
		m_banca06Shader = 0;
	}

	if (m_puenteShader01)
	{
		m_puenteShader01->Shutdown(m_OpenGL);
		delete m_puenteShader01;
		m_puenteShader01 = 0;
	}
	if (m_puenteShader02)
	{
		m_puenteShader02->Shutdown(m_OpenGL);
		delete m_puenteShader02;
		m_puenteShader02 = 0;
	}
	if (m_puenteShader03)
	{
		m_puenteShader03->Shutdown(m_OpenGL);
		delete m_puenteShader03;
		m_puenteShader03 = 0;
	}

	if (m_campañaShader)
	{
		m_campañaShader->Shutdown(m_OpenGL);
		delete m_campañaShader;
		m_campañaShader = 0;
	}
	
	if (m_faroShader)
	{
		m_faroShader->Shutdown(m_OpenGL);
		delete m_faroShader;
		m_faroShader = 0;
	}
	if (m_faro2Shader)
	{
		m_faro2Shader->Shutdown(m_OpenGL);
		delete m_faro2Shader;
		m_faro2Shader = 0;
	}

	if (m_bicicletaShader)
	{
		m_bicicletaShader->Shutdown(m_OpenGL);
		delete m_bicicletaShader;
		m_bicicletaShader = 0;
	}

	if (m_pez01Shader)
	{
		m_pez01Shader->Shutdown(m_OpenGL);
		delete m_pez01Shader;
		m_pez01Shader = 0;
	}

	if (m_PerroShader)
	{
		m_PerroShader->Shutdown(m_OpenGL);
		delete m_PerroShader;
		m_PerroShader = 0;
	}

	if (m_SakuraShader01)
	{
		m_SakuraShader01->Shutdown(m_OpenGL);
		delete m_SakuraShader01;
		m_SakuraShader01 = 0;
	}
	//if (m_SakuraShader02)
	//{
	//	m_SakuraShader02->Shutdown(m_OpenGL);
	//	delete m_SakuraShader02;
	//	m_SakuraShader02 = 0;
	//}
	if (m_SakuraShader03)
	{
		m_SakuraShader03->Shutdown(m_OpenGL);
		delete m_SakuraShader03;
		m_SakuraShader03 = 0;
	}

	//if (m_ArbustoShader)
	//{
	//	m_ArbustoShader->Shutdown(m_OpenGL);
	//	delete m_ArbustoShader;
	//	m_ArbustoShader = 0;
	//}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the terreno object.
	if (terreno)
	{
		delete terreno;
		m_Camera = 0;
	}
	if (terreno02)
	{
		delete terreno02;
		m_Camera = 0;
	}


	// Release the pointer to the OpenGL class object.
	m_OpenGL = 0;

	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += 0.0174532925f * 2.0f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	float worldMatrix[16];
	float viewMatrix[16];
	float projectionMatrix[16];
	float lightDirection[3];
	float diffuseLightColor[4];
	float ambientLight[4];
	float worldMatrixWater[16];
	float worldMatrixBill[16];

	///////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// CAMARA Y MUNDO
	{
		// Clear the buffers to begin the scene.
		m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

		// Generate the view matrix based on the camera's position.
		m_Camera->SetRotation(angx, angy, angz);
		m_Camera->SetYPos(terreno->Superficie(m_Camera->GetXPos(), m_Camera->GetZPos()) + 10);
		//posc.Y = terreno->Superficie(posc.X, posc.Z) * 4 + 15;
		m_Camera->Render(vel);
		posicionCameraX = m_Camera->GetXPos();
		posicionCameraY = m_Camera->GetYPos();
		posicionCameraZ = m_Camera->GetZPos();

		//posc.Y = terreno->Superficie(posc.X, posc.Z) * 4 + 15;
		//CamaraUpdate();

		// Get the world, view, and projection matrices from the opengl and camera objects.
		m_OpenGL->GetWorldMatrix(worldMatrix);
		m_OpenGL->GetWorldMatrix(worldMatrixBill);
		m_OpenGL->GetWorldMatrix(worldMatrixWater);
		m_Camera->GetViewMatrix(viewMatrix);
		m_OpenGL->GetProjectionMatrix(projectionMatrix);

		// Get the light properties.
		m_Light->GetDirection(lightDirection);
		m_Light->GetDiffuseColor(diffuseLightColor);
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// SKYDOME
	{
		glDisable(GL_DEPTH_TEST);
		m_LightShaderSky->SetShader(m_OpenGL);
		m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrix);
		m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_LightShaderSky->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_LightShaderSky->Pon1Entero(m_OpenGL, (char*)"cielo", 2);
		m_LightShaderSky->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_LightShaderSky->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		sky->Render(m_OpenGL);
		glEnable(GL_DEPTH_TEST);
		// Rotate the world matrix by the rotation value so that the triangle will spin.
		//m_OpenGL->MatrixRotationY(worldMatrix, rotation);
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// TERRENO01
	{
		m_LightShader->SetShader(m_OpenGL);
		m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrix);
		m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_LightShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_LightShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 0);
		m_LightShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture2", 1);
		m_LightShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_LightShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		terreno->Render(m_OpenGL);
	}

	////////////////////////////// TERRENO02
	{
		m_LightShader02->SetShader(m_OpenGL);
		m_LightShader02->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrix);
		m_LightShader02->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_LightShader02->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_LightShader02->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 1);
		m_LightShader02->Pon1Entero(m_OpenGL, (char*)"shaderTexture2", 3);
		m_LightShader02->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_LightShader02->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		terreno02->Render(m_OpenGL);
	}

	//////////////////////////// TERRENO03
	{
		m_LightShader03->SetShader(m_OpenGL);
		m_LightShader03->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrix);
		m_LightShader03->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_LightShader03->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_LightShader03->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 150);
		m_LightShader03->Pon1Entero(m_OpenGL, (char*)"shaderTexture2", 151);
		m_LightShader03->Pon1Entero(m_OpenGL, (char*)"shaderTexture3", 152);
		m_LightShader03->Pon1Entero(m_OpenGL, (char*)"shaderTexture4", 153);
		m_LightShader03->Pon1Entero(m_OpenGL, (char*)"Blending", 154);
		m_LightShader03->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_LightShader03->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		terreno03->Render(m_OpenGL);

	}	

	//////////////////////////// TERRENO04
	{
		// Set the light shader as the current shader program and set the matrices that it will use for rendering.
		m_LightShader04->SetShader(m_OpenGL);
		m_LightShader04->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrix);
		m_LightShader04->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_LightShader04->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_LightShader04->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 1);
		m_LightShader04->Pon1Entero(m_OpenGL, (char*)"shaderTexture2", 3);
		m_LightShader04->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_LightShader04->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		terreno04->Render(m_OpenGL);
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// AGUA01
	{
		
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_LightShaderWater01->SetShader(m_OpenGL);
		m_LightShaderWater01->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixWater);
		m_LightShaderWater01->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_LightShaderWater01->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_LightShaderWater01->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 4);
		m_LightShaderWater01->Pon1Entero(m_OpenGL, (char*)"shaderTexture2", 1);
		m_LightShaderWater01->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_LightShaderWater01->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		water01->Render(m_OpenGL);
		
	}

	//////////////////////////// AGUA02
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_LightShaderWater02->SetShader(m_OpenGL);
		m_LightShaderWater02->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixWater);
		m_LightShaderWater02->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_LightShaderWater02->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_LightShaderWater02->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 6);
		m_LightShaderWater02->Pon1Entero(m_OpenGL, (char*)"shaderTexture2", 1);
		m_LightShaderWater02->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_LightShaderWater02->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		water02->Render(m_OpenGL);
		glDisable(GL_BLEND);
	}

	///////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////// NUBE01
	{
		// NUBE 01
		m_nube01Shader->SetShader(m_OpenGL);
		float modmatrix[16];
		m_OpenGL->GetWorldMatrix(modmatrix);
		m_OpenGL->MatrixTranslation(modmatrix, nube01->x, 150, nube01->z);
		m_nube01Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix);
		m_nube01Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube01Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube01Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 20);
		m_nube01Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 21);
		m_nube01Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube01Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube01->Render(m_OpenGL);
	}
	//////////////////////////// NUBE02
	{
		m_nube02Shader->SetShader(m_OpenGL);
		float modmatrix02[16];
		m_OpenGL->GetWorldMatrix(modmatrix02);
		m_OpenGL->MatrixTranslation(modmatrix02, 86, 200, 126);
		m_nube02Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix02);
		m_nube02Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube02Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube02Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 22);
		m_nube02Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 23);
		m_nube02Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube02Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube02->Render(m_OpenGL);
	}
	//////////////////////////// NUBE03
	{
		m_nube03Shader->SetShader(m_OpenGL);
		float modmatrix03[16];
		float rotationmatriz03[16];
		float traslatematrix03[16];
		m_OpenGL->GetWorldMatrix(modmatrix03);
		m_OpenGL->MatrixRotationY(rotationmatriz03, 180.0f);
		m_OpenGL->MatrixTranslation(traslatematrix03, -11, 150, 183);
		m_OpenGL->MatrixMultiply(modmatrix03, rotationmatriz03, traslatematrix03);
		m_nube03Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix03);
		m_nube03Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube03Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube03Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 24);
		m_nube03Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 25);
		m_nube03Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube03Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube03->Render(m_OpenGL);
	}
	//////////////////////////// NUBE04
	{
		m_nube04Shader->SetShader(m_OpenGL);
		float modmatrix04[16];
		m_OpenGL->GetWorldMatrix(modmatrix04);
		m_OpenGL->MatrixTranslation(modmatrix04, -107, 250, 101);
		m_nube04Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix04);
		m_nube04Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube04Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube04Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 26);
		m_nube04Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 27);
		m_nube04Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube04Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube04->Render(m_OpenGL);
	}
	//////////////////////////// NUBE05
	{
		m_nube05Shader->SetShader(m_OpenGL);
		float modmatrix05[16];
		m_OpenGL->GetWorldMatrix(modmatrix05);
		m_OpenGL->MatrixTranslation(modmatrix05, -190, 150, -31);
		m_nube05Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix05);
		m_nube05Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube05Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube05Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 28);
		m_nube05Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 29);
		m_nube05Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube05Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube05->Render(m_OpenGL);
	}
	//////////////////////////// NUBE06
	{
		m_nube06Shader->SetShader(m_OpenGL);
		float modmatrix06[16];
		m_OpenGL->GetWorldMatrix(modmatrix06);
		m_OpenGL->MatrixTranslation(modmatrix06, -181, 200, -180);
		m_nube06Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix06);
		m_nube06Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube06Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube06Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 30);
		m_nube06Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 31);
		m_nube06Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube06Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube06->Render(m_OpenGL);
	}
	//////////////////////////// NUBE07
	{
		m_nube07Shader->SetShader(m_OpenGL);
		float modmatrix07[16];
		m_OpenGL->GetWorldMatrix(modmatrix07);
		m_OpenGL->MatrixTranslation(modmatrix07, -66, 250, -131);
		m_nube07Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix07);
		m_nube07Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube07Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube07Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 32);
		m_nube07Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 33);
		m_nube07Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube07Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube07->Render(m_OpenGL);
	}
	//////////////////////////// NUBE08
	{
		m_nube08Shader->SetShader(m_OpenGL);
		float modmatrix08[16];
		m_OpenGL->GetWorldMatrix(modmatrix08);
		m_OpenGL->MatrixTranslation(modmatrix08, 76, 150, -145);
		m_nube08Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix08);
		m_nube08Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube08Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube08Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 34);
		m_nube08Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 35);
		m_nube08Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube08Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube08->Render(m_OpenGL);
	}
	//////////////////////////// NUBE09
	{
		m_nube09Shader->SetShader(m_OpenGL);
		float modmatrix09[16];
		m_OpenGL->GetWorldMatrix(modmatrix09);
		m_OpenGL->MatrixTranslation(modmatrix09, 175, 200, -48);
		m_nube09Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix09);
		m_nube09Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube09Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube09Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 36);
		m_nube09Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 37);
		m_nube09Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube09Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube09->Render(m_OpenGL);
	}
	//////////////////////////// NUBE10
	{
		m_nube10Shader->SetShader(m_OpenGL);
		float modmatrix10[16];
		m_OpenGL->GetWorldMatrix(modmatrix10);
		m_OpenGL->MatrixTranslation(modmatrix10, 152, 300, 89);
		m_nube10Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix10);
		m_nube10Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_nube10Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_nube10Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 38);
		m_nube10Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 39);
		m_nube10Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_nube10Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		nube10->Render(m_OpenGL);
	}

	//////////////////////////// CASA JAPONESA01
	{
		m_casaJaponesa01Shader->SetShader(m_OpenGL);
		float modmatrix11[16];
		float rotationmatriz11[16];
		float traslatematrix11[16];
		m_OpenGL->GetWorldMatrix(modmatrix11);
		m_OpenGL->MatrixRotationY(rotationmatriz11, 0.0f);
		m_OpenGL->MatrixTranslation(traslatematrix11, -159, 8, -3);
		m_OpenGL->MatrixMultiply(modmatrix11, rotationmatriz11, traslatematrix11);
		m_casaJaponesa01Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix11);
		m_casaJaponesa01Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_casaJaponesa01Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_casaJaponesa01Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 40);
		m_casaJaponesa01Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 41);
		m_casaJaponesa01Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_casaJaponesa01Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		casaJaponesa01->Render(m_OpenGL);
	}
	//////////////////////////// CASA JAPONESA02
	{
		m_casaJaponesa02Shader->SetShader(m_OpenGL);
		float modmatrix18[16];
		float rotationmatriz18[16];
		float traslatematrix18[16];
		m_OpenGL->GetWorldMatrix(modmatrix18);
		m_OpenGL->MatrixRotationY(rotationmatriz18, 80.0f);
		m_OpenGL->MatrixTranslation(traslatematrix18, 41, 8, -163);
		m_OpenGL->MatrixMultiply(modmatrix18, rotationmatriz18, traslatematrix18);
		m_casaJaponesa02Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix18);
		m_casaJaponesa02Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_casaJaponesa02Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_casaJaponesa02Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 54);
		m_casaJaponesa02Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 55);
		m_casaJaponesa02Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_casaJaponesa02Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		casaJaponesa02->Render(m_OpenGL);
	}
	//////////////////////////// CASA JAPONESA03
	{
		m_casaJaponesa03Shader->SetShader(m_OpenGL);
		float modmatrix19[16];
		float rotationmatriz19[16];
		float traslatematrix19[16];
		m_OpenGL->GetWorldMatrix(modmatrix19);
		m_OpenGL->MatrixRotationY(rotationmatriz19, -300.0f);
		m_OpenGL->MatrixTranslation(traslatematrix19, -62, 8, 156);
		m_OpenGL->MatrixMultiply(modmatrix19, rotationmatriz19, traslatematrix19);
		m_casaJaponesa03Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix19);
		m_casaJaponesa03Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_casaJaponesa03Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_casaJaponesa03Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 56);
		m_casaJaponesa03Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 57);
		m_casaJaponesa03Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_casaJaponesa03Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		casaJaponesa03->Render(m_OpenGL);
	}
	//////////////////////////// CASA JAPONESA04
	{
		m_casaJaponesa04Shader->SetShader(m_OpenGL);
		float modmatrix20[16];
		float rotationmatriz20[16];
		float traslatematrix20[16];
		m_OpenGL->GetWorldMatrix(modmatrix20);
		m_OpenGL->MatrixRotationY(rotationmatriz20, 110.0f);
		m_OpenGL->MatrixTranslation(traslatematrix20, 159, 8, -28);
		m_OpenGL->MatrixMultiply(modmatrix20, rotationmatriz20, traslatematrix20);
		m_casaJaponesa04Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix20);
		m_casaJaponesa04Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_casaJaponesa04Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_casaJaponesa04Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 58);
		m_casaJaponesa04Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 59);
		m_casaJaponesa04Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_casaJaponesa04Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		casaJaponesa04->Render(m_OpenGL);
	}

	//////////////////////////// BANCA01
	{
		m_banca01Shader->SetShader(m_OpenGL);
		float modmatrix12[16];
		float rotationmatriz12[16];
		float traslatematrix12[16];
		m_OpenGL->GetWorldMatrix(modmatrix12);
		m_OpenGL->MatrixRotationY(rotationmatriz12, 0.0f);
		m_OpenGL->MatrixTranslation(traslatematrix12, -7, 9.5, -150);
		m_OpenGL->MatrixMultiply(modmatrix12, rotationmatriz12, traslatematrix12);
		m_banca01Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix12);
		m_banca01Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_banca01Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_banca01Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 42);
		m_banca01Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 43);
		m_banca01Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_banca01Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		banca01->Render(m_OpenGL);
	}
	//////////////////////////// BANCA02
	{
		m_banca02Shader->SetShader(m_OpenGL);
		float modmatrix13[16];
		float rotationmatriz13[16];
		float traslatematrix13[16];
		m_OpenGL->GetWorldMatrix(modmatrix13);
		m_OpenGL->MatrixRotationY(rotationmatriz13, 200.0f);
		m_OpenGL->MatrixTranslation(traslatematrix13, 138, 9.5, -100);
		m_OpenGL->MatrixMultiply(modmatrix13, rotationmatriz13, traslatematrix13);
		m_banca02Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix13);
		m_banca02Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_banca02Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_banca02Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 44);
		m_banca02Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 45);
		m_banca02Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_banca02Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		banca02->Render(m_OpenGL);
	}
	//////////////////////////// BANCA03
	{
		m_banca03Shader->SetShader(m_OpenGL);
		float modmatrix14[16];
		float rotationmatriz14[16];
		float traslatematrix14[16];
		m_OpenGL->GetWorldMatrix(modmatrix14);
		m_OpenGL->MatrixRotationY(rotationmatriz14, -200.0f);
		m_OpenGL->MatrixTranslation(traslatematrix14, -128, 9.5, -100);
		m_OpenGL->MatrixMultiply(modmatrix14, rotationmatriz14, traslatematrix14);
		m_banca03Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix14);
		m_banca03Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_banca03Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_banca03Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 46);
		m_banca03Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 47);
		m_banca03Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_banca03Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		banca03->Render(m_OpenGL);
	}
	//////////////////////////// BANCA04
	{
		m_banca04Shader->SetShader(m_OpenGL);
		float modmatrix15[16];
		float rotationmatriz15[16];
		float traslatematrix15[16];
		m_OpenGL->GetWorldMatrix(modmatrix15);
		m_OpenGL->MatrixRotationY(rotationmatriz15, 185.0f);
		m_OpenGL->MatrixTranslation(traslatematrix15, -7, 9.5, 150);
		m_OpenGL->MatrixMultiply(modmatrix15, rotationmatriz15, traslatematrix15);
		m_banca04Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix15);
		m_banca04Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_banca04Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_banca04Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 48);
		m_banca04Shader->Pon1Entero(m_OpenGL, (char*)"modnorm",49);
		m_banca04Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_banca04Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		banca04->Render(m_OpenGL);
	}
	//////////////////////////// BANCA05
	{
		m_banca05Shader->SetShader(m_OpenGL);
		float modmatrix16[16];
		float rotationmatriz16[16];
		float traslatematrix16[16];
		m_OpenGL->GetWorldMatrix(modmatrix16);
		m_OpenGL->MatrixRotationY(rotationmatriz16, 180.0f);
		m_OpenGL->MatrixTranslation(traslatematrix16, 138, 9.5, 100);
		m_OpenGL->MatrixMultiply(modmatrix16, rotationmatriz16, traslatematrix16);
		m_banca05Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix16);
		m_banca05Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_banca05Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_banca05Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 50);
		m_banca05Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 51);
		m_banca05Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_banca05Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		banca05->Render(m_OpenGL);
	}
	//////////////////////////// BANCA06
	{
		m_banca06Shader->SetShader(m_OpenGL);
		float modmatrix17[16];
		float rotationmatriz17[16];
		float traslatematrix17[16];
		m_OpenGL->GetWorldMatrix(modmatrix17);
		m_OpenGL->MatrixRotationY(rotationmatriz17, -180.0f);
		m_OpenGL->MatrixTranslation(traslatematrix17, -128, 9.5, 100);
		m_OpenGL->MatrixMultiply(modmatrix17, rotationmatriz17, traslatematrix17);
		m_banca06Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix17);
		m_banca06Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_banca06Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_banca06Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 52);
		m_banca06Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 53);
		m_banca06Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_banca06Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		banca06->Render(m_OpenGL);
	}

	//////////////////////////// PUENTE01
	{
		m_puenteShader01->SetShader(m_OpenGL);
		float modmatrix21[16];
		float rotationmatriz21[16];
		float traslatematrix21[16];
		m_OpenGL->GetWorldMatrix(modmatrix21);
		m_OpenGL->MatrixRotationY(rotationmatriz21, 0);
		m_OpenGL->MatrixTranslation(traslatematrix21, 0, 10, -8);
		m_OpenGL->MatrixMultiply(modmatrix21, rotationmatriz21, traslatematrix21);
		m_puenteShader01->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix21);
		m_puenteShader01->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_puenteShader01->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_puenteShader01->Pon1Entero(m_OpenGL, (char*)"modtext", 60);
		m_puenteShader01->Pon1Entero(m_OpenGL, (char*)"modnorm", 61);
		m_puenteShader01->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_puenteShader01->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		puente01->Render(m_OpenGL);
	}
	//////////////////////////// PUENTE02
	{
		m_puenteShader02->SetShader(m_OpenGL);
		float modmatrix22[16];
		float rotationmatriz22[16];
		float traslatematrix22[16];
		m_OpenGL->GetWorldMatrix(modmatrix22);
		m_OpenGL->MatrixRotationY(rotationmatriz22, 0);
		m_OpenGL->MatrixTranslation(traslatematrix22, -39.6, 10, -8);
		m_OpenGL->MatrixMultiply(modmatrix22, rotationmatriz22, traslatematrix22);
		m_puenteShader02->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix22);
		m_puenteShader02->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_puenteShader02->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_puenteShader02->Pon1Entero(m_OpenGL, (char*)"modtext", 62);
		m_puenteShader02->Pon1Entero(m_OpenGL, (char*)"modnorm", 63);
		m_puenteShader02->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_puenteShader02->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		puente02->Render(m_OpenGL);
	}
	//////////////////////////// PUENTE03
	{
		m_puenteShader03->SetShader(m_OpenGL);
		float modmatrix23[16];
		float rotationmatriz23[16];
		float traslatematrix23[16];
		m_OpenGL->GetWorldMatrix(modmatrix23);
		m_OpenGL->MatrixRotationY(rotationmatriz23, 0);
		m_OpenGL->MatrixTranslation(traslatematrix23, 39.6, 10, -8);
		m_OpenGL->MatrixMultiply(modmatrix23, rotationmatriz23, traslatematrix23);
		m_puenteShader03->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix23);
		m_puenteShader03->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_puenteShader03->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_puenteShader03->Pon1Entero(m_OpenGL, (char*)"modtext", 64);
		m_puenteShader03->Pon1Entero(m_OpenGL, (char*)"modnorm", 65);
		m_puenteShader03->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_puenteShader03->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		puente03->Render(m_OpenGL);
	}

	//////////////////////////// CAMPAÑA
	{
		m_campañaShader->SetShader(m_OpenGL);
		float modmatrix24[16];
		float rotationmatriz24[16];
		float traslatematrix24[16];
		m_OpenGL->GetWorldMatrix(modmatrix24);
		m_OpenGL->MatrixRotationY(rotationmatriz24, 0);
		m_OpenGL->MatrixTranslation(traslatematrix24, -113, 10, -151);
		m_OpenGL->MatrixMultiply(modmatrix24, rotationmatriz24, traslatematrix24);
		m_campañaShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix24);
		m_campañaShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_campañaShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_campañaShader->Pon1Entero(m_OpenGL, (char*)"modtext", 66);
		m_campañaShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 67);
		m_campañaShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_campañaShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		campaña->Render(m_OpenGL);
	}


	////////////////////////////// FARO
	{
		m_faroShader->SetShader(m_OpenGL);
		float modmatrix25[16];
		float rotationmatriz25[16];
		float traslatematrix25[16];
		m_OpenGL->GetWorldMatrix(modmatrix25);
		m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
		m_OpenGL->MatrixTranslation(traslatematrix25, -167, 8, 73);
		m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
		m_faroShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
		m_faroShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_faroShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		/*m_faroShader->Pon1Entero(m_OpenGL, (char*)"modtext", 68);
		m_faroShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 69);*/
		m_faroShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 68);
		m_faroShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture01", 69);
		m_faroShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_faroShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		m_faroShader->PonVec4(m_OpenGL, (char*)"ambientLight", ambientLight);
		// Render the model using the light shader.
		faro->Render(m_OpenGL);
	}

	////////////////////////////// FARO2
	{
		m_faro2Shader->SetShader(m_OpenGL);
		float modmatrix28[16];
		float rotationmatriz28[16];
		float traslatematrix28[16];
		m_OpenGL->GetWorldMatrix(modmatrix28);
		m_OpenGL->MatrixRotationY(rotationmatriz28, 180);
		m_OpenGL->MatrixTranslation(traslatematrix28, 167, 8, -73);
		m_OpenGL->MatrixMultiply(modmatrix28, rotationmatriz28, traslatematrix28);
		m_faro2Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix28);
		m_faro2Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_faro2Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		//m_faro2Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 68);
		//m_faro2Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 69);
		m_faroShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 68);
		m_faroShader->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 69);
		m_faro2Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_faro2Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		m_faro2Shader->PonVec4(m_OpenGL, (char*)"ambientLight", ambientLight);
		// Render the model using the light shader.
		faro2->Render(m_OpenGL);
	}

	////////////////////////////// BICICLETA
	{
		m_bicicletaShader->SetShader(m_OpenGL);
		float modmatrix26[16];
		float rotationmatriz26[16];
		float traslatematrix26[16];
		m_OpenGL->GetWorldMatrix(modmatrix26);
		// Relación constante para convertir la medida de un ángulo de grados a radianes. 
		m_OpenGL->MatrixRotationY(rotationmatriz26, angy * DEG_TO_RAD);
		if (tercerapersona == false) {
			m_OpenGL->MatrixTranslation(traslatematrix26, m_Camera->GetXPos()+ .25,terreno->Superficie(m_Camera->GetXPos(), m_Camera->GetZPos())+2, m_Camera->GetZPos());
		}
		else {

			m_OpenGL->MatrixTranslation(traslatematrix26, m_Camera->GetXPos() + bicicletaTercerX, terreno->Superficie(m_Camera->GetXPos(), m_Camera->GetZPos()) + 2, m_Camera->GetZPos() + bicicletaTercerZ);

		
		
		}
		//m_OpenGL->MatrixTranslation(traslatematrix26, 92, 10, 0);
		m_OpenGL->MatrixMultiply(modmatrix26, rotationmatriz26, traslatematrix26);
		m_bicicletaShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix26);
		m_bicicletaShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_bicicletaShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_bicicletaShader->Pon1Entero(m_OpenGL, (char*)"modtext", 70);
		m_bicicletaShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 71);
		m_bicicletaShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_bicicletaShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		bicicleta->Render(m_OpenGL);
	}

	////////////////////////////// PEZ01
	{
		m_pez01Shader->SetShader(m_OpenGL);
		float modmatrix27[16];
		float rotationmatriz27[16];
		float traslatematrix27[16];
		m_OpenGL->GetWorldMatrix(modmatrix27);
		m_OpenGL->MatrixRotationY(rotationmatriz27, 0);
		m_OpenGL->MatrixTranslation(traslatematrix27, 7, 4.5, -41);
		m_OpenGL->MatrixMultiply(modmatrix27, rotationmatriz27, traslatematrix27);
		m_pez01Shader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix27);
		m_pez01Shader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_pez01Shader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_pez01Shader->Pon1Entero(m_OpenGL, (char*)"modtext", 72);
		m_pez01Shader->Pon1Entero(m_OpenGL, (char*)"modnorm", 73);
		m_pez01Shader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_pez01Shader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		pez01->Render(m_OpenGL);
	}
	
	//////////////////////////////// PERRITO
	{
		m_PerroShader->SetShader(m_OpenGL);
		float modmatrix29[16];
		float rotationmatriz29[16];
		float traslatematrix29[16];
		m_OpenGL->GetWorldMatrix(modmatrix29);
		m_OpenGL->MatrixRotationY(rotationmatriz29, 15);
		m_OpenGL->MatrixTranslation(traslatematrix29, 65, 9, 75);
		m_OpenGL->MatrixMultiply(modmatrix29, rotationmatriz29, traslatematrix29);
		m_PerroShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix29);
		m_PerroShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_PerroShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_PerroShader->Pon1Entero(m_OpenGL, (char*)"modtext", 81);
		m_PerroShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 82);
		m_PerroShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_PerroShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		perro->Render(m_OpenGL);
	}



	//////////////////////////////// SAKURA_Arbol
	{
		m_SakuraShader01->SetShader(m_OpenGL);
		float modmatrix30[16];
		float rotationmatriz30[16];
		float traslatematrix30[16];
		m_OpenGL->GetWorldMatrix(modmatrix30);
		m_OpenGL->MatrixRotationY(rotationmatriz30, 95);
		m_OpenGL->MatrixTranslation(traslatematrix30, -65, 3, -65);
		m_OpenGL->MatrixMultiply(modmatrix30, rotationmatriz30, traslatematrix30);
		m_SakuraShader01->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix30);
		m_SakuraShader01->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_SakuraShader01->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_SakuraShader01->Pon1Entero(m_OpenGL, (char*)"modtext", 83);
		m_SakuraShader01->Pon1Entero(m_OpenGL, (char*)"modnorm", 84);
		m_SakuraShader01->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_SakuraShader01->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		ASakura01->Render(m_OpenGL);
	}
	////--------------------- SAKURA_Arbol GRUPO_2
	//{
	//	m_SakuraShader02->SetShader(m_OpenGL);
	//	float modmatrix31[16];
	//	float rotationmatriz31[16];
	//	float traslatematrix31[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix31);
	//	m_OpenGL->MatrixRotationY(rotationmatriz31, -95);
	//	m_OpenGL->MatrixTranslation(traslatematrix31, 70, 3, 70);
	//	m_OpenGL->MatrixMultiply(modmatrix31, rotationmatriz31, traslatematrix31);
	//	m_SakuraShader02->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix31);
	//	m_SakuraShader02->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_SakuraShader02->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_SakuraShader02->Pon1Entero(m_OpenGL, (char*)"modtext", 85);
	//	m_SakuraShader02->Pon1Entero(m_OpenGL, (char*)"modnorm", 86);
	//	m_SakuraShader02->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_SakuraShader02->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	ASakura02->Render(m_OpenGL);
	//}
	//--------------------- SAKURA_Arbol GRUPO_3
	{
		m_SakuraShader03->SetShader(m_OpenGL);
		float modmatrix32[16];
		float rotationmatriz32[16];
		float traslatematrix32[16];
		m_OpenGL->GetWorldMatrix(modmatrix32);
		m_OpenGL->MatrixRotationY(rotationmatriz32, 180);
		m_OpenGL->MatrixTranslation(traslatematrix32, 40, 3, 40);
		m_OpenGL->MatrixMultiply(modmatrix32, rotationmatriz32, traslatematrix32);
		m_SakuraShader03->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix32);
		m_SakuraShader03->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_SakuraShader03->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_SakuraShader03->Pon1Entero(m_OpenGL, (char*)"modtext", 87);
		m_SakuraShader03->Pon1Entero(m_OpenGL, (char*)"modnorm", 88);
		m_SakuraShader03->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_SakuraShader03->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		ASakura03->Render(m_OpenGL);
	}




	////////////////////////////////						ARBUSTOS		///////////////////////////////////////////////////
	////--------------------- ARBUSTO #1
	//{
	//	m_ArbustoShader->SetShader(m_OpenGL);
	//	float modmatrix25[16];
	//	float rotationmatriz25[16];
	//	float traslatematrix25[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix25);
	//	m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
	//	m_OpenGL->MatrixTranslation(traslatematrix25, -95, 9, -107);
	//	m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modtext", 89);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 90);
	//	m_ArbustoShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_ArbustoShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	Arbusto->Render(m_OpenGL);
	//}
	////--------------------- ARBUSTO #2
	//{
	//	m_ArbustoShader->SetShader(m_OpenGL);
	//	float modmatrix25[16];
	//	float rotationmatriz25[16];
	//	float traslatematrix25[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix25);
	//	m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
	//	m_OpenGL->MatrixTranslation(traslatematrix25, -50, 9, -132);
	//	m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modtext", 91);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 92);
	//	m_ArbustoShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_ArbustoShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	Arbusto->Render(m_OpenGL);
	//}
	////--------------------- ARBUSTO #3
	//{
	//	m_ArbustoShader->SetShader(m_OpenGL);
	//	float modmatrix25[16];
	//	float rotationmatriz25[16];
	//	float traslatematrix25[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix25);
	//	m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
	//	m_OpenGL->MatrixTranslation(traslatematrix25, 58, 9, 142);
	//	m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modtext", 93);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 94);
	//	m_ArbustoShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_ArbustoShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	Arbusto->Render(m_OpenGL);
	//}
	////--------------------- ARBUSTO #4
	//{
	//	m_ArbustoShader->SetShader(m_OpenGL);
	//	float modmatrix25[16];
	//	float rotationmatriz25[16];
	//	float traslatematrix25[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix25);
	//	m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
	//	m_OpenGL->MatrixTranslation(traslatematrix25, -12, 9, 120);
	//	m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modtext", 95);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 96);
	//	m_ArbustoShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_ArbustoShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	Arbusto->Render(m_OpenGL);
	//}
	////--------------------- ARBUSTO #5
	//{
	//	m_ArbustoShader->SetShader(m_OpenGL);
	//	float modmatrix25[16];
	//	float rotationmatriz25[16];
	//	float traslatematrix25[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix25);
	//	m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
	//	m_OpenGL->MatrixTranslation(traslatematrix25, 82, 9, -116);
	//	m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modtext", 97);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 98);
	//	m_ArbustoShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_ArbustoShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	Arbusto->Render(m_OpenGL);
	//}
	////--------------------- ARBUSTO #6
	//{
	//	m_ArbustoShader->SetShader(m_OpenGL);
	//	float modmatrix25[16];
	//	float rotationmatriz25[16];
	//	float traslatematrix25[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix25);
	//	m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
	//	m_OpenGL->MatrixTranslation(traslatematrix25, -89, 9, -119);
	//	m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modtext", 99);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 100);
	//	m_ArbustoShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_ArbustoShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	Arbusto->Render(m_OpenGL);
	//}
	////--------------------- ARBUSTO #7
	//{
	//	m_ArbustoShader->SetShader(m_OpenGL);
	//	float modmatrix25[16];
	//	float rotationmatriz25[16];
	//	float traslatematrix25[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix25);
	//	m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
	//	m_OpenGL->MatrixTranslation(traslatematrix25, 135, 9, 8);
	//	m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modtext", 101);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 102);
	//	m_ArbustoShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_ArbustoShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	Arbusto->Render(m_OpenGL);
	//}
	////--------------------- ARBUSTO #8
	//{
	//	m_ArbustoShader->SetShader(m_OpenGL);
	//	float modmatrix25[16];
	//	float rotationmatriz25[16];
	//	float traslatematrix25[16];
	//	m_OpenGL->GetWorldMatrix(modmatrix25);
	//	m_OpenGL->MatrixRotationY(rotationmatriz25, 0);
	//	m_OpenGL->MatrixTranslation(traslatematrix25, 103, 9, 89);
	//	m_OpenGL->MatrixMultiply(modmatrix25, rotationmatriz25, traslatematrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", modmatrix25);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
	//	m_ArbustoShader->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modtext", 103);
	//	m_ArbustoShader->Pon1Entero(m_OpenGL, (char*)"modnorm", 104);
	//	m_ArbustoShader->PonVec3(m_OpenGL, (char*)"lightDirection", lightDirection);
	//	m_ArbustoShader->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
	//	// Render the model using the light shader.
	//	Arbusto->Render(m_OpenGL);
	//}

	///////////////////////////////////////////////////////////////////	

	//////////////////////////// BILLBOARD ARBOL 01
	{

		// Set the light shader as the current shader program and set the matrices that it will use for rendering.

		
		float rotationmatrizbill01[16];
		float traslatematrixbill01[16];
		m_OpenGL->MatrixRotationY(rotationmatrizbill01, -billArbol01->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixTranslation(worldMatrixBill, 91, 10,117);
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotationmatrizbill01, worldMatrixBill);
		m_BillShaderArbol01->SetShader(m_OpenGL);
		m_BillShaderArbol01->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillShaderArbol01->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillShaderArbol01->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillShaderArbol01->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 74);
		m_BillShaderArbol01->PonVec4(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillShaderArbol01->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billArbol01->Render(m_OpenGL);


	}

	//////////////////////////// BILLBOARD ARBOL 02
	{

		// Set the light shader as the current shader program and set the matrices that it will use for rendering.


		float rotationmatrizbill02[16];
		float traslatematrixbill02[16];
		m_OpenGL->MatrixRotationY(rotationmatrizbill02, billArbol02->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixTranslation(worldMatrixBill, -142, 10, 169);
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotationmatrizbill02, worldMatrixBill);
		m_BillShaderArbol02->SetShader(m_OpenGL);
		m_BillShaderArbol02->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillShaderArbol02->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillShaderArbol02->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillShaderArbol02->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 75);
		m_BillShaderArbol02->PonVec4(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillShaderArbol02->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billArbol02->Render(m_OpenGL);


	}

	//////////////////////////// BILLBOARD ARBOL 03
	{

		// Set the light shader as the current shader program and set the matrices that it will use for rendering.


		float rotationmatrizbill03[16];
		float traslatematrixbill03[16];
		m_OpenGL->MatrixRotationY(rotationmatrizbill03, billArbol03->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixTranslation(worldMatrixBill, -182, 10, 49);
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotationmatrizbill03, worldMatrixBill);
		m_BillShaderArbol03->SetShader(m_OpenGL);
		m_BillShaderArbol03->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillShaderArbol03->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillShaderArbol03->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillShaderArbol03->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 76);
		m_BillShaderArbol03->PonVec4(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillShaderArbol03->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billArbol03->Render(m_OpenGL);


	}

	//////////////////////////// BILLBOARD ARBOL 04
	{

		// Set the light shader as the current shader program and set the matrices that it will use for rendering.


		float rotationmatrizbill04[16];
		float traslatematrixbill04[16];
		m_OpenGL->MatrixRotationY(rotationmatrizbill04, billArbol04->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixTranslation(worldMatrixBill, -192, 10, -107);
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotationmatrizbill04, worldMatrixBill);
		m_BillShaderArbol04->SetShader(m_OpenGL);
		m_BillShaderArbol04->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillShaderArbol04->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillShaderArbol04->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillShaderArbol04->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 74);
		m_BillShaderArbol04->PonVec4(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillShaderArbol04->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billArbol04->Render(m_OpenGL);


	}

	//////////////////////////// BILLBOARD ARBOL 05
	{

		// Set the light shader as the current shader program and set the matrices that it will use for rendering.


		float rotationmatrizbill05[16];
		float traslatematrixbill05[16];
		m_OpenGL->MatrixRotationY(rotationmatrizbill05, -billArbol05->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixTranslation(worldMatrixBill, -49, 10, -183);
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotationmatrizbill05, worldMatrixBill);
		m_BillShaderArbol05->SetShader(m_OpenGL);
		m_BillShaderArbol05->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillShaderArbol05->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillShaderArbol05->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillShaderArbol05->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 78);
		m_BillShaderArbol05->PonVec4(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillShaderArbol05->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billArbol05->Render(m_OpenGL);


	}

	//////////////////////////// BILLBOARD ARBOL 06
	{

		// Set the light shader as the current shader program and set the matrices that it will use for rendering.


		float rotationmatrizbill06[16];
		float traslatematrixbill06[16];
		m_OpenGL->MatrixRotationY(rotationmatrizbill06, -billArbol06->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixTranslation(worldMatrixBill, 123, 10, -188);
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotationmatrizbill06, worldMatrixBill);
		m_BillShaderArbol06->SetShader(m_OpenGL);
		m_BillShaderArbol06->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillShaderArbol06->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillShaderArbol06->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillShaderArbol06->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 79);
		m_BillShaderArbol06->PonVec4(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillShaderArbol06->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billArbol06->Render(m_OpenGL);


	}

	//////////////////////////// BILLBOARD ARBOL 07
	{

		// Set the light shader as the current shader program and set the matrices that it will use for rendering.


		float rotationmatrizbill07[16];
		float traslatematrixbill07[16];
		m_OpenGL->MatrixRotationY(rotationmatrizbill07, -billArbol07->angBill(m_Camera->GetXPos(), m_Camera->GetZPos()));
		m_OpenGL->MatrixTranslation(worldMatrixBill, 182, 10, 23);
		m_OpenGL->MatrixMultiply(worldMatrixBill, rotationmatrizbill07, worldMatrixBill);
		m_BillShaderArbol07->SetShader(m_OpenGL);
		m_BillShaderArbol07->PonMatriz4x4(m_OpenGL, (char*)"worldMatrix", worldMatrixBill);
		m_BillShaderArbol07->PonMatriz4x4(m_OpenGL, (char*)"viewMatrix", viewMatrix);
		m_BillShaderArbol07->PonMatriz4x4(m_OpenGL, (char*)"projectionMatrix", projectionMatrix);
		m_BillShaderArbol07->Pon1Entero(m_OpenGL, (char*)"shaderTexture", 80);
		m_BillShaderArbol07->PonVec4(m_OpenGL, (char*)"lightDirection", lightDirection);
		m_BillShaderArbol07->PonVec4(m_OpenGL, (char*)"diffuseLightColor", diffuseLightColor);
		// Render the model using the light shader.
		billArbol07->Render(m_OpenGL);


	}
	
	// Present the rendered scene to the screen.	
	m_OpenGL->EndScene();

	return true;
}