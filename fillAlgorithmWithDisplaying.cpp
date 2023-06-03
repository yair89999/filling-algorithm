#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>

using namespace std;

vector<vector<int>> floodFill(vector<vector<int>> board, int pos[2], int replaceValue,SDL_Renderer* renderer,int x,int startX,int y,int startY,int rectSize) {
    x = startX;
    y = startY;
    if (board.at(pos[0]).at(pos[1]) == replaceValue) {
        // setting the current position
        board.at(pos[0]).at(pos[1]) = 2;
        // displaying the board
        SDL_Rect currentCubeRect;
        for (vector<int> line : board) {
            for (int value : line) {
                currentCubeRect = { x,y,rectSize,rectSize };
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
                SDL_RenderDrawRect(renderer, &currentCubeRect);

                if (value == 1) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                    SDL_RenderFillRect(renderer, &currentCubeRect);
                }
                else if (value == 2) {
                    SDL_SetRenderDrawColor(renderer, 122, 197, 205, 150);
                    SDL_RenderFillRect(renderer, &currentCubeRect);
                }
                x += rectSize;
            }
            x = startX;
            y += rectSize;
        }
        SDL_RenderPresent(renderer);
        Sleep(75);
        // calling the function again to set the positions on the sides
        if (pos[0] + 1 < board.size()) {
            int pos1[] = { pos[0] + 1, pos[1] };
            board = floodFill(board, pos1, replaceValue,renderer,x,startX,y, startY,rectSize);
        }
        if (pos[0] - 1 >= 0) {
            int pos2[] = { pos[0] - 1, pos[1] };
            board = floodFill(board, pos2, replaceValue, renderer, x, startX, y, startY, rectSize);
        }
        if (pos[1] + 1 < board.at(0).size()) {
            int pos3[] = { pos[0], pos[1] + 1 };
            board = floodFill(board, pos3, replaceValue, renderer, x, startX, y, startY, rectSize);
        }
        if (pos[1] - 1 >= 0) {
            int pos4[] = { pos[0], pos[1] - 1 };
            board = floodFill(board, pos4, replaceValue, renderer, x, startX, y, startY, rectSize);
        }
    }
    return board;
}

int main(int argc, char* argv[]) {
    static int width = 800;
    static int height = width;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // change the next line to the full code of opening a SDL2 window(with the options to draw and thisd kind of crap)
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    window = SDL_CreateWindow("Filling Algorithm",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        0);

    if (!window)
    {
        cout << "Failed to create window\n";
        return -1;
    }

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, 0); // creating a render so we will be able to do stuff on the screen


    if (!window_surface)
    {
        cout << "Failed to get the surface from the window\n";
        return -1;
    }

    SDL_UpdateWindowSurface(window);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    vector<vector<int>> board;
    int boardSize = 15; // the board size you are using: boardSizeXboardSize
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board.size() == i) {
                board.push_back({ 0 });
            }
            else {
                board.at(i).push_back(0);
            }
        }
    }

    int pos[2] = { -1,-1 };

    int rectSize = width / (boardSize+5);
    int startX = 150;
    startX = width / 2 - rectSize * boardSize / 2;
    int startY = startX;

    int x = startX;
    int y = startY;

    SDL_Event e;
    bool placingCubes = true;
    bool bGameOn = true;
    while (placingCubes) {
        while (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) {
                placingCubes = false;
                bGameOn = false;
                break;
            }
            else if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    placingCubes = false;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {

                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    x = startX;
                    y = startY;
                    vector<int> line;
                    int value;
                    for (int i = 0; i < board.size(); i++) {
                        line = board.at(i);
                        for (int j = 0; j < line.size(); j++) {
                            if (mouseX >= x && mouseX < x + rectSize) {
                                if (mouseY >= y && mouseY < y + rectSize) {
                                    value = line.at(j);
                                    if (value == 0) {
                                        board.at(i).at(j) = 1; // placing a block
                                    }
                                    else if (value == 1) {
                                        board.at(i).at(j) = 0;
                                    }
                                    else if (value == 2) {
                                        board.at(i).at(j) = 1;
                                        pos[0] = -1;
                                        pos[1] = -1;
                                    }
                                }
                            }
                            x += rectSize;
                        }
                        x = startX;
                        y += rectSize;
                    }
                }
                else if (e.button.button == SDL_BUTTON_RIGHT) {

                    int mouseX = e.button.x;
                    int mouseY = e.button.y;
                    x = startX;
                    y = startY;
                    vector<int> line;
                    int value;
                    for (int i = 0; i < board.size(); i++) {
                        line = board.at(i);
                        for (int j = 0; j < line.size(); j++) {
                            if (mouseX >= x && mouseX < x + rectSize) {
                                if (mouseY >= y && mouseY < y + rectSize) {
                                    if (board.at(i).at(j) == 2) {
                                        board.at(i).at(j) = 0;
                                    }
                                    else {
                                        if (pos[0] != -1) {
                                            for (int i = 0; i < board.size(); i++) {
                                                for (int j = 0; j < line.size(); j++) {
                                                    if (board.at(i).at(j) == 2) {
                                                        board.at(i).at(j) = 0;
                                                    }
                                                }
                                            }
                                        }
                                        board.at(i).at(j) = 2;
                                        pos[0] = i;
                                        pos[1] = j;
                                    }
                                }
                            }
                            x += rectSize;
                        }
                        x = startX;
                        y += rectSize;
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // parameters; render, red value,green value, blue value, alpha level
        SDL_RenderClear(renderer);// clrear the current rendering target

        x = startX;
        y = startY;
        SDL_Rect currentCubeRect;
        for (vector<int> line : board) {
            for (int value : line) {
                currentCubeRect = { x,y,rectSize,rectSize };
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
                SDL_RenderDrawRect(renderer, &currentCubeRect);

                if (value == 1) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
                    SDL_RenderFillRect(renderer, &currentCubeRect);
                }
                else if (value == 2) {
                    SDL_SetRenderDrawColor(renderer, 122, 197, 205, 150);
                    SDL_RenderFillRect(renderer, &currentCubeRect);
                }
                x += rectSize;
            }
            x = startX;
            y += rectSize;
        }

        SDL_RenderPresent(renderer);

    }

    if (bGameOn = true) { // meaning he didnt close the app
        if (pos[0] == -1) {
            pos[0] = 0;
            pos[1] = 0;
            board.at(0).at(0) = 0;
        }
        board[pos[0]][pos[1]] = 0;
        board = floodFill(board, pos, 0, renderer, x, startX, y, startY, rectSize);
        for (vector<int> v1 : board) {
            cout << "{";
            for (int n : v1) {
                cout << n << ",";
            }
            cout << "}" << endl;
        }
    }
    while (bGameOn) {
        while (SDL_PollEvent(&e) > 0) {
            if (e.type == SDL_QUIT) {
                bGameOn = false;
                break;
            }
            else if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_SPACE) {
                    
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // parameters; render, red value,green value, blue value, alpha level
        SDL_RenderClear(renderer);// clrear the current rendering target

        int x = startX;
        int y = startY;
        SDL_Rect currentCubeRect;
        for (vector<int> line : board) {
            for (int value : line) {
                currentCubeRect = { x,y,rectSize,rectSize };
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
                SDL_RenderDrawRect(renderer, &currentCubeRect);

                if (value == 1) {
                    SDL_SetRenderDrawColor(renderer, 0,0,0, 100);
                    SDL_RenderFillRect(renderer, &currentCubeRect);
                } else if (value == 2) {
                    SDL_SetRenderDrawColor(renderer, 122, 197, 205, 150);
                    SDL_RenderFillRect(renderer, &currentCubeRect);
                }
                x += rectSize;
            }
            x = startX;
            y += rectSize;
        }

        SDL_RenderPresent(renderer);
        
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
