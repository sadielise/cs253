#ifndef EXCEPTION_H_DEFINED
#define EXCEPTION_H_DEFINED

#include<exception>
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;

namespace csucv {

/*! \file Exception.h
 *  \brief Specializations of std::exception for errors detected by CSUCV. 
 *
 * In general, CSUCV is templated so as to catch as many errors as possible at compile time
 * (particularly data type errors). Run-time errors are thrown as exceptions that inherit from
 * the Exception class. The Exception class itself inherits std::exception, so code that catches
 * std::exception will catch all CSUCV errors as well. There are then specialized subclasses for
 * specific types of run-time errors, for example out of bounds exceptions and data type mismatches
 * that cannot be caught at compiler time, e.g. when getting an image from OpenCV.
 */

/*! \class Exception
 * \brief Parent class for all CSUCV exceptions. Inherits std::exception.
 *
 * Parent class for all CSUCV exceptions that specializes the std::exception class. All it does
 * is add extra information to the message returned by the what() method (inherited from std::exception).
 */
class Exception : public std::exception {
public:
  /// Default constructor. What() message is simply "CSU Exception".
  Exception() : msg("CSU Exception") {}
  /// Constructor with error message provided as std::string.
  Exception(const string& error_msg) : msg(error_msg) {}
  /// Constructor with error message provided as char*
  Exception(const char* error_msg) : msg(error_msg) {}
  /// Empty destructor
  virtual ~Exception() noexcept {}
  /// Overloaded method for printing error message.
  virtual const char* what() const noexcept {return msg.c_str();}

 protected:
  /// Error message associated with this exception.
  string msg;
};

/*! \class BoundsException
 * \brief Exception class for errors in which data is accessed out of bounds.
 *
 * Exception class for errors in which data is accessed out of bounds. May be generated
 * by 1D (e.g. pixel), 2D (e.g. Image) or 3D (e.g. ImageCube) accesses, but if the access
 * is safe. In other words, at() may throw this exception, but operator [] and operator () will not.
 */
class BoundsException : public Exception {
public:
  /// Constructor for 1D out of bounds errors.
  BoundsException(const char* object_name, int index, int max_index)
  {
    ostringstream ostr;
    ostr << ": out of bounds exception. Object " << object_name << " indexed by position " << index << "; max index should be " << max_index;
    msg.append(ostr.str());
  }
};

/*! \class TypeException
 * \brief Exception class for errors in which there is a run-time data type mismatch.
 *
 * Exception class for errors in which there is a run-time data type mismatch. In general,
 * CSUCV uses templates to make sure that data type errors are caught at compile time (and for
 * efficiency). However, not all computer vision libraries do. Therefore, when passing data
 * to or from a library, there may be data type mismatches that are not caught at compile-time.
 * This is the run-time exception to signal that.
 */
class TypeException : public Exception {
public:
  /// Constructor for run-time type errors.
  TypeException(const string& csucv_type, const string& external_type)
  {
    ostringstream ostr;
    ostr << ": run-time type exception. Mismatch between CSUCV type " << csucv_type 
	 << " and external data type " << external_type;
    msg.append(ostr.str());
  }
};

/*! \class SizeException
 * \brief Exception class for errors in which there is a run-time size mismatch between arguments.
 *
 * Exception class for errors in which there is a run-time size mismatch between arguments. The 
 * mismatch may be between two vectors, two images, or two cubes.
 */
class SizeException : public Exception {
public:
  /// Constructor for 2D size mismatch errors.
    SizeException(unsigned int width1, unsigned int height1, unsigned int width2, unsigned int height2)
  {
    ostringstream ostr;
    ostr << ": run-time size exception. Mismatch between ( " << width1 << "," << height1 
	 << ") and (" << width2 << "," << height2 << ")";
    msg.append(ostr.str());
  }
};


} // namespace csucv 
#endif // EXCEPTION_H_DEFINED
