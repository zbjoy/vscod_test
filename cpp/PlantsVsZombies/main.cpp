#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
//#include <windows.h>
#include <mmsystem.h>
//#pragma comment(lib, "winmm.lib")
#include "tools.h"
#include "vector2.h"

#define WIN_WIDTH 900
#define WIN_HEIGHT 600

enum 
{
    WAN_DOU, //豌豆
    XIANG_RI_KUI, //向日葵
    ZHI_WU_COUNT //植物数量
};

/*
*开发日志
*1.创建新项目
*2.导入素材
*3.实现初始场景
*4.实现游戏顶部的工具栏
*5.*/

IMAGE imgBg; //表示背景图片
IMAGE imgBar; 
IMAGE imgCards[ZHI_WU_COUNT];
IMAGE* imgPlants[ZHI_WU_COUNT][20];

int curX, curY; //当前选中的植物， 在移动过程中的位置
int curPlant; // 0:没有选择  

struct zhiwu
{
    int type; //0:没有植物
    int frameIndex; //序列帧的序号

    bool catched; //是否被僵尸逮住
    int deadTimer; //死亡记数器

    int timer;
    int x, y;
};

struct zhiwu map[3][9];

enum
{
    SUNSHINE_DOWN,
    SUNSHINE_GROUND,
    SUNSHINE_COLLECT,
    SUNSHINE_PRODUCT
};

struct sunshineBall
{
    int x, y; //阳光球在飘落过程中的坐标位置
    int frameIndex; //当前显示的图片帧的序号
    int destY; //飘落的目标位置 
    bool used; //是否在使用
    int timer; //定时器

    float xOff;
    float yOff;

    float t; //贝塞尔曲线的时间点 0 - 1
    vector2 p1, p2, p3, p4; //四个控制点
    vector2 pCur; //当前时刻阳光球的位置
    float speed; //阳光球的速度
    int status;
};

//阳光池
struct sunshineBall balls[10];
IMAGE imgSunshineBall[29];
int sunshine;

struct zm
{
    int x, y;
    int frameIndex;
    bool uesd;
    int speed;
    int row;
    int blood;
    bool dead;
    bool eating; //或者使用状态机  verilog
};

struct zm zms[10];
IMAGE imgZM[22];
IMAGE imgZMDead[20];
IMAGE imgZMEat[21];

//子弹
struct bullet
{
    int x, y;
    int row;
    bool used;
    int speed;
    bool blast; //是否发声爆炸
    int frameIndex; //帧序号
};

struct bullet bullets[30];
IMAGE imgBulletNormal;
IMAGE imgBulletBlast[4];

bool fileExist(const char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        return false;
    }
    else
    {
        fclose(fp);
        return true;
    }
}

void startUI()
{
    IMAGE imgBg, imgMenu1, imgMenu2;
    loadimage(&imgBg, "res/menu.png");
    loadimage(&imgMenu1, "res/menu1.png");
    loadimage(&imgMenu2, "res/menu2.png");
    int flag = 0;

    while(1)
    {
        BeginBatchDraw();
        putimagePNG(0, 0, &imgBg);
        putimagePNG(474, 75, flag ? &imgMenu2 : &imgMenu1);

        ExMessage msg;
        if(peekmessage(&msg))
        {
            if(msg.x > 474 && msg.x < 474 + 331 && msg.y >75 && msg.y < 75 + 140)
            {
                flag = 1;
            }
            else
            {
                flag = 0;
            }
            
            if(msg.message == WM_LBUTTONUP && flag == 1)
            {
                flag = 0;
                
                return;
            }
        }
        EndBatchDraw();
    }
}

//加载背景图片
void gameInit()
{
    loadimage(&imgBg, "res/bg.jpg");

    //loadimage(&imgBar, "res/bar.png", 650, 100);
    loadimage(&imgBar, "res/bar5.png");

    //指针清零
    memset(imgPlants, 0, sizeof(imgPlants));
    memset(map, 0, sizeof(map));

    //初始化植物卡牌
    char name[64];
    for(int i = 0; i < ZHI_WU_COUNT; i++)
    {
        // 生成植物卡牌的文件名
        sprintf(name, "res/Cards/card_%d.png", i + 1);
        loadimage(&imgCards[i], name);

        for(int j = 0; j < 20; j++)
        {
            sprintf(name, "res/zhiwu/%d/%d.png", i, j + 1);
            //判断文件是否存在
            if(fileExist(name))
            {
                imgPlants[i][j] = new IMAGE;
                loadimage(imgPlants[i][j], name);
            }
            else
            {
                break;
            }
        }
    }


    curPlant = 0;

    sunshine = 50;

    memset(balls, 0, sizeof(balls));
    for(int i = 0; i < 29; i++)
    {
        sprintf(name, "res/sunshine/%d.png", i + 1);
        loadimage(&imgSunshineBall[i], name);
    }

    //配置随机种子
    srand(time(NULL));

    //创建游戏窗口
    initgraph(WIN_WIDTH, WIN_HEIGHT, 1);

    //设置字体
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = 30;
    f.lfWeight = 15;
    strcpy(f.lfFaceName, "Segoe UI Black");
    f.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&f);
    setbkmode(TRANSPARENT);
    setcolor(BLACK);

    //初始化僵尸
    memset(zms, 0, sizeof(zms));
    for(int i = 0; i < 22; i++)
    {
        sprintf(name, "res/zm/%d.png", i + 1);
        loadimage(&imgZM[i], name);
    }

    loadimage(&imgBulletNormal, "res/bullets/bullet_normal.png");
    memset(bullets, 0, sizeof(bullets));

    //初始化豌豆子弹帧图片数组
    loadimage(&imgBulletBlast[3], "res/bullets/bullet_blast.png");
    for(int i = 0; i < 3; i ++)
    {
        float k = (i + 1) * 0.2;
        loadimage(&imgBulletBlast[i], "res/bullets/bullet_blast.png", imgBulletBlast[3].getwidth() * k, imgBulletBlast[3].getheight() * k, true);

    }

    for(int i = 0; i < 20; i++)
    {
        sprintf(name, "res/zm_dead/%d.png", i + 1);
        loadimage(&imgZMDead[i], name);
    }

    //僵尸吃植物图片帧
    for(int i = 0; i < 21; i++)
    {
        sprintf(name, "res/zm_eat/%d.png", i +1);
        loadimage(&imgZMEat[i], name);
    }
}

void drawZM()
{
    int zmCount = sizeof(zms) / sizeof(zms[0]);
    for(int i = 0; i < zmCount; i++)
    {
        // if(zms[i].uesd)
        // {
            
        //     putimagePNG(zms[i].x, zms[i].y - imgZM[zms[i].frameIndex].getheight(), &imgZM[zms[i].frameIndex]);
        // }
        if(zms[i].uesd)
        {
            IMAGE* img = (zms[i].dead) ? imgZMDead : ((zms[i].eating) ? imgZMEat : imgZM);
            // IMAGE* img;
            // if(zms[i].dead)
            // {
            //     img = imgZMDead;
            // }
            // else if(zms[i].eating)
            // {
            //     img = imgZMEat;
            // }
            // else
            // {
            //     img = imgZM;
            // }

            img += zms[i].frameIndex;

            putimagePNG(zms[i].x, zms[i].y - img->getheight(), img);
        }


    }
}

void drawSunshine()
{
    int ballMax = sizeof(balls) / sizeof(balls[0]);
    for(int i = 0; i < ballMax; i++)
    {
        if(balls[i].used)
        {
            //putimagePNG(balls[i].x, balls[i].y, &imgSunshineBall[balls[i].frameIndex]);
            putimagePNG(balls[i].pCur.x, balls[i].pCur.y, &imgSunshineBall[balls[i].frameIndex]);
        }

    }
}

void drawCards()
{
    for(int i = 0; i < ZHI_WU_COUNT; i++)
    {
        int x = 338 + i * 64;
        putimagePNG(x, 6, &imgCards[i]);
    }    
}

void drawPlants()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(map[i][j].type > 0)
            {
                // int x = 256 + j * 81;
                // int y = 179 + i * 102.6 + 13;
                int plantType = map[i][j].type - 1;
                int index = map[i][j].frameIndex;
                //if(imgPlants[plantType][index])
                //putimagePNG(x, y, imgPlants[plantType][index]);
                putimagePNG(map[i][j].x, map[i][j].y, imgPlants[plantType][index]);
            }
        }
    }

    //渲染拖动过程
    if(curPlant > 0)
    {
        putimagePNG(curX - imgPlants[curPlant - 1][0]->getwidth() / 2
                , curY - imgPlants[curPlant - 1][0]->getheight() / 2
                , imgPlants[curPlant - 1][0]);
    }

}

void drawBullets()
{
    int bulletsMax = sizeof(bullets) / sizeof(bullets[0]);
    for(int i = 0; i < bulletsMax; i++)
    {
        if(!bullets[i].used)
        {
            continue;
        }

        if(bullets[i].blast)
        {
            IMAGE* img = &imgBulletBlast[bullets[i].frameIndex];
            putimagePNG(bullets[i].x, bullets[i].y, img);
        }
        else// if(bullets[i].used)
        {
            putimagePNG(bullets[i].x, bullets[i].y, &imgBulletNormal);
        }
    }

    char scoreText[8];
    sprintf(scoreText, "%d", sunshine);
    outtextxy(278, 67, scoreText);
}

//场景渲染
void updateWindow()
{
    BeginBatchDraw();

    putimage(0, 0, &imgBg);

    putimagePNG(250, 0, &imgBar);

    //植物渲染
    drawCards();

    drawPlants();

    drawSunshine();

    drawZM();

    drawBullets();

    EndBatchDraw();
}

void collectSunshine(ExMessage* msg)
{
    int ballMax = sizeof(balls) / sizeof(balls[0]);
    for(int i = 0; i < ballMax; i++)
    {
        if(balls[i].used)
        {
            // int x = balls[i].x;
            // int y = balls[i].y;
            int x = balls[i].pCur.x;
            int y = balls[i].pCur.y;
            if(msg->x > x && msg->x < x + imgSunshineBall[0].getwidth() && msg->y > y && msg->y < y + imgSunshineBall[0].getheight())
            {
                //balls[i].used = false;
                balls[i].status = SUNSHINE_COLLECT;
                //sunshine += 25;
                mciSendString("play res/sunshine.mp3", 0, 0, 0);
                //PlaySound("res/sunshine.mp3"); //需要mav格式
                //设置阳光偏移量
                // float destY = 0;
                // float destX = 262;
                // float angle = atan((y - destY) / (x - destX));
                // balls[i].xOff = 7 * cos(angle);
                // balls[i].yOff = 7 * sin(angle);

                balls[i].p1 = balls[i].pCur;
                balls[i].p4 = vector2(262, 0);
                balls[i].t = 0;
                float distance = dis(balls[i].p1 - balls[i].p4);
                float off = 8; //每次移动的像素
                balls[i].speed = 1.0 / (distance / off);
                break;
            }
        }
    }
}

void userClick()
{
    ExMessage msg;
    static int status = 0;
    if(peekmessage(&msg))
    {
        if(msg.message == WM_LBUTTONDOWN)
        {
            if(msg.x > 338 && msg.x < 338 + 65 * ZHI_WU_COUNT && msg.y > 6 && msg.y < 100)
            {
                int index = (msg.x - 338) / 65;
                printf("%d\n", index);
                status = 1;
                curPlant = index + 1;
            }
            else
            {
                collectSunshine(&msg);
            }
        }
        else if(msg.message == WM_MOUSEMOVE && status == 1)
        {
            curX = msg.x;
            curY = msg.y;
        }
        else if(msg.message == WM_LBUTTONUP)
        {
            int row = (msg.y - 179) / 102.6;
            int col = (msg.x - 256) / 81;
            //printf("%d, %d\n", row, col);

            if(map[row][col].type == 0)
            {
                map[row][col].type = curPlant;
                map[row][col].frameIndex = 0;

                map[row][col].x = 256 + col * 81; //181有问题
                map[row][col].y = 179 + row * 102 + 14;
            }


            status = 0;
            curPlant = 0;
        }
    }
}

void createSunshine()
{
    static int count = 0;
    static int fre = 200;
    count += 4;
    if(count >= fre)
    {
        count = 0;
        fre = 200 + rand() % 201; //每两百到四百次创建一个阳光
        //从阳光池中取出一个可以使用的
        int ballMax = sizeof(balls) / sizeof(balls[0]);
        int i = 0;
        for(i = 0; i < ballMax && balls[i].used; i++);
        if(i >= ballMax)
        {
            return;
        }

        balls[i].used = true;
        balls[i].frameIndex = 0;
        // balls[i].x = 260 + rand() % (641 - imgSunshineBall[0].getwidth()); //阳光生成范围 260-900
        // balls[i].y = 60;
        //balls[i].destY = 200 + (rand() % 4) * 90;
        balls[i].timer = 0;
        // balls[i].xOff = 0;
        // balls[i].yOff = 0;

        balls[i].status = SUNSHINE_DOWN;
        balls[i].t = 0;
        balls[i].p1 = vector2(260 + rand() % (641 - imgSunshineBall[0].getwidth()), 60);
        balls[i].p4 = vector2(balls[i].p1.x, 200 + (rand() % 4) * 90);
        int off = 2;
        float distance = balls[i].p4.y - balls[i].p1.y;
        balls[i].speed = 1.0 / (distance / off);
    }
    //生产阳光
    int ballMax = sizeof(balls) / sizeof(balls[0]);
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(map[i][j].type == XIANG_RI_KUI + 1)
            {
                map[i][j].timer++;
                if(map[i][j].timer > 200)
                {
                    map[i][j].timer = 0;

                    int k = 0;
                    for(; k < ballMax && balls[k].used; k++);
                    if(k >= ballMax)
                    {
                        return;
                    }

                    balls[k].used = true;
                    balls[k].p1 = vector2(map[i][j].x, map[i][j].y);
                    int w = (50 + rand() % 51) * (rand() % 2 ? 1 : -1); 
                    balls[k].p4 = vector2(map[i][j].x + w, map[i][j].y + imgPlants[XIANG_RI_KUI][0]->getheight() - imgSunshineBall[0].getheight());
                    balls[k].p2 = vector2(balls[k].p1.x + w * 0.3, balls[k].p1.y - 100);
                    balls[k].p3 = vector2(balls[k].p1.x + w * 0.7, balls[k].p1.y - 100);
                    balls[k].status = SUNSHINE_PRODUCT;
                    balls[k].speed = 0.05;
                    balls[k].t = 0;
                }
            }
        }
    }
}

void updateSunshine()
{
    int ballMax = sizeof(balls) / sizeof(balls[0]);
    for(int i = 0; i < ballMax; i++)
    {
        if(balls[i].used)
        {
            balls[i].frameIndex = (balls[i].frameIndex + 1) % 29;
            if(balls[i].status == SUNSHINE_DOWN)
            {
                struct sunshineBall* sun = &balls[i];
                sun->t += sun->speed;
                sun->pCur = sun->p1 + sun->t * (sun->p4 - sun->p1);
                if(sun->t >= 1)
                {
                    sun->status = SUNSHINE_GROUND;
                    sun->timer = 0;
                }
            }
            else if(balls[i].status == SUNSHINE_GROUND)
            {
                balls[i].timer++;
                if(balls[i].timer > 100)
                {
                    balls[i].used = false;
                    balls[i].timer = 0;
                }
            }
            else if(balls[i].status == SUNSHINE_COLLECT)
            {
                struct sunshineBall* sun = &balls[i];
                sun->t += sun->speed;
                sun->pCur = sun->p1 + sun->t * (sun->p4 - sun->p1);
                if(sun->t > 1)
                {
                    sun->used = false;
                    sunshine += 25;
                }
            }
            else if(balls[i].status == SUNSHINE_PRODUCT)
            {
                struct sunshineBall* sun = &balls[i];
                sun->t += sun->speed;
                sun->pCur = calcBezierPoint(sun->t, sun->p1, sun->p2, sun->p3, sun->p4);
                if(sun->t > 1)
                {
                    sun->status = SUNSHINE_GROUND;
                    sun->timer = 0;
                }
            }
            

            // balls[i].frameIndex = (balls[i].frameIndex + 1) % 29;
           
            // if(balls[i].timer == 0)
            // balls[i].y += 3;
            
            // if(balls[i].y >= balls[i].destY)
            // {
            //     //balls[i].used = false;
            //     balls[i].timer++;
            //     if(balls[i].timer > 50)
            //     {
            //         balls[i].used = false;
            //     }
            // }
            
            // if(balls[i].xOff)
            // {
            //     float destY = 0;
            //     float destX = 262;
            //     float angle = atan((balls[i].y - destY) / (balls[i].x - destX));
            //     balls[i].xOff = 7 * cos(angle);
            //     balls[i].yOff = 7 * sin(angle);
            //     balls[i].x -= balls[i].xOff;
            //     balls[i].y -= balls[i].yOff;
            //     if(balls[i].y < 0 || balls[i].x < 262 - imgSunshineBall[0].getwidth())
            //     {
            //         balls[i].xOff = 0;
            //         balls[i].yOff = 0;
            //         sunshine += 25;
            //         balls[i].used = false;
            //     }
            // }
        }
        
    }
}

void createZM()
{
    static int zmFre = 30;
    static int count = 0;
    count++;
    if(count > zmFre)
    {
        count = 0;
        zmFre = rand() % 201 + 300;
        int i = 0;
        int zmMax = sizeof(zms) / sizeof(zms[0]);
        for(i = 0; i < zmMax && zms[i].uesd; i++);
        //{
        if(i < zmMax)
        {
            memset(&zms[i], 0, sizeof(zms[i])); //顺带把eating 设为 false
            zms[i].uesd = true;
            zms[i].x = WIN_WIDTH;
            zms[i].row = rand() % 3; // 0 - 2
            zms[i].y = 172 + (zms[i].row + 1) * 100;
            zms[i].speed = 2;
            zms[i].blood = 100;
            zms[i].dead = false;
        }
        //}
    }
}

void updateZM()
{
    int zmMax = sizeof(zms) / sizeof(zms[0]);

    static int count = 0;
    count++;

    if(count > 2)
    {
        count = 0;
        // 更新僵尸位置
        for(int i = 0; i < zmMax; i++)
        {
            if(zms[i].uesd)
            {
                zms[i].x -= zms[i].speed;
                if(zms[i].dead)
                {
                    zms[i].frameIndex++;
                    if(zms[i].frameIndex >= 20)
                    {
                        zms[i].uesd = false;
                    }

                }
                else if (zms[i].eating)
                {
                    zms[i].frameIndex = (zms[i].frameIndex + 1) % 21;
                }
                
                else
                {
                    zms[i].frameIndex = (zms[i].frameIndex + 1) % 22;
                }

                if(zms[i].x < 170)
                {
                    printf("Game over\n");
                    MessageBox(NULL, "over", "over", 0);
                    exit(0);
                }
            }
        }
    }
    
}

void shoot()
{
    int direction[3] = { 0 };
    int zmCount = sizeof(zms) / sizeof(zms[0]);
    //int dangerX = WIN_WIDTH - imgZM[0].getwidth();
    int dangerX = WIN_WIDTH;
    for(int i = 0; i < zmCount; i++)
    {
        if(zms[i].uesd && zms[i].x < dangerX)
        {
            direction[zms[i].row] = 1;
        }
    }
    int bulletCount = sizeof(bullets) / sizeof(bullets[0]);
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(map[i][j].type == WAN_DOU + 1 && direction[i])
            {
                static int count = 0;
                count++;
                if(count > 35)
                {
                    count = 0;

                    int k = 0;
                    for(; k < bulletCount && bullets[k].used; k++);
                    if(k < bulletCount)
                    {
                        bullets[k].used = true;
                        bullets[k].row = i;
                        bullets[k].speed = 6;

                        bullets[k].blast = false;
                        bullets[k].frameIndex = 0;

                        int zwX = 256 + j * 81;
                        int zmY = 179 + i * 102 + 14;
                        bullets[k].x = zwX + imgPlants[map[i][j].type - 1][0]->getwidth() - 10;
                        bullets[k].y = zmY + 7;
                    }
                }
            }
        }
    }
}

void checkBulletToZm()
{
    int bulletCount = sizeof(bullets) / sizeof(bullets[0]);
    int zombiesCount = sizeof(zms) / sizeof(zms[0]);
    for(int i = 0; i < bulletCount; i++)
    {
        if(bullets[i].used == false || bullets[i].blast)
        {
            continue;
        }

        for(int j = 0; j < zombiesCount; j++)
        {
            if(zms[j].uesd == false)
            {
                continue;
            }

            int x1 = zms[j].x + 80;
            int x2 = zms[j].x + 110;
            int x = bullets[i].x;
            if(x > x1 && x < x2 && bullets[i].row == zms[j].row && !zms[j].dead)
            {
                zms[j].blood -= 10;
                bullets[i].blast = true;
                bullets[i].speed = 0;

                if(zms[j].blood <= 0)
                {
                    zms[j].dead = true;
                    zms[j].speed = 0;
                    zms[j].frameIndex = 0;
                }
                break;
            }
        }
    }
}

void checkZmToPlant()
{
    int zmCount = sizeof(zms) / sizeof(zms[0]);
    for(int i = 0; i < zmCount; i++)
    {
        if(zms[i].dead)
        {
            continue;
        }
        int row = zms[i].row;
        for(int k = 0; k < 9; k++)
        {
            if(map[row][k].type == 0)
            {
                continue;
            }
            else
            {
                int plantX = 256 + k * 81;
                int x1 = plantX + 10;
                int x2 = plantX + 60;
                int x3 = zms[i].x + 80;
                if(x3 > x1 && x3 < x2)
                {
                    //if(map[row][k].catched = true)时为什么只是一闪一闪但植物不的type不会为0
                    if(map[row][k].catched == true)
                    {
                        //zms[i].frameIndex++;
                        //static int time = 0;
                        //time++;
                        //if(time >= 2)
                        //{
                            map[row][k].deadTimer++;
                            //time = 0;
                        //}

                        if(map[row][k].deadTimer > 100)
                        {
                            map[row][k].deadTimer = 0;
                            map[row][k].type = 0;
                            zms[i].eating = false;
                            zms[i].frameIndex = 0;
                            zms[i].speed = 2;
                        }
                    }
                    else
                    {
                        map[row][k].catched = true;
                        map[row][k].deadTimer = 0;
                        zms[i].eating = true;
                        zms[i].speed = 0;
                        zms[i].frameIndex = 0;
                    }
                }
            }
            
        }
    }
}

void collisionCheck()
{
    checkBulletToZm(); //子弹对僵尸的碰撞检测
    checkZmToPlant(); //僵尸对植物的碰撞检测
}

void updateBullet()
{
    int bulletCount = sizeof(bullets) / sizeof(bullets[0]);
    for(int i = 0; i < bulletCount; i++)
    {
        if(bullets[i].used)
        {
            bullets[i].x += bullets[i].speed;
            if(bullets[i].x > WIN_WIDTH)
            {
                bullets[i].used = false;
            }
            
            if(bullets[i].blast)
            {
                bullets[i].frameIndex++;
                if(bullets[i].frameIndex >= 4)
                {
                    bullets[i].used = false;
                }
            }
        }
    }
}

void updatePlant()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(map[i][j].type > 0)
            {
                map[i][j].frameIndex++;
                if(imgPlants[map[i][j].type - 1][map[i][j].frameIndex] == NULL)
                {
                    map[i][j].frameIndex = 0;
                }
            }
        }
    }
}

void updateGame()
{
    updatePlant(); //改变植物

    createSunshine(); //创建阳光
    updateSunshine(); //更新阳光状态

    createZM(); //创建僵尸
    updateZM(); //更新僵尸状态

    shoot(); //发射子弹
    updateBullet(); //更新子弹

    collisionCheck(); //（豌豆）碰撞检测 新加了僵尸检测
}

int main()
{
    gameInit();

    startUI();

    int timer = 0;
    bool flag = true;
    while(1)
    {
        userClick();
        timer += getDelay();
        if(timer > 80)
        {
            flag = true;
            timer = 0;
        }

        if(flag)
        {
            updateWindow();
            updateGame();
            flag = false;
        }


        //Sleep(40);//帧等待
    }


    system("pause");

    return 0;
}