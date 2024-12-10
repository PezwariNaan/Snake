#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>

#define HEIGHT 500
#define WIDTH 600
#define BLOCK_SIZE 15

typedef struct Node {
	SDL_FRect segment;
	struct Node *next;
	struct Node *prev;
} Snake;

void EventLoop(SDL_Renderer *renderer);
void CreateGrid(SDL_Renderer *renderer);
void DrawSnake(SDL_Renderer *renderer, int *direction, Snake *snake_head);
void GrowSnake(Snake **tail);
void MakeSnack(SDL_Renderer *renderer, bool *generate_snack, SDL_FRect *snack);

void EventLoop(SDL_Renderer *renderer) {
	bool running = true;
	bool generate_snack = true;
	unsigned int lastTime = 0, currentTime;
	int direction = 2; // 1: UP, 2: Right, 3: Down, 4: Left

	Snake *snake_head = malloc(sizeof(Snake));
	snake_head->segment.x = WIDTH/2.0 - BLOCK_SIZE;
	snake_head->segment.y = (HEIGHT/2.0 - BLOCK_SIZE) + 5;
	snake_head->segment.w = BLOCK_SIZE;
	snake_head->segment.h = BLOCK_SIZE;
	snake_head->next = NULL;
	snake_head->prev = NULL;

	Snake *tail = snake_head;

	while(running) {
		SDL_Event event;

		if (snake_head->segment.x < 0.0 ||
			snake_head->segment.x > WIDTH ||
			snake_head->segment.y < 0.0 ||
			snake_head->segment.y > HEIGHT) {
			running = false;
		}
		
		SDL_FRect snack;

		if (snake_head->segment.x == snack.x && snake_head->segment.y == snack.y) {
			generate_snack = true;
			GrowSnake(&tail);
		}

		while(SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
					SDL_Quit();
					running = false;
					break;
				case SDL_EVENT_KEY_DOWN:
					if (event.key.scancode == SDL_SCANCODE_Q) {
						running = false;
					} 

					else if (event.key.scancode == SDL_SCANCODE_UP) {
						direction = 1;
						break;
					} 
					else if (event.key.scancode == SDL_SCANCODE_RIGHT) {
						direction = 2;
						break;
					}
					else if (event.key.scancode == SDL_SCANCODE_DOWN) {
						direction = 3;
						break;
					}
					else if (event.key.scancode == SDL_SCANCODE_LEFT) {
						direction = 4;
						break;
					}
				default:
					break;
			}
		}

		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 100) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			MakeSnack(renderer, &generate_snack, &snack);
			CreateGrid(renderer);
			DrawSnake(renderer, &direction, snake_head);
			SDL_RenderPresent(renderer);
			lastTime = currentTime;
		}

	}
	return;
}

void CreateGrid(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

	for (int i = 0; i < HEIGHT; i += BLOCK_SIZE) {
		// Draw Horizonal Lines
		SDL_RenderLine(renderer, 0.0, i, WIDTH, i);
	}

	for (int i = 0; i < WIDTH; i += BLOCK_SIZE) {
		// Draw Vertical Lines
		SDL_RenderLine(renderer, i, 0.0, i, HEIGHT);
	}

	return;
}

void DrawSnake(SDL_Renderer *renderer, int *direction, Snake *snake_head) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_FRect previous_position = snake_head->segment;

    switch(*direction) {
        case 1: // UP
            snake_head->segment.y -= BLOCK_SIZE;
            break;
        case 2: // RIGHT
            snake_head->segment.x += BLOCK_SIZE;
            break;
        case 3: // DOWN
            snake_head->segment.y += BLOCK_SIZE;
            break;
        case 4: // LEFT
            snake_head->segment.x -= BLOCK_SIZE;
            break;
        default:
            break;
    }

	SDL_RenderFillRect(renderer, &snake_head->segment);
	Snake *current = snake_head->next;
	while (current != NULL) {
		SDL_FRect temp_position = current->segment;
		current->segment = previous_position;
		previous_position = temp_position;
		SDL_RenderFillRect(renderer, &current->segment);
		current = current->next;
	}
	
	return;
}

void MakeSnack(SDL_Renderer *renderer, bool *generate_snack, SDL_FRect *snack) {
	if (*generate_snack) {
		snack->x = (rand() % (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
		snack->y = (rand() % (HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;
		snack->w = BLOCK_SIZE;
		snack->h = BLOCK_SIZE;
		*generate_snack = false;
	}
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, snack);
	
	return;
}

void GrowSnake(Snake **tail) {
	Snake *new_node = malloc(sizeof(Snake));
	new_node->prev = *tail;
	new_node->next = NULL;
	new_node->segment = (*tail)->segment;

	(*tail)->next = new_node;
	*tail = new_node;
	
	return;
}

int main(void) {
	SDL_Window *my_window;
	SDL_Renderer *renderer;
	srand(time(NULL));

	SDL_Init(SDL_INIT_VIDEO);

	my_window = SDL_CreateWindow("My Window", WIDTH, HEIGHT, 0);
	if (my_window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could Not Create Window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer(my_window, 0);
	if (renderer == NULL) {
		SDL_Log("SDL_CreateRenderer() failed: %s", SDL_GetError());
		SDL_DestroyWindow(my_window);
		SDL_Quit();
		return 1;
	}


	EventLoop(renderer);
	SDL_DestroyWindow(my_window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}

