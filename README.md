# 🐶🥟 肉包子打狗專案 - Coin Catcher

## 一、主題說明
這個專案是一款利用 OpenGL 開發的獨立遊戲，遊戲目標是**接住掉落的麵包**，並以此獲取分數。遊戲的設計靈感源自於簡單易上手的街機風格遊戲。玩家控制的角色是一隻可愛的**黃金獵犬**。

## 二、遊戲內容
### 🎮 遊戲角色
- **主角：黃金獵犬 🐕**
  - 使用紋理繪製，角色的位置由 `updateCharacterPosition()` 函數更新，並在 `display()` 函數中顯示。

### 🥖 掉落物
- **麵包與葡萄 🍇**
  - 這些掉落物同樣是以紋理進行繪製，並由 `updateBun()` 和 `updateGrape()` 函數更新位置。
  - 掉落速率會隨著遊戲進行逐漸增加，每獲得五個麵包，難度將會提升。

### ⏫ 角色操作
- **移動 🕹️**
  - 玩家可以透過按下 `'a'` 和 `'d'` 鍵來左右移動角色。
- **跳躍 🦘**
  - 按下空格鍵可以讓角色跳躍，跳躍的高度和速度分別由 `jumpHeight` 和 `jumpSpeed` 控制。

### 🏆 得分系統
- **得分規則**
  - 玩家透過接住麵包來得分，分數會儲存在 `bunCount` 變量中，並以 `bunCountStr` 顯示在螢幕頂部。

### 💀 遊戲結束
- **失敗條件**
  - 若玩家接住了葡萄，遊戲即告失敗。失敗後會顯示遊戲結束畫面，並可以按 `'r'` 鍵重新開始。

### 畫面預覽：
![image](https://github.com/user-attachments/assets/02cbe196-0d42-4ede-84c1-734ee2c2cec7)
![image](https://github.com/user-attachments/assets/614f8fc1-de28-416a-87bb-36d27d934759)
![image](https://github.com/user-attachments/assets/0fb6e5e2-4832-422f-a978-f0e11a435f8a)


