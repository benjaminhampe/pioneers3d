// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_HAMPE_SINCOS_TABLE_EXTENSIONS_H__
#define __IRR_HAMPE_SINCOS_TABLE_EXTENSIONS_H__

#include <irrlicht.h>

namespace irr
{
namespace core
{

	//! sinus table
	template <class T>
	class TSinTable : public IReferenceCounted
	{
	public:
		explicit TSinTable( u32 count = 36, T radian_angle_start = T(0.0), T radian_angle_end = 2.0f*core::PI )
		{
			m_count = (count>0)?count:1;
			m_table = new T[m_count];
			m_angle_start = radian_angle_start;
			m_angle_end = radian_angle_end;
			m_angle_step = (m_angle_end - m_angle_start) / m_count;

			for (u32 i=0; i<m_count; i++)
			{
				if (sizeof(T) < 8)
				{	m_table[i] = sinf( m_angle_start + m_angle_step * i ); }
				else
				{	m_table[i] = sin( m_angle_start + m_angle_step * i ); }
			}
		}
		~TSinTable() { if (m_table) delete [] m_table; }

		T& operator[] (u32 index) { return m_table[index%m_count]; }

		const T& operator[] (u32 index) const { return m_table[index%m_count]; }

		const T& getAngleStepRad() const { return m_angle_step; }

		const T& getAngleStartRad() const { return m_angle_start; }

		const T& getAngleEndRad() const { return m_angle_end; }

	private:
		u32 m_count;
		T* m_table;

		T m_angle_step;
		T m_angle_start;
		T m_angle_end;

	}; // end class TSinTable

	//! cosinus table
	template <class T> class TCosTable  : public IReferenceCounted
	{
	public:
		explicit TCosTable( u32 count, T radian_angle_start = T(0), T radian_angle_end = 2.0f*core::PI )
		{
			m_count = (count>0)?count:1;
			m_table = new T[m_count];
			m_angle_start = radian_angle_start;
			m_angle_end = radian_angle_end;
			m_angle_step = (m_angle_end - m_angle_start) / m_count;

			for (u32 i=0; i<m_count; i++)
			{
				if (sizeof(T) < 8)
				{	m_table[i] = cosf( m_angle_start + m_angle_step * i ); }
				else
				{	m_table[i] = cos( m_angle_start + m_angle_step * i ); }
			}
		}
		~TCosTable() { if (m_table) delete [] m_table; }

		T& operator[] (u32 index) { return m_table[index%m_count]; }

		const T& operator[] (u32 index) const { return m_table[index%m_count]; }

		const T& getAngleStepRad() const { return m_angle_step; }

		const T& getAngleStartRad() const { return m_angle_start; }

		const T& getAngleEndRad() const { return m_angle_end; }

	private:
		u32 m_count;
		T* m_table;

		T m_angle_step;
		T m_angle_start;
		T m_angle_end;
	}; // end class TCosTable

	typedef TSinTable<f32> CSinTablef;

	typedef TCosTable<f32> CCosTablef;

} // end namespace core

} // end namespace irr

#endif // __IRR_HAMPE_SINCOS_TABLE_EXTENSIONS_H__
