#include <SDL2/SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>

#include "Fuse_Core.hpp"

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
	Core.AddCFunc("Random", _Random, {TYPE_NUMBER, TYPE_NUMBER});
	
	Core.SetReader((std::istream*)&file);
	Core.SetOut(&std::cout, "");
	if (Core.Load()) {
		std::cerr << Core.GetErrorMessage() << std::endl;
	}
	
	if (Core.Error()) {
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
	auto x = dynamic_cast<Fuse::Number*>(args.at(0).get()),
	     y = dynamic_cast<Fuse::Number*>(args.at(1).get()),
	     w = dynamic_cast<Fuse::Number*>(args.at(2).get()),
	     h = dynamic_cast<Fuse::Number*>(args.at(3).get());
	auto c = dynamic_cast<Fuse::Table*>(args.at(4).get());
	     
	SDL_Rect rect;
	rect.x = (x->GetNum().type == INT ? x->GetNum().INT : (int)x->GetNum().DOUBLE);
	rect.y = (y->GetNum().type == INT ? y->GetNum().INT : (int)y->GetNum().DOUBLE);
	rect.w = (w->GetNum().type == INT ? w->GetNum().INT : (int)w->GetNum().DOUBLE);
	rect.h = (h->GetNum().type == INT ? h->GetNum().INT : (int)h->GetNum().DOUBLE);
	SDL_Colour colour;
	
	colour.r = dynamic_cast<Fuse::Number*>(c->Access(0).get())->GetNum().INT;
	colour.g = dynamic_cast<Fuse::Number*>(c->Access(1).get())->GetNum().INT;
	colour.b = dynamic_cast<Fuse::Number*>(c->Access(2).get())->GetNum().INT;
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
	auto l = dynamic_cast<Fuse::Number*>(args.at(0).get()),
	     u = dynamic_cast<Fuse::Number*>(args.at(1).get());
	   
	double lower = (l->GetNum().type == DOUBLE ? l->GetNum().DOUBLE : (double)l->GetNum().INT);
	double upper = (u->GetNum().type == DOUBLE ? u->GetNum().DOUBLE : (double)u->GetNum().INT);
	
	return std::make_shared<Number>( (std::rand() / (double)__INT_MAX__) * (upper - lower) + lower );
}
