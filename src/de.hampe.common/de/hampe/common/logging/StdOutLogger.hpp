//////////////////////////////////////////////////////////////////////
/// @file 	StdOutLogger.hpp
/// @brief 	Definition of class StdOutLogger
/// @author Copyright (c) Benjamin Hampe <benjaminhampe@gmx.de>
///
///	The author grants permission of free use, free distribution and
/// free usage for commercial applications even for modified sources.
///
///	What is not allowed is to remove the original authors name or claim
/// any intellectual rights. This original code was written in my spare time
/// and is distributed publicly as free software to anyone over GitLab and GitHub.
///
//////////////////////////////////////////////////////////////////////

#ifndef DE_HAMPE_COMMON_LOGGING_STDOUTLOGGER_HPP
#define DE_HAMPE_COMMON_LOGGING_STDOUTLOGGER_HPP

#include <de/hampe/common/logging/Types.hpp>
#include <de/hampe/common/logging/LogLevel.hpp>
#include <de/hampe/common/sprintf.hpp>
#include <iostream>

BEGIN_NAMESPACE_DE_HAMPE_COMMON_LOGGING

   class StdOutLogger
   {
   public:
      StdOutLogger();
      StdOutLogger( std::string const & name );
      StdOutLogger( StdOutLogger const & other );
      ~StdOutLogger();

      void
      flush();

      std::string const &
      getName() const;

      void
      setName( std::string const & name );

      template < typename T >
      StdOutLogger&
      operator<< ( T const & t )
      {
         std::cout << t;
         return *this;
      }

      StdOutLogger&
      operator<< ( LogLevel const & logLevel );

      StdOutLogger&
      operator<< ( std::ostream& (*func)( std::ostream& ) );

   private:
      std::string m_Name;
   };

END_NAMESPACE_DE_HAMPE_COMMON_LOGGING

#endif // DE_HAMPE_LOGGING_STDOUTLOGGER_HPP















