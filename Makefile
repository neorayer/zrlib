DEBUG		= DEBUG_YES
#DEBUG		= DEBUG_NO

#6.warrning C4530: C++ exception handler used, but unwind semantics are not enabled. Specify -GX
CPP			= cl.exe /nologo /D $(DEBUG) -GX
CXX			= $(CPP)
CC			= $(CPP)
LINK32		= link.exe

OUTDIR		= ..\build
SRCDIR		= 
DLLDIR	= 

OBJS		= zr_logger.obj zr_bzero.obj zr_file.obj zr_bzero.obj zr_netutils.obj zr_str.obj zr_sock.obj zr_sockVarSrv.obj zr_TcpServer.obj zr_charset.obj zr_mem.obj

TARGET 		= zrlib.lib test

LINK32_FLAGS= /nologo
LIBS 		=  ws2_32.lib version.lib 	User32.lib
#LIBS		=$(LIBS) ws2_32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib	

"$(OUTDIR)" :
	if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)

zrlib.lib: $(OBJS)
	$(LINK32) -lib  $(LINK32_FLAGS) $(LIBS) $(OBJS) /out:$(OUTDIR)\$@   
	
test: $@.obj zrlib.lib $(OBJS)
	$(CPP)  $@.obj $(OUTDIR)\zrlib.lib -o $(OUTDIR)\$@.exe
	

all: $(TARGET)

clean:
	erase  *.obj $(TARGET) 



