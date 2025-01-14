/* Copyright (C) 2005 Martin Koegler
 * Copyright (C) 2010 TigerVNC Team
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 */

#ifndef __RDR_TLSOUTSTREAM_H__
#define __RDR_TLSOUTSTREAM_H__

#ifdef HAVE_GNUTLS
#include <gnutls/gnutls.h>
#include <rdr/OutStream.h>

namespace rdr {

  class TLSOutStream : public OutStream {
  public:
    TLSOutStream(OutStream* out, gnutls_session_t session);
    virtual ~TLSOutStream();

    void flush();
    size_t length();
    virtual void cork(bool enable);

  protected:
    virtual void overrun(size_t needed);

  private:
    size_t writeTLS(const U8* data, size_t length);
    static ssize_t push(gnutls_transport_ptr_t str, const void* data, size_t size);

    gnutls_session_t session;
    OutStream* out;
    size_t bufSize;
    U8* start;
    size_t offset;

    Exception* saved_exception;
  };
};

#endif
#endif
