# What
Arduino nanoで熱帯魚の照明をリレー制御する

# How
Sleepでやってるだけ。nanoはWifiがないから時間が取れない。
```
#define CORRECT_PER_DAY 21L // 60*60*24 との誤差sec
```
結構長期測定して値を決めた。
