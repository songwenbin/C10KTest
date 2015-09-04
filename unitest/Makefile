OBJS=../server.c
OBJS+=../anet.c
OBJS+=../ae_epoll.c
OBJS+=../ae.c
OBJS+=../zmalloc.c
OBJS+=../networking.c
OBJS+=../adlist.c
OBJS+=../dict.c
OBJS+=../sds.c
OBJS+=../protocol.c
OBJS+=../wstable.c

TESTOBJS=AllTests.c
TESTOBJS+=CuTest.c
TESTOBJS+=UTestProtocol.c
TESTOBJS+=UTestWSTable.c
TESTOBJS+=UTestWakeup.c

UniTest: $(OBJS)
	gcc -o $@ $(TESTOBJS) $(OBJS) -I../

clean:
	rm -rf UniTest
