// Part of the varbvs package, https://github.com/pcarbo/varbvs
//
// Copyright (C) 2012-2017, Peter Carbonetto
//
// This program is free software: you can redistribute it under the
// terms of the GNU General Public License; either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANY; without even the implied warranty of
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
#include <Rcpp.h>
using namespace Rcpp;

// Return the sigmoid function at x.
//
// [[Rcpp::export]]
double sigmoid_rcpp (double x) {
  return(1/(1 + exp(-x)));
}

// Execute a single coordinate ascent update to maximize the variational 
// lower bound for Bayesian variable selection in linear regression.
//
// [[Rcpp::export]]
void varbvsnormupdate_rcpp (const NumericMatrix& X, double sigma, double sa,
			    double b0, const NumericVector& logodds,
			    const NumericVector& xy, const NumericVector& d,
			    NumericVector& alpha, NumericVector& mu,
			    NumericVector& Xr, const IntegerVector& i) {

  // This is the prior contribution to the posterior means.
  double mu0 = sqrt(sigma)*b0/sa;

  // Cycle through the coordinate ascent updates.
  for (int iter = 0; iter < i.size(); iter++) {

    // j is the coordinate we update in this iteration.
    int j = i[iter];

    // Compute the variational estimate of the posterior variance.
    double s = sa*sigma/(sa*d[j] + 1);

    // Update the variational estimate of the posterior mean.
    double r = alpha[j] * mu[j];
    mu[j] = s/sigma*(mu0 + xy[j] + d[j]*r - sum(X.column(j) * Xr));

    // Update the variational estimate of the posterior inclusion probability.
    alpha[j] = sigmoid_rcpp(logodds[j] + log(s/(sa*sigma))/2 +
			    (mu[j]*mu[j]/s - b0*b0/sa)/2);

    // Update Xr = X*r.
    Xr = Xr + (alpha[j] * mu[j] - r) * X.column(j);
  }
}
