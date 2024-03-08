# This Makefile can be used with GNU Make or BSD Make

#LIB=libkyber512_clean.a
#HEADERS=api.h cbd.h indcpa.h kem.h ntt.h params.h poly.h polyvec.h reduce.h symmetric.h verify.h 
#OBJECTS=cbd.o indcpa.o kem.o ntt.o poly.o polyvec.o reduce.o symmetric-shake.o verify.o 

#CFLAGS=-O3 -Wall -Wextra -Wpedantic -Werror -Wmissing-prototypes -Wredundant-decls -std=c99 -I../../../common $(EXTRAFLAGS)

#all: $(LIB)

#%.o: %.c $(HEADERS)
#	$(CC) $(CFLAGS) -c -o $@ $<

#$(LIB): $(OBJECTS)
#	$(AR) -r $@ $(OBJECTS)

#clean:
#	$(RM) $(OBJECTS)
#	$(RM) $(LIB)


	
  DEBUG=no
  BENCH=no
  MULDIV=no

  SOURCES = util/crt.S \
            util/util.c \
            util/Murax.c

  INC += -I../murax/software/VexRiscvSocSoftware/libs/
  INC += -I../murax/software/VexRiscvSocSoftware/projects/murax/libs/
  INC += -Iutil/
  INC += -I../mbedtls-2.8.0/include/
  
  LDSCRIPT = resources/linker.ld
  
  CFLAGS += -DMBEDTLS  
  CFLAGS += -DSW_FIXED_INLEN -DSW_PRECOMP
  CFLAGS += -DSIM	
  CFLAGS += -DTARGET=Murax -DMurax


  SOURCES += ../mbedtls-2.8.0/library/sha256.c
  include resources/gcc.mk
  include resources/subproject.mk	
  
  OBJDIR = test

  PROJ_NAME=Murax_$(PROJ)

  
  SOURCES += *.c
  HEADERS += *.h
  
  
  
  TESTS = test/*_verify
  
  all: $(OBJDIR)/$(PROJ_NAME)
  
  test/Murax_%: test/%.c $(SOURCES) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(INC) -o $@ $(SOURCES) $< $(LDFLAGS)

  tests: $(TESTS)
  ui: $(UI)

  test: $(TESTS:=.exec)

  .PHONY: clean test
  
  test/Murax_%.exec: test/%
	@$<
	
  run: $(OBJDIR)/$(PROJ_NAME)
	/opt/riscv/bin/riscv64-unknown-elf-gdb \
         -ex "target remote localhost:3333" \
         -ex "set remotetimeout 60" \
         -ex "set arch riscv:rv32" \
         -ex "monitor reset halt" \
         -ex "load" \
         -ex "continue" \
         $(OBJDIR)/$(PROJ_NAME)
         
   clean:
	-$(RM) $(TEST)
	-$(RM) $(UI)      	
	
