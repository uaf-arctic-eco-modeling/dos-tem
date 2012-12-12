# Basic dos-tem Makefile 

CC=g++
CFLAGS=-c -Wall -ansi -O2 -g -fPIC
LIBS=-lnetcdf_c++ -lnetcdf 
LIBDIR=-Lnetcdf/libs
INCLUDES=-Inetcdf/includes
SOURCES= src/TEM.o \
         src/atmosphere/AtmosUtil.o \
         src/atmosphere/Atmosphere.o \
         src/data/BgcData.o \
         src/data/CohortData.o \
         src/data/EnvData.o \
         src/data/FirData.o \
         src/data/GridData.o \
         src/data/RegionData.o \
         src/data/RestartData.o \
         src/disturb/WildFire.o \
         src/ground/DoubleLinkedList.o \
         src/ground/Ground.o \
         src/ground/Mineral.o \
         src/ground/Moss.o \
         src/ground/Peat.o \
         src/ground/Richard.o \
         src/ground/Rock.o \
         src/ground/Snow_Env.o \
         src/ground/Soil_Bgc.o \
         src/ground/Soil_Env.o \
         src/ground/Stefan.o \
         src/ground/layer/Front.o \
         src/ground/layer/Layer.o \
         src/ground/layer/MineralLayer.o \
         src/ground/layer/MossLayer.o \
         src/ground/layer/OutputDepth.o \
         src/ground/layer/PeatLayer.o \
         src/ground/layer/RockLayer.o \
         src/ground/layer/SnowLayer.o \
         src/ground/layer/SoilLayer.o \
         src/input/CohortInputer.o \
         src/input/GridInputer.o \
         src/input/RegionInputer.o \
         src/input/RestartInputer.o \
         src/input/SiteinInputer.o \
         src/input/SoilclmInputer.o \
         src/lookup/CCohortLookup.o \
         src/lookup/CohortLookup.o \
         src/lookup/SoilLookup.o \
         src/output/AtmosphereOutputer.o \
         src/output/CCohortdriver.o \
         src/output/RegnOutputer.o \
         src/output/RestartOutputer.o \
         src/output/SiteOutputer.o \
         src/output/SnowSoilOutputer.o \
         src/output/SoilclmOutputer.o \
         src/output/StatusOutputer.o \
         src/output/VegetationOutputer.o \
         src/run/AtmOutData.o \
         src/run/Cohort.o \
         src/run/Controller.o \
         src/run/Grid.o \
         src/run/ModelData.o \
         src/run/RegnOutData.o \
         src/run/SiteIn.o \
         src/run/SnowSoilOutData.o \
         src/run/SoilClm.o \
         src/run/Timer.o \
         src/run/VegOutData.o \
         src/runmodes/Regioner.o \
         src/runmodes/RunCohort.o \
         src/runmodes/Siter.o \
         src/util/CrankNicholson.o \
         src/util/Exception.o \
         src/util/FileChecking.o \
         src/util/Integrator.o \
         src/util/Interpolator.o \
         src/vegetation/Vegetation_Bgc.o \
         src/vegetation/Vegetation_Env.o

OBJECTS= AtmosUtil.o \
         Atmosphere.o \
         BgcData.o \
         CohortData.o \
         EnvData.o \
         FirData.o \
         GridData.o \
         RegionData.o \
         RestartData.o \
         WildFire.o \
         DoubleLinkedList.o \
         Ground.o \
         Mineral.o \
         Moss.o \
         Peat.o \
         Richard.o \
         Rock.o \
         Snow_Env.o \
         Soil_Bgc.o \
         Soil_Env.o \
         Stefan.o \
         Front.o \
         Layer.o \
         MineralLayer.o \
         MossLayer.o \
         OutputDepth.o \
         PeatLayer.o \
         RockLayer.o \
         SnowLayer.o \
         SoilLayer.o \
         CohortInputer.o \
         GridInputer.o \
         RegionInputer.o \
         RestartInputer.o \
         SiteinInputer.o \
         SoilclmInputer.o \
         CCohortLookup.o \
         CohortLookup.o \
         SoilLookup.o \
         AtmosphereOutputer.o \
         CCohortdriver.o \
         RegnOutputer.o \
         RestartOutputer.o \
         SiteOutputer.o \
         SnowSoilOutputer.o \
         SoilclmOutputer.o \
         StatusOutputer.o \
         VegetationOutputer.o \
         AtmOutData.o \
         Cohort.o \
         Controller.o \
         Grid.o \
         ModelData.o \
         RegnOutData.o \
         SiteIn.o \
         SnowSoilOutData.o \
         SoilClm.o \
         Timer.o \
         VegOutData.o \
         Regioner.o \
         RunCohort.o \
         Siter.o \
         CrankNicholson.o \
         Exception.o \
         FileChecking.o \
         Integrator.o \
         Interpolator.o \
         Vegetation_Bgc.o \
         Vegetation_Env.o

TEMOBJ=	TEM.o
	

dos-tem: $(SOURCES) $(TEMOBJ)
	$(CC) -o DOSTEM $(OBJECTS) $(TEMOBJ) $(LIBDIR) $(LIBS)

lib: $(SOURCES) 
	$(CC) -o libDOSTEM.so -shared $(INCLUDES) $(OBJECTS) $(LIBDIR) $(LIBS)

.cpp.o:  
	$(CC) $(CFLAGS) $(INCLUDES) $<

clean:
	rm -f $(OBJECTS) DVMDOSTEM TEM.o libDOSTEM.so* *~

