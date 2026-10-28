#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#pragma pack(push,1)

struct WAVHeader{
    char ChunkID[4];
    uint32_t ChunkSize;
    char Format[4];
    char Subchunk1ID[4];
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
    char Subchunk2ID[4];
    uint32_t Subchunk2Size;
};

#pragma pack(pop)

int main(){
    FILE* f = fopen("input.wav","rb");

    if(f==NULL){
        printf("Opening the wav file failed.");
        return 1;
    }

    struct WAVHeader H;
    fread(&H,sizeof(struct WAVHeader),1,f);

    printf("Sample Rate is %d\n",H.SampleRate);
    printf("Channels: %d (1 = Mono, 2 = Stereo)\n", H.NumChannels);
    printf("Data Size: %d bytes\n", H.Subchunk2Size);

    int total_samples = H.Subchunk2Size/2;

    int16_t* audio = (int16_t*) malloc (H.Subchunk2Size);
    if(audio==NULL){
        printf("Memory Allocation Failed.");
        fclose(f);
        return 1;
    }

    fread(audio,1,H.Subchunk2Size,f);
    printf("Audio loaded into RAM. Reversing...\n");

    for(int i=0;i<total_samples/2;++i){
        uint16_t temp = audio[i];
        audio[i] = audio[total_samples-1-i];
        audio[total_samples-1-i]=temp;
    }

    FILE* output=fopen("reversed.wav","wb");
    fwrite(&H,sizeof(struct WAVHeader),1,output);
    fwrite(audio, 1, H.Subchunk2Size, output);

    printf("Saved as reversed.wav");

    fclose(f);
    fclose(output);
    free(audio);
    return 0;
}