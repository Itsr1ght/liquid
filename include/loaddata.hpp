#ifndef LOADDATA
#define LOADDATA

#include <iostream>
using namespace std;


extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <inttypes.h>
}

struct framedata_struct
{
    int f_width=0, f_height=0;
};

// Functions
bool load_data( char* filename, 
                AVFormatContext* av_format_ctx, 
                AVCodecParameters* av_codec_params, 
                AVCodec* av_codec, 
                AVCodecContext* av_codec_ctx,
                AVPacket* av_packet,
                AVFrame* av_frame,
                framedata_struct* state
            );
#endif