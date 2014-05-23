#ifndef ___M_STACK_IMAGE_H___
#define ___M_STACK_IMAGE_H___

//typedef unsigned char VOXEL;

#include "CObjectCommunicator.h"
#include "CObjectCommunicatorID.h"
#include "BPoint3D.h"

class MStackImage : public BTerminal {
 public:
	MStackImage(void);
	MStackImage(int x, int y, int z);
	~MStackImage(void);

    virtual MStackImage &operator= (MStackImage &orig);

	// getters
	unsigned char	getData(int x, int y, int z) { return DataArray[Size.x * Size.y * z + Size.x * y + x]; }
	unsigned char   getData(int sfx) { return DataArray[sfx]; }
	
	int             getX(void) { return Size.x; }
	int		        getY(void) { return Size.y; }
	int		        getZ(void) { return Size.z; }

	double          getScaleX(void) { return Scale.x; }
	double          getScaleY(void) { return Scale.y; }
	double          getScaleZ(void) { return Scale.z; }

	// setters
	unsigned char	setData(int x, int y, int z, unsigned char value) { return DataArray[Size.x * Size.y * z + Size.x * y + x] = value; }
	unsigned char	setData(int sfx, unsigned char value) { return DataArray[sfx] = value; }
	unsigned char   setData(POINT3D point, unsigned char value);

	void            setScaleX(double value) { Scale.x = value; }
	void            setScaleY(double value) { Scale.y = value; }
	void            setScaleZ(double value) { Scale.z = value; }

	// file I/O
	int		        loadGraphs(const char *in_sFileName, int in_nNum, bool doMedian = false);
	int             saveGraphs(const char *in_sFileName, int in_nNum = -1);
	int		        saveData(const char *in_sFileName);

	int             load(const char *iFileName, int iStartSfx = 0);
	int             save(const char *iFileName);

    void            reset(unsigned char value = 0);
    void            reset(int x, int y, int z, unsigned char value = 0);

    // generate data
    int             generateData(int type, double params[GENERATE_STACKIMAGE_PARAMNUM]);

 protected:
	unsigned char	*DataArray;

	struct _Size {
		int x;
		int y;
		int z;
	}               Size;

	struct _Scale {
		double x;
		double y;
		double z;
	}               Scale;

	char            BaseNameFormat[1024];
	int             ImageNumberDigits;

 public:
    void setDataNo(int no) { DataNo = no; }
    int getDataNo(void) { return DataNo; }

 protected:
    int DataNo;
	void procedure(int ID, char *data, int byte);
    
};

typedef MStackImage VoxelClass;

class DistanceLabelClass {
	DistanceLabelClass(void);
 public:
	DistanceLabelClass(int in_x, int in_y, int in_z, unsigned int in_initValue = 0);
	~DistanceLabelClass(void);

	unsigned int	getData(int in_x, int in_y, int in_z) { return m_Data[m_nX * m_nY * in_z + m_nX * in_y + in_x]; }
	unsigned int	setData(int in_x, int in_y, int in_z, unsigned int value) { return m_Data[m_nX * m_nY * in_z + m_nX * in_y + in_x] = value; }

	int		getX(void) { return m_nX; }
	int		getY(void) { return m_nY; }
	int		getZ(void) { return m_nZ; }

	unsigned int	setMaxValue(unsigned int in_MaxValue) { return m_uMaxValue = in_MaxValue; }
	unsigned int	getMaxValue(void) { return m_uMaxValue; }

	int     	loadGraphs(const char *in_sFileName, int in_nNum);
	int		saveGraphs(const char *in_sFileName, int in_nNum = -1);
	int		saveData(const char *in_sFileName);

 protected:
	unsigned int	*m_Data;

#if defined (POINT3D_DOUBLE_)
	double			m_nX;
	double			m_nY;
	double			m_nZ;
#else
	short				m_nX;
	short				m_nY;
	short				m_nZ;
#endif

	unsigned int	m_uMaxValue;
};

#endif//___M_STACK_IMAGE_H___

