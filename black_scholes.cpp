/*
 Options pricing calculator based on the Black-Scholes Model.

 Function of five inputs:
    - stock price
    - exercise/strike price
    - time to expiration
    - volatility of underlying stock
    - risk-free rate of interest
*/

#include <iostream>
#include <cmath>

using namespace std;

double cdf_normal_distribution(double value) {
    // https://en.wikipedia.org/wiki/Normal_distribution
    // phi(x) = 1 / (sqrt(2 * pi)) * integral(-infinity, x) { exp(-t^2 / 2) dt }
    // erf(x) = 2 / sqrt(pi) * integral(0, x) { exp(-t^2) dt }
    // phi(x) = 0.5 * [1 + erf(x / sqrt(2)]

    // M_SQRT1_2 = 1 / sqrt(2)
    return 0.5 * (1 + erf(value * M_SQRT1_2));
}

double calculate_call_price(double stock_price, double strike_price, double days_to_expiration, double volatility, double risk_free_rate) {
    double d1 = (log(stock_price / strike_price) + ((risk_free_rate + (pow(volatility, 2.0) / 2.0)) * days_to_expiration)) / (volatility * sqrt(days_to_expiration));
    double d2 = d1 - (volatility * sqrt(days_to_expiration));

    return (cdf_normal_distribution(d1) * stock_price) - (cdf_normal_distribution(d2) * strike_price * exp(-risk_free_rate * days_to_expiration));
}

double calculate_put_price(double stock_price, double strike_price, double days_to_expiration, double volatility, double risk_free_rate) {

    return calculate_call_price(stock_price, strike_price, days_to_expiration, volatility, risk_free_rate) + (strike_price / exp(risk_free_rate * days_to_expiration)) - stock_price;
}

int main(int argc, const char** argv) {
    cout << "Options pricing calculator based on the Black-Scholes Model." << endl;

    if (argc != 6) {
        cerr << "Error: Input [Stock Price ($)] [Strike Price ($)] [Days to Expiration (days)] [Volatility (%)] [Risk-Free Rate of Interest (%)]" << endl;
        exit(1);
    }

    cout << endl;

    // get input
    double stock_price = strtod(argv[1], nullptr);
    double strike_price = strtod(argv[2], nullptr);
    double days_to_expiration = strtod(argv[3], nullptr);
    double volatility = strtod(argv[4], nullptr);
    double risk_free_rate = strtod(argv[5], nullptr);

    // output
    cout << "Stock Price: $" << stock_price << endl;
    cout << "Strike Price: $" << strike_price << endl;
    cout << "Days to Expiration: " << days_to_expiration << " days" << endl;
    cout << "Volatility: " << volatility << "%" << endl;
    cout << "Risk-Free Rate of Interest: " << risk_free_rate << "%" << endl;

    cout << endl;

    // convert to years
    days_to_expiration /= 365.0;
    // convert to decimal
    volatility /= 100.0;
    risk_free_rate /= 100.0;

    cout.precision(2);
    cout << fixed;
    cout << "Call Option Value: $" << calculate_call_price(stock_price, strike_price, days_to_expiration, volatility, risk_free_rate) << endl;
    cout << "Put Option Value: $" << calculate_put_price(stock_price, strike_price, days_to_expiration, volatility, risk_free_rate) << endl;

    return 0;
}
