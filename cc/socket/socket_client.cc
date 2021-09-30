#include "log.hpp"
#include "tcpsocket.h"

#include "doipprotocol.h"

#include <thread>
#include <future>
#include <functional>


int main(int argc ,char ** argv) {
    // ClientUdpSocket client;
    // client.Init("client");
    // // client.Start();
    // client.SendVehicleIdentificationRequest("172.16.9.5");

    ClientTcpSocket client;
    client.Init();
    client.Start();

    return 0;
}