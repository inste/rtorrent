// libTorrent - BitTorrent library
// Copyright (C) 2005-2011, Jari Sundell
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// In addition, as a special exception, the copyright holders give
// permission to link the code of portions of this program with the
// OpenSSL library under certain conditions as described in each
// individual source file, and distribute linked combinations
// including the two.
//
// You must obey the GNU General Public License in all respects for
// all of the code used other than OpenSSL.  If you modify file(s)
// with this exception, you may extend this exception to your version
// of the file(s), but you are not obligated to do so.  If you do not
// wish to do so, delete this exception statement from your version.
// If you delete this exception statement from all source files in the
// program, then also delete it here.
//
// Contact:  Jari Sundell <jaris@ifi.uio.no>
//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#ifndef RTORRENT_UTILS_SOCKET_FD_H
#define RTORRENT_UTILS_SOCKET_FD_H

#include <unistd.h>

namespace rak {
  class socket_address;
}

namespace utils {

class SocketFd {
public:
  typedef uint8_t priority_type;

  SocketFd() : m_fd(-1) {}
  explicit SocketFd(int fd) : m_fd(fd) {}

  bool                is_valid() const                        { return m_fd >= 0; }
  
  int                 get_fd() const                          { return m_fd; }
  void                set_fd(int fd)                          { m_fd = fd; }

  bool                set_nonblock();
  bool                set_reuse_address(bool state);
  bool                set_dont_route(bool state);

  bool                set_bind_to_device(const char* device);

  bool                set_priority(priority_type p);

  bool                set_send_buffer_size(uint32_t s);
  bool                set_receive_buffer_size(uint32_t s);

  int                 get_error() const;

  bool                open_stream();
  bool                open_datagram();
  bool                open_local();
  void                close();

  void                clear()                                 { m_fd = -1; }

  bool                bind(const rak::socket_address& sa);
  bool                bind(const rak::socket_address& sa, unsigned int length);
  bool                connect(const rak::socket_address& sa);
  bool                getsockname(rak::socket_address* sa);

  bool                listen(int size);
  SocketFd            accept(rak::socket_address* sa);

//   unsigned int        get_read_queue_size() const;
//   unsigned int        get_write_queue_size() const;

private:
  inline void         check_valid() const;

  int                 m_fd;
#ifdef RAK_USE_INET6
  bool                m_ipv6_socket;
#endif
};

}

#endif
