#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
int PORT_NO = 9999;
int main()
{
    int socketReturn = socket(AF_INET, SOCK_STREAM, 0);
    if(socketReturn<0)
        std::cout << "Error opening socket";
    struct sockaddr_in serv_addr, cli_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT_NO);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(socketReturn, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout << "Cannot bind";
    }
    listen(socketReturn, 5);
    while(true){
        socklen_t clilen = sizeof(cli_addr);
        int newConnectionSockFd =  accept(socketReturn, (struct sockaddr*) &cli_addr, &clilen);
        char buffer[512];
        memset(&buffer, 0, 512);
        const char* httpResponse = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: 32\r\n"
                "\r\n"
                "<html><body>Hello World</body></html>";

        int n = read(newConnectionSockFd, buffer, 511);
        write(newConnectionSockFd, httpResponse ,strlen(httpResponse));
        if(n<0)
            std::cout << "read failed";
        std::cout << buffer; 
        close(newConnectionSockFd);
    }
    close(socketReturn);
    
}