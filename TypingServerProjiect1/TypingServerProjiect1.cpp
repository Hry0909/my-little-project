#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <winsock2.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

const int PORT = 8080;

// 生成随机文本
string generateText(int len) {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string res;
    for (int i = 0; i < len; i++) {
        res += chars[rand() % chars.size()];
    }
    return res;
}

int main() {
    srand(time(0));

    // 初始化 Winsock
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // 创建 Socket
    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);

    // 绑定地址和端口
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, 5);

    cout << "打字练习服务器已启动！端口：8080" << endl;

    while (true) {
        // 等待客户端连接
        SOCKET client = accept(server, NULL, NULL);

        // 接收请求
        char buf[2048] = { 0 };
        recv(client, buf, 2048, 0);
        string request(buf);

        string response;

        // 处理获取文本的请求
        if (request.find("GET /get-text") != string::npos) {
            string text = generateText(20);
            response =
                "HTTP/1.1 200 OK\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "Content-Type: application/json\r\n"
                "\r\n"
                "{\"text\":\"" + text + "\"}";
        }
        else {
            response = "HTTP/1.1 404 Not Found\r\n\r\n";
        }

        // 发送响应
        send(client, response.c_str(), response.size(), 0);
        closesocket(client);
    }

    closesocket(server);
    WSACleanup();
    return 0;
}