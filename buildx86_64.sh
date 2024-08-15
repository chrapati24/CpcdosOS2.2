clear
echo Building Cpcdos OS2.2
echo
echo *** Building xfont ***
echo ./xfont.sh
echo *** Building xfont done ***

echo ***Building loader.cpp***
g++ -c OS2.2/Cpcdos/Core/loader.cpp -o obj/loader.o
echo ***Building loader.cpp done***

echo *** Creating LIBCpcdos.a ***
ar -crs libcpcdos.a obj/loader.o
echo *** Creating LIBCpcdos.a done ***

echo *** Building ElieDraw for Cpcdos UI ***
echo fbc -v -p @args.cfg
echo *** Building ElieDraw for Cpcdos UI done ***


echo ***Building CPCDOS_INIT.BAS***
fbc -v -l stdc++ -l ncurses -l fbgfx -l png -l z @cpcdos.cfg
echo ***Building CPCDOS_INIT.BAS done***

echo ***Copying cpcldr to BIN/***
cp cpcldr bin/cpcldr
echo ***Copying cpcldr to BIN/ done***
