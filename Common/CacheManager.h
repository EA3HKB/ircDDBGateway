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

#ifndef CacheManager_H
#define	CacheManager_H

#include <wx/wx.h>

#if defined(__WINDOWS__)
#include "Inaddr.h"
#else
#include <netinet/in.h>
#endif

#include "RepeaterCache.h"
#include "GatewayCache.h"
#include "UserCache.h"

class CUserData {
public:
	CUserData(const wxString& user, const wxString& repeater, const wxString& gateway, in_addr address, unsigned int g2Port) :
	m_user(user),
	m_repeater(repeater),
	m_gateway(gateway),
	m_address(address),
	m_g2Port(g2Port)
	{
	}

	wxString getUser() const
	{
		return m_user;
	}

	wxString getRepeater() const
	{
		return m_repeater;
	}

	wxString getGateway() const
	{
		return m_gateway;
	}

	in_addr getAddress() const
	{
		return m_address;
	}

	unsigned int getG2Port() const
	{
		return m_g2Port;
	}

private:
	wxString m_user;
	wxString m_repeater;
	wxString m_gateway;
	in_addr  m_address;
	unsigned int m_g2Port;
};

class CRepeaterData {
public:
	CRepeaterData(const wxString& repeater, const wxString& gateway, in_addr address, DSTAR_PROTOCOL protocol, unsigned int g2Port) :
	m_repeater(repeater),
	m_gateway(gateway),
	m_address(address),
	m_protocol(protocol),
	m_g2Port(g2Port)
	{
	}

	wxString getRepeater() const
	{
		return m_repeater;
	}

	wxString getGateway() const
	{
		return m_gateway;
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

private:
	wxString       m_repeater;
	wxString       m_gateway;
	in_addr        m_address;
	DSTAR_PROTOCOL m_protocol;
	unsigned int m_g2Port;
};

class CGatewayData {
public:
	CGatewayData(const wxString& gateway, in_addr address, DSTAR_PROTOCOL protocol, unsigned int g2Port) :
	m_gateway(gateway),
	m_address(address),
	m_protocol(protocol),
	m_g2Port(g2Port)
	{
	}

	wxString getGateway() const
	{
		return m_gateway;
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

private:
	wxString       m_gateway;
	in_addr        m_address;
	DSTAR_PROTOCOL m_protocol;
	unsigned int   m_g2Port;
};

class CCacheManager {
public:
	CCacheManager();
	~CCacheManager();

	CUserData*     findUser(const wxString& user);
	CGatewayData*  findGateway(const wxString& gateway);
	CRepeaterData* findRepeater(const wxString& repeater);

	void updateUser(const wxString& user, const wxString& repeater, const wxString& gateway, const wxString& address, const wxString& timeStamp, DSTAR_PROTOCOL protocol, bool addrLock, bool protoLock);
	void updateRepeater(const wxString& repeater, const wxString& gateway, const wxString& address, DSTAR_PROTOCOL protocol, bool addrLock, bool protoLock);
	void updateGateway(const wxString& gateway, const wxString& address, DSTAR_PROTOCOL protocol,bool addrLock, bool protoLock);
	void updateGatewayG2(const wxString& gateway, const in_addr& address, unsigned int g2Port);

private:
	wxMutex        m_mutex;
	CUserCache     m_userCache;
	CGatewayCache  m_gatewayCache;
	CRepeaterCache m_repeaterCache;
};

#endif
