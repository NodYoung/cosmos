//
// Created by liyanan on 8/26/19.
//

#include <iostream>
#include <string>
#include <MessageBus.hpp>

MessageBus g_bus;
const std::string Topic="Drive";
const std::string CallBackTopic="DriveOk";

struct Subject {
    Subject() {
        g_bus.Attach([this]{DriveOk();}, CallBackTopic);
    }
    void SendReq(const std::string& topic) {
        g_bus.SendReq<void, int>(50, topic);
    }
    void DriveOk() {
        std::cout << "drive ok" << std::endl;
    }
};

struct Car {
    Car() {
        g_bus.Attach([this](int speed){Drive(speed);}, Topic);
    }
    void Drive(int speed) {
        std::cout << "Car drive" << speed << std::endl;
        g_bus.SendReq<void>(CallBackTopic);
    }
};

struct Bus {
    Bus() {
        g_bus.Attach([this](int speed){Drive(speed);}, Topic);
    }
    void Drive(int speed) {
        std::cout << "Bus drive" << speed << std::endl;
        g_bus.SendReq<void>(CallBackTopic);
    }
};

struct Truck {
    Truck() {
        g_bus.Attach([this](int speed){Drive(speed);}, Topic);
    }
    void Drive(int speed) {
        std::cout << "Truck drive" << speed << std::endl;
        g_bus.SendReq<void>(CallBackTopic);
    }
};

int main() {
    Subject subject;
    Car car;
    Bus bus;
    Truck truck;
    subject.SendReq(Topic);
    subject.SendReq("");
    return 0;
}
