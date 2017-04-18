#include "../AvbtpToWav/AvtpToWav.h"

int main()
{
	AvbTools::AvtpToWav::getInstance()->init("D:\\Work\\Temp", "D:\\Work\\Wireshark\\tshark.exe", "");

	AvbTools::AvtpToWav::getInstance()->convertToWav("D:\\Work\\Wireshark\\____AA_03_avb_ALEV4.pcapng", "");

	return 0;
}