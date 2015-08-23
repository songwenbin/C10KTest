wakeserver: main.o server.o anet.o ae_epoll.o ae.o zmalloc.o
	cc -o wakeserver main.o server.o anet.o ae_epoll.o ae.o zmalloc.o -I.
