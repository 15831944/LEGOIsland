#ifndef __LEGOANIM_H
#define __LEGOANIM_H

#include "LegoTree.h"
#include "LegoVertex.h"

class LegoSplineFlags {
public:
    LegoSplineFlags();
    LegoBool GetUseTension() { return m_useTension; }
    void SetUseTension(LegoBool p_useTension) { m_useTension = p_useTension; }
    LegoBool GetUseContinuity() { return m_useContinuity; }
    void SetUseContinuity(LegoBool p_useContinuity) { m_useContinuity = p_useContinuity; }
    LegoBool GetUseBias() { return m_useBias; }
    void SetUseBias(LegoBool p_useBias) { m_useBias = p_useBias; }
    LegoBool GetUseEaseTo() { return m_useEaseTo; }
    void SetUseEaseTo(LegoBool p_useEaseTo) { m_useEaseTo = p_useEaseTo; }
    LegoBool GetUseEaseFrom() { return m_useEaseFrom; }
    void SetUseEaseFrom(LegoBool p_useEaseFrom) { m_useEaseFrom = p_useEaseFrom; }
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
protected:
    LegoBool m_useTension : 1;
    LegoBool m_useContinuity : 1;
    LegoBool m_useBias : 1;
    LegoBool m_useEaseTo : 1;
    LegoBool m_useEaseFrom : 1;
};

class LegoSplineParameters {
public:
    LegoSplineParameters();
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
    LegoSplineFlags& GetFlags() { return m_flags; }
    void SetFlags(LegoSplineFlags& p_flags) { m_flags = p_flags; }
    LegoFloat GetTension() { return m_tension; }
    void SetTension(LegoFloat p_tension) { m_tension = p_tension; }
    LegoFloat GetContinuity() { return m_continuity; }
    void SetContinuity(LegoFloat p_continuity) { m_continuity = p_continuity; }
    LegoFloat GetBias() { return m_bias; }
    void SetBias(LegoFloat p_bias) { m_bias = p_bias; }
    LegoFloat GetEaseTo() { return m_easeTo; }
    void SetEaseTo(LegoFloat p_easeTo) { m_easeTo = p_easeTo; }
    LegoFloat GetEaseFrom() { return m_easeFrom; }
    void SetEaseFrom(LegoFloat p_easeFrom) { m_easeFrom = p_easeFrom; }
protected:
    LegoSplineFlags m_flags;
    LegoFloat m_tension;
    LegoFloat m_continuity;
    LegoFloat m_bias;
    LegoFloat m_easeTo;
    LegoFloat m_easeFrom;
};

class LegoAnimKey {
public:
    LegoAnimKey();
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
    LegoTime GetTime() { return m_time; }
    void SetTime(LegoTime p_time) { m_time = p_time; }
    LegoSplineParameters& GetSplineParameters() { return m_splineParameters; }
    void SetSplineParameters(LegoSplineParameters& p_splineParameters) { m_splineParameters = p_splineParameters; }
protected:
    LegoTime m_time;
    LegoSplineParameters m_splineParameters;
};

class LegoTranslationKey : public LegoAnimKey {
public:
    LegoTranslationKey();
    LegoResult Read(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ);
    LegoResult Write(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ);
    LegoFloat GetX() { return m_x; }
    void SetX(LegoFloat p_x) { m_x = p_x; }
    LegoFloat GetY() { return m_y; }
    void SetY(LegoFloat p_y) { m_y = p_y; }
    LegoFloat GetZ() { return m_z; }
    void SetZ(LegoFloat p_z) { m_z = p_z; }
protected:
    LegoFloat m_x;
    LegoFloat m_y;
    LegoFloat m_z;
};

class LegoRotationKey : public LegoAnimKey {
public:
    LegoRotationKey();
    LegoResult Read(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ);
    LegoResult Write(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ);
    LegoFloat GetAngle() { return m_angle; }
    void SetAngle(LegoFloat p_angle) { m_angle = p_angle; }
    LegoFloat GetX() { return m_x; }
    void SetX(LegoFloat p_x) { m_x = p_x; }
    LegoFloat GetY() { return m_y; }
    void SetY(LegoFloat p_y) { m_y = p_y; }
    LegoFloat GetZ() { return m_z; }
    void SetZ(LegoFloat p_z) { m_z = p_z; }
protected:
    LegoFloat m_angle;
    LegoFloat m_x;
    LegoFloat m_y;
    LegoFloat m_z;
};

class LegoScaleKey : public LegoAnimKey {
public:
    LegoScaleKey();
    LegoResult Read(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ);
    LegoResult Write(LegoStorage* p_storage, LegoBool p_useX, LegoBool p_useY, LegoBool p_useZ);
    LegoFloat GetX() { return m_x; }
    void SetX(LegoFloat p_x) { m_x = p_x; }
    LegoFloat GetY() { return m_y; }
    void SetY(LegoFloat p_y) { m_y = p_y; }
    LegoFloat GetZ() { return m_z; }
    void SetZ(LegoFloat p_z) { m_z = p_z; }
protected:
    LegoFloat m_x;
    LegoFloat m_y;
    LegoFloat m_z;
};

class LegoMorphKey : public LegoAnimKey {
public:
    LegoMorphKey();
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
    LegoChar* GetName() { return m_name; }
    void SetName(const LegoChar* p_name);
protected:
    LegoChar* m_name;
};

class LegoAnimTrackFlags {
public:
    LegoAnimTrackFlags();
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
    LegoBool GetLoop() { return m_loop; }
    void SetLoop(LegoBool p_loop) { m_loop = p_loop; }
    LegoBool GetLockX() { return m_lockX; }
    void SetLockX(LegoBool p_lockX) { m_lockX = p_lockX; }
    LegoBool GetLockY() { return m_lockY; }
    void SetLockY(LegoBool p_lockY) { m_lockY = p_lockY; }
    LegoBool GetLockZ() { return m_lockZ; }
    void SetLockZ(LegoBool p_lockZ) { m_lockZ = p_lockZ; }
protected:
    LegoBool m_loop : 1;
    LegoBool m_lockX : 1;
    LegoBool m_lockY : 1;
    LegoBool m_lockZ : 1;
};

class LegoAnimNodeData : public LegoTreeNodeData {
public:
    LegoAnimNodeData();
    virtual ~LegoAnimNodeData();
    virtual LegoResult Read(LegoStorage* p_storage);
    virtual LegoResult Write(LegoStorage* p_storage);
    LegoChar* GetName() { return m_name; }
    void SetName(const LegoChar* p_name);
    LegoVertex& GetPivot() { return m_pivot; }
    void SetPivot(LegoVertex& p_pivot) { m_pivot = p_pivot; }
    LegoAnimTrackFlags GetTranslationFlags() { return m_translationFlags; }
    void SetTranslationFlags(LegoAnimTrackFlags p_translationFlags) { m_translationFlags = p_translationFlags; }
    LegoU32 GetNumTranslationKeys() { return m_numTranslationKeys; }
    void SetNumTranslationKeys(LegoU32 p_numTranslationKeys) { m_numTranslationKeys = p_numTranslationKeys; }
    LegoTranslationKey* GetTranslationKeys() { return m_translationKeys; }
    LegoTranslationKey& GetTranslationKey(LegoU32 p_i) { return m_translationKeys[p_i]; }
    void SetTranslationKeys(LegoTranslationKey* p_translationKeys) { m_translationKeys = p_translationKeys; }
    LegoAnimTrackFlags GetRotationFlags() { return m_rotationFlags; }
    void SetRotationFlags(LegoAnimTrackFlags p_rotationFlags) { m_rotationFlags = p_rotationFlags; }
    LegoU32 GetNumRotationKeys() { return m_numRotationKeys; }
    void SetNumRotationKeys(LegoU32 p_numRotationKeys) { m_numRotationKeys = p_numRotationKeys; }
    LegoRotationKey* GetRotationKeys() { return m_rotationKeys; }
    LegoRotationKey& GetRotationKey(LegoU32 p_i) { return m_rotationKeys[p_i]; }
    void SetRotationKeys(LegoRotationKey* p_rotationKeys) { m_rotationKeys = p_rotationKeys; }
    LegoAnimTrackFlags GetScaleFlags() { return m_scaleFlags; }
    void SetScaleFlags(LegoAnimTrackFlags p_scaleFlags) { m_scaleFlags = p_scaleFlags; }
    LegoU32 GetNumScaleKeys() { return m_numScaleKeys; }
    void SetNumScaleKeys(LegoU32 p_numScaleKeys) { m_numScaleKeys = p_numScaleKeys; }
    LegoScaleKey* GetScaleKeys() { return m_scaleKeys; }
    LegoScaleKey& GetScaleKey(LegoU32 p_i) { return m_scaleKeys[p_i]; }
    void SetScaleKeys(LegoScaleKey* p_scaleKeys) { m_scaleKeys = p_scaleKeys; }
    LegoAnimTrackFlags GetMorphFlags() { return m_morphFlags; }
    void SetMorphFlags(LegoAnimTrackFlags p_morphFlags) { m_morphFlags = p_morphFlags; }
    LegoU32 GetNumMorphKeys() { return m_numMorphKeys; }
    void SetNumMorphKeys(LegoU32 p_numMorphKeys) { m_numMorphKeys = p_numMorphKeys; }
    LegoMorphKey* GetMorphKeys() { return m_morphKeys; }
    LegoMorphKey& GetMorphKey(LegoU32 p_i) { return m_morphKeys[p_i]; }
    void SetMorphKeys(LegoMorphKey* p_morphKeys) { m_morphKeys = p_morphKeys; }
    void GetTranslation(LegoTime p_time, LegoFloat& p_x, LegoFloat& p_y, LegoFloat& p_z);
    void GetRotation(LegoTime p_time, LegoFloat& p_angle, LegoFloat& p_x, LegoFloat& p_y, LegoFloat& p_z);
    void GetScale(LegoTime p_time, LegoFloat& p_x, LegoFloat& p_y, LegoFloat& p_z);
#ifdef _DEBUG
    virtual void Dump(FILE* p_file);
#endif
protected:
    LegoU32 FindKeys(LegoTime p_time, LegoU32 p_numKeys, LegoAnimKey* p_keys, LegoU32 p_size, LegoU32& p_index);
    LegoFloat Interpolate(LegoTime p_time, LegoAnimKey& p_key1, LegoFloat p_value1, LegoAnimKey& p_key2, LegoFloat p_value2);
    LegoAnimKey& GetKey(LegoU32 p_i, LegoAnimKey* p_keys, LegoU32 p_size);
    LegoChar* m_name;
    LegoVertex m_pivot;
    LegoAnimTrackFlags m_translationFlags;
    LegoU32 m_numTranslationKeys;
    LegoTranslationKey* m_translationKeys;
    LegoAnimTrackFlags m_rotationFlags;
    LegoU32 m_numRotationKeys;
    LegoRotationKey* m_rotationKeys;
    LegoAnimTrackFlags m_scaleFlags;
    LegoU32 m_numScaleKeys;
    LegoScaleKey* m_scaleKeys;
    LegoAnimTrackFlags m_morphFlags;
    LegoU32 m_numMorphKeys;
    LegoMorphKey* m_morphKeys;
};

class LegoAnim : public LegoTree {
public:
    LegoAnim();
    LegoTime GetDuration() { return m_duration; }
    void SetDuration(LegoTime p_duration) { m_duration = p_duration; }
    void CalculateDuration();
    virtual LegoResult Read(LegoStorage* p_storage);
    virtual LegoResult Write(LegoStorage* p_storage);
protected:
    LegoTime m_duration;
    virtual LegoTreeNodeData* CreateData() { return new LegoAnimNodeData(); }
    void CalculateDuration(LegoTreeNode* p_node);
};

class LegoAnimBuilder : public LegoTreeBuilder {
protected:
    virtual LegoTree* CreateTree() { return new LegoAnim(); }
};

#endif // __LEGOANIM_H

