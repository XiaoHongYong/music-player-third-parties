asio-1.24.0
mbedtls-3.4.1
libuv: 1.45.0
  cd libuv
  mkdir build
  cd build
  cmake .. -DLIBUV_BUILD_SHARED=0
  make
  https://github.com/libuv/libuv/releases
