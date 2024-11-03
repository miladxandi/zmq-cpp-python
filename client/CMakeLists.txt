cmake_minimum_required(VERSION 3.25)
project(zmq_client)

# تنظیم C++ Standard
set(CMAKE_CXX_STANDARD 17)

# پیدا کردن پکیج zmqpp
find_package(crow REQUIRED)
find_package(asio REQUIRED)
find_package(zmqpp REQUIRED)
find_package(ZeroMQ REQUIRED)
find_package(libsodium REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)


# اضافه کردن اجرایی
add_executable(zmq_client main.cpp libraries/security.cpp libraries/command.cpp)

# لینک کردن کتابخانه‌ها
target_link_libraries(zmq_client asio::asio zmqpp::zmqpp libsodium::libsodium nlohmann_json::nlohmann_json)  # فرض بر اینه که از zmqpp و zmq استفاده می‌کنید
