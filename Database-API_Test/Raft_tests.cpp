/*
This program has been developed by students from the bachelor Computer Science at
Utrecht University within the Software Project course.
© Copyright Utrecht University (Department of Information and Computing Sciences)
*/

#include "RAFTConsensus.h"
#include "Networking.h"
#include "RequestHandlerMock.cpp"
#include "ConnectionHandler.h"

#include <gtest/gtest.h>

#define TESTLISTENPORT 9043

MATCHER_P(matcherNotNull, request, "") 
{
	return arg != nullptr;
}

TEST(RaftTests, AssumeLeaderTest) 
{
	RequestHandlerMock handler; 
	ConnectionHandler listen;
	std::thread* t = new std::thread(&ConnectionHandler::startListen, &listen, nullptr, nullptr, nullptr, TESTLISTENPORT, &handler);
	usleep(500000); // Just to make sure the listner has started.

	EXPECT_CALL(handler, handleRequest("conn", "8003\n", matcherNotNull(nullptr))).Times(0);

	RAFTConsensus raft;
	raft.start(nullptr, true, {{"127.0.0.1", std::to_string(TESTLISTENPORT)}});

	ASSERT_TRUE(raft.isLeader());
}

TEST(RaftTests, ConnectToLeader) 
{
	RequestHandlerMock handler; 
	ConnectionHandler listen;
	EXPECT_CALL(handler, handleRequest("conn", std::to_string(PORT) + "\n", matcherNotNull(nullptr))).Times(1)
		.WillOnce(testing::Return(RESPONSE_OK + ("?127.0.0.1?" + std::to_string(PORT) + "\n")));
	std::thread* t = new std::thread(&ConnectionHandler::startListen, &listen, nullptr, nullptr, nullptr, TESTLISTENPORT, &handler);
	usleep(500000); // Just to make sure the listner has started.


	RAFTConsensus raft;
	raft.start(nullptr, false, {{"127.0.0.1", std::to_string(TESTLISTENPORT)}});

	ASSERT_TRUE(!raft.isLeader());	
}