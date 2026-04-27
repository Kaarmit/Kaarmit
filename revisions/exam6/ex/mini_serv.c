#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>

int		max_fd = 0, next_id = 0;
int		ids[65536];
char	*msgs[65536];
fd_set	active, ready_read, ready_write;
char	buf[200000];

void fatal() {
	write(2, "Fatal error\n", 12);
	exit(1);
}

void notify(int sender, char *str) {
	for (int fd = 0; fd <= max_fd; fd++) {
		if (FD_ISSET(fd, &ready_write) && fd != sender)
			send(fd, str, strlen(str), 0);
	}
}

int extract_message(char **buf, char **msg) {
	char *newbuf; int i;
	*msg = 0;
	if (*buf == 0)
        return (0);
	i = 0;
	while ((*buf)[i]) {
		if ((*buf)[i] == '\n') {
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
                return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add) {
	char *newbuf; int len;
	if (buf == 0)
        len = 0;
	else
        len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
        return (0);
	newbuf[0] = 0;
	if (buf != 0)
        strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

int main(int ac, char **av) {
	if (ac != 2) {
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
        fatal();
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) fatal();
	if (listen(sockfd, 10) != 0) fatal();
	FD_ZERO(&active);
	FD_SET(sockfd, &active);
	max_fd = sockfd;
	while (1) {
		ready_read = ready_write = active;
		if (select(max_fd + 1, &ready_read, &ready_write, NULL, NULL) < 0)
			continue;
		for (int fd = 0; fd <= max_fd; fd++) {
			if (!FD_ISSET(fd, &ready_read))
				continue;
			if (fd == sockfd) {
				int conn = accept(sockfd, NULL, NULL);
				if (conn >= 0) {
					if (conn > max_fd)
                        max_fd = conn;
					ids[conn] = next_id++;
					msgs[conn] = NULL;
					FD_SET(conn, &active);
					sprintf(buf, "server: client %d just arrived\n", ids[conn]);
					notify(conn, buf);
				}
			}
			else {
				int bytes = recv(fd, buf, 1000, 0);
				if (bytes <= 0) {
					sprintf(buf, "server: client %d just left\n", ids[fd]);
					notify(fd, buf);
					free(msgs[fd]);
					msgs[fd] = NULL;
					FD_CLR(fd, &active);
					close(fd);
				}
				else {
					buf[bytes] = '\0';
					msgs[fd] = str_join(msgs[fd], buf);
					char *msg;
					while (extract_message(&msgs[fd], &msg)) {
						sprintf(buf, "client %d: ", ids[fd]);
						notify(fd, buf);
						notify(fd, msg);
						free(msg);
					}
				}
			}
		}
	}
	return (0);
}
