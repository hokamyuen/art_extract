# art_extract
从路由器编程器固件中提取ART
自动识别固件大小：
* 1M固件为固件最后16KB数据，输出时自动填充到64KB
* 2M以上固件为最后64KB数据

注：只适用于AR/QCA处理器的固件

# compile
```bash
git clone https://github.com/hokamyuen/art_extract.git
cd art_extract
gcc art_extract.c -o art_extract
```
# usage
```
./art_extract input.bin output.bin
```
