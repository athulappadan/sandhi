/* -*- c++ -*- */
/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "complex_to_arg_impl.h"
#include <gr_io_signature.h>
#include <volk/volk.h>
#include <gr_math.h>

namespace gr {
  namespace blocks {

    complex_to_arg::sptr complex_to_arg::make(size_t vlen)
    {
      return gnuradio::get_initial_sptr(new complex_to_arg_impl(vlen));
    }

    complex_to_arg_impl::complex_to_arg_impl(size_t vlen)
      : gr_sync_block("complex_to_arg",
		      gr_make_io_signature (1, 1, sizeof(gr_complex)*vlen),
		      gr_make_io_signature (1, 1, sizeof(float)*vlen)),
	d_vlen(vlen)
    {
      const int alignment_multiple =
	volk_get_alignment() / sizeof(float);
      set_alignment(std::max(1,alignment_multiple));
    }

    int
    complex_to_arg_impl::work(int noutput_items,
			      gr_vector_const_void_star &input_items,
			      gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      float *out = (float *) output_items[0];
      int noi = noutput_items * d_vlen;
      
      // The fast_atan2f is faster than Volk
      for (int i = 0; i < noi; i++){
	//    out[i] = std::arg (in[i]);
	out[i] = gr_fast_atan2f(in[i]);
      }
      
      return noutput_items;
    }

  } /* namespace blocks */
}/* namespace gr */
