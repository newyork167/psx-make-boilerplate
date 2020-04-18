set nc_path = D:\Development\PSX\Virtual Machine\Shared\Windows XP\\netcat-win32-1.11\netcat-1.11\nc.exe
echo make -f Makefile | nc_path -v 192.168.0.161 4444