#include <stdio.h>

unsigned short checksum_ply = 0x8005;
unsigned short checksum_rotate(unsigned short crc, unsigned char value) {
	char l_c_c1;
	unsigned short l_us_top;
	for (l_c_c1 = 0; l_c_c1 < 8; l_c_c1++) {
	l_us_top = crc & 0x8000;
	crc = (crc << 1) + ((value >> (7 - l_c_c1)) & 1);
	if (l_us_top)
	crc ^= checksum_ply;
	}
	return crc;
}
unsigned short checksum_update(void* msg, short length, unsigned short crc) {
	short count = 0;
	char* message = (char*) msg;
	for (count = 0; count < length; ++count)
	crc = checksum_rotate(crc, message[count]);
	return crc;
}
unsigned short checksum_publish(unsigned short crc) {
	crc = checksum_rotate(crc, 0);
	crc = checksum_rotate(crc, 0);
	return crc;
}

int main(void)
{
    unsigned crc;
    unsigned char buf[] = {0x0005};
    
    crc = checksum_publish(checksum_update(buf,1,0));

    //crc = crc16(0x0000, buf, 1);
    printf("%04x\n", crc);
    return 0;
}


