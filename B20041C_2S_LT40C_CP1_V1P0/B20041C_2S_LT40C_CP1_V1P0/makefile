# ---------------------User Definition Area Begin-----------------------------
# PLN_SOURCE: Specify plan source file name whose extension name is .pln.
# PLN_CFLAGS: plncmp options on compiling phase e.g. -c, -v
#
# PAT_SOURCE: Specify pattern source file name whose extension name is .pat.
# PAT_CFLAGS: patcmp options on compiling phase e.g. -x, -p, -eXXX
# PAT_LFLAGS: patcmp options on linking phase e.g -oXXX, -r
# NOCOMPRESS_FLAG => remove comment mark "#" below to turn on the patcmp's "-n" flag.
#
PATH_PAT0     = .\PAT
PLN_SOURCE   = arithmetic.pln B20041C_2S_LT40C_CP1_V1P0.PLN 
PLN_TARGET   = arithmetic.pin
PLN_CFLAGS   = 
PAT_SOURCE0_0   =                 $(PATH_PAT0)\EN_SET_86H.pat\ 
              $(PATH_PAT0)\EN_SET_87H.pat\ 
              $(PATH_PAT0)\EN_SET_8BH.pat\ 
              $(PATH_PAT0)\EN_SET_8CH.pat\ 
              $(PATH_PAT0)\H086.pat\ 
              $(PATH_PAT0)\H087.pat\ 
              $(PATH_PAT0)\H08B.pat\ 
              $(PATH_PAT0)\H08C.pat\ 
              $(PATH_PAT0)\mode_operation_spi.pat\ 
              $(PATH_PAT0)\READ_BACK.pat\ 
              $(PATH_PAT0)\RESET_PAT.pat\ 
              $(PATH_PAT0)\R_0_a0x002.pat\ 
              $(PATH_PAT0)\TRIM_SCAN.pat\ 
              $(PATH_PAT0)\WR_024H.pat 
PAT_SOURCE0   =  $(PAT_SOURCE0_0)  
PAT_CFLAGS0   =
PAT_LFLAGS0   = -o.\PAT\B20041C
PAT_TARGET0   =.\PAT\B20041C.ppo
# ---------------------User Definition Area End------------------------------

PAT_OBJECTS_TMP0    = $(PAT_SOURCE0:.pat=.pdt)
PAT_OBJECTS0        = $(PAT_OBJECTS_TMP0:.PAT=.pdt)
# ---------------------------------------------------------------------------
.precious: $(PAT_OBJECTS0) $(PAT_COBJECTS0)

all: $(PLN_TARGET) $(PAT_TARGET0) 

$(PLN_TARGET): $(PLN_SOURCE) .\PAT\pins.dec
  @$(CRAFT_HOME)\bin\plncmp $(PLN_CFLAGS) $(PLN_SOURCE)

$(PAT_TARGET0):: .\PAT\pins.dec
  @$(CRAFT_HOME)\bin\patcmp $(PAT_CFLAGS0) $(PAT_LFLAGS0) -f makefile_pat0.lst

$(PAT_TARGET0):: $(PAT_OBJECTS0)
  @$(CRAFT_HOME)\bin\patcmp $(PAT_LFLAGS0) -f makefile_pdt0.lst

.pat.pdt :
  @$(CRAFT_HOME)\bin\patcmp -c -s $(PAT_CFLAGS0) $<

build:
  @$(CRAFT_HOME)\bin\plncmp $(PLN_CFLAGS) $(PLN_SOURCE)
  @$(CRAFT_HOME)\bin\patcmp $(PAT_CFLAGS0) $(PAT_LFLAGS0) -f makefile_pat0.lst

clean:
  @touch -c *.pln
  @touch -c $(PATH_PAT0)\EN_SET_86H.pat
  @touch -c $(PATH_PAT0)\EN_SET_87H.pat
  @touch -c $(PATH_PAT0)\EN_SET_8BH.pat
  @touch -c $(PATH_PAT0)\EN_SET_8CH.pat
  @touch -c $(PATH_PAT0)\H086.pat
  @touch -c $(PATH_PAT0)\H087.pat
  @touch -c $(PATH_PAT0)\H08B.pat
  @touch -c $(PATH_PAT0)\H08C.pat
  @touch -c $(PATH_PAT0)\mode_operation_spi.pat
  @touch -c $(PATH_PAT0)\READ_BACK.pat
  @touch -c $(PATH_PAT0)\RESET_PAT.pat
  @touch -c $(PATH_PAT0)\R_0_a0x002.pat
  @touch -c $(PATH_PAT0)\TRIM_SCAN.pat
  @touch -c $(PATH_PAT0)\WR_024H.pat
