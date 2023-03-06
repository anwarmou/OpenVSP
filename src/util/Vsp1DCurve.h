//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

// Vsp1DCurve.h:
//
//////////////////////////////////////////////////////////////////////

#ifndef VSP_1D_CURVE_H
#define VSP_1D_CURVE_H

#include "Matrix4d.h"
#include "BndBox.h"

#include <vector>
using std::vector;

#include "eli/code_eli.hpp"

#include "eli/geom/curve/bezier.hpp"
#include "eli/geom/curve/piecewise.hpp"

typedef eli::geom::curve::bezier<double, 1> oned_curve_segment_type;
typedef eli::geom::curve::piecewise<eli::geom::curve::bezier, double, 1> oned_piecewise_curve_type;

class Vsp1DCurve
{
public:

    Vsp1DCurve();
    virtual ~Vsp1DCurve();

    void Copy( Vsp1DCurve & input_crv );
    void Split( double u );
    void Append( Vsp1DCurve & input_crv ); // Append Curve

    bool IsClosed() const;

    // creates C0 continuous piecewise line
    void InterpolateLinear( vector< double > & input_pnt_vec, const vector<double> &param, bool closed_flag );

    // creates C1 continuous Piecewise Cubic Hermite Interpolating Polynomial
    void InterpolatePCHIP( vector< double > & input_pnt_vec, const vector<double> &param, bool closed_flag );

    // creates C2 continuous piecewise cubic spline polynomial with not-a-knot or closed end conditions
    void InterpolateCSpline( vector< double > & input_pnt_vec, const vector<double> &param, bool closed_flag );

    // creates C2 continuous piecewise cubic spline polynomial with clamped end slopes
    void InterpolateCSpline( vector< double > & input_pnt_vec, const double &start_slope, const double &end_slope, const vector<double> &param );

    void BinCubicTMap( vector < double > &tmap, vector < double > &tdisc ) const;
    void GetTMap( vector < double > &tmap, vector < double > &tdisc ) const;
    void GetTMap( vector < double > &tmap ) const;
    void ToBinaryCubic( );
    void ToCubic();

    void SetCubicControlPoints( const vector< double > & cntrl_pts, bool closed_flag );
    void SetCubicControlPoints( const vector< double > & cntrl_pts, const vector< double > & param, bool closed_flag );

    void GetCubicControlPoints( vector< double > & cntrl_pts, vector< double > & param );

    const oned_piecewise_curve_type & GetCurve() const;
    void SetCurve( const oned_piecewise_curve_type &c );
    void AppendCurveSegment( oned_curve_segment_type &c );

    double FindNearest( double &u, const double &pt ) const;
    double FindNearest( double &u, const double &pt, const double &u0 ) const;

    double FindNearest01( double &u, const double &pt ) const;
    double FindNearest01( double &u, const double &pt, const double &u0 ) const;

    //===== Bezier Funcs ====//
    double CompPnt( double u ) const;
    double CompTan( double u ) const;

    double CompPnt01( double u ) const;
    double CompTan01( double u ) const;

    //===== Tesselate ====//
    void TesselateNoCorner( int num_pnts_u, double umin, double umax, vector< double > & output, vector< double > &uout );
    void Tesselate( const vector< double > &u, vector< double > & output );

    void TessAdapt( vector< double > & output, vector< double > & uout, double tol, int Nlimit );
    void TessAdapt( double umin, double umax, std::vector< double > & pnts, vector< double > & uout, double tol, int Nlimit );
    void TessAdapt( double umin, double umax, const double & pmin, const double & pmax, std::vector< double > & pnts, vector< double > & uout, double tol, int Nlimit, int Nadapt = 0 );

    void Scale( double s );

    void Reverse();

    void Roll( double u );
    void Trim( double u, bool before );
    void Join( const Vsp1DCurve &a, const Vsp1DCurve &b );
    void CapMax();
    void CapMin();
    double Invert( double f ) const;

    void product( Vsp1DCurve c1, Vsp1DCurve c2 );

    bool IsEqual( const Vsp1DCurve & crv );

    void GetBoundingBox( double &ymin, double &ymax ) const;

    double IntegrateCrv( );
    double IntegrateCrv( double r0 );
    double IntegrateCrv_r( );
    double IntegrateCrv_r( double r0 );
    double IntegrateCrv_rsq( );
    double IntegrateCrv_rsq( double r0 );
    double IntegrateCrv_rcub( );
    double IntegrateCrv_rcub( double r0 );

    double GetSegFirstPoint( int i ) const;
    double GetSegLastPoint( int i ) const;

protected:
    oned_piecewise_curve_type m_Curve;

    int GetNumSections() const;
    void GetCurveSegment( oned_curve_segment_type &c, int i ) const;
    double GetCurveDt( int i ) const;
};


#endif


