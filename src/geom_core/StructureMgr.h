//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

// StructureMgr.h
//
// Justin Gravett
//////////////////////////////////////////////////////////////////////

#if !defined(STRUCTUREMGR__INCLUDED_)
#define STRUCTUREMGR__INCLUDED_

#include "FeaStructure.h"

class StructureMgrSingleton : public ParmContainer
{
protected:
    StructureMgrSingleton();

public:

    static StructureMgrSingleton& getInstance()
    {
        static StructureMgrSingleton instance;
        return instance;
    }

    virtual ~StructureMgrSingleton();

    virtual xmlNodePtr EncodeXml( xmlNodePtr & node );
    virtual xmlNodePtr DecodeXml( xmlNodePtr & node );

    void Renew();
    void Wype();

    void AddLinkableContainers( vector< string > & linkable_container_vec );

    //==== FeaStructure Management ====//
    static vector < FeaStructure* > GetAllFeaStructs();
    void ResetAllExportFileNames();
    FeaStructure* GetFeaStruct( int total_struct_ind );
    FeaStructure* GetFeaStruct( const string & struct_id );
    string GetFeaStructParentID( const string & struct_id );
    bool ValidTotalFeaStructInd( int index );
    int NumFeaStructures();
    int GetTotFeaStructIndex( FeaStructure* fea_struct );
    int GetGeomFeaStructIndex( const string & struct_id );
    FeaPart* GetFeaPart( const string & feapart_id );
    SubSurface* GetFeaSubSurf( const string & feasubsurf_id );
    int GetFeaSubSurfIndex( const string & ss_id );
    string GetFeaPartName( const string & id );
    int GetFeaPropertyIndex( const string & FeaPartID );
    int GetFeaMaterialIndex( const string & FeaPartID );
    void ShowAllParts();

    void UpdateStructUnit( int new_unit );

    //==== FeaProperty Management ====//
    void AddFeaProperty( FeaProperty* fea_prop )
    {
        m_FeaPropertyVec.push_back( fea_prop );
    }
    FeaProperty* AddFeaProperty( int property_type );
    void DeleteFeaProperty( int index );
    bool ValidFeaPropertyInd( int index );
    FeaProperty* GetFeaProperty( int index );

    vector < FeaProperty* > GetFeaPropertyVec()
    {
        return m_FeaPropertyVec;
    }
    int NumFeaProperties()
    {
        return m_FeaPropertyVec.size();
    }
    void InitFeaProperties();

    //==== FeaMaterial Management ====//
    void AddFeaMaterial( FeaMaterial* fea_mat )
    {
        m_FeaMaterialVec.push_back( fea_mat );
    }
    FeaMaterial* AddFeaMaterial();
    void DeleteFeaMaterial( int index );
    bool ValidFeaMaterialInd( int index );
    FeaMaterial* GetFeaMaterial( int index );
    void InitFeaMaterials();

    vector < FeaMaterial* > GetFeaMaterialVec()
    {
        return m_FeaMaterialVec;
    }
    int NumFeaMaterials()
    {
        return m_FeaMaterialVec.size();
    }

    FeaAssembly* GetFeaAssembly( const string & assyid );
    void AddFeaAssembly( FeaAssembly* fea_assy )
    {
        m_FeaAssemblyVec.push_back( fea_assy );
    }
    FeaAssembly* AddFeaAssembly( );
    void DeleteFeaAssembly( int index );
    bool ValidFeaAssemblyInd( int index );
    FeaAssembly* GetFeaAssembly( int index );

    vector < FeaAssembly* > GetFeaAssemblyVec()
    {
        return m_FeaAssemblyVec;
    }
    int NumFeaAssembly()
    {
        return m_FeaAssemblyVec.size();
    }

    void SetCurrPartIndex( int ind )
    {
        m_CurrPartIndex = ind;
    }
    int GetCurrPartIndex()
    {
        return m_CurrPartIndex;
    }

    void SetCurrAssemblyIndex( int ind )
    {
        m_CurrFeaAssemblyIndex = ind;
    }
    int GetCurrAssemblyIndex()
    {
        return m_CurrFeaAssemblyIndex;
    }

    void SetCurrMaterialIndex( int ind )
    {
        m_CurrFeaMaterialIndex = ind;
    }
    int GetCurrMaterialIndex()
    {
        return m_CurrFeaMaterialIndex;
    }

    void SetCurrPropertyIndex( int ind )
    {
        m_CurrFeaPropertyIndex = ind;
    }
    int GetCurrPropertyIndex()
    {
        return m_CurrFeaPropertyIndex;
    }

    void SetCurrBCIndex( int ind )
    {
        m_CurrFeaBCIndex = ind;
    }
    int GetCurrBCIndex()
    {
        return m_CurrFeaBCIndex;
    }

    void SetFeaSliceOrientIndex( int ind )
    {
        m_FeaSliceOrientationIndex = ind;
    }
    int GetFeaSliceOrientIndex()
    {
        return m_FeaSliceOrientationIndex;
    }

    IntParm m_CurrStructIndex;

protected:

    vector < FeaAssembly* > m_FeaAssemblyVec;
    int m_FeaAssemblyCount;

    vector < FeaProperty* > m_FeaPropertyVec;
    int m_FeaPropertyCount;

    vector < FeaMaterial* > m_FeaMaterialVec;
    int m_FeaMatCount;

    int m_CurrPartIndex;
    int m_CurrFeaAssemblyIndex;
    int m_CurrFeaMaterialIndex;
    int m_CurrFeaPropertyIndex;
    int m_CurrFeaBCIndex;
    int m_FeaSliceOrientationIndex; // Identifies the default orientation for FeaSlices; 0: XY_PLANE, 1: YZ_PLANE, 2: XZ_PLANE
};

#define StructureMgr StructureMgrSingleton::getInstance()

#endif