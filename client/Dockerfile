# از ایمیج پایه برای C++ استفاده می‌کنیم
FROM gcc:latest

# نصب کتابخانه ZeroMQ و وابستگی‌ها
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libzmq3-dev \
    g++ \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

#نصب Conan Package Manager
RUN wget https://github.com/conan-io/conan/releases/download/2.8.0/conan-2.8.0-amd64.deb && dpkg -i conan-2.8.0-amd64.deb

# اضافه کردن فایل‌های پروژه
WORKDIR /srv/app
COPY . .
RUN conan profile detect && conan install . --build=missing -s compiler=gcc -s compiler.version=11 -s compiler.libcxx=libstdc++11 -s compiler.cppstd=17

# کامپایل برنامه C++
RUN cmake -G Ninja -DCMAKE_PREFIX_PATH=build/Release/generators  -DCMAKE_BUILD_TYPE=Release .

RUN cmake --build .

## اجرای کلاینت
CMD ["./zmq_client"]
#"{\"command_type\":\"os\",\"command_name\":\"ping\",\"parameters\":[\"google.com\",\"-c\",\"2\"]}"]
#["./zmq_client","{\"command_type\":\"compute\",\"expression\":\"( 2 + 2 ) * 10\"}"]