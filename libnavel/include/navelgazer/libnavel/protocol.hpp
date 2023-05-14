#pragma once
#include "navelgazer/libnavel/types.hpp"

namespace leapus::navelgazer::protocol{

//Each packet is headed with an opcode which determines the format
//of the rest of its content
enum packet_opcodes{
    popHello,
    popRequirePlugin,
    popBeginFrame,
    popVideoStream,
    popEndFrame
};

//Very unambiguously identifies the protocol discipline.
//The question of how a navel would shake hands remains unresolved.
static constexpr char navel_handshake[]=
    "If you gaze long into the navel, the navel gazes back at you";

//Handshake packet
//-greeting comparison traps connection to the wrong port 
// if the string doesn't match
//-version checks version compatibility
struct packet_hello{
    char greeting[sizeof(navel_handshake)];
    version_type version;
};

//Inform the other endpoint we require a certain plugin to talk to
struct packet_require_plugin{
    plugin_spec spec;
};

struct frame_packet_base{
    size_t frame_no;
}

//Video data between packet_begin_frame and packet_end_frame belongs to a specific frame of video
//We care about what frame we are on so that we can discard stale data
struct packet_begin_frame:public frame_packet_base{
};

//A packet of video stream data. Maybe a frame of video.
//Currently, it's just a size integer, which is to be followed by a corresponding length
//of binary data bytes
struct packet_video_stream:public frame_packet_base{
};

struct packet_end_frame:public frame_packet_base{
};

}
