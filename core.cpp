#include<iostream>
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

Core::Core(){}

void Core::RecvString(int port, char* data)
{
}

void Core::SendString(int port, char* data)
{
}

Core::~Core(){}
