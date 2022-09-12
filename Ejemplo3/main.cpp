#include <windows.h>
#include <windowsx.h>
#include "openglclass.h"
#include "graphicsclass.h"
#include "GamepadRR.h"
#include <sstream>
#include "cameraclass.h"

#define radioBici .07
// radio de 6.30

#pragma comment (lib,"Gdiplus.lib")


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

LPCSTR m_applicationName;
HINSTANCE m_hinstance;
HWND m_hwnd;

OpenGLClass* m_OpenGL;
GraphicsClass* m_Graphics;
CameraClass* m_camera;
GamePadRR* control;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{	
	
	int screenWidth, screenHeight;
	bool result;
	m_OpenGL = 0;
	m_Graphics = 0;
	
	screenWidth = 0;
	screenHeight = 0;

	// Create the OpenGL object.
	m_OpenGL = new OpenGLClass;
	if (!m_OpenGL)
	{
		return false;
	}

	
	// Create the window the application will be using and also initialize OpenGL.
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = (LPCSTR)"Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = (LPCSTR)m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Create a temporary window for the OpenGL extension setup.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCSTR)m_applicationName, (LPCSTR)m_applicationName, WS_POPUP,
		0, 0, 640, 480, NULL, NULL, m_hinstance, NULL);
	if (m_hwnd == NULL)
	{
		return false;
	}

	// Don't show the window.
	ShowWindow(m_hwnd, SW_HIDE);

	// Initialize a temporary OpenGL window and load the OpenGL extensions.
	result = m_OpenGL->InitializeExtensions(m_hwnd);
	if (!result)
	{
		MessageBox(m_hwnd, (LPCSTR)"Could not initialize the OpenGL extensions.", (LPCSTR)"Error", MB_OK);
		return false;
	}

	// Release the temporary window now that the extensions have been initialized.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCSTR)m_applicationName, (LPCSTR)m_applicationName, WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);
	if (m_hwnd == NULL)
	{
		return false;
	}

	// Initialize OpenGL now that the window has been created.
	result = m_OpenGL->InitializeOpenGL(m_hwnd, screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);
	if (!result)
	{
		MessageBox(m_hwnd, (LPCSTR)"Could not initialize OpenGL, check if video card supports OpenGL 4.0.",
			(LPCSTR)"Error", MB_OK);
		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);	

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if (!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(m_OpenGL, m_hwnd);
	if (!result)
	{
		return false;
	}

	control = new GamePadRR(1);

	MSG msg;
	bool done;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	SetTimer(m_hwnd, 1000, 20, NULL);
	// Loop until there is a quit message from the window or the user.
	done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
			KillTimer(m_hwnd, 1000);
		}
		else
		{
			bool result;

			// Do the frame processing for the graphics object.
			result = m_Graphics->Frame();
			if (!result)
			{
				return false;
			}
		}

	}

	// Release the graphics object.
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}	

	// Release the OpenGL object.
	if (m_OpenGL)
	{
		m_OpenGL->Shutdown(m_hwnd);
		delete m_OpenGL;
		m_OpenGL = 0;
	}

	if (control)
	{		
		delete control;
		control = 0;
	}

	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass((LPCSTR)m_applicationName, m_hinstance);
	m_hinstance = NULL;	

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}	

	case WM_TIMER:
	{
		bool conectado = control->IsConnected();
		if (control->IsConnected())
		{
			////convierto a flotante el valor analogico de tipo entero
			//float grados = (float)control->GetState().Gamepad.sThumbLX / 32767.0;
			////debido a que los controles se aguadean con el uso entonces ya no dan el cero
			////en el centro, por eso lo comparo con una ventana de aguadencia de mi control
			//if (grados > 0.19 || grados < -0.19) {
			//	m_Graphics->angy += grados * 2.0;
			//}

			//float velocidad = (float)control->GetState().Gamepad.sThumbLY / 32767.0;
			//if (velocidad > 0.19 || velocidad < -0.19) {
			//	m_Graphics->vel = velocidad / 2.0;
			//}
			//else {
			//	m_Graphics->vel = 0;
			//}

			float grados = (float)control->GetState().Gamepad.sThumbRX / 32767.0;
			grados = grados / 2;
			if (grados > 0.19 || grados < -0.19) {
				m_Graphics->angx += grados * 1.0;
			}

			grados = (float)control->GetState().Gamepad.sThumbRY / 32767.0;
			if (grados > 0.19 || grados < -0.19) {
				m_Graphics->angx += grados * 1.0;
			}

			float otrasTeclas = (float)control->GetState().Gamepad.wButtons;

			////// INICIO
			if (otrasTeclas == 0x00000010) { /// START
				PostQuitMessage(0);
				break;
			}
			if (otrasTeclas == 0x1000) {  //// A
				m_Graphics->tercerapersona = false;
				break;
			}
			if (otrasTeclas == 0x2000) { //// B
				m_Graphics->tercerapersona = true;
				break;
			}

			if (otrasTeclas == 0x00000001) {  //// XINPUT_GAMEPAD_DPAD_UP
				m_Graphics->vel = 0.5;
				break;
			}
			else if (otrasTeclas == 0x00000002) { //// XINPUT_GAMEPAD_DPAD_DOWN
				m_Graphics->vel = -0.5;
				break;;
			}
			else if (otrasTeclas == 0x00000004) {  //// XINPUT_GAMEPAD_DPAD_LEFT 
				m_Graphics->angy -= 1;

				if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= -90) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
				}
				else if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= 180) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - (-radioBici);
				}
				else if (m_Graphics->bicicletacontador >= 180 && m_Graphics->bicicletacontador <= 270) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
				}
				else if (m_Graphics->bicicletacontador >= 270 && m_Graphics->bicicletacontador <= 359) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
				}
				else if (m_Graphics->bicicletacontador <= -90 && m_Graphics->bicicletacontador >= -180) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
				}
				else if (m_Graphics->bicicletacontador <= -180 && m_Graphics->bicicletacontador >= -270) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
				}
				else if (m_Graphics->bicicletacontador <= -270 && m_Graphics->bicicletacontador >= -359) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
				}
				else {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
				}


				if (m_Graphics->bicicletacontador <= 90 && m_Graphics->bicicletacontador >= 0) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
				}
				else if (m_Graphics->bicicletacontador <= 180 && m_Graphics->bicicletacontador >= 90) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
				}
				else if (m_Graphics->bicicletacontador <= 270 && m_Graphics->bicicletacontador >= 180) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
				}
				else if (m_Graphics->bicicletacontador <= 359 && m_Graphics->bicicletacontador >= 270) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
				}
				else if (m_Graphics->bicicletacontador <= 0 && m_Graphics->bicicletacontador >= -180) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
				}
				else if (m_Graphics->bicicletacontador <= -180 && m_Graphics->bicicletacontador >= -270) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
				}
				else if (m_Graphics->bicicletacontador <= -270 && m_Graphics->bicicletacontador >= -359) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
				}
				else {
					m_Graphics->bicicletacontador = 0;
				}
				break;
			}
			else if (otrasTeclas == 0x00000008) { //// XINPUT_GAMEPAD_DPAD_RIGHT
				m_Graphics->angy += 1;
				if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= 0) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
				}
				if (m_Graphics->bicicletacontador >= -90 && m_Graphics->bicicletacontador <= 0) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
				}
				else if (m_Graphics->bicicletacontador <= -90 && m_Graphics->bicicletacontador >= -180) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
				}
				else if (m_Graphics->bicicletacontador <= -180 && m_Graphics->bicicletacontador >= -270) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
				}
				else if (m_Graphics->bicicletacontador <= -270 && m_Graphics->bicicletacontador >= -359) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
				}
				else if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= 180) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
				}
				else if (m_Graphics->bicicletacontador >= 180 && m_Graphics->bicicletacontador <= 270) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
				}
				else if (m_Graphics->bicicletacontador >= 270 && m_Graphics->bicicletacontador <= 359) {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
				}
				else {
					m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
				}


				if (m_Graphics->bicicletacontador >= -90 && m_Graphics->bicicletacontador <= 0) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
				}
				else if (m_Graphics->bicicletacontador <= -90 && m_Graphics->bicicletacontador >= -180) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
				}
				else if (m_Graphics->bicicletacontador <= -180 && m_Graphics->bicicletacontador >= -270) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
				}
				else if (m_Graphics->bicicletacontador <= -270 && m_Graphics->bicicletacontador >= -359) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
				}
				else if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= 180) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
				}
				else if (m_Graphics->bicicletacontador >= 180 && m_Graphics->bicicletacontador <= 270) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
				}
				else if (m_Graphics->bicicletacontador >= 270 && m_Graphics->bicicletacontador <= 359) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
				}
				else if (m_Graphics->bicicletacontador >= 0 && m_Graphics->bicicletacontador <= 90) {
					m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ + radioBici;
					m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
				}
				else {
					m_Graphics->bicicletacontador = 0;
				}
				break;
			}
				else {
				m_Graphics->vel = 0;
				break;
			}
			
			
		}
	}

	case WM_KEYDOWN: {

		
		
		switch (wparam)
		{

		case VK_F1: //INFORMACION COORDENADAS POSICION KEYBOARD
		{
			/*string info = "X: " + to_string(scene->px) + " Y: " + to_string(scene->py)+ " Z: " +to_string(scene->pz);
			MessageBox(hWnd,info.c_str(),"INFO",MB_OK);*/

			string info = "X: " + to_string(m_Graphics->posicionCameraX) + " Y: " + to_string(m_Graphics->posicionCameraY) + " Z: " + to_string(m_Graphics->posicionCameraZ);
			MessageBox(hwnd, info.c_str(), "Informacion posicion", MB_OK);
			break;
		}
		case VK_F2: //INFORMACION COORDENADAS DIRECCION KEYBOARD
		{
			string info = "X: " + to_string(m_Graphics->angx) + " Y: " + to_string(m_Graphics->angy) + " Z: " + to_string(m_Graphics->angz);
			MessageBox(hwnd, info.c_str(), "Informacion direccion", MB_OK);
			break;
		}
		case 0x1B:  // CERRAR VENTANA
			PostQuitMessage(0);
			break;

			//CAMARA DEL GAMEPAD
		case 0x44: //D
		{
			m_Graphics->angy += 1;
			if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= 0) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
			}
			if (m_Graphics->bicicletacontador >= -90 && m_Graphics->bicicletacontador <= 0) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
			}
			else if (m_Graphics->bicicletacontador <= -90 && m_Graphics->bicicletacontador >= -180) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
			}
			else if (m_Graphics->bicicletacontador <= -180 && m_Graphics->bicicletacontador >= -270) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
			}
			else if (m_Graphics->bicicletacontador <= -270 && m_Graphics->bicicletacontador >= -359) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
			}
			else if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= 180) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
			}
			else if (m_Graphics->bicicletacontador >= 180 && m_Graphics->bicicletacontador <= 270) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
			}
			else if (m_Graphics->bicicletacontador >= 270 && m_Graphics->bicicletacontador <= 359) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
			}
			else{
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
			}


			if (m_Graphics->bicicletacontador >= -90 && m_Graphics->bicicletacontador <= 0) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
			}
			else if (m_Graphics->bicicletacontador <= -90 && m_Graphics->bicicletacontador >= -180) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
			}
			else if (m_Graphics->bicicletacontador <= -180 && m_Graphics->bicicletacontador >= -270) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
			}
			else if (m_Graphics->bicicletacontador <= -270 && m_Graphics->bicicletacontador >= -359) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
			}
			else if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= 180) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ -(-radioBici);
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
			}
			else if (m_Graphics->bicicletacontador >= 180 && m_Graphics->bicicletacontador <= 270) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
			}
			else if (m_Graphics->bicicletacontador >= 270 && m_Graphics->bicicletacontador <= 359) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
			}
			else if (m_Graphics->bicicletacontador >= 0 && m_Graphics->bicicletacontador <= 90) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ + radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador - 1;
			}
			else {
				m_Graphics->bicicletacontador = 0;
			}
			break;
		}
		case 0x41: //A
		{
			m_Graphics->angy -= 1;

			if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= -90) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
			}
			else if (m_Graphics->bicicletacontador >= 90 && m_Graphics->bicicletacontador <= 180) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - (-radioBici);
			}
			else if (m_Graphics->bicicletacontador >= 180 && m_Graphics->bicicletacontador <= 270) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
			}
			else if (m_Graphics->bicicletacontador >= 270 && m_Graphics->bicicletacontador <= 359) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
			}
			else if (m_Graphics->bicicletacontador <= -90 && m_Graphics->bicicletacontador >= -180) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
			}
			else if (m_Graphics->bicicletacontador <= -180 && m_Graphics->bicicletacontador >= -270) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX + radioBici;
			}
			else if (m_Graphics->bicicletacontador <= -270 && m_Graphics->bicicletacontador >= -359) {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
			}
			else {
				m_Graphics->bicicletaTercerX = m_Graphics->bicicletaTercerX - radioBici;
			}


			if (m_Graphics->bicicletacontador <= 90 && m_Graphics->bicicletacontador >= 0) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
			}
			else if (m_Graphics->bicicletacontador <= 180 && m_Graphics->bicicletacontador >= 90) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
			}
			else if (m_Graphics->bicicletacontador <= 270 && m_Graphics->bicicletacontador >= 180) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
			}
			else if (m_Graphics->bicicletacontador <= 359 && m_Graphics->bicicletacontador >= 270) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
			}
			else if (m_Graphics->bicicletacontador <= 0 && m_Graphics->bicicletacontador >= -180) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - (-radioBici);
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
			}
			else if (m_Graphics->bicicletacontador <= -180 && m_Graphics->bicicletacontador >= -270) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
			}
			else if (m_Graphics->bicicletacontador <= -270 && m_Graphics->bicicletacontador >= -359) {
				m_Graphics->bicicletaTercerZ = m_Graphics->bicicletaTercerZ - radioBici;
				m_Graphics->bicicletacontador = m_Graphics->bicicletacontador + 1;
			}
			else {
				m_Graphics->bicicletacontador = 0;
			}
			break;
		}
		case 0x57: //W
		{
			m_Graphics->vel = 0.5;
			break;
		}
		case 0x53: //S
		{
			m_Graphics->vel = -0.5;
			break;
		}
		case 0x42: // B
		{
			m_Graphics->tercerapersona = true;
			break;
		}
		case 0x56:
		{
			m_Graphics->tercerapersona = false;
			break;
		}
		case VK_UP: // FLECHA ARRIBA
		{
			m_Graphics->angx += 1;
			break; }
		case VK_DOWN: // FLECHA ABAJO
		{
			m_Graphics->angx -= 1;
			break; }
		}
		break;
		}

	case WM_KEYUP: {



		switch (wparam)
		{

		case 0x57: //W
		{
			m_Graphics->vel = 0;
			break;
		}
		case 0x53: //S
		{
			m_Graphics->vel = 0;
			break;
		}
		default:
			break;
		}
		
		break;
	}

	
	// Any other messages send to the default message handler as our application won't make use of them.
	default:
	{
		return DefWindowProc(hwnd, umessage, wparam, lparam);
	}		
	
	}
}