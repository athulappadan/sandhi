//
// Copyright 2012 Josh Blum
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with io_sig program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef INCLUDED_GNURADIO_ELEMENT_HPP
#define INCLUDED_GNURADIO_ELEMENT_HPP

#include <gnuradio/runtime_api.h>
#include <gruel/pmt.h>

namespace gnuradio
{

struct GR_RUNTIME_API Element : boost::shared_ptr<ElementImpl>
{

    //! Create an empty element
    Element(void);

    /*!
     * Create an element from a shared pointer to an element.
     * Good for that factory function/shared ptr paradigm.
     */
    template <typename T>
    Element(const boost::shared_ptr<T> &elem):
        boost::shared_ptr<ElementImpl>(*reinterpret_cast<const Element*>(elem.get()))
    {    }

};

} //namespace gnuradio

#endif /*INCLUDED_GNURADIO_ELEMENT_HPP*/
