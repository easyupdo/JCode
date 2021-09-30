#include "util.h"
#include <stdint.h>
#include "log.hpp"
#include <iomanip>
void CharOut(void * s,int32_t pos, int32_t size,std::string flag){
    char *cs = static_cast<char*>(s);
    LogDebug << flag << ":[char]:";
    for(int32_t i = pos;i<size;++i) {
        std::cout<<std::dec<<i<<": "<<cs[i]<<std::endl;
    }
}

void StringOut(void * s,int32_t pos, int32_t size,std::string flag){
    char *cs = static_cast<char*>(s);
    LogDebug << flag << ":[string]:";
    for(int32_t i = pos;i<size;++i) {
        std::cout<<cs[i];
    }
    std::cout<<std::endl;
}

void HexOut(void * s,int32_t pos,int32_t size,std::string flag){
    char *cs = static_cast<char*>(s);
    LogDebug << flag << ":[hex]:";
    for(int32_t i = pos;i<size;++i) {
        // std::cout<<std::dec<<i<<": 0x"<<std::hex<<(unsigned int)(unsigned char)cs[i]<<std::endl;
        std::cout<<std::showbase<<std::right<<std::setw(4)<<std::setfill('0')<<std::internal<<std::hex<<(unsigned int)(unsigned char)cs[i]<<" ";
    }
    std::cout<<std::endl;
}


int32_t Util::Serialize(const void * src,int32_t byte_size) {
    const unsigned char * c_src = static_cast<const unsigned char*>(src);
    for(int i = 0;i<byte_size;++i) {
        buffer_.push_back(c_src[i]);
    }
    return buffer_.size();
}

//string
int32_t Util::Serialize(std::string src,int32_t byte_size) {
    for(int i = 0;i<byte_size;++i) {
        buffer_.push_back(src[i]);
    }
    return buffer_.size();
}

//Header
int32_t Util::Serialize(Header src,int32_t byte_size) {
    Util util;
    util.ClearBuffer();
    // ver
    util.Serialize(static_cast<void*>(&(src.version_)),1);

    //ver_xor
    util.Serialize(static_cast<void*>(&(src.version_xor_)),1);
    //payload type
    util.Serialize(static_cast<void*>(src.payload_type_),2);
    //payload len
    char len[4];
    uint32_t payload_length_tmp = src.payload_length_;
    for(int i = 0;i<4;++i) {
        len[i] = (char)payload_length_tmp;
        payload_length_tmp = payload_length_tmp >> 8;
    }   
    util.Serialize(static_cast<void*>(len),4); 

    std::vector<unsigned char> buffer_tmp = util.get_buffer();

    this->buffer_.insert(buffer_.begin(),buffer_tmp.begin(),buffer_tmp.end());

    return buffer_.size();

}