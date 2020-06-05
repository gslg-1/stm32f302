DEBUG = 1
UTEST = 0

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

ifeq ($(UTEST), 1)
CFLAGS += -D__UTEST
endif