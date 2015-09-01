wakeserver: main.o server.o anet.o ae_epoll.o ae.o zmalloc.o networking.o adlist.o dict.o sds.o protocol.o wstable.o
	cc -o wakeserver main.o server.o anet.o ae_epoll.o ae.o zmalloc.o networking.o adlist.o dict.o sds.o protocol.o wstable.o -I.

#libwake: server.o anet.o ae_epoll.o ae.o zmalloc.o networking.o adlist.o dict.o sds.o protocol.o
	#ar rcs libwake.a $^

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf wakeserver
