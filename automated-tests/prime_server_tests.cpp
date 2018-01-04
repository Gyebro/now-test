/**
 * prime_server_tests.cpp - C++ source file
 * (C) Nowtechnologies Inc, 2018
 * Maintained by: Gergely Gyebroszki
 */

#include <gtest/gtest.h>
#include "tcpconnection.h"
#include "tcpconnection.cpp"

/**
 * Test-fixture
 * Initializes the TCP connection, closes it after test finishes
 */
class PrimeServerTest : public ::testing::Test {
private:
    string host, port;
public:
    TcpConnection c;
    PrimeServerTest() {
        host = "localhost";
        port = "4444";
    }
    void SetUp( ) {
        c.open(host, port);
    }
    void TearDown( ) {
        c.close();
    }
    ~PrimeServerTest( )  {
    }
    bool prime(size_t i) {
        for (size_t j=2; j*j<=i; j++) {
            if (i%j==0) return false;
        }
        return true;
    }
    string prime_str(size_t i) {
        return ( prime(i) ? "PRIME" : "NOT_PRIME" );
    }
    string default_error_str() {
        return "UNKNOWN_ERROR";
    }
};

class PrimeServerTestInt : public PrimeServerTest,
                public ::testing::WithParamInterface<int> {
};

// Parametrized test

TEST_P(PrimeServerTestInt, Integers) {
    int param = GetParam();
    if (param > 0 && param <= 100) {
        EXPECT_EQ(prime_str(param), c.send_data(param));
    } else {
        EXPECT_EQ(default_error_str(), c.send_data(param));
    }
}

// Standard tests

TEST_F(PrimeServerTest, RepeatedPrime) {
    for (size_t i=0; i<1000; i++) {
        EXPECT_EQ(prime_str(7), c.send_data(7));
    }
}

TEST_F(PrimeServerTest, RepeatedNotPrime) {
    for (size_t i=0; i<1000; i++) {
        EXPECT_EQ(prime_str(16), c.send_data(16));
    }
}

// Instantiation of parametrized tests

INSTANTIATE_TEST_CASE_P(ValidIntegers, PrimeServerTestInt, ::testing::Range(1, 100));

// These tests kill the server

TEST_F(PrimeServerTest, FloatingPoint) {
    float a = 7.01;
    EXPECT_EQ(default_error_str(), c.send_data(to_string(a)));
}

TEST_F(PrimeServerTest, String) {
    EXPECT_EQ(default_error_str(), c.send_data("HelloWorld"));
}

INSTANTIATE_TEST_CASE_P(LargeIntegers, PrimeServerTestInt, ::testing::Range(101, 110));

INSTANTIATE_TEST_CASE_P(NegativeIntegers, PrimeServerTestInt, ::testing::Range(-20, -1));