// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <grextras/datagram_to_stream.hpp>
#include <boost/make_shared.hpp>

using namespace grextras;

struct Datagram2StreamImpl : Datagram2Stream
{
    Datagram2StreamImpl(const size_t itemsize):
        gras::Block("GrExtras Datagram2Stream")
    {
        //setup the input for messages only
        gras::InputPortConfig config = this->get_input_config(0);
        config.reserve_items = 0;
        this->set_input_config(0, config);

        //setup the output for streaming
        this->set_output_size(0, itemsize);
    }

    void work(const InputItems &ins, const OutputItems &)
    {
        //read the input message, and post
        const PMCC msg = this->pop_input_msg(0);
        if (not msg.is<gras::PacketMsg>()) return;
        this->post_output_buffer(0, msg.as<gras::PacketMsg>().buff);
    }
};

Datagram2Stream::sptr Datagram2Stream::make(const size_t itemsize)
{
    return boost::make_shared<Datagram2StreamImpl>(itemsize);
}
