#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Scene.h"
#include <cmath>

#define COLOUR_DEPTH 16	//Colour depth

HWND        ghwnd;
HDC			ghdc;
HGLRC		ghrc;			//hardware RENDERING CONTEXT
HINSTANCE	ghInstance;
RECT		gRect;
RECT		screenRect;

//client area resolution
int S_WIDTH	 =	800;		
int S_HEIGHT =	600;

bool		keys[256];

//scene object
Scene scene;

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

HWND CreateOurWindow(LPSTR strWindowName, int width, int height, DWORD dwStyle, bool bFullScreen, HINSTANCE hInstance)
{
	HWND hwnd;

	WNDCLASS wcex;

	memset(&wcex, 0, sizeof(WNDCLASS));
	wcex.style			= CS_HREDRAW | CS_VREDRAW;		
	wcex.lpfnWndProc	= WndProc;		
	wcex.hInstance		= hInstance;						
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);; 
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);		
	wcex.hbrBackground	= (HBRUSH) (COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;	
	wcex.lpszClassName	= "FirstWindowClass";	

	
	RegisterClass(&wcex);// Register the class

	dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	ghInstance	= hInstance;// Assign our global hInstance to the window's hInstance

	//Set the Client area of the window to be our resolution.
	RECT glwindow;
	glwindow.left		= 0;		
	glwindow.right		= width;	
	glwindow.top		= 0;		
	glwindow.bottom		= height;	

	AdjustWindowRect( &glwindow, dwStyle, false);

	//Create the window
	hwnd = CreateWindow(	"FirstWindowClass", 
							strWindowName, 
							dwStyle, 
							0, 
							0,
							glwindow.right  - glwindow.left,
							glwindow.bottom - glwindow.top, 
							NULL,
							NULL,
							hInstance,
							NULL
							);

	if(!hwnd) return NULL;// If we could get a handle, return NULL

	ShowWindow(hwnd, SW_SHOWNORMAL);	
	UpdateWindow(hwnd);					
	SetFocus(hwnd);						

	return hwnd;
}

bool SetPixelFormat(HDC hdc) 
{ 
    PIXELFORMATDESCRIPTOR pfd = {0}; 
    int pixelformat; 
 
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);	// Set the size of the structure
    pfd.nVersion = 1;							// Always set this to 1
	// Pass in the appropriate OpenGL flags
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; 
    pfd.dwLayerMask = PFD_MAIN_PLANE;			// standard mask (this is ignored anyway)
    pfd.iPixelType = PFD_TYPE_RGBA;				// RGB and Alpha pixel type
    pfd.cColorBits = COLOUR_DEPTH;				// Here we use our #define for the color bits
    pfd.cDepthBits = COLOUR_DEPTH;				// Ignored for RBA
    pfd.cAccumBits = 0;							// nothing for accumulation
    pfd.cStencilBits = 0;						// nothing for stencil
 
	//Gets a best match on the pixel format as passed in from device
    if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == false ) 
    { 
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK); 
        return false; 
    } 
 
	//sets the pixel format if its ok. 
    if (SetPixelFormat(hdc, pixelformat, &pfd) == false) 
    { 
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK); 
        return false; 
    } 
 
    return true;
}

void ResizeGLWindow(int width, int height)// Initialize The GL Window
{
	if (height==0)// Prevent A Divide By Zero error
	{
		height=1;// Make the Height Equal One
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//calculate aspect ratio
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, 1 ,150.0f);

	glMatrixMode(GL_MODELVIEW);// Select The Modelview Matrix
	glLoadIdentity();// Reset The Modelview Matrix
}

void InitializeOpenGL(int width, int height) 
{  
    ghdc = GetDC(ghwnd);//  sets  global HDC

    if (!SetPixelFormat(ghdc))//  sets  pixel format
        PostQuitMessage (0);


    ghrc = wglCreateContext(ghdc);	//  creates  rendering context from  hdc
    wglMakeCurrent(ghdc, ghrc);		//	Use this HRC.

	ResizeGLWindow(width, height);	// Setup the Screen
}

void Init(HWND hwnd)
{
	ghwnd = hwnd;
	GetClientRect(ghwnd, &gRect);	//get rect into our handy global rect
	InitializeOpenGL(gRect.right, gRect.bottom);// initialise openGL

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	//glEnable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
}

void Cleanup()
{
	if (ghrc)
	{
		wglMakeCurrent(NULL, NULL);	// free rendering memory
		wglDeleteContext(ghrc);		// Delete our OpenGL Rendering Context
	}

	if (ghdc) 
	ReleaseDC(ghwnd, ghdc);			// Release our HDC from memory

	UnregisterClass("FirstWindowClass", ghInstance);// Free the window class

	PostQuitMessage (0);		// Post a QUIT message to the window
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)											
    {														
		case WM_CREATE:	
			break;

		case WM_SIZE:
			//resize the open gl window when the window is resized
			ResizeGLWindow(LOWORD(lParam),HIWORD(lParam));
			GetClientRect(hwnd, &gRect);
			break;	

		case WM_KEYDOWN:
			keys[wParam]=true;
			break;

		case WM_KEYUP:
			keys[wParam]=false;
			break;

		case WM_MOUSEMOVE:
			break;

		case WM_PAINT:
		    break;		

		case WM_DESTROY:	
			
			PostQuitMessage(0);	
								
			break;				
	}													

	return DefWindowProc (hwnd, message, wParam, lParam);		
															
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int nCmdShow)			
{	
	HWND		hwnd;
    MSG         msg;

	//initialise and create window
	hwnd = CreateOurWindow("Breakout", S_WIDTH, S_HEIGHT, 0, false, hInstance);	
	if(hwnd == NULL) return true;

	//initialise opengl and other settings
	Init(hwnd);
	
	while (true)					
    {							
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		    if (msg.message==WM_QUIT)
				break;
			TranslateMessage (&msg);							
			DispatchMessage (&msg);
		}
		else
		{		
			//allow user controls
			scene.Controls(keys);

			//update the scene
			scene.Update(1.0f);

			//render the scene
			scene.RenderScene();

			//swap frame buffers
			SwapBuffers(ghdc);		
		}
    }

	return msg.wParam ;										
}