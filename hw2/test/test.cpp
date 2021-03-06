#define BOOST_TEST_MODULE test_ip_filter

#include <ip_pool.h>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <sstream>

using IP4 = IP<4>;

template<typename T>
void read(const std::string& in, const T& out) {
  std::istringstream iss(in);
  T t;
  iss >> t;
  BOOST_CHECK(t == out);
}

template<typename T>
void readwrite(const std::string& in, const std::string& out) {
  std::istringstream iss(in);
  T t;
  iss >> t;
  std::ostringstream oss;
  oss << t;
  BOOST_CHECK(oss.str() == out);
}

BOOST_AUTO_TEST_SUITE(test_suite_ip_filter)

BOOST_AUTO_TEST_CASE(test_ip_io) {
  readwrite<IP4>("192.168.0.1", "192.168.0.1");
}

BOOST_AUTO_TEST_CASE(test_ip_cmp) {
  IP4 ip1 {{192, 168, 0, 1}};
  IP4 ip2 {{193, 168, 0, 1}};
  IP4 ip3 {{192, 169, 0, 1}};
  IP4 ip4 {{192, 168, 1, 1}};
  IP4 ip5 {{192, 168, 1, 2}};
  BOOST_CHECK(ip1 < ip2);
  BOOST_CHECK(ip1 < ip3);
  BOOST_CHECK(ip1 < ip4);
  BOOST_CHECK(ip1 < ip5);
  BOOST_CHECK(!(ip1 < ip1));
  BOOST_CHECK(!(ip2 < ip1));
  BOOST_CHECK(!(ip3 < ip3));
  BOOST_CHECK(!(ip4 < ip4));
  BOOST_CHECK(!(ip5 < ip5));
}

BOOST_AUTO_TEST_CASE(test_ip_lexicography) {
  IP4 ip1 {{192, 168, 0, 1}};
  IP4 ip2 {{22, 168, 0, 1}};
  IP4 ip3 {{3, 169, 0, 1}};
  BOOST_CHECK(ip2 < ip1);
  BOOST_CHECK(ip3 < ip2);
  BOOST_CHECK(ip3 < ip1);
  BOOST_CHECK(!(ip1 < ip2));
  BOOST_CHECK(!(ip2 < ip3));
  BOOST_CHECK(!(ip1 < ip3));
}

BOOST_AUTO_TEST_CASE(test_ip_pool_io) {
  readwrite<IPPool<4>>("192.168.0.1 bla bla\n192.168.0.2 bla bla\n",
                    "192.168.0.1\n192.168.0.2\n");
}

BOOST_AUTO_TEST_SUITE_END()
