#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE netlistDB_expr_sensitivity_probe_test

#include <boost/test/unit_test.hpp>
#include <functional>
#include <iostream>
#include <fstream>
#include <stdint.h>

#include <netlistDB/netlist.h>
#include <netlistDB/statement_if.h>
#include <netlistDB/hw_type/common.h>
#include <netlistDB/query/expr_sensitivity_probe.h>

using namespace netlistDB;
using namespace netlistDB::hw_type;
using namespace netlistDB::query;
using namespace netlistDB::utils;

using namespace std;
namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE( netlistDB_expr_sensitivity_probe_testsuite )

BOOST_AUTO_TEST_CASE( single_signal ) {
	Netlist ctx("test");
	auto &a = ctx.sig_in("a", hw_bit);
	auto & ar = a.rising();

	{
		SensitivityCtx sens;
		set<iNode*> seen;
		ExprSensitivityProbe::apply(a, seen, sens);
		BOOST_TEST(sens == vector<iNode*>({&a}), tt::per_element());
	}
	{
		SensitivityCtx sens;
		set<iNode*> seen;
		ExprSensitivityProbe::apply(ar, seen, sens);
		BOOST_TEST(sens == vector<iNode*>({ar.drivers[0]}), tt::per_element());
	}
	{
		auto & a_gate = a.rising() & ctx.sig_in("b", hw_bit);
		SensitivityCtx sens;
		set<iNode*> seen;
		ExprSensitivityProbe::apply(a_gate, seen, sens);
		BOOST_TEST(sens == vector<iNode*>({ar.drivers[0]}), tt::per_element());
	}
	{
		auto & b = ctx.sig_in("b", hw_bit);
		auto & c = ctx.sig_in("c", hw_bit);

		auto & expr = (a & b) & c;
		SensitivityCtx sens;
		set<iNode*> seen;
		ExprSensitivityProbe::apply(expr, seen, sens);
		BOOST_TEST(sens == set<iNode*>({&a, &b, &c, }), tt::per_element());
	}
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_SUITE_END()
