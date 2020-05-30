# SPRESENSE_to_M5Stack
<img src="image/top.jpg" alt="topview" title="topview" width="280">

SPRESENSEをM-BUS経由でM5Stack とつなぐM5Stackの拡張モジュールです。
IO電圧1.8V<->

## 主な機能
- 標準ボトムとLoPoバッテリーを共用(バッテリ切断用の物理スイッチ付)
- M5StackとSPRESENSEはSerial2で接続。コマンドのやり取りで双方を制御可能
- 割り込み用にGPIOポートを接続、例えば「Deepsleepに入れたM5StackをSPRESENSEから起こす」という事が可能
- M5StackのポートからSPRESENSEのReset端子を制御可能
- 拡張モジュールボード上にSPRESENSEのI2CとADCのGrove互換コネクタを装備
- 接続はSPRESENSEメインボード上面の低背ピンヘッダなので、Hirose 100Pinコネクタを使用する拡張ボードと共存可能

### SPRESENSEを搭載した状態
<img src="image/top_w_spr.jpg" alt="top_w_spr" title="top_w_spr" width="280">

### ケースに装着した状態
<img src="image/IMG_20200529_192441.jpg" alt="withcase" title="withcase" width="280">

### シリアル経由でLCDに任意の文字表示(動画へのリンク)
[M5LCD](https://video.twimg.com/ext_tw_video/1266506357739409409/pu/vid/480x270/Aiy6zItiOErrypOG.mp4)
