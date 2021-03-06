/*
 *   Copyright (C) 2010,2011,2012 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef GatewayCache_H
#define	GatewayCache_H

#include "DStarDefines.h"
#include "Defs.h"

#if defined(__WINDOWS__)
#include "Inaddr.h"
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include <wx/wx.h>
#include <wx/ffile.h>

class CGatewayRecord {
public:
	CGatewayRecord(const wxString& gateway, in_addr address, unsigned int g2Port, DSTAR_PROTOCOL protocol, bool addrLock, bool protoLock) :
	m_gateway(gateway),
	m_address(address),
	m_g2Port(g2Port),
	m_protocol(DP_UNKNOWN),
	m_addrLock(addrLock),
	m_protoLock(false)
	{
		if (protocol != DP_UNKNOWN) {
			m_protocol  = protocol;
			m_protoLock = protoLock;
		}
	}

	wxString getGateway() const
	{
		return m_gateway;
	}

	void setGateway(const wxString& gateway)
	{
		m_gateway = gateway;
	}

	in_addr getAddress() const
	{
		return m_address;
	}

	DSTAR_PROTOCOL getProtocol() const
	{
		return m_protocol;
	}

	unsigned int getG2Port() const
	{
		return m_g2Port;
	}

	void setData(in_addr address, DSTAR_PROTOCOL protocol, bool addrLock, bool protoLock)
	{
		if (!m_addrLock) {
			m_address  = address;
			m_addrLock = addrLock;
		}

		if (!m_protoLock) {
			if (protocol != DP_UNKNOWN) {
				m_protocol  = protocol;
				m_protoLock = protoLock;
			}
		}
	}

	void setG2Data(in_addr address, unsigned int g2Port)
	{
		if (!m_addrLock) {
			m_address  = address;
		}

		m_g2Port = g2Port;
	}

private:
	wxString       m_gateway;
	in_addr        m_address;	
	//the incoming G2 port, keep track of it and use it to answer back instead of the default one. This helps us defeat NAT with no port forwarding to G2_DVPORT
	unsigned int   m_g2Port;
	DSTAR_PROTOCOL m_protocol;
	bool           m_addrLock;
	bool           m_protoLock;
};

WX_DECLARE_STRING_HASH_MAP(CGatewayRecord*, CGatewayCache_t);

class CGatewayCache {
public:
	CGatewayCache();
	~CGatewayCache();

	CGatewayRecord* find(const wxString& gateway);

	void update(const wxString& gateway, const wxString& address, DSTAR_PROTOCOL protocol, bool addrLock, bool protoLock);
	void updateG2(const wxString& gateway, in_addr address, unsigned int g2Port);

	unsigned int getCount() const;

private:
	CGatewayRecord* findByAddress(in_addr address);

	CGatewayCache_t m_cache;
};

#endif
