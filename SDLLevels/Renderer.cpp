#include "Renderer.h"

Renderer::Renderer()
{
	m_window = nullptr;//will hold SDL window object
	m_renderer = nullptr;//will hold SDL renderer object
	m_srcRect = {};//texture is loaded onto this source rect(sub region of texture img to display, good for spritesheet)
	m_destRect = {};//an empty rectangle,destination rect
	m_surface = nullptr;//SDL surfaces are 2D images before beign converted to textures
	m_viewPort = {};//portion of screen visible for rendering
}

Renderer::~Renderer()
{
	Shutdown();
}

void Renderer::Initialize(int _xResolution, int _yResolution)
{
	M_ASSERT((SDL_Init(SDL_INIT_EVERYTHING) >= 0), "Could not Init");//initializes SDL with all its systems(video,audio,etc)
	m_window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _xResolution, _yResolution, SDL_WINDOW_SHOWN);//creates the window
	M_ASSERT(m_window != nullptr, "Failed to initialize SDL window.");//checks if window was created 
	m_renderer = SDL_CreateRenderer(Renderer::Instance().GetWindow(), -1, SDL_RENDERER_PRESENTVSYNC);//associates the renderer with the window 
	M_ASSERT(m_renderer != nullptr, "Failed to initialize SDL renderer.");
}

void Renderer::Shutdown()//cleans up resources when we are done with renderer, avoiding memory leaks
{
	for (auto it = m_textures.begin(); it != m_textures.end(); it++)
	{
		SDL_DestroyTexture(it->second);//loops through textures and destroys them, frees GPU memory
	}
	m_textures.clear();
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);//destroys the renderer when there are no textures
	}
	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);//destroys the window
	}
	SDL_Quit();//turn off all SDL subsystems
}

void Renderer::SetDrawColor(Color _color)
{
	SDL_SetRenderDrawColor(m_renderer, _color.R, _color.G, _color.B, _color.A);//set/define draw color for renderer
}

void Renderer::ClearScreen()
{
	SDL_RenderClear(m_renderer);//clears screen of current draw colour
}

void Renderer::RenderPoint(Point _position)
{//Renders a point on the screen at the specified position
	SDL_RenderDrawPoint(m_renderer, _position.X, _position.Y);
}

void Renderer::RenderLine(Rect _points)
{//Renders a line between two points
	SDL_RenderDrawLine(m_renderer, _points.X1, _points.Y1, _points.X2, _points.Y2);
}

void Renderer::RenderRectangle(Rect _rect)
{//Renders the outline of a rectangle 
	m_destRect.x = _rect.X1;
	m_destRect.y = _rect.Y1;
	m_destRect.w = _rect.X2 - _rect.X1;
	m_destRect.h = _rect.Y2 - _rect.Y1;
	SDL_RenderDrawRect(m_renderer, &m_destRect);
}

void Renderer::RenderFillRectangle(Rect _rect)
{//renders a filled rectangle
	m_destRect.x = _rect.X1;
	m_destRect.y = _rect.Y1;
	m_destRect.w = _rect.X2 - _rect.X1;
	m_destRect.h = _rect.Y2 - _rect.Y1;
	SDL_RenderFillRect(m_renderer, &m_destRect);
}

SDL_Texture* Renderer::GetSDLTexture(Texture* _texture)
{//Retrieves or creates an SDL texture for a given Texture object
	//if texture created, return texture
	Asset* asset = _texture->GetData();
	string guid = asset->GetGUID();
	if (m_textures.count(guid) != 0)
	{
		return m_textures[guid];
	}
	/*If the texture does not exist, it creates an SDL surface from
	the raw image data (_texture->GetImageInfo())
	and then converts it to an SDL texture with SDL_CreateTextureFromSurface.
	The texture is stored in the m_textures map with its GUID,
	and the surface is freed once the texture is created.*/
	//otherwise, create GPU texture
	ImageInfo* ii = _texture->GetImageInfo();
	m_surface = SDL_CreateRGBSurfaceFrom(asset->GetData() + _texture->GetImageInfo()->DataOffset, ii->Width, ii->Height, ii->BitsPerPixel, ii->Width * ii->BitsPerPixel / 8, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);
	m_surface = nullptr;
	m_textures[guid] = texture;
	return texture;
}

void Renderer::RenderTexture(Texture* _texture, Point _point)
{//Renders a texture at the specified point on the screen
	m_destRect.x = _point.X;
	m_destRect.y = _point.Y;
	m_destRect.w = _texture->GetImageInfo()->Width;
	m_destRect.h = _texture->GetImageInfo()->Height;
	M_ASSERT(((SDL_RenderCopyEx(m_renderer, GetSDLTexture(_texture), NULL, &m_destRect, 0, NULL, SDL_FLIP_VERTICAL)) >= 0), "Could not render texture.");

}

Point Renderer::GetWindowSize()
{//gets window size for the window managed by renderer
	int w;
	int h;
	SDL_GetWindowSize(m_window, &w, &h);
	return Point(w, h);
}

void Renderer::SetViewport(Rect _viewport)
{//sets the viewport for rendering
	m_viewPort.x = _viewport.X1;
	m_viewPort.y = _viewport.Y1;
	m_viewPort.w = _viewport.X2 - _viewport.X1;
	m_viewPort.h = _viewport.Y2 - _viewport.Y1;
	SDL_RenderSetViewport(m_renderer, &m_viewPort);

}

void Renderer::RenderTexture(Texture* _texture, Rect _rect)
{//used to render texture on screen in specific location
	//like a sprite or even a background img
	m_destRect.x = _rect.X1;
	m_destRect.y = _rect.Y1;
	m_destRect.w = _rect.X2 - _rect.X1;
	m_destRect.h = _rect.Y2 - _rect.Y1;
	M_ASSERT(((SDL_RenderCopyEx(m_renderer, GetSDLTexture(_texture), NULL, &m_destRect, 0, NULL, SDL_FLIP_VERTICAL)) >= 0), "Could not render texture.");

}

void Renderer::RenderTexture(Texture* _texture, Rect _srcRect, Rect _destRect)
{//defining destination rect size and position
	m_destRect.x = _destRect.X1;
	m_destRect.y = _destRect.Y1;
	m_destRect.w = _destRect.X2 - _destRect.X1;
	m_destRect.h = _destRect.Y2 - _destRect.Y1;

	//the part ofthe texture to render
	m_srcRect.x = _srcRect.X1;
	m_srcRect.y = _texture->GetImageInfo()->Height - _srcRect.Y2;
	m_srcRect.w = _srcRect.X2 - _srcRect.X1;
	m_srcRect.h = _srcRect.Y2 - _srcRect.Y1;

	//SDL_RenderCopyEx() copies the texture(srcRect) to the screen(destRect)
	M_ASSERT(((SDL_RenderCopyEx(m_renderer, GetSDLTexture(_texture), &m_srcRect, &m_destRect, 0, NULL, SDL_FLIP_VERTICAL)) >= 0), "Could not render texture");

}
