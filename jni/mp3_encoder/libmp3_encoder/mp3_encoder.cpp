#include "mp3_encoder.h"

Mp3Encoder::Mp3Encoder() {
}

Mp3Encoder::~Mp3Encoder() {
}

int Mp3Encoder::Init(const char* pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate) {
	int ret = -1;
	pcmFile = fopen(pcmFilePath, "rb");
	if(pcmFile) {
		mp3File = fopen(mp3FilePath, "wb");
		if(mp3File) {
			lameClient = lame_init();
			lame_set_in_samplerate(lameClient, sampleRate);
			lame_set_out_samplerate(lameClient, sampleRate);
			lame_set_num_channels(lameClient, channels);
			lame_set_brate(lameClient, bitRate / 1000);
			lame_init_params(lameClient);
			ret = 0;
		}
	}
	return ret;
}

void Mp3Encoder::Encode() {
	int bufferSize = 1024 * 256;
	short* buffer = new short[bufferSize / 2];
	short* leftBuffer = new short[bufferSize / 4];
	short* rightBuffer = new short[bufferSize / 4];
	uint8_t* mp3_buffer = new uint8_t[bufferSize];
	int readBufferSize = 0;
	while ((readBufferSize = fread(buffer, 2, bufferSize / 2, pcmFile)) > 0) {
		for (int i = 0; i < readBufferSize; i++) {
			if (i % 2 == 0) {
				leftBuffer[i / 2] = buffer[i];
			} else {
				rightBuffer[i / 2] = buffer[i];
			}
		}
		int wroteSize = lame_encode_buffer(lameClient, (short int *) leftBuffer, (short int *) rightBuffer, readBufferSize / 2, mp3_buffer, bufferSize);
		fwrite(mp3_buffer, 1, wroteSize, mp3File);
	}
	delete[] buffer;
	delete[] leftBuffer;
	delete[] rightBuffer;
	delete[] mp3_buffer;
}

void Mp3Encoder::Destory() {
	if(pcmFile) {
		fclose(pcmFile);
	}
	if(mp3File) {
		fclose(mp3File);
		lame_close(lameClient);
	}
}
