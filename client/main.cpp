#include <zmqpp/zmqpp.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

// تابع برای دریافت زمان فعلی و اضافه کردن آن به لاگ‌ها
string get_current_time() {
    time_t now = time(0);
    char* dt = ctime(&now);
    string time_str(dt);
    time_str.pop_back(); // حذف کاراکتر newline
    return time_str;
}

int main(int argc, char *argv[]) {
    ofstream logFile("client.log", ios_base::app);  // باز کردن فایل لاگ در حالت append

    try {
        const string endpoint = "tcp://localhost:5510";
        string input = argv[1];

        logFile << get_current_time() << " - Starting client..." << endl;
        cout << "Starting client..." << endl;


        logFile << get_current_time() << " - Input command: " << input << endl;
        cout << "Input command: " << input << endl;

        zmqpp::context context;
        zmqpp::socket_type type = zmqpp::socket_type::req;
        zmqpp::socket socket(context, type);

        logFile << get_current_time() << " - Connecting to server at " << endpoint << "..." << endl;
        cout << "Connecting to server…" << endl;
        socket.connect(endpoint);

        // ارسال پیام به سرور
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

    } catch (const std::exception &e) {
        string error_message = e.what();
        logFile << get_current_time() << " - Error: " << error_message << endl;
        cerr << "Error: " << error_message << endl;
    }

    logFile << get_current_time() << " - Client session ended." << endl;
    logFile.close();  // بستن فایل لاگ
    return 0;
}
