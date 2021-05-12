/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#pragma once

#include "RAFTConsensus.h"

#include <boost/shared_ptr.hpp>

class TcpConnection;

class JobRequestHandler
{
public:
	JobRequestHandler(RAFTConsensus* raft, RequestHandler* requestHandler);

	std::string handleConnectRequest(boost::shared_ptr<TcpConnection> connection);

	std::string addJob(std::string request, std::string data);

private:
	RAFTConsensus* raft;
	RequestHandler* requestHandler;
};
