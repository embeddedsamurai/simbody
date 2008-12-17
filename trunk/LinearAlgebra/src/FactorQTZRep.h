#ifndef _FACTOR_QTZ_REP_H_ 
#define _FACTOR_QTZ_REP_H_
/* Portions copyright (c) 2007 Stanford University and Jack Middleton.
 * Contributors:
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "SimTKmath.h"
#include "WorkSpace.h"

namespace SimTK {

class FactorQTZRepBase {
public:
    FactorQTZRepBase() : isFactored(false), rank(0) {}

    virtual ~FactorQTZRepBase(){};

    virtual FactorQTZRepBase* clone() const { return 0; };
    virtual void solve( const Vector_<float>& b, Vector_<float>& x ) const {
        checkIfFactored();
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
        "solve called with rhs of type <float>  which does not match type of original linear system \n");
   }
   virtual void solve( const Vector_<double>& b, Vector_<double>& x ) const {
        checkIfFactored();
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
        "solve called with rhs of type <double>  which does not match type of original linear system \n");
   }
   virtual void solve( const Vector_<std::complex<float> >& b, Vector_<std::complex<float> >& x ) const {
        checkIfFactored();
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
        "solve called with rhs of type complex<float> which does not match type of original linear system \n");
   }
   virtual void solve( const Vector_<std::complex<double> >& b, Vector_<std::complex<double> >& x ) const {
        checkIfFactored();
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
        "solve called with rhs of type complex<double>  which does not match type of original linear system \n");   
   }
    virtual void solve( const Matrix_<float>& b, Matrix_<float>& x ) const {
        checkIfFactored();
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
        "solve called with rhs of type <float>  which does not match type of original linear system \n");
   }
   virtual void solve( const Matrix_<double>& b, Matrix_<double>& x ) const {
        checkIfFactored();
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
        "solve called with rhs of type <double>  which does not match type of original linear system \n");
   }
   virtual void solve( const Matrix_<std::complex<float> >& b, Matrix_<std::complex<float> >& x ) const {
        checkIfFactored();
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
        "solve called with rhs of type complex<float> which does not match type of original linear system \n");
   }
   virtual void solve  ( const Matrix_<std::complex<double> >& b, Matrix_<std::complex<double> >& x ) const {
       checkIfFactored();
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
        "solve called with rhs of type complex<double>  which does not match type of original linear system \n");   
   }
    virtual void inverse(  Matrix_<double>& inverse ) const {
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","inverse",
        "inverse(  <double> ) called with type that is inconsistant with the original matrix  \n");
    }
    virtual void inverse(  Matrix_<float>& inverse ) const {
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","inverse",
        "inverse(  <float> ) called with type that is inconsistant with the original matrix  \n");
    }
    virtual void inverse(  Matrix_<std::complex<float> >& inverse ) const {
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","inverse",
        "inverse(  std::complex<float> ) called with type that is inconsistant with the original matrix  \n");
    }
    virtual void inverse(  Matrix_<std::complex<double> >& inverse ) const {
        SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","inverse",
        "inverse(  std::complex<double> ) called with type that is inconsistant with the original matrix  \n");
    }


   bool isFactored;
   int rank;     // esitmated rank computed during factorization

   void checkIfFactored()  const {
       if( !isFactored ) {
           SimTK_APIARGCHECK_ALWAYS(false,"FactorQTZ","solve",
           "solve called before the matrix was factored \n");
       }
   }

}; // class FactorQTZRepBase

class FactorQTZDefault : public FactorQTZRepBase {
   public:
	   FactorQTZDefault();
	   FactorQTZRepBase* clone() const;
};

template <typename T>
class FactorQTZRep : public FactorQTZRepBase {
public:
   template <class ELT> FactorQTZRep( const Matrix_<ELT>&, typename CNT<T>::TReal );
   FactorQTZRep();

   ~FactorQTZRep();

   template < class ELT > void factor(const Matrix_<ELT>& ); 
   void inverse( Matrix_<T>& ) const; 
   void solve( const Vector_<T>& b, Vector_<T>& x ) const;
   void solve( const Matrix_<T>& b, Matrix_<T>& x ) const;

   FactorQTZRepBase* clone() const;
 
private:
   void doSolve( Matrix_<T>& b, Matrix_<T>& x ) const;

   int                      mn;           // min of number of rows or columns
   int                      maxmn;        // max of number of rows or columns
   int                      nRow;         // number of rows in original matrix
   int                      nCol;         // number of columns in original matrix
   bool                     scaleLinSys; // true if matrix was scaled during factorization
   typename CNT<T>::TReal   linSysScaleF; // scale factor applied to matrix 
   typename CNT<T>::TReal   anrm;
   typename CNT<T>::TReal   rcond;   // reciprocol condition number
   TypedWorkSpace<int>      pivots;
   TypedWorkSpace<T>        qtz;     // factored matrix
   TypedWorkSpace<T>        tauGEQP3;
   TypedWorkSpace<T>        tauORMQR;

}; // end class FactorQTZRep

} // namespace SimTK

#endif   //  _FACTOR_QTZ_REP_H_
