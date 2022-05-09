#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


#define HEIGHT 20
#define WIDTH 40


using namespace std;


class Point {
public:
    int x, y;
    char shape;

    void draw();
    void init();
};


class Snake {
    Point body[10000];
    int length;
    char dir;

public:
    Snake();
    void changeDir(char);
    void grow();
    void draw();
    void move();
    bool eatFood(Point);
    bool die();
};

class Game {
public:
    static void gotoxy(int, int);
    void scoreDisplay(int);
    void drawFrame();
    void play();
};



int main() {
    Game game;
    game.play();

    getch();
    system("cls");
    return 0;
}

void Game::play() {
    Snake snake;
    Point food;
    int score = 0;
    food.init();
    drawFrame();
    scoreDisplay(score);


    char key;
    while (key != 'E' && key != 'e') {
    	food.draw();
    	
        if (kbhit()) {
            key = getch();
            if (key != ' ') snake.changeDir(key);
        }
        
        snake.move();
        if (snake.eatFood(food)) {
        	food.init();
        	scoreDisplay(++score);
            snake.grow();
        }
        if (snake.die()) {
        	gotoxy(WIDTH + 3, 1);
        	cout << "You losed!";
        	break;
        }


        Sleep(100);
    }
}

void Point::draw() {
    Game::gotoxy(x, y);
    cout << shape;
}

void Point::init() {
        x = rand() % (WIDTH - 1) + 1;
        y = rand() % (HEIGHT - 1) + 1;
        shape = rand() % (255 - 33 + 1) + 33;
}

Snake::Snake() {
        dir = 77;
        length = 4;
        body[0].x = 10;
        body[0].y = 10;
        body[0].shape = ':';
        for (int i = 1; i < length; i++) {
            body[i].x = 10 - i; 
            body[i].y = 10; 
            body[i].shape = '#';
        }
    
}


void Snake::changeDir(char key) {
    dir = key;
}

void Snake::draw() {
    for (int i = length - 1; i >= 0; i--) {
        body[i].draw();
    }
}

void Snake::move() {
    for (int i = 0; i < length; i++) {
    	Game::gotoxy(body[i].x, body[i].y);
    	cout << ' ';
    }

    for (int i = length - 1; i > 0; i--) {
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }
    if (dir == 77) {
    	if (body[0].x == WIDTH) body[0].x = 1;
    	else body[0].x++;
        body[0].shape = ':';
    }
    else if (dir == 75) {
    	if (body[0].x == 1) body[0].x = WIDTH;
    	else body[0].x--;
        body[0].shape = ':';
    }
    else if (dir == 72) {
    	if (body[0].y == 1) body[0].y = HEIGHT;
    	else body[0].y--;
        body[0].shape = 249;
    }
    else if (dir == 80) {
    	if (body[0].y == HEIGHT) body[0].y = 1;
    	else body[0].y++;
        body[0].shape = 249;
    }
    draw();
}

void Snake::grow() {
	body[length] = body[length - 1];
	length++;
}

bool Snake::eatFood(Point food) {
	if (body[0].x == food.x && body[0].y == food.y) return true;
	return false;
}

bool Snake::die() {
	for (int i = 2; i < length; i++) {
		if (body[i].x == body[0].x && body[i].y == body[0].y) return true;
	}
	return false;
}

void Game::drawFrame(){
    cout << (char)(218);
    for (int i = 0; i < WIDTH; i++) cout << (char)(196);
    cout << (char)(191);
    for (int i = 0; i < HEIGHT; i++) {
        gotoxy(0, i + 1);
        cout << (char)(179);
        gotoxy(WIDTH + 1, i + 1);
        cout << (char)(179);
    }
    gotoxy(0, HEIGHT + 1);
    cout << (char)(192);
    for (int i = 0; i < WIDTH; i++) cout << (char)(196);
    cout << (char)(217);

}

void Game::scoreDisplay(int score) {
	gotoxy(WIDTH + 3, 1);
	cout << "Score: " << score << "   ";
}

void Game::gotoxy(int x, int y){
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
