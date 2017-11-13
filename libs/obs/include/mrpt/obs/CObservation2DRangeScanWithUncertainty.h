/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          http://www.mrpt.org/                          |
   |                                                                        |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file     |
   | See: http://www.mrpt.org/Authors - All rights reserved.                |
   | Released under BSD License. See details in http://www.mrpt.org/License |
   +------------------------------------------------------------------------+ */
#ifndef CObservation2DRangeScanWithUncertainty_H
#define CObservation2DRangeScanWithUncertainty_H

#include <mrpt/obs/CObservation2DRangeScan.h>
#include <vector>

namespace mrpt
{
namespace obs
{
/** A 2D range scan plus an uncertainty model for each range.
  * \sa mrpt::maps::COccupancyGridMap2D::laserScanSimulatorWithUncertainty()
  */
class CObservation2DRangeScanWithUncertainty
{
   public:
	/** The observation with the mean ranges in the scan field */
	CObservation2DRangeScan rangeScan;
	/** The same ranges than in rangeScan.scan[], for convenience as an Eigen
	 * container, and with `double` precision */
	Eigen::VectorXd rangesMean;
	/** The covariance matrix for all the ranges in rangeScan.scan[] */
	Eigen::MatrixXd rangesCovar;

	struct TEvalParams
	{
		/** (Default: 0.5) Probability of having an outlier (dynamic obstacles,
		 * not mapped) in each scan ray. */
		double prob_outliers;
		/** (Default: 0.3) Conditional probability: how many of the "no return"
		 * ranges come from a failure to detect a real obstacle. */
		double prob_lost_ray;
		/** (Default: 1.0m) Maximum std deviation of overall uncertainty for a
		 * range prediction to be considered as reliable for evaluation */
		double max_prediction_std_dev;
		/** (Default: -20) Minimum log-likelihood of a single ray */
		double min_ray_log_lik;

		TEvalParams();
	};

	/** Returns a measure of the likelihood of a given scan, compared to this
	 * scan variances */
	double evaluateScanLikelihood(
		const CObservation2DRangeScan& otherScan,
		const TEvalParams& params) const;
};

}  // End of namespace
}  // End of namespace
#endif
