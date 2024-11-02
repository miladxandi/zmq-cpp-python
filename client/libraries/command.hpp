//
// Created by istock on ۰۲/۱۱/۲۰۲۴.
//

#ifndef ZMQ_PROJECT_COMMAND_HPP
#define ZMQ_PROJECT_COMMAND_HPP

#include <string>
#include <optional>
#include <vector>
#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

class Command {
public:
    string command_type;
    optional <string> command_name;
    optional <string> free_command;
    optional <string> expression;
    optional <vector<string>> parameters;

    // Constructor to parse JSON string
    Command(const string &jsonString) {
        json j = json::parse(jsonString);

        command_type = j.at("command_type").get<string>();

        if (j.find("command_name") != j.end() && !j.at("command_name").is_null())
            command_name = j.at("command_name").get<string>();

        if (j.find("free_command") != j.end() && !j.at("free_command").is_null())
            free_command = j.at("free_command").get<string>();

        if (j.find("expression") != j.end() && !j.at("expression").is_null())
            expression = j.at("expression").get<string>();

        if (j.find("parameters") != j.end() && !j.at("parameters").is_null())
            parameters = j.at("parameters").get<vector<string>>();
    }
};
#endif //ZMQ_PROJECT_COMMAND_HPP