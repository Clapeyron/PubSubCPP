//#define DEBUG 1
#include <iostream>
#include "topic.hpp"
#include <stdio.h>
#include <chrono>

int main(int argc, char** args) {
    ui msg_size = 256;
    ui msg_count = 10;
    ui striplen = 0;
    using C = std::chrono::high_resolution_clock;
    std::string name = "/clap0";
    int receiver = 0;
    int create = 0;
    Topic::TopPtr t;
    if (argc > 1) name = std::string(args[1]);
    if (argc > 2) sscanf(args[2], "%d", &receiver);
    if (argc > 3) sscanf(args[3], "%d", &create);
    if (argc > 4) sscanf(args[4], "%lu", &msg_size);
    char msg[msg_size];
    if (argc > 5) sscanf(args[5], "%lu", &msg_count);
    if (argc > 6) sscanf(args[6], "%lu", &striplen);
    if (argc > 7) sscanf(args[7], "%s", msg);
    DEBUG_MSG("Receivers: "+std::to_string(receiver));
    DEBUG_MSG("Create: "+std::to_string(create));
    DEBUG_MSG("Msg_size: "+std::to_string(msg_size));
    DEBUG_MSG("Msg_count: "+std::to_string(msg_count));
    DEBUG_MSG("Msg: " + std::string(msg));
    if (create) t = Topic::spawn_create(name, msg_size, msg_count);
    else t = Topic::spawn(name, msg_size, msg_count);
    C::time_point c = C::now();
    if (receiver){
        for (ui i = 0; i < striplen; i++){
            t->sub(msg);
        }
    }else {
        for (ui i = 0; i < striplen; i++){
            t->pub(msg);
        }
    }
    C::time_point d = C::now();
    std::cout << (d - c).count() << std::endl;

    return 0;
}