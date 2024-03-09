#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
//#include <SFML/Audio.hpp>
#include "./Library/SOIL/include/SOIL.h"
#include "./Library/glut/glut.h"
int gameOverTimer = 0, gameOverDuration = 200;
#pragma comment( lib, "./Library/glut/glut32.lib" )
#pragma comment( lib, "./Library/SOIL/lib/SOIL.lib" )
GLuint texture;
GLuint characterTexture, bunTexture, boneTexture, grapeTexture, tombTexture;
unsigned char* image;
int width, height, channels;
int screenWidth = 1024, screenHeight = 768;
bool isGameOver = false;
float characterX = 0.0f;  // 角色的X坐標
float characterY = -0.5f;
float jumpHeight = 0.2f; // 跳躍高度
float jumpSpeed = 0.03f; // 跳躍速度
bool isJumping = false;  // 是否正在跳躍
float gravity = 0.0001f; // 重力加速度
float velocityY = 0.0f; // 垂直速度
bool isBunVisible = true, isGrapeVisible = true;
bool restartRequested;
int tmp;
int bunCount = 0;
std::string Difficulty = "    Difficulty:";
std::string bunCountStr = "Buns Count: ";
float myArray[] = { 0.5f, -0.2f, -0.3f, -0.1f, 0.7f,-0.6f , 0.4f };
struct Bun {
    float x;
    float y;
    float speed;

    Bun(float x, float y, float speed) : x(x), y(y), speed(speed) {}
};
struct Grape {
    float x;
    float y;
    float speed;

    Grape(float x, float y, float speed) : x(x), y(y), speed(speed) {}
};
Bun bun(0.0f, 1.0f, 0.015f);
Grape grape(0.5f, 1.0f, 0.02f);
// *********************************** glDrawPixels Version **************************************************
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f); // 设置文本颜色为白色
    glRasterPos2f(-0.95f, 0.9f); // 设置文本位置
    for (char c : bunCountStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // 使用字体绘制字符
    }
    glColor3f(1.0f, 1.0f, 1.0f); // 设置文本颜色为白色
    glRasterPos2f(-0.95f, 0.85f); // 设置文本位置
    for (char c : Difficulty) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // 使用字体绘制字符
    }
    glEnable(GL_TEXTURE_2D);
    if (!isGameOver) {
        glBindTexture(GL_TEXTURE_2D, characterTexture); // 繪製狗狗
        // 在绘制图像之前启用混合
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glPushMatrix();
        glTranslatef(characterX, characterY, 0.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.2f, -0.2f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(0.2f, -0.2f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(0.2f, 0.2f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.2f, 0.2f);
        glEnd();
        glPopMatrix();
    }
    else {
        std::string word = "Play again? press r";
        glColor3f(1.0f, 1.0f, 1.0f); // 设置文本颜色为白色
        glRasterPos2f(-0.25f, 0.8f); // 设置文本位置
        for (char c : word) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // 使用字体绘制字符
        }

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture(GL_TEXTURE_2D, tombTexture);
        glPushMatrix();
        glTranslatef(characterX, characterY, 0.0f); // 设置墓碑位置，通常在狗狗位置上
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.2f, -0.2f); // 左下角
        glTexCoord2f(1.0f, 0.0f); glVertex2f(0.2f, -0.2f);  // 右下角
        glTexCoord2f(1.0f, 1.0f); glVertex2f(0.2f, 0.4f);   // 右上角
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.2f, 0.4f);  // 左上角
        glEnd();
        glPopMatrix();
    }
    if (!isGameOver) {
        if (isBunVisible) {
            glBindTexture(GL_TEXTURE_2D, bunTexture);
            // 繪製 bun
            glPushMatrix();
            glTranslatef(bun.x, bun.y, 0.0f);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.15f, -0.15f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(0.15f, -0.15f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(0.15f, 0.15f);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.15f, 0.15f);
            glEnd();
            glPopMatrix();
        }
        else if (isGrapeVisible) {
            glBindTexture(GL_TEXTURE_2D, grapeTexture);
            // 繪製 grape
            glPushMatrix();
            glTranslatef(grape.x, grape.y, 1.0f);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.11f, -0.11f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(0.11f, -0.11f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(0.11f, 0.11f);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.11f, 0.11f);
            glEnd();
            glPopMatrix();
        }
    }


    /*
    glRasterPos2i(0, height);  // Set the position to the bottom-left corner
    if (channels == 3) {
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else if (channels == 4) {
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    */
    glPopMatrix();
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);  // 解綁紋理
    glDisable(GL_TEXTURE_2D);  // 停用紋理映射
    glutSwapBuffers();
}
void flipImage(unsigned char* image, int width, int height, int channels) {
    int rowSize = width * channels;
    unsigned char* tempRow = (unsigned char*)malloc(rowSize);

    for (int y = 0; y < height / 2; ++y) {
        memcpy(tempRow, image + y * rowSize, rowSize);
        memcpy(image + y * rowSize, image + (height - 1 - y) * rowSize, rowSize);
        memcpy(image + (height - 1 - y) * rowSize, tempRow, rowSize);
    }

    free(tempRow);
}
void loadTexture() {
    // 載入紋理圖像
    characterTexture = SOIL_load_OGL_texture(
        "../Images/Golden-Retriever.png",  // 圖像文件的路徑
        SOIL_LOAD_AUTO,           // 自動檢測圖像的格式
        SOIL_CREATE_NEW_ID,       // 創建新的紋理ID
        SOIL_FLAG_INVERT_Y        // 上下翻轉紋理（如果需要）
    );
    bunTexture = SOIL_load_OGL_texture(
        "../Images/meat_bun.png",  // 圖像文件的路徑
        SOIL_LOAD_AUTO,           // 自動檢測圖像的格式
        SOIL_CREATE_NEW_ID,       // 創建新的紋理ID
        SOIL_FLAG_INVERT_Y        // 上下翻轉紋理（如果需要）
    );
    boneTexture = SOIL_load_OGL_texture(
        "../Images/Bone.png",  // 圖像文件的路徑
        SOIL_LOAD_AUTO,           // 自動檢測圖像的格式
        SOIL_CREATE_NEW_ID,       // 創建新的紋理ID
        SOIL_FLAG_INVERT_Y        // 上下翻轉紋理（如果需要）
    );
    grapeTexture = SOIL_load_OGL_texture(
        "../Images/Grape.png",  // 圖像文件的路徑
        SOIL_LOAD_AUTO,           // 自動檢測圖像的格式
        SOIL_CREATE_NEW_ID,       // 創建新的紋理ID
        SOIL_FLAG_INVERT_Y        // 上下翻轉紋理（如果需要）
    );
    tombTexture = SOIL_load_OGL_texture(
        "../Images/tomb.png",  // 墓碑纹理的路径
        SOIL_LOAD_AUTO,           // 自动检测图像格式
        SOIL_CREATE_NEW_ID,       // 创建新的纹理ID
        SOIL_FLAG_INVERT_Y        // 上下翻转纹理（如果需要）
    );
    if (!characterTexture||!grapeTexture) {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        exit(-1);
    }
}
void jump() {
    if (!isJumping) {
        isJumping = true;
    }
}
void updateCharacterPosition() {
    if (isJumping) {
        characterY += jumpSpeed; // 向上移動
        if (characterY >= jumpHeight) {
            isJumping = false;
        }
    }
    else {
        characterY -= jumpSpeed; // 向下移動
        if (characterY <=-0.5f) {
            characterY =-0.5f; // 回到原始Y座標
        }
    }
}
void updateGrape() {
    velocityY += gravity;
    grape.y -= velocityY; // 更新 bun 的 y 坐標，使其下降
    if (grape.y < -1.2f) {
        grape.x = myArray[(tmp++) % 7];
        grape.y = 1.0f;
        velocityY = 0.0f;
        if (tmp % 3 == 0) {
            isGrapeVisible = false;
            bun.y = 1.0f;
            isBunVisible = true;
        }        
    }
}
void updateBun() {
    //std::cout << "hello";
    velocityY += gravity;
    bun.y -= velocityY; // 更新 bun 的 y 坐標，使其下降
    if (bun.y < -1.2f) {
        bun.x = myArray[(tmp++) % 7];
        bun.y = 1.0f; // 如果 bun 超出視窗，重新初始化它
        velocityY = 0.0f;
        if (tmp % 3==0) {
            isBunVisible = false;
            grape.y = 1.0f;
            isGrapeVisible = true;
        }
    }
}
void update(int value) {
    gravity = 0.0005f + bunCount / 5 * 0.0005f;
    if (isGameOver&&!restartRequested) {
        glColor3f(1.0f, 1.0f, 1.0f); // 设置文本颜色为白色
        glRasterPos2f(0.0f, 0.0f); // 设置文本位置
        
        if (gameOverTimer < gameOverDuration) {
            gameOverTimer++;
        }
        else {
            exit(0);
        }
    }
    else {
        Difficulty = "Difficulty: " + std::to_string(bunCount / 5);
        updateBun();
        updateGrape();
        updateCharacterPosition();
            if (isBunVisible && bun.x >= characterX - 0.2f && bun.x <= characterX + 0.2f && grape.y >= -0.5f - 0.1f && grape.y <= -0.5f + 0.1f) {
                isBunVisible = false; // 包子被吃掉
                bunCountStr = "Buns count: " + std::to_string(++bunCount) + "\n";
                tmp = rand() % 7;
                grape.x = myArray[tmp];
                grape.y = 1.0f;
            }
            else if (isGrapeVisible && grape.x >= characterX - 0.2f && grape.x <= characterX + 0.2f && grape.y >= -0.5f - 0.1f && grape.y <= -0.5f + 0.1f) {
                isGrapeVisible = false; // 葡萄被吃掉
                isGameOver = 1;
                //std::cout << "Game Over! You ate a grape and died!" << std::endl;
                //exit(0); // 游戏结束
            }
    
    }
    display();
    glutTimerFunc(16, update, 0); // 設定下一次更新的時間間隔
}
void init() {
    image = SOIL_load_image("../Images/Mario_NSMBW.png", &width, &height, &channels, SOIL_LOAD_AUTO);

    if (!image) {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        exit(-1);
    }

    flipImage(image, width, height, channels);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}



void keyboard(unsigned char key, int x, int y) {
    if (!isGameOver) {
        switch (key) {
        case 'a':
            if (characterX - 0.15f > -1.0f) { // 左移时检查是否超出左边界
                characterX -= 0.15f;  // 左移
            }
            break;
        case 'd':
            if (characterX + 0.15f < 1.0f) { // 右移时检查是否超出右边界
                characterX += 0.15f;  // 右移
            }
            break;
        case ' ':
            jump(); // 空白鍵觸發跳躍
            break;
        default:
            break;
        }
    }
    else {
        if (key == 'r' || key == 'R') {
            // 玩家按下 'r' 键，请求重新开始游戏
            restartRequested = true;
            isGameOver = false; // 或者执行其他重置游戏状态的操作
            bunCount = 0;
            Difficulty = "    Difficulty:";
            bunCountStr = "Buns Count: ";
            display();
        }
    }
    glutPostRedisplay();
}

void cleanup() {
    SOIL_free_image_data(image);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("Starving Golden Retriever!!!");
    //init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    loadTexture();
    glutTimerFunc(0, update, 0); // 啟動定時器
    // atexit(cleanup);  // Register a cleanup function to free image data on exit
    glutMainLoop();

    return 0;
}

// 