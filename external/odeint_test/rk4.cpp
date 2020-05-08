#define CATCH_CONFIG_MAIN
#include <boost/array.hpp>
#include <boost/numeric/odeint.hpp>
#include "catch.hpp"
#include <cmath>

namespace
{
    const double pi = acos(-1.);
    const double g = 9.81; // acceleration due to gravity [m/s/s]
	const double FIVE_PERCENT = 0.05;
}

SCENARIO( "RK4 works on a simple problem", "[odeint]" ) {

	// Small angle apporximation pendulum model
	class Pendulum
	{
	public:
		Pendulum(double length) : L(length) { T = 2. * pi * std::sqrt(L / g); }
		double angularAcceleration(double theta) const { return -g / L * std::sin(theta); }
		double getPeriod() const { return T; }
	private:
		double L; // length [m]
		double T; // period [s]
		Pendulum() = delete;
	};

	// 2D array for holding pendulum state vector
	using Array2D = std::array<double, 2>;

	// list of state variable for a pendulum
	struct State
	{
		double theta; // arm's angular displacement [rad]
		double thetaDot; // arm's angular velocity [rad/s]

		// conversion between array and struct
		static State from_array(const Array2D& x) { return State{ x[0], x[1] }; }
	};

    GIVEN( "A frictionless pendulum simulation" ) {

		// Odeint state space model of a large pendulum system
		const Pendulum p(0.8);

		// System Dynamics
		auto pendulumStateSpaceModel = [&p](const Array2D& x, Array2D& dxdt, double /*time invariant system*/) {
			auto s = State::from_array(x);
			dxdt = { s.thetaDot, p.angularAcceleration(s.theta) };
		};
		
		// Numerical Solver
		boost::numeric::odeint::runge_kutta4<Array2D> rk4;

        WHEN( "the simulation is run over a time interal equal to the period of the pendulum" ) {

			const double tSimStart = 0.;
			const double tSimEnd = p.getPeriod() + tSimStart;       // Simulate one complete swing
			const double tSimStep = 0.1 * (tSimEnd - tSimStart);

			const State xInitial{ pi * 0.002, 0.01 };

			Array2D x = { xInitial.theta, xInitial.thetaDot };
			boost::numeric::odeint::integrate_const(rk4, pendulumStateSpaceModel, x, tSimStart, tSimEnd, tSimStep);
			auto xFinal = State::from_array(x);

            THEN( "the pendulum should return to its initial state at the end of the simulation" ) {
				
				// https://github.com/catchorg/Catch2/blob/master/docs/assertions.md#top
                REQUIRE(xFinal.theta == Approx(xInitial.theta).epsilon(FIVE_PERCENT));
				REQUIRE(xFinal.thetaDot == Approx(xInitial.thetaDot).epsilon(FIVE_PERCENT));
            }
        }
    }
}