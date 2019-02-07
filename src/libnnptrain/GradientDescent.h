// n2p2 - A neural network potential package
// Copyright (C) 2018 Andreas Singraber (University of Vienna)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include "Updater.h"
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace nnp
{

class GradientDescent : public Updater
{
public:
    /// Enumerate different gradient descent variants.
    enum DescentType
    {
        /// Fixed step size.
        DT_FIXED,
        /// Adaptive moment estimation (Adam).
        DT_ADAM
    };

    /** %GradientDescent class constructor.
     *
     * @param[in] type Descent type used for step size.
     * @param[in] sizeState Number of neural network connections (weights
     *                      and biases).
     */
    GradientDescent(DescentType const type, std::size_t const sizeState);
    /** Destructor.
     */
    ~GradientDescent() {};
    /** Set state vector.
     *
     * @param[in,out] state State vector (changed in-place upon calling
     *                      #update()).
     */
    void                     setState(double* state);
    /** Set error.
     *
     * @param[in] error Error value (left unchanged).
     */
    void                     setError(double const* const error);
    /** Set derivative matrix.
     *
     * @param[in] derivatives Derivative matrix (left unchanged).
     */
    void                     setDerivativeMatrix(
                                              double const* const derivatives);
    /** Perform connection update.
     *
     * Update the connections via steepest descent method.
     */
    void                     update();
    /** Set parameters for fixed step gradient descent algorithm.
     *
     * @param[in] eta Step size = ratio of gradient subtracted from current
     *                weights.
     */
    void                     setParametersFixed(double const eta);
    /** Set parameters for Adam algorithm.
     *
     * @param[in] eta Step size (corresponds to @f$\alpha@f$ in Adam
     *                publication).
     * @param[in] beta1 Decay rate 1 (first moment).
     * @param[in] beta2 Decay rate 2 (second moment).
     * @param[in] epsilon Small scalar.
     */
    void                     setParametersAdam(double const eta,
                                               double const beta1,
                                               double const beta2,
                                               double const epsilon);
    /** Status report.
     *
     * @param[in] epoch Current epoch.
     *
     * @return Line with current status information.
     */
    std::string              status(std::size_t epoch) const;
    /** Header for status report file.
     *
     * @return Vector with header lines.
     */
    std::vector<std::string> statusHeader() const;
    /** Information about gradient descent settings.
     *
     * @return Vector with info lines.
     */
    std::vector<std::string> info() const;

private:
    DescentType         type;
    /// Number of neural network connections (weights + biases).
    std::size_t         sizeState;
    /// Learning rate @f$\eta@f$.
    double              eta;
    /// Decay rate 1 (Adam).
    double              beta1;
    /// Decay rate 2 (Adam).
    double              beta2;
    /// Small scalar.
    double              epsilon;
    /// Decay rate 1 to the power of t (Adam).
    double              beta1t;
    /// Decay rate 2 to the power of t (Adam).
    double              beta2t;
    /// State vector pointer.
    double*             state;
    /// Error pointer (single double value).
    double const*       error;
    /// Derivatives vector pointer.
    double const*       derivatives;
    /// First moment estimate (Adam).
    std::vector<double> m;
    /// Second moment estimate (Adam).
    std::vector<double> v;
};

}

#endif
