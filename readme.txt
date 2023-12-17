asio-1.24.0
mbedtls-3.4.1
libuv: 1.45.0
  cd libuv
  mkdir build
  cd build
  cmake .. -DLIBUV_BUILD_SHARED=0
  make
  https://github.com/libuv/libuv/releases
* glog-0.6.0
  * https://github.com/google/glog/releases
* libpng-1.6.40
  * https://github.com/glennrp/libpng/tags
* zlib-1.3
  * https://www.zlib.net/
* libspng-0.7.4
  * https://libspng.org/

* MP3 decoder 2023-12:
  * https://github.com/lieff/minimp3
* AAC/MP4 decoder:
  * faad2-2.11.1: https://github.com/knik0/faad2
* flac-1.4.3
  * https://ftp.osuosl.org/pub/xiph/releases/flac/
* libogg-1.3.5:
  * https://www.xiph.org/downloads/
