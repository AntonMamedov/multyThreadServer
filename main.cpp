
#include "core.h"
#include "httpparser.h"
#include <signal.h>
#include <thread>
#include <sys/epoll.h>
#include <errno.h>


using namespace std;

int main()
{
    int server_d = create_socket("8000"); // создаю сервер
     printf("HTTP server created!\n");


     while(1)
     {
         int client_d =  create_client(server_d);
         if (fork() == 0){
             char* request = get_request(client_d);
             printf("%s \n", request);
             struct request_HTTP_data current;
             parse_HTTP_message(request, &current);
             free(request);
             request_processing_http(client_d, &current);
             free_request_data(&current);
             close(client_d);
         }
         close(client_d);

     }

     return 0;
 }

