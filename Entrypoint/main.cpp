#include "../AvbtpToWav/AvtpToWav.h"

const static std::string kCurrentDir(MY_SOLUTIONDIR);
const static std::string kWiresharkBin = kCurrentDir + "HelperTools\\Wireshark\\tshark.exe";
const static std::string kSoxBin = kCurrentDir + "HelperTools\\sox-14-4-2\\sox.exe";
const static std::string kTempDir = kCurrentDir + "__temp__";

const static std::string input = "D:\\Work\\avb_tools_working_dir\\____AA_03_avb_ALEV4.pcapng";

int main()
{
	AvbTools::AvtpToWav::getInstance()->init(kTempDir, kWiresharkBin, kSoxBin);

	AvbTools::AvtpToWav::getInstance()->convertToWav(input, kTempDir);

	return 0;
}