#include "class.Direct.h"
#include "../../Global.h"
#include "../Math/class.vec.h"

Direct::Direct() : IGraphicDeviceManager(this) {
	m_win = NULL;
	m_graphicoption = NULL;
}
void Direct::Initialize(HWND win, GraphicOptions *a) {
	m_graphicoption = a;
	m_win = win;
	BaseDirect::Initialize();
}
void Direct::WND_SIZE(WPARAM& wparam) {
	if (wparam == SIZE_RESTORED) {
		// TODO 
		// m_graphicoption->screen.width = LOWORD(lParam);
		// m_graphicoption->screen.height = HIWORD(lParam);
	}
}
HWND Direct::getWindow() {
	return m_win;
}

void Direct::SetDirectDesc() {
	BaseDirect::SetDirectDesc();

	//+ A teraz prepiseme vlastnosti ktore potrebujeme
	if( m_graphicoption->vsyn ) {
		m_swapChainDesc.BufferDesc.RefreshRate.Numerator = m_numerator;
		m_swapChainDesc.BufferDesc.RefreshRate.Denominator = m_denominator;
	}
	m_swapChainDesc.BufferDesc.Width = m_graphicoption->screen.width;
	m_swapChainDesc.BufferDesc.Height = m_graphicoption->screen.height;
	m_swapChainDesc.SampleDesc = m_graphicoption->multysampling;
	m_swapChainDesc.Windowed = !m_graphicoption->screen.fullscreen;

	m_depthBufferDesc.Width =  m_graphicoption->screen.width;
	m_depthBufferDesc.Height =  m_graphicoption->screen.height;
	m_depthBufferDesc.SampleDesc = m_graphicoption->multysampling;

    m_viewport.Width = (float) m_graphicoption->screen.width;
    m_viewport.Height = (float) m_graphicoption->screen.height;
}

void Direct::DefaultMatrixes() {
	// Setup the projection matrix.
	float fieldOfView = (float)D3DX_PI / 4.0f;
	float screenAspect = (float)m_graphicoption->screen.width / (float) m_graphicoption->screen.height;;

	// Create the projection matrix for 3D rendering.
	D3DXMatrixPerspectiveFovLH(
		&m_projectionMatrix, 
		fieldOfView, 
		screenAspect,
		m_graphicoption->fov.neardepth, 
		m_graphicoption->fov.fardepth
	);

    // Initialize the world matrix to the identity matrix.
    D3DXMatrixIdentity(&m_worldMatrix);

	// Create an orthographic projection matrix for 2D rendering.
	D3DXMatrixOrthoLH(&m_orthoMatrix, 
		(float) m_graphicoption->screen.width, 
		(float) m_graphicoption->screen.height, 
		m_graphicoption->fov.neardepth, 
		m_graphicoption->fov.fardepth
	);
}
void Direct::EndScene()
{
	// Present the back buffer to the screen since rendering is complete.
	if( m_graphicoption->vsyn) {
		// Lock to screen refresh rate.
		m_swapChain->Present(1, 0);
	} else {
		// Present as fast as possible.
		m_swapChain->Present(0, 0);
	}
}
void Direct::BeginScene()
{
	float color[4];
	color[0] = 0.5f;
	color[1] = 0.5f;
	color[2] = 0.5f;
	color[3] = 1.f;
	BaseDirect::BeginScene(color);
}
void Direct::FindBestModeForMonitor(IDXGIOutput* adapterOutput, UINT screenWidth, UINT screenHeight) {
	// Alebo ak je nastaveny VSYn tak rovno preskoc
	if(!m_graphicoption->vsyn) return;
	BaseDirect::FindBestModeForMonitor(adapterOutput, m_graphicoption->screen.width, m_graphicoption->screen.height);
}