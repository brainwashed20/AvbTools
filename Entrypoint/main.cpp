#include "../AvbtpToWav/AvtpToWav.h"

int main()
{
	AvbTools::AvtpToWav::getInstance()->init("D:\\Work\\avb_tools_working_dir\\Temp", "D:\\Work\\avb_tools_working_dir\\Wireshark\\tshark.exe", "");

	AvbTools::AvtpToWav::getInstance()->convertToWav("D:\\Work\\avb_tools_working_dir\\____AA_03_avb_ALEV4.pcapng", "D:\\Work\\avb_tools_working_dir\\Temp");

	return 0;
}