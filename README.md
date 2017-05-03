# CPP_getFrame
## 摘要
本專案主要為提供一個快速取得指定間隔之影像的方法。

## Feature
+ 可指定輸出之間隔數量 (Can customize the number of interval frames.)
+ 可直接使用Console進行批次處理 (Can use console to batch processing.)
+ 只有輸出原始大小以及480x272之選項 (The output size supply the original size and 480x272.) 

## 使用方法
0. 你需要自行建立一個output資料夾於本程式旁邊 (First you have to create an output folder.)
1. 一般啟動，直接輸入影片檔案路徑，並輸入欲輸出資料夾名稱 (In normal, enter the video file path and output folder name.)
2. 於Console使用，請參照下方參數含意 (In console, please refer to the following infomation.)

       >getframe source [interval][-r][-f]
   
         source        影片路徑
         folder        輸出資料夾名稱
         interval      間隔數字，預設為15
         -r            是否需要壓縮至272p
         -f            是否要忽略程式暫停

## 執行環境
+ Visual studio 2013
+ VC++ 12
+ OpenCV 2.4.9 library