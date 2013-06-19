/**
 * \file TC.cpp
 * \brief Derplotter Test Chamber
 * \author Eduardo Pinho ( enet4mikeenet AT gmail.com )
 * \date 2013
 * \copyright Academic Free License version 3.0
 *
 * This executable demonstrates how an application can use the renderer with
 * the SDL library. The contents of the rendering buffer are passed to the SDL_Surface
 * in each frame.
 */

#include <SDL.h>
#include <iostream>
#include <Derplotter.h>
#include <math.h>

using namespace std;
using namespace derplot;
using namespace math;   // derplot::math

constexpr unsigned int FRAMES_PER_SECOND = 30;
constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;

typedef std::pair<int,int> ipair;

void drawAThing(Renderer& renderer);
void setMyProjection(Renderer& renderer);

int main(int argc, char** argv)
{
	// Init SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{	cerr << "Failed to init SDL" << endl;
		return 1; }

	// Set SDL video mode (using surface rendering)
	SDL_Surface* p_surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);
	if(p_surface == nullptr)
	{	cerr << "Failed to set video mode" << endl;
		return 1; }
	SDL_WM_SetCaption( "Derplotter Test Chamber", NULL );

	Renderer renderer(WIDTH, HEIGHT); // create a new rederer

	if (!renderer)
	{
		cerr << "Renderer Error" << endl;
		return 2;
	}

	setMyProjection(renderer);

	renderer.clear_color(0xFF111111);

	bool running = true;
	unsigned int framenum = 0;
	Vector4f moving_point(0.5,1,0.5,1);
	float ang = 0;
	int f = 0, lr = 0, ud = 0;
	do
	{
		//Event Handling (SDL)
		SDL_Event event;
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
			{
				running = false;
			}
			else if( event.type == SDL_KEYDOWN )
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					case SDLK_q:
						running = false; break;
					case SDLK_LEFT:
						lr--; break;
					case SDLK_RIGHT:
						lr++; break;
					case SDLK_UP:
						ud--; break;
					case SDLK_DOWN:
						ud++; break;
					case SDLK_w:
						f++; break;
					case SDLK_s:
						f--; break;
					default: break;
				}
			}
			else if( event.type == SDL_KEYUP )
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_w:
						f--; break;
					case SDLK_s:
						f++; break;
					case SDLK_UP:
						ud++; break;
					case SDLK_DOWN:
						ud--; break;
					case SDLK_LEFT:
						lr++; break;
					case SDLK_RIGHT:
						lr--; break;
					default: break;
				}
			}
		}

		//Update status
		renderer.translate({0,0,f*0.08f});
		renderer.translate({0.5,0.5,0.5});
		renderer.rotateY(degrees2radians(lr*-5.f));
		renderer.rotateX(degrees2radians(ud*5.f));
		renderer.translate({-0.5,-0.5,-0.5});

		ang += degrees2radians(11.25f); if (ang >= 360) ang -= 360;
		moving_point.x() = 0.5f + cos(ang) * 0.25f;
		moving_point.z() = 0.5f + sin(ang) * 0.25f;

		// draw stuff
		renderer.clear();
		renderer.front_color(0xFF888888);
		const Vector4f middle{0.5, 1, 0.5};
		renderer.drawLine(middle, moving_point);
		Vector4f tp = moving_point;
		tp.x() = -tp.x() + 1;
		renderer.drawLine(middle, tp);
		tp.z() = -tp.z() + 1;
		renderer.drawLine(middle, tp);
		tp.x() = -tp.x() + 1;
		renderer.drawLine(middle, tp);

		renderer.front_color(0xFFFFFFFF);
		renderer.scale({1,1,1.5});
		drawAThing(renderer);
		renderer.scale({1,1,1/1.5});

		// X
		renderer.front_color(0xFFFF0000);
		renderer.drawLine({0.5,0.5,0.5}, {1,0.5,0.5});
		// Y
		renderer.front_color(0xFF00FF00);
		renderer.drawLine({0.5,0.5,0.5}, {0.5,1,0.5});
		// Z
		renderer.front_color(0xFF0000FF);
		renderer.drawLine({0.5,0.5,0.5}, {0.5,0.5,1});

		// flush
		renderer.flush();

		// copy result to SDL surface
		SDL_LockSurface( p_surface );
		renderer.bufferCopy(p_surface->pixels);
		SDL_UnlockSurface( p_surface );

		//swap SDL buffers
		SDL_Flip(p_surface);

		//Sleep for a bit (lazy framerate capping)
		SDL_Delay(1000/FRAMES_PER_SECOND);
		framenum++;
	}
	while(running);

	renderer.terminate();
	return 0;
}

void setMyProjection(Renderer& renderer)
{
	//renderer.orthoProjection(-4, 4, -3, 3, 1, 100);
	renderer.perspectiveProjection(60, 0.01, 100, (float)WIDTH/(float)HEIGHT);
	renderer.rotateX(degrees2radians(10));
	renderer.translate({0.5, -1.5, -5});
}

void drawAThing(Renderer& renderer)
{
	const float line_stream[] = {
		0,0,0, 1,0,0, 1,0,0, 1,1,0, 1,1,0, 0,1,0, 0,1,0, 0,0,0,
		0,0,1, 1,0,1, 1,0,1, 1,1,1, 1,1,1, 0,1,1, 0,1,1, 0,0,1,
		0,0,0, 0,0,1, 1,0,0, 1,0,1, 1,1,0, 1,1,1, 0,1,0, 0,1,1,

		0,0,1, .5,.5,2,  1,0,1, .5,.5,2,  0,1,1, .5,.5,2,  1,1,1, .5,.5,2,

		0,0,1, -1,.5,1,  0,1,1, -1,.5,1,  0,0,0, -1,.5,0,  0,1,0, -1,.5,0,
		-1,.5,0, -1,.5,1,

		1,0,1, 2,.5,1,  1,1,1, 2,.5,1,  1,0,0, 2,.5,0,  1,1,0, 2,.5,0,
		2,.5,0, 2,.5,1,
	};
	Vector4f p1, p2;
	for (unsigned int i = 0 ; i < sizeof(line_stream)/sizeof(float) ;  )
	{
		p1.x() = line_stream[i++];
		p1.y() = line_stream[i++];
		p1.z() = line_stream[i++];
		p2.x() = line_stream[i++];
		p2.y() = line_stream[i++];
		p2.z() = line_stream[i++];
		renderer.drawLine(p1,p2);
	}
}
