#ifndef P3D_TILE_TYPE_H
#define P3D_TILE_TYPE_H

class TileType
{
public:
	enum ETileType
	{
		WASSER = 0,
		HOLZ,
		LEHM,
		WEIZEN,
		ERZ,
		WOLLE,
		HAFEN_3_ZU_1,
		HAFEN_HOLZ,
		HAFEN_LEHM,
		HAFEN_WEIZEN,
		HAFEN_ERZ,
		HAFEN_WOLLE,
		FORCE_32BIT = 65536
	};
	
	TileType() : m_TileType( WASSER ) {}
	
	TileType( ETileType tileType ) : m_TileType( tileType ) {}
	
	TileType( TileType const & other ) : m_TileType( other.m_TileType ) {}
	
	TileType& operator=( TileType const & other ) { m_TileType = other.m_TileType; return *this; }
	
	operator ETileType() const { return m_TileType; }
	
	void setValue( ETileType tileType ) { m_TileType = tileType; }
	
	ETileType getValue() const { return m_TileType; }
	
private:
	ETileType m_TileType;
};

#endif // P3D_TILE_TYPE_H
