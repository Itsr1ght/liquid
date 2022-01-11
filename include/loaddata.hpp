#ifndef LOADDATA
#define LOADDATA

#include <iostream>
using namespace std;


extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
}

struct framedata_struct
{
    int f_width=0, f_height=0, video_stream_index = -1, audio_stream_index = -1, p_response, f_response, num_bytes;
    AVFormatContext* av_format_ctx;
    AVCodecParameters* av_codec_params;
    AVCodec* av_codec;
    AVCodecContext* av_codec_ctx;
    AVPacket* av_packet;
    AVFrame* av_frame;
    AVFrame * decoded_frame;
    uint8_t * buffer = NULL;
    SwsContext* sws_ctx;
};

bool load_data(char* filename, framedata_struct* state);
void close_data(framedata_struct* state);

#endif