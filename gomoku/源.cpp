#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
#include <time.h>
#include <windows.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 1200
#define STAGE_WIDTH 15
#define STAGE_HEIGHT 15
#define GRIDSIZE 46.5  //纹理尺寸
#define START_X 125.4  //纹理尺寸
#define START_Y 462  //纹理尺寸
using namespace sf;
bool gameOver = false;    //判断游戏是否有人获得胜利
const int width = STAGE_WIDTH;
const int height = STAGE_HEIGHT;
int x, y;//选择落子坐标
Font font, font1;
Text text, text1, text2, text3, textScore, textTip;		//定义字体和文字
int score1, score2;		//定义两个分数


//yjw
int player1;
int player2;
int Mode = 0;
int Whoplay;
int ifsure1;
int ifsure2;

//end

Event event;
int flagStart;    //判断是否进入对战
int flagClose;    //判断是否关闭窗口
int flagGoing;    //判断是否完全重新开始游戏
int flagGame;     //判断是否继续该局游戏
int flagOverlay;	//判断弹窗是否弹出
int flagScore;		//判断胜利后的分数是否已经被加上
Clock mouseClicktimer;

//保存棋盘的类
class box
{
public:
	void draw();
public:
	int x = START_X;
	int y = START_Y;
	int value = -1;         // 值（黑棋：1，白棋：0，空位：-1）
	int modle;              // 模式
	bool isnew = false;     // 是否有选择框
	bool isnew2 = false;
	int number = 0;         // 分数
};

// 保存位置的类 new
class seat
{
public:
	int i = 0;      // y 坐标
	int j = 0;      // x 坐标
	int number = 0; // 分数
};


//wyw部分
box Box[15][15];
sf::Vector2i mousePosition, mousePosition2;
int dx[4]{ 1,0,1,1 }; // - | \ / 四个方向
int dy[4]{ 0,1,1,-1 };
int win;         // 谁赢了（0：白棋，1：黑棋，2：平局）

int turn;

Music music1, music2, music3, music4, music5, music6, musicClick;
Clock clock1;
//end

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "work!");

Texture tBackground, tPlayer1Por, tPlayer1, tPlayer2, tPlayer2Por;
Sprite spBackground, sPlayer1Por, sPlayer1, sPlayer2, sPlayer2Por;

//cyt精灵
Texture tFrontpage, tStart, tExit, tEnd, tRestartGame, tExitGame, tRestartPage, tScore, tName1, tName2;
Sprite spFrontpage, spStart, spExit, spEnd, spRestartGame, spExitGame, spRestartPage, spScore, spName1Mode0, spName2Mode0, spName1Mode1, spName2Mode1;
//yjw精灵
Texture  tFramePor, tch[4], tfrontBackground, tchoose1, tchoose2;
Sprite   sFramePor, sch[4], sfrontBackground, schoose1, schoose2;
Texture tInsure;
Sprite sInsure;
Texture tShining;
Sprite sShining;

//wyw精灵
Texture tFrame, tFrame2;
Sprite sFrame, sFrame2;

Vector2f originalSize1, originalSize2, originalSize3, originalSize4,
originalSize5, originalSize6, originalSize7, originalSize8, originalSize9, originalSize10;
Vector2f originalCenter1, originalCenter2, originalCenter3, originalCenter4,
originalCenter5, originalCenter6, originalCenter7, originalCenter8, originalCenter9, originalCenter10;

bool isHovering1 = false;
bool isHovering2 = false;
bool isHovering3 = false;
bool isHovering4 = false;
bool isHovering5 = false;
bool isHovering6 = false;
bool isHovering7 = false;
bool isHovering8 = false;
bool isHovering9 = false;
bool isHovering10 = false;

//end

void Initial()
{
	//加载字体
	font.loadFromFile("assets/fonts/xingti.ttf");
	text.setFont(font);
	text.setCharacterSize(60);

	font1.loadFromFile("assets/fonts/xingkai.ttf");
	text1.setFont(font);
	text1.setCharacterSize(50);
	Color textColor(135, 81, 17);
	text1.setFillColor(textColor);

	text2.setFont(font);
	text2.setCharacterSize(40);

	text3.setFont(font);
	text3.setCharacterSize(35);
	Color textColor1(153, 147, 131);
	text3.setFillColor(textColor1);

	textScore.setFont(font);
	textScore.setCharacterSize(32);
	Color textColor2(113, 80, 60);
	textScore.setFillColor(textColor2);

	textTip.setFont(font);
	textTip.setCharacterSize(23);

	//各种变量初始化
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Box[i][j].x = START_X;
			Box[i][j].y = START_Y;
		}
	}

	gameOver = false;
	player1 = -1;
	player2 = -1;
	win = -1;
	flagStart = 0;    //判断是否进入对战
	flagClose = 0;

	score1 = 0;
	score2 = 0;

	//加载背景图
	window.setFramerateLimit(20);
	tBackground.loadFromFile("assets/images/background.jpg");
	tFrontpage.loadFromFile("assets/images/frontpage.jpg");
	tScore.loadFromFile("assets/images/score.png");

	spBackground.setTexture(tBackground);
	spFrontpage.setTexture(tFrontpage);
	spScore.setTexture(tScore);

	//加载按钮
	tStart.loadFromFile("assets/images/start.png");
	tExit.loadFromFile("assets/images/exit.png");
	tEnd.loadFromFile("assets/images/end.png");
	tRestartGame.loadFromFile("assets/images/restart.png");
	tExitGame.loadFromFile("assets/images/exitGame.png");
	tRestartPage.loadFromFile("assets/images/restart_page.png");

	spStart.setTexture(tStart);
	spExit.setTexture(tExit);
	spEnd.setTexture(tEnd);
	spRestartGame.setTexture(tRestartGame);
	spExitGame.setTexture(tExitGame);
	spRestartPage.setTexture(tRestartPage);
	flagGoing = 0;

	//yjw部分
	tchoose1.loadFromFile("assets/images/player1.png");
	schoose1.setTexture(tchoose1);
	tchoose2.loadFromFile("assets/images/player2.png");
	schoose2.setTexture(tchoose2);

	tch[0].loadFromFile("assets/images/cat por0.png");
	sch[0].setTexture(tch[0]);
	tch[1].loadFromFile("assets/images/dog por0.png");
	sch[1].setTexture(tch[1]);
	tch[2].loadFromFile("assets/images/duck por0.png");
	sch[2].setTexture(tch[2]);
	tch[3].loadFromFile("assets/images/wolf por0.png");
	sch[3].setTexture(tch[3]);

	tShining.loadFromFile("assets/images/shining.png");
	sShining.setTexture(tShining);

	//对战界面精灵初始化
	tFramePor.loadFromFile("assets/images/frame.png");

	Whoplay = 0;
	Mode = 0;

	ifsure1 = 0;
	ifsure2 = 0;
	tInsure.loadFromFile("assets/images/insure.png");
	sInsure.setTexture(tInsure);
	//end

	//wyw部分

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			Box[i][j].x += j * 1.0 * GRIDSIZE;
			Box[i][j].y += i * 1.0 * GRIDSIZE;
			//cout << "(" << Box[i][j].x << "," << Box[i][j].y << ")" << endl;
		}
	}


	//tPlayer1.loadFromFile("assets/images/cat cir.png");
	//tPlayer2.loadFromFile("assets/images/duck cir.png");

	//sPlayer1.setTexture(tPlayer1);
	//sPlayer2.setTexture(tPlayer2);

	tFrame.loadFromFile("assets/images/frame2.png");
	sFrame.setTexture(tFrame);
	tFrame2.loadFromFile("assets/images/frame3.png");
	sFrame2.setTexture(tFrame2);

	//加载音乐
	music1.openFromFile("assets/audios/background.MP3");// 确保路径正确
	music2.openFromFile("assets/audios/chesstap.MP3"); // 确保路径正确
	music3.openFromFile("assets/audios/mew.mp3"); // 确保路径正确
	music4.openFromFile("assets/audios/wong.mp3"); // 确保路径正确
	music5.openFromFile("assets/audios/gaga.mp3"); // 确保路径正确
	music6.openFromFile("assets/audios/wolf.MP3");
	musicClick.openFromFile("assets/audios/click.mp3");
	
	//设定中心
	originalCenter1.x = spStart.getLocalBounds().width / 2;
	originalCenter1.y = spStart.getLocalBounds().height / 2;
	originalCenter2.x = spExit.getLocalBounds().width / 2;
	originalCenter2.y = spExit.getLocalBounds().height / 2;
	originalCenter3.x = spExitGame.getLocalBounds().width / 2;
	originalCenter3.y = spExitGame.getLocalBounds().height / 2;
	originalCenter4.x = spRestartGame.getLocalBounds().width / 2;
	originalCenter4.y = spRestartGame.getLocalBounds().height / 2;
	originalCenter5.x = sch[0].getLocalBounds().width / 2;
	originalCenter5.y = sch[0].getLocalBounds().height / 2;
	originalCenter6.x = sch[1].getLocalBounds().width / 2;
	originalCenter6.y = sch[1].getLocalBounds().height / 2;
	originalCenter7.x = sch[2].getLocalBounds().width / 2;
	originalCenter7.y = sch[2].getLocalBounds().height / 2;
	originalCenter8.x = sch[3].getLocalBounds().width / 2;
	originalCenter8.y = sch[3].getLocalBounds().height / 2;
	originalCenter9.x = sInsure.getLocalBounds().width / 2;
	originalCenter9.y = sInsure.getLocalBounds().height / 2;
	originalCenter10.x = spRestartPage.getLocalBounds().width / 2;
	originalCenter10.y = spRestartPage.getLocalBounds().height / 2;

	spStart.setOrigin(originalCenter1.x, originalCenter1.y);
	spExit.setOrigin(originalCenter2.x, originalCenter2.y);
	spExitGame.setOrigin(originalCenter3.x, originalCenter3.y);
	spRestartGame.setOrigin(originalCenter4.x, originalCenter4.y);
	sch[0].setOrigin(originalCenter5.x, originalCenter5.y);
	sch[1].setOrigin(originalCenter6.x, originalCenter6.y);
	sch[2].setOrigin(originalCenter7.x, originalCenter7.y);
	sch[3].setOrigin(originalCenter8.x, originalCenter8.y);
	sInsure.setOrigin(originalCenter9.x, originalCenter9.y);
	spRestartPage.setOrigin(originalCenter10.x, originalCenter10.y);

	music1.setLoop(true);
	music1.play();

	//end
}

void InitialGame() {
	win = -1;
	turn = 0;
	gameOver = false;
	//清空棋盘
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			Box[i][j].value = -1;
			Box[i][j].isnew = false;
			Box[i][j].number = 0;
			Box[i][j].isnew2 = false;
		}
	}
	flagGame = 1;		//对局开始
	flagGoing = 0;		//并不完全重新开始游戏
	flagOverlay = 0;	//没有弹窗
	flagScore = 0;		//分数还没被加上
	tName1.loadFromFile("assets/images/player1 name.png");
	switch (player1)
	{
	case 0:
		tPlayer1Por.loadFromFile("assets/images/cat por.png");
		tPlayer1.loadFromFile("assets/images/cat cir.png");
		break;
	case 1:
		tPlayer1Por.loadFromFile("assets/images/dog por.png");
		tPlayer1.loadFromFile("assets/images/dog cir.png");
		break;
	case 2:
		tPlayer1Por.loadFromFile("assets/images/duck por.png");
		tPlayer1.loadFromFile("assets/images/duck cir.png");
		break;
	case 3:
		tPlayer1Por.loadFromFile("assets/images/wolf por.png");
		tPlayer1.loadFromFile("assets/images/wolf cir.png");
		break;
	default:
		break;
	}

	if (player2 != -1 && ifsure2 == 1)
	{
		tName2.loadFromFile("assets/images/player2 name.png");
		switch (player2)
		{
		case 0:
			tPlayer2Por.loadFromFile("assets/images/cat por.png");
			tPlayer2.loadFromFile("assets/images/cat cir.png");
			break;
		case 1:
			tPlayer2Por.loadFromFile("assets/images/dog por.png");
			tPlayer2.loadFromFile("assets/images/dog cir.png");
			break;
		case 2:
			tPlayer2Por.loadFromFile("assets/images/duck por.png");
			tPlayer2.loadFromFile("assets/images/duck cir.png");
			break;
		case 3:
			tPlayer2Por.loadFromFile("assets/images/wolf por.png");
			tPlayer2.loadFromFile("assets/images/wolf cir.png");
			break;
		default:
			break;
		}
	}
	else
	{
		Mode = 1;
		tPlayer2Por.loadFromFile("assets/images/com por.png");
		tPlayer2.loadFromFile("assets/images/com cir.png");

		tName1.loadFromFile("assets/images/player name.png");
		tName2.loadFromFile("assets/images/com name.png");
	}
	sFramePor.setTexture(tFramePor);
	sPlayer1Por.setTexture(tPlayer1Por);
	sPlayer2Por.setTexture(tPlayer2Por);

	sPlayer1.setTexture(tPlayer1);
	sPlayer2.setTexture(tPlayer2);

	if (Mode == 0) {
		spName1Mode0.setTexture(tName1);
		spName2Mode0.setTexture(tName2);
	}
	if (Mode == 1) {
		spName1Mode1.setTexture(tName1);
		spName2Mode1.setTexture(tName2);
	}
}

//初始界面的输入
void InputFront()
{
	while (window.pollEvent(event)) // 获取窗口中的事件
	{
		if (player1 == -1 || ifsure1 == 0)
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				int i, j;
				// 获取鼠标点击的位置
				Vector2i mousePos = Mouse::getPosition(window);
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				i = worldPos.x; // 鼠标点击位置的 x 坐标
				j = worldPos.y; // 鼠标点击位置的 y 坐标
				//printf("%d,%d", i, j);
				int player1_pre = player1;
				if (i >= 250 && i <= 450 && j >= 500 && j <= 700)
				{
					schoose1.setPosition(200-25, 450);
					player1 = 0;

				}
				else if (i >= 550 && i <= 750 && j >= 500 && j <= 700)
				{
					schoose1.setPosition(500 - 25, 450);
					player1 = 1;
				}
				else if (i >= 250 && i <= 450 && j >= 725 && j <= 925)
				{
					schoose1.setPosition(200 - 25, 675);
					player1 = 2;
				}
				else if (i >= 550 && i <= 750 && j >= 725 && j <= 925)
				{
					schoose1.setPosition(500 - 25, 675);
					player1 = 3;
				}
				if (player1_pre == player1) {
					if (player1 == 0 && i >= 400 && i <= 515 && j >= 650 && j <= 700)
					{
						ifsure1 = 1;
						musicClick.play();
					}
					else if (player1 == 1 && i >= 700 && i <= 815 && j >= 650 && j <= 700)
					{
						ifsure1 = 1;
						musicClick.play();
					}
					else if (player1 == 2 && i >= 400 && i <= 515 && j >= 875 && j <= 925)
					{
						ifsure1 = 1;
						musicClick.play();
					}
					else if (player1 == 3 && i >= 700 && i <= 815 && j >= 875 && j <= 925)
					{
						ifsure1 = 1;
						musicClick.play();
					}
				}
			}
		}

		if ((player1 != -1 && ifsure1 == 1 && player2 == -1) || (ifsure1 == 1 && ifsure2 == 0))
		{
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				int i, j;
				// 获取鼠标点击的位置
				Vector2i mousePos = Mouse::getPosition(window);
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				i = worldPos.x; // 鼠标点击位置的 x 坐标
				j = worldPos.y; // 鼠标点击位置的 y 坐标
				//printf("%d,%d", i, j);
				int player2_pre = player2;
				if (i >= 250 && i <= 450 && j >= 500 && j <= 700 && player1 != 0)
				{
					schoose2.setPosition(200 - 25, 450);
					player2 = 0;

				}
				else if (i >= 550 && i <= 750 && j >= 500 && j <= 700 && player1 != 1)
				{
					schoose2.setPosition(500 - 25, 450);
					player2 = 1;
				}
				else if (i >= 250 && i <= 450 && j >= 725 && j <= 925 && player1 != 2)
				{
					schoose2.setPosition(200 - 25, 675);
					player2 = 2;
				}
				else if (i >= 550 && i <= 750 && j >= 725 && j <= 925 && player1 != 3)
				{
					schoose2.setPosition(500 - 25, 675);
					player2 = 3;
				}
				if (player2_pre == player2) {
					if (player2 == 0 && i >= 400 && i <= 515 && j >= 650 && j <= 700)
					{
						ifsure2 = 1;
						musicClick.play();
					}
					else if (player2 == 1 && i >= 700 && i <= 815 && j >= 650 && j <= 700)
					{
						ifsure2 = 1;
						musicClick.play();
					}
					else if (player2 == 2 && i >= 400 && i <= 515 && j >= 875 && j <= 925)
					{
						ifsure2 = 1;
						musicClick.play();
					}
					else if (player2 == 3 && i >= 700 && i <= 815 && j >= 875 && j <= 925)
					{
						ifsure2 = 1;
						musicClick.play();
					}
				}
			}
		}
		//end

		//cyt部分
		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (spStart.getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering1) { // 防止重复缩放
					isHovering1 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					spStart.setOrigin(originalCenter1); // 设置原点为原始中心
					spStart.setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering1) { // 鼠标之前在按钮上
					isHovering1 = false;
					spStart.setOrigin(originalCenter1); // 设置原点为原始中心
					spStart.setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spStart.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					musicClick.play();
					spStart.setOrigin(originalCenter1);
					spStart.setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spStart.getGlobalBounds().contains(worldPos)) {
					flagGame = 1;
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					spStart.setOrigin(originalCenter1);
					spStart.setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}

		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (spExit.getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering2) { // 防止重复缩放
					isHovering2 = true;
					spExit.setOrigin(originalCenter2); // 设置原点为原始中心
					spExit.setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering2) { // 鼠标之前在按钮上
					isHovering2 = false;
					spExit.setOrigin(originalCenter2); // 设置原点为原始中心
					spExit.setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spExit.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					musicClick.play();
					spExit.setOrigin(originalCenter2);
					spExit.setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spExit.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					spExit.setOrigin(originalCenter2);
					spExit.setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}

		//start
		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (sch[0].getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering5) { // 防止重复缩放
					music3.play();
					isHovering5 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					sch[0].setOrigin(originalCenter5); // 设置原点为原始中心
					sch[0].setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering5) { // 鼠标之前在按钮上
					isHovering5 = false;
					music3.stop();
					sch[0].setOrigin(originalCenter5); // 设置原点为原始中心
					sch[0].setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sch[0].getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sch[0].setOrigin(originalCenter5);
					sch[0].setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sch[0].getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sch[0].setOrigin(originalCenter5);
					sch[0].setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}
		//end

		//start2
		// //
		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (sch[1].getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering6) { // 防止重复缩放
					music4.play();
					isHovering6 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					sch[1].setOrigin(originalCenter6); // 设置原点为原始中心
					sch[1].setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering6) { // 鼠标之前在按钮上
					music4.stop();
					isHovering6 = false;
					sch[1].setOrigin(originalCenter6); // 设置原点为原始中心
					sch[1].setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sch[1].getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sch[1].setOrigin(originalCenter6);
					sch[1].setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sch[1].getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sch[1].setOrigin(originalCenter6);
					sch[1].setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}
		//
		//end2

		//start3
		// //
		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (sch[2].getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering7) { // 防止重复缩放
					music5.play();
					isHovering7 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					sch[2].setOrigin(originalCenter7); // 设置原点为原始中心
					sch[2].setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering7) { // 鼠标之前在按钮上
					music5.stop();
					isHovering7 = false;
					sch[2].setOrigin(originalCenter7); // 设置原点为原始中心
					sch[2].setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sch[2].getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sch[2].setOrigin(originalCenter7);
					sch[2].setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sch[2].getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sch[2].setOrigin(originalCenter7);
					sch[2].setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}
		//
		//end3

		//start4
		// //
		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (sch[3].getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering8) { // 防止重复缩放
					music6.play();
					isHovering8 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					sch[3].setOrigin(originalCenter8); // 设置原点为原始中心
					sch[3].setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering8) { // 鼠标之前在按钮上
					music6.stop();
					isHovering8 = false;
					sch[3].setOrigin(originalCenter8); // 设置原点为原始中心
					sch[3].setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sch[3].getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sch[3].setOrigin(originalCenter8);
					sch[3].setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sch[3].getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sch[3].setOrigin(originalCenter8);
					sch[3].setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}
		//
		//end4

			//start5
		// //
		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (sInsure.getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering9) { // 防止重复缩放
					isHovering9 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					sInsure.setOrigin(originalCenter9); // 设置原点为原始中心
					sInsure.setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering9) { // 鼠标之前在按钮上
					isHovering9 = false;
					sInsure.setOrigin(originalCenter9); // 设置原点为原始中心
					sInsure.setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sInsure.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sInsure.setOrigin(originalCenter9);
					sInsure.setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (sInsure.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					sInsure.setOrigin(originalCenter9);
					sInsure.setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}
		//
		//end5

		if (ifsure1 != 0)
		{
			//if(Mouse::isButtonPressed(Mouse::Left))
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				mouseClicktimer.restart();
				if (spStart.getGlobalBounds().contains(worldPos))
				{
					flagStart = 1;
					spStart.setScale(1.0f, 1.0f);
				}

			}
		}
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			Vector2i mousePos = Mouse::getPosition(window);
			// 将鼠标点击位置转换为窗口内的坐标
			Vector2f worldPos = window.mapPixelToCoords(mousePos);
			if (spExit.getGlobalBounds().contains(worldPos))
			{
				flagClose = 1;
			}
		}
	}

}

//输入
void Input()
{
	// 获取鼠标当前位置
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);

	// 这里假设你有一个矩形形状或者其他图形对象
	sf::RectangleShape rectangle(sf::Vector2f(900, 1200));
	rectangle.setPosition(0, 0); // 设置矩形的位置

	// 将鼠标位置转换为窗口坐标
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(currentMousePos);

	// 检查鼠标位置是否在矩形内
	if (rectangle.getGlobalBounds().contains(mouseWorldPos)) {
		// 鼠标正在悬停在矩形上
		// 更新鼠标位置
		mousePosition2 = currentMousePos;
	}

	while (window.pollEvent(event))
	{
		//退出游戏
		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (spExitGame.getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering3) { // 防止重复缩放
					isHovering3 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					spExitGame.setOrigin(originalCenter3); // 设置原点为原始中心
					spExitGame.setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering3) { // 鼠标之前在按钮上
					isHovering3 = false;
					spExitGame.setOrigin(originalCenter3); // 设置原点为原始中心
					spExitGame.setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spExitGame.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					musicClick.play();
					spExitGame.setOrigin(originalCenter3);
					spExitGame.setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spExitGame.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					spExitGame.setOrigin(originalCenter3);
					spExitGame.setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}

		//再来一局
		//start2
		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (spRestartGame.getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering4) { // 防止重复缩放
					isHovering4 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					spRestartGame.setOrigin(originalCenter4); // 设置原点为原始中心
					spRestartGame.setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering4) { // 鼠标之前在按钮上
					isHovering4 = false;
					spRestartGame.setOrigin(originalCenter4); // 设置原点为原始中心
					spRestartGame.setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spRestartGame.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					musicClick.play();
					spRestartGame.setOrigin(originalCenter4);
					spRestartGame.setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spRestartGame.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					spRestartGame.setOrigin(originalCenter4);
					spRestartGame.setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}
		//end2
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			mousePosition = Mouse::getPosition(window);
			// 将鼠标点击位置转换为窗口内的坐标
			//Vector2f worldPos = window.mapPixelToCoords(mousePos);
		}

		//重新开始
		//start3

		if (event.type == sf::Event::MouseMoved) {
			Vector2i mousePos = sf::Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			// 检查鼠标位置是否在spStart按钮的范围内
			if (spRestartPage.getGlobalBounds().contains(worldPos)) {
				// 鼠标悬停，缩小按钮
				if (!isHovering10) { // 防止重复缩放
					isHovering10 = true;
					//Vector2f newCenter = originalCenter * 0.9f;
					spRestartPage.setOrigin(originalCenter10); // 设置原点为原始中心
					spRestartPage.setScale(1.05f, 1.05f); // 放大按钮
				}
			}
			else {
				// 鼠标离开，恢复按钮原状
				if (isHovering10) { // 鼠标之前在按钮上
					isHovering10 = false;
					spRestartPage.setOrigin(originalCenter10); // 设置原点为原始中心
					spRestartPage.setScale(1.0f, 1.0f); // 恢复按钮大小
				}
			}
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spRestartPage.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					musicClick.play();
					spRestartPage.setOrigin(originalCenter10);
					spRestartPage.setScale(0.9f, 0.9f); // 缩小按钮
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				Vector2i mousePos = Mouse::getPosition(window);
				// 将鼠标点击位置转换为窗口内的坐标
				Vector2f worldPos = window.mapPixelToCoords(mousePos);

				if (spRestartPage.getGlobalBounds().contains(worldPos)) {
					//Vector2f newCenter = originalCenter * 0.9f;
					// 设置缩小按钮的中心位置
					spRestartGame.setOrigin(originalCenter10);
					spRestartGame.setScale(1.0f, 1.0f); // 恢复原来的大小
				}
			}
		}
		//end2

		//cyt部分
		//各个按钮按下后的效果
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			Vector2i mousePos = Mouse::getPosition(window);
			// 将鼠标点击位置转换为窗口内的坐标
			Vector2f worldPos = window.mapPixelToCoords(mousePos);

			mouseClicktimer.restart();
			if (spRestartGame.getGlobalBounds().contains(worldPos))
			{
				flagStart = 0;
				flagGoing = 1;
				flagGame = 0;
			}
			if (spExitGame.getGlobalBounds().contains(worldPos) && flagOverlay == 0)
			{
				flagClose = 1;
				flagGame = 0;
			}
			if (spRestartPage.getGlobalBounds().contains(worldPos) && flagOverlay == 1)
			{
				flagGoing = 1;
				flagGame = 1;
			}
		}

		//end
	}
}

// 寻找最佳位置
seat findbestseat(int color)
{
	// 评分表
	int Score[3][5] = {
	  { 0, 10, 100, 1000, 10000 }, // 防守0子
	  { 0, 0, 10, 100, 10000 },    // 防守1子
	  { 0, 0, 0, 0, 10000 }        // 防守2子
	};
	seat bestseat;              // 最佳位置
	int MAXnumber[361] = { 0 }; // 最佳分数
	int MAXx[361] = { 0 };      // 最佳 x 坐标
	int MAXy[361] = { 0 };      // 最佳 y 坐标
	int number = 0;             // 下一个最佳分数储存位置
	int truenumber;             // 输出的最佳分数位置
	int nowi = 0;               // 现在遍历到的y坐标
	int nowj = 0;               // 现在遍历到的x坐标
	int length[4];              // 四个方向的长度
	int emeny[4];               // 四个方向的敌子
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (Box[i][j].value == -1)
			{
				// 遍历每一个可能的位置

				// 自己
				Box[i][j].value = color; // 尝试下在这里
				for (int k = 0; k < 4; k++)
				{
					length[k] = 0;
					emeny[k] = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && Box[nowi][nowj].value == color)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					if (Box[nowi][nowj].value == 1 - color || nowi < 0 || nowj < 0 || nowi > 14 || nowj > 14)
					{
						emeny[k]++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && Box[nowi][nowj].value == color)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
					if (Box[nowi][nowj].value == 1 - color || nowi < 0 || nowj < 0 || nowi > 14 || nowj > 14)
					{
						emeny[k]++;
					}
					length[k] -= 2; // 判断长度
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					Box[i][j].number += Score[emeny[k]][length[k]] * 4 + !(!length[k]) * 15;//加分系统
					length[k] = 0;
					emeny[k] = 0;
				}
				// 敌人（原理同上）
				Box[i][j].value = 1 - color;
				for (int k = 0; k < 4; k++)
				{
					length[k] = 0;
					emeny[k] = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && Box[nowi][nowj].value == 1 - color)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					if (Box[nowi][nowj].value == color || nowi < 0 || nowj < 0 || nowi > 14 || nowj > 14)
						emeny[k]++;
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && Box[nowi][nowj].value == 1 - color)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
					if (Box[nowi][nowj].value == color || nowi < 0 || nowj < 0 || nowi > 14 || nowj > 14)
					{
						emeny[k]++;
					}
					length[k] -= 2;
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					Box[i][j].number += Score[emeny[k]][length[k]]*2;
					length[k] = 0;
					emeny[k] = 0;
				}
				Box[i][j].value = -1;
			}
			if (Box[i][j].number == MAXnumber[0])
			{
				// 如果和最高分数相同
				MAXnumber[number] = Box[i][j].number;
				MAXy[number] = i;
				MAXx[number] = j;
				number++;
				// 新增一个分数及坐标
			}
			if (Box[i][j].number > MAXnumber[0])
			{
				// 如果比最高分数高
				for (int k = 0; k < number; k++)
				{
					MAXnumber[k] = 0;
					MAXy[k] = 0;
					MAXx[k] = 0;
				}
				number = 0;
				MAXnumber[number] = Box[i][j].number;
				MAXy[number] = i;
				MAXx[number] = j;
				number++;
				// 清空数组再加入
			}
		}
	}
	// 生成随机位置
	srand(time(NULL));
	truenumber = rand() % number;
	bestseat.i = MAXy[truenumber];
	bestseat.j = MAXx[truenumber];
	bestseat.number = MAXnumber[truenumber];
	// 返回位置
	return bestseat;
}
// 判断输赢
void isWIN()
{
	bool isinit = true; // 是否刚刚开局
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (Box[i][j].value != -1)
			{
				// 遍历每个可能的位置
				isinit = false;                 // 如果有，那么就不是刚刚开局
				int nowcolor = Box[i][j].value; // 现在遍历到的颜色
				int length[4] = { 0,0,0,0 };    // 四个方向的长度
				for (int k = 0; k < 4; k++)
				{
					// 原理同寻找最佳位置
					int nowi = i;
					int nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && Box[nowi][nowj].value == nowcolor)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					nowi = i;
					nowj = j;
					while (nowi <= 14 && nowj <= 14 && nowi >= 0 && nowj >= 0 && Box[nowi][nowj].value == 1 - nowcolor)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
				}
				for (int k = 0; k < 4; k++)
				{
					if (length[k] >= 5) {
						// 如果满五子
						if (nowcolor == turn)
						{
							win = turn; // 玩家胜
						}
						if (nowcolor == 1 - turn)
						{
							win = 1 - turn; // 电脑胜
						}
					}
				}
			}
		}
	}
}

//逻辑
void Logic()
{

	if (flagClose == 1)
	{
		window.close();
	}
	else {
		if (win >= 0)
		{
			gameOver = true;
		}
		if (gameOver)
		{
			if (flagScore == 0)
			{
				if (win == 0)
					score1++;
				if (win == 1)
					score2++;
				flagScore = 1;
			}
			//结束游戏
		}
		else
		{
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (abs(mousePosition2.x - Box[i][j].x) < 20 && abs(mousePosition2.y - Box[i][j].y) < 20 && Box[i][j].value == -1)
					{
						Box[i][j].isnew = true;
						//printf("Box[%d][%d].isnew = true\n", i, j);
					}

				}
			}
			if (Mode == 0) {
				//int flag = 0;
				for (int i = 0; i < 15; i++)
				{
					for (int j = 0; j < 15; j++)
					{
						if (abs(mousePosition.x - Box[i][j].x) < 20 && abs(mousePosition.y - Box[i][j].y) < 20 && Box[i][j].value == -1)
						{
							//flag = 1;
							for (int a = 0; a < 15; a++) {
								for (int b = 0; b < 15; b++) {
									Box[a][b].isnew2 = false;
								}
							}
							Box[i][j].value = turn;
							Box[i][j].isnew2 = true;
							//printf("Box[%d][%d].value = %d\n", i, j, turn);
							turn = 1 - turn;

							music2.play();
							//break;
						}
					}
					/*if (flag == 1) {
						break;
					}*/
				}
			}
			else {
				if (Whoplay == 0)
				{
					//int flag = 0;
					for (int i = 0; i < 15; i++)
					{
						for (int j = 0; j < 15; j++)
						{
							if (abs(mousePosition.x - Box[i][j].x) < 15 && abs(mousePosition.y - Box[i][j].y) < 15 && Box[i][j].value == -1)
							{
								//flag = 1;
								for (int a = 0; a < 15; a++) {
									for (int b = 0; b < 15; b++) {
										Box[a][b].isnew2 = false;
									}
								}
								Box[i][j].value = 0;
								Box[i][j].isnew2 = true;
								Whoplay = 1 - Whoplay;
								//break;
							}
						}
						/*if (flag == 1) {
							Whoplay = 1 - Whoplay;
							break;
						}*/
					}

				}
				else
				{
					for (int a = 0; a < 15; a++) {
						for (int b = 0; b < 15; b++) {
							Box[a][b].isnew2 = false;
						}
					}
					seat best;
					best = findbestseat(Whoplay);
					while (Box[best.i][best.j].value != -1) {
						best = findbestseat(Whoplay);
					}
					Sleep(300);
					if (best.number == 0)
					{
						// 开局情况
						int drawi = 7;
						int drawj = 7;
						while (Box[drawi][drawj].value != -1)
						{
							drawi--;
							drawj++;
						}
						Box[drawi][drawj].value = 1 - turn;
						Box[drawi][drawj].isnew = true;
					}
					else
					{

						Box[best.i][best.j].value = 1 - turn;//下在最佳位置
						//printf("%d,%d;", best.i, best.j);
						Box[best.i][best.j].isnew2 = true;//下在最佳位置
						Box[best.i][best.j].isnew = true;
					}
					music2.play();
					Whoplay = 1 - Whoplay;
				}
			}
		}
	}
}

//初始界面的绘制
void DrawFront() {
	window.clear();
	spFrontpage.setPosition(0, 0);
	window.draw(spFrontpage);
	spStart.setPosition(500 + 128, 950 + 54);
	spExit.setPosition(500 + 128, 1080 + 54);
	window.draw(spStart);
	window.draw(spExit);

	text1.setPosition(200+60-35, 350-50);
	text1.setString(L"Choose Your Character");
	window.draw(text1);

	text2.setPosition(200+60, 410-50);
	text2.setString(L"Select two characters");
	window.draw(text2);

	text2.setPosition(200+60, 440-40);
	text2.setString(L"to play VS Player mode");
	window.draw(text2);


	text3.setPosition(195-20, 950+25);
	text3.setString(L"Select one character");
	window.draw(text3);

	text3.setPosition(200-20, 1000+25);
	text3.setString(L" to play VS AI mode");
	window.draw(text3);

	text3.setPosition(205-20, 1050+25);
	text3.setString(L" (Player goes first)");
	window.draw(text3);
	/*
	text3.setPosition(210, 1100);
	text3.setString(L"模式且玩家先手");
	window.draw(text3);*/

	//yjw部分
	sch[0].setPosition(250 + 75, 500 + 100);
	sch[1].setPosition(550 + 75, 500 + 100);
	sch[2].setPosition(250 + 75, 725 + 100);
	sch[3].setPosition(550 + 75, 725 + 100);
	window.draw(sch[0]);
	window.draw(sch[1]);
	window.draw(sch[2]);
	window.draw(sch[3]);

	switch (player1)
	{
	case(0):
		sInsure.setPosition(400 + 62 - 25, 650 + 29);
		break;
	case(1):
		sInsure.setPosition(700 + 62 - 25, 650 + 29);
		break;
	case(2):
		sInsure.setPosition(400 + 62 - 25, 875 + 29);
		break;
	case(3):
		sInsure.setPosition(700 + 62 - 25, 875 + 29);
		break;
	default:
		break;
	}
	if (player1 != -1)
	{
		window.draw(schoose1);
		if (ifsure1 == 0)
		{
			window.draw(sInsure);
		}
	}

	switch (player2)
	{
	case(0):
		sInsure.setPosition(400 + 62 - 25, 650 + 29);
		break;
	case(1):
		sInsure.setPosition(700 + 62 - 25, 650 + 29);
		break;
	case(2):
		sInsure.setPosition(400 + 62 - 25, 875 + 29);
		break;
	case(3):
		sInsure.setPosition(700 + 62 - 25, 875 + 29);
		break;
	default:
		break;
	}
	if (player2 != -1)
	{
		window.draw(schoose2);
		if (ifsure2 == 0) {
			window.draw(sInsure);
		}
	}
	//end
	window.display();
}

//绘制界面
void Draw()
{
	window.clear();

	spBackground.setPosition(0, 0);
	window.draw(spBackground);

	//绘制分数
	spScore.setPosition(65, 320);
	window.draw(spScore);
	spScore.setPosition(725, 320);
	window.draw(spScore);

	std::string scoreStr = std::to_string(score1);
	textScore.setPosition(130+6, 320);
	textScore.setString(scoreStr);
	window.draw(textScore);

	scoreStr = std::to_string(score2);
	textScore.setPosition(790+6, 320);
	textScore.setString(scoreStr);
	window.draw(textScore);

	spRestartGame.setPosition(190 + 126, 300 + 54);
	window.draw(spRestartGame);
	spExitGame.setPosition(470 + 126, 300 + 54);
	window.draw(spExitGame);


	//yjw部分
	//绘制头像和头像框
	sPlayer1Por.setPosition(50, 170);
	sPlayer2Por.setPosition(710, 170);
	window.draw(sPlayer1Por);
	window.draw(sPlayer2Por);
	sFramePor.setPosition(45, 163);
	window.draw(sFramePor);
	sFramePor.setPosition(705, 163);
	window.draw(sFramePor);
	if (Mode == 0) {
		spName1Mode0.setPosition(60, 115);
		window.draw(spName1Mode0);

		spName2Mode0.setPosition(720, 115);
		window.draw(spName2Mode0);
		if (turn == 0)
		{
			sShining.setPosition(50, 170);
		}
		else
		{
			sShining.setPosition(710, 170);
		}
		window.draw(sShining);
	}
	if (Mode == 1) {
		spName1Mode1.setPosition(65, 115);
		window.draw(spName1Mode1);
		spName2Mode1.setPosition(740, 115);
		window.draw(spName2Mode1);
	}
	//end

	//wyw部分
	//下棋
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (Box[i][j].isnew) {
				sFrame.setPosition(Box[i][j].x - 20, Box[i][j].y - 20);
				window.draw(sFrame);
				Box[i][j].isnew = false;
			}
			if (Box[i][j].isnew2) {
				sFrame2.setPosition(Box[i][j].x - 20, Box[i][j].y - 20);
				window.draw(sFrame2);
				//Box[i][j].isnew = false;
			}
			if (Box[i][j].value == 0)
			{
				sPlayer1.setPosition(Box[i][j].x - 20, Box[i][j].y - 20);
				window.draw(sPlayer1);
			}
			else if (Box[i][j].value == 1)
			{
				sPlayer2.setPosition(Box[i][j].x - 20, Box[i][j].y - 20);
				window.draw(sPlayer2);
			}
			/*printf("Box[%d,%d].isnew = %d\n", i, j, Box[i][j].isnew);
			printf("Box[%d,%d].value = %d\n", i, j, Box[i][j].value);*/
		}
	}
	//end

	//分出胜负后弹窗部分
	if (gameOver == true) {
		flagOverlay = 1;
		spEnd.setPosition(150, 150);
		window.draw(spEnd);
		spRestartGame.setPosition(220 + 104, 310 + 44);
		window.draw(spRestartGame);
		spRestartPage.setPosition(480 + 104, 310 + 44);
		window.draw(spRestartPage);
		text.setPosition(270, 200);
		if (Mode == 0) {
			if (win == 0)
				text.setString(L"Player1");
			else if (win == 1)
				text.setString(L"Player2");
		}
		else {
			if (win == 0)
				text.setString(L"Player");
			else if (win == 1)
			{
				text.setPosition(260, 200);
				text.setString(L"Computer");
			}
		}
		window.draw(text);
		if (score1 == 1 || score2 == 1) {
			textTip.setPosition(480-10, 395);
			textTip.setString(L"（Score will not be reset）");
			window.draw(textTip);
		}
	}
	//绘制元素
	window.display();
}

int main()
{

	while (window.isOpen() && flagClose == 0)
	{
		Initial();

		if (flagStart == 0) {
			while (window.isOpen())
			{

				{
					DrawFront();
					InputFront();
					if (flagStart == 1)
						break;
					Logic();
				}
			}
		}
		while (flagGame) {
			InitialGame();
			if (flagStart == 1) {
				{
					while (window.isOpen())
					{
						Input();
						Logic();
						isWIN();
						Draw();
						if (flagGoing == 1)
						{
							break;
						}
					}
				}

			}
		}
		music1.stop();
	}
	return 0;
}