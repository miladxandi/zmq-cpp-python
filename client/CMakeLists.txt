cmake_minimum_required(VERSION 3.25)
project(zmq_client)

# تنظیم C++ Standard
set(CMAKE_CXX_STANDARD 17)

# پیدا کردن پکیج zmqpp
find_package(zmqpp REQUIRED)
find_package(ZeroMQ REQUIRED)
find_package(libsodium REQUIRED)

# اضافه کردن اجرایی
add_executable(zmq_client main.cpp)

# لینک کردن کتابخانه‌ها
target_link_libraries(zmq_client zmqpp::zmqpp libsodium::libsodium)  # فرض بر اینه که از zmqpp و zmq استفاده می‌کنید
