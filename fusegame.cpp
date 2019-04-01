#include <SDL2/SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

#include "Fuse.hpp"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

std::shared_ptr<Fuse::Object> _DrawRect(std::vector<std::shared_ptr<Fuse::Object>>& args); // x y w h
std::shared_ptr<Fuse::Object> _ClearScreen(std::vector<std::shared_ptr<Fuse::Object>>& args);
std::shared_ptr<Fuse::Object> _UpdateScreen(std::vector<std::shared_ptr<Fuse::Object>>& args);
std::shared_ptr<Fuse::Object> _Random(std::vector<std::shared_ptr<Fuse::Object>>& args); // lower upper

using namespace Fuse;

int main(int argc, char ** argv) {
	if (argc < 2) return -1;
	std::ifstream file(argv[1]);
	if (!file) return -1;
	
	Core.AddCFunc("DrawRect", _DrawRect, {TYPE_NUMBER, TYPE_NUMBER, TYPE_NUMBER, TYPE_NUMBER, TYPE_TABLE});
	Core.AddCFunc("ClearScreen", _ClearScreen, {});
	Core.AddCFunc("UpdateScreen", _UpdateScreen, {});
	
	//            function | function |         argument
	//            name     | pointer  |         types
	Core.AddCFunc("Random",  _Random,   {TYPE_NUMBER, TYPE_NUMBER});
	
	Fuse::Core.SetReader((std::istream*)&file);
	Fuse::Core.SetOut(&std::cout, "");
	Fuse::Core.Load();
	
	if (Core.Error()) {
		std::cerr << Core.GetErrorMessage() << std::endl;
		return -1;
	}
		
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}
	
	window = SDL_CreateWindow("FUSE GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	}
	
	std::srand(time(nullptr));
	
	bool going = true;
	std::vector<std::shared_ptr<Fuse::Object>> call_args;
	bool keyup = false, keydown = false;
	while (going) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				going = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_DOWN:
					keydown = true;
					break;
				case SDLK_UP:
					keyup = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_DOWN:
					keydown = false;
					break;
				case SDLK_UP:
					keyup = false;
					break;
				}
				break;
			}
		}
		
		if (keydown) Core.CallFunction("keydown", call_args);
		if (keyup) Core.CallFunction("keyup", call_args);
		
		std::vector<std::shared_ptr<Object>> call_args = {};
		Core.CallFunction("loop", call_args);
		
		if (Core.Error()) {
			std::cerr << Core.GetErrorMessage() << std::endl;
			going = false;
		}
		
		SDL_Delay(15);
		//break;
	}
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}

std::shared_ptr<Fuse::Object> _DrawRect(std::vector<std::shared_ptr<Fuse::Object>>& args) {
	auto x = Fuse::GetNumber(args.at(0)),
	     y = Fuse::GetNumber(args.at(1)),
	     w = Fuse::GetNumber(args.at(2)),
	     h = Fuse::GetNumber(args.at(3));
	auto c = Fuse::GetTable(args.at(4));
	     
	SDL_Rect rect;
	rect.x = x->Int();
	rect.y = y->Int();
	rect.w = w->Int();
	rect.h = h->Int();
	SDL_Colour colour;
	
	colour.r = Fuse::GetNumber(c->Access(0))->Int();
	colour.g = Fuse::GetNumber(c->Access(1))->Int();
	colour.b = Fuse::GetNumber(c->Access(2))->Int();
	colour.a = 0xff;
	
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(renderer, &rect);
	
	return std::make_shared<Null>();
}

std::shared_ptr<Fuse::Object> _ClearScreen(std::vector<std::shared_ptr<Fuse::Object>>& args) {
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
	SDL_RenderClear(renderer);
	
	return std::make_shared<Null>();
}

std::shared_ptr<Fuse::Object> _UpdateScreen(std::vector<std::shared_ptr<Fuse::Object>>& args) {
	SDL_RenderPresent(renderer);
	
	return std::make_shared<Null>();
}

std::shared_ptr<Fuse::Object> _Random(std::vector<std::shared_ptr<Fuse::Object>>& args) {
	auto l = Fuse::GetNumber(args.at(0)),
	     u = Fuse::GetNumber(args.at(1));
	   
	double lower = l->Double();
	double upper = l->Double();
	
	return std::make_shared<Number>( (std::rand() / (double)__INT_MAX__) * (upper - lower) + lower );
}
