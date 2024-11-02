#include "libraries/crow/crow_all.h"
#include "libraries/command.hpp"
#include "libraries/security.hpp"
#include "libraries/nlohmann/json.hpp"
#include <zmqpp/zmqpp.hpp>
#include <fstream>
#include <ctime>

using json = nlohmann::json;
using namespace std;

// تابع برای دریافت زمان فعلی و اضافه کردن آن به لاگ‌ها
string get_current_time() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string time_str(dt);
    time_str.pop_back(); // حذف کاراکتر newline
    return time_str;
}
int main() {
    crow::SimpleApp app;

    ofstream logFile("client.log", ios_base::app);  // باز کردن فایل لاگ در حالت append
    const string endpoint = "tcp://server:5510";

    CROW_ROUTE(app, "/execute").methods("POST"_method)([&logFile,endpoint](const crow::request& req) {

        // پارس کردن JSON از درخواست ورودی
        auto req_json = json::parse(req.body, nullptr, false);

        // بررسی اینکه آیا داده ورودی json است یا خیر
        if (req_json.is_discarded()) {
            logFile << get_current_time() << " - Error: Invalid JSON format" << endl;
            return crow::response(400, "Invalid JSON format");
        }

        // تبدیل JSON به کلاس Command
        string input = req.body;
        Command command(input);

        // بررسی امنیت دستور
        Security sec;
        sec.command = command.expression.value_or("");

        if (!sec.Check()) {
            logFile << get_current_time() << " - Dangerous command detected! Execution denied." << endl;
            return crow::response(403, "Dangerous command detected! Execution denied.");
        }

        logFile << get_current_time() << " - Starting client..." << endl;
        cout << "Starting client..." << endl;

        logFile << get_current_time() << " - Input command: " << input << endl;
        cout << "Input command: " << input << endl;

        // ایجاد اشیا مربوط به اتصال و ارتباط با zmq
        zmqpp::context context;
        zmqpp::socket_type type = zmqpp::socket_type::req;
        zmqpp::socket socket(context, type);


        logFile << get_current_time() << " - Connecting to server at " << endpoint << "..." << endl;
        cout << "Connecting to server…" << endl;
        socket.connect(endpoint);


        logFile << get_current_time() << " - Command is safe. Executing command..." << endl;
        zmqpp::message message;
        message << input;
        socket.send(message);
        logFile << get_current_time() << " - Message sent to server." << endl;
        cout << "Message sent to server." << endl;

        // دریافت پاسخ از سرور
        string buffer;
        socket.receive(buffer);

        logFile << get_current_time() << " - Response: " << buffer << endl;
        cout << "Response: " << buffer << endl;

        logFile << get_current_time() << " - Response: " << buffer << endl;

        crow::response res;
        res.set_header("Content-Type", "application/json");
        res.write(buffer);
        return res;
    });

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });
    logFile << get_current_time() << " - Server started on port 8080." << endl;
    app.port(8080).multithreaded().run();

    logFile << get_current_time() << " - Server stopped." << endl;
    logFile.close();
    return 0;
}
